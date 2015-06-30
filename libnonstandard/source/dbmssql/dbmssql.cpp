//-----------------------------------------------------------------------------
#include "dbmssql.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
#define MSSQL_COLUMNSIZEMAX 4096 // 欄位大小最大值
#define MSSQL_ROWREADCOUNT 100 // 每次讀取數據行數
#define MSSQL_RETRYWAITTIME 10000 // 重連等待時間(毫秒)
#define MSSQL_HEARTBEATTIME 10000 // 保持與伺服器連線的心跳查詢發送時間(毫秒)
//-----------------------------------------------------------------------------
const nstring C_DBMSSQL::m_szType = __T("mssql");
//-----------------------------------------------------------------------------
// 取得MSSQL錯誤
nstring MSSQLError(IN IUnknown *pObject, IN REFIID Interface)
{
	if(pObject == nullptr)
		return __T("");

	C_ICom<ISupportErrorInfo> ccISupportErrorInfo; // 檢查是否支援取得錯誤的介面

	if(FAILED(pObject->QueryInterface(IID_ISupportErrorInfo, (void **)ccISupportErrorInfo.PPointer())))
		return __T("interface failed");

	if(ccISupportErrorInfo == nullptr)
		return __T("interface null");

	if(FAILED(ccISupportErrorInfo.Pointer()->InterfaceSupportsErrorInfo(Interface)))
		return __T("interface not support error info");

	C_ICom<IErrorInfo> ccIErrorInfoAll; // 用來取得錯誤的介面

	// 取得錯誤
	if(FAILED(GetErrorInfo(0, ccIErrorInfoAll.PPointer())))
		return __T("get error failed");

	BSTR bszDescription;
	nstring szError;

	ccIErrorInfoAll.Pointer()->GetDescription(&bszDescription);
	szError = static_cast<nstring>(C_NString(bszDescription));

	SysFreeString(bszDescription);

	return szError;
}
//-----------------------------------------------------------------------------
// 對資料庫連線
bool _Connect(IN C_ICom<ICommandText> &ccCommand, IN const nstring &szDBAddr, IN const nstring &szDBName, IN const nstring &szUserID, IN const nstring &szPassword)
{
	if(ccCommand != nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("already connect"));

	if(szDBAddr.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("dbattr null"));

	if(szDBName.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("dbname null"));

	if(szUserID.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("userid null"));

	C_NString szConnect;

	// 建立連線字串
	{
		szConnect << __T("Provider=SQLNCLI10;");
		szConnect << __T("Data Source=") << szDBAddr << __T(";");
		szConnect << __T("Initial Catalog=") << szDBName << __T(";");
		szConnect << __T("User ID=") << szUserID << __T(";");
		szConnect << __T("Password=") << szPassword << __T(";");
		szConnect << __T("QueryLog_On=Yes;QueryLogFile=mssqllog\\sqlquery.log;");
		szConnect << __T("StatsLog_On=Yes;StatsLogFile=mssqllog\\sqlstats.log;");
		szConnect << __T("Connect Timeout=60000;");
	}

	C_ICom<IDataInitialize> ccIDataInitialize; // 資料來源介面

	// 建立資料來源介面
	{
		HRESULT hr = CoCreateInstance(CLSID_MSDAINITIALIZE, nullptr, CLSCTX_INPROC_SERVER, IID_IDataInitialize, (void **)ccIDataInitialize.PPointer());

		if(FAILED(hr) || ccIDataInitialize == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create IDataInitialize failed"));
	}

	C_ICom<IDBInitialize> ccIDBInitialize; // 資料庫連接介面

	// 建立資料庫連接介面
	{
		HRESULT hr = ccIDataInitialize.Pointer()->GetDataSource(nullptr, CLSCTX_INPROC_SERVER, szConnect.w_str(), IID_IDBInitialize, (IUnknown **)ccIDBInitialize.PPointer());

		if(FAILED(hr) || ccIDBInitialize == nullptr)
		{
			if(hr == 0x80040154) // 沒有安裝正確版本的 SQL Server Native Client 錯誤
				return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccIDataInitialize.Pointer(), IID_IDataInitialize), __T("create IDBInitialize failed, please install SQL Server Native Client (sqlncli.msi)"));
			else
				return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccIDataInitialize.Pointer(), IID_IDataInitialize), __T("create IDBInitialize failed"));
		}//if
	}

	// 連線到資料庫
	{
		HRESULT hr = ccIDBInitialize.Pointer()->Initialize();

		if(FAILED(hr))
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccIDBInitialize.Pointer(), IID_IDBInitialize), __T("connect to database failed"));
	}

	C_ICom<IDBCreateSession> ccIDBCreateSession; // 事務對象介面

	// 取得事務對象介面
	{
		HRESULT hr = ccIDBInitialize.Pointer()->QueryInterface(IID_IDBCreateSession, (void **)ccIDBCreateSession.PPointer());

		if(FAILED(hr) || ccIDBCreateSession == nullptr)
		{
			C_ErrorMSSQL ccError(ccIDBInitialize.Pointer(), IID_IDBInitialize);

			ccIDBInitialize.Pointer()->Uninitialize(); // 對資料庫斷線

			return C_NOutput::Instance().Error(ERRORNSTD, ccError, __T("create IDBCreateSession failed"));
		}//if
	}

	C_ICom<IDBCreateCommand> ccDBCreateCommand; // 建立命令介面

	// 取得建立命令介面
	{
		HRESULT hr = ccIDBCreateSession.Pointer()->CreateSession(nullptr, IID_IDBCreateCommand, (IUnknown **)ccDBCreateCommand.PPointer());

		if(FAILED(hr) || ccDBCreateCommand == nullptr)
		{
			C_ErrorMSSQL ccError(ccIDBCreateSession.Pointer(), IID_IDBCreateSession);

			ccIDBInitialize.Pointer()->Uninitialize(); // 對資料庫斷線

			return C_NOutput::Instance().Error(ERRORNSTD, ccError, __T("create IDBCreateCommand failed"));
		}//if
	}

	// 取得執行命令介面
	{
		HRESULT hr = ccDBCreateCommand.Pointer()->CreateCommand(nullptr, IID_ICommandText, (IUnknown **)ccCommand.PPointer());

		if(FAILED(hr) || ccCommand == nullptr)
		{
			C_ErrorMSSQL ccError(ccDBCreateCommand.Pointer(), IID_IDBCreateCommand);

			ccIDBInitialize.Pointer()->Uninitialize(); // 對資料庫斷線

			return C_NOutput::Instance().Error(ERRORNSTD, ccError, __T("create ICommandText failed"));
		}//if
	}

	return true;
}
//-----------------------------------------------------------------------------
// 對資料庫斷線
bool _Disconnect(IN C_ICom<ICommandText> &ccCommand)
{
	if(ccCommand == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("already disconnect"));

	C_ICom<IGetDataSource> ccIGetDataSource; // 查詢資料來源介面

	// 從執行命令介面取得查詢資料來源介面
	{
		HRESULT hr = ccCommand.Pointer()->GetDBSession(IID_IGetDataSource, (IUnknown **)ccIGetDataSource.PPointer());

		if(FAILED(hr) || ccIGetDataSource == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccCommand.Pointer(), IID_ICommandText), __T("create IGetDataSource failed"));
	}

	C_ICom<IDBInitialize> ccIDBInitialize; // 資料來源介面

	// 從查詢資料來源介面取得資料來源介面
	{
		HRESULT hr = ccIGetDataSource.Pointer()->GetDataSource(IID_IDBInitialize, (IUnknown **)ccIDBInitialize.PPointer());

		if(FAILED(hr) || ccIDBInitialize == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccIGetDataSource.Pointer(), IID_IGetDataSource), __T("create IDBInitialize failed"));
	}

	ccCommand.DelData(); // 釋放執行命令介面
	ccIDBInitialize.Pointer()->Uninitialize(); // 對資料庫斷線

	return true;
}
//-----------------------------------------------------------------------------
// 執行資料庫語法
bool _Execute(IN C_ICom<ICommandText> &ccCommand, IN unsigned long &ulUpdateTime, IN const nstring &szCommand, IN C_DBStore *pDBStore)
{
	if(ccCommand == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("disconnect"));

	if(szCommand.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("command null"));

	if(pDBStore)
		pDBStore->Clear(); // 清除結果物件

	// 設定要執行的SQL語句
	{
		HRESULT hr = ccCommand.Pointer()->SetCommandText(DBGUID_DEFAULT, C_NString(szCommand).w_str());

		if(FAILED(hr))
			return C_NOutput::Instance().Error(ERRORNSTD, __T("set command text failed"));
	}

	C_ICom<IRowset> ccIRowset; // 結果集介面

	// 執行! 取得結果集
	{
		HRESULT hr = ccCommand.Pointer()->Execute(nullptr, IID_IRowset, nullptr, nullptr, (IUnknown **)ccIRowset.PPointer());

		if(FAILED(hr))
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccCommand.Pointer(), IID_ICommandText), szCommand);

		ulUpdateTime = timeGetTime() + MSSQL_HEARTBEATTIME; // 重置心跳查詢時間
	}

	// 如果此次查詢沒有結果就結束
	if(ccIRowset == nullptr)
		return true;

	C_ICom<IColumnsInfo> ccIColumnsInfo; // 欄位訊息介面

	// 取得欄位訊息介面
	{
		HRESULT hr = ccIRowset.Pointer()->QueryInterface(IID_IColumnsInfo, (void **)ccIColumnsInfo.PPointer());

		if(FAILED(hr) || ccIColumnsInfo == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccIRowset.Pointer(), IID_IRowset), __T("get IColumnsInfo failed"));
	}

	C_DBMSSQLBind ccDBBind; // 綁定欄位資料

	// 建立綁定欄位資料
	if(ccDBBind.Create(ccIColumnsInfo) == false)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create column info failed"));

	C_ICom<IAccessor> ccIAccessor; // 訪問器介面

	// 取得訪問器介面
	{
		HRESULT hr = ccIRowset.Pointer()->QueryInterface(IID_IAccessor, (void **)ccIAccessor.PPointer());

		if(FAILED(hr) || ccIAccessor == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccIRowset.Pointer(), IID_IRowset), __T("get IAccessor failed"));
	}

	HACCESSOR hAccessor; // 訪問器HANDLE

	// 建立訪問器HANDLE
	{
		HRESULT hr = ccIAccessor.Pointer()->CreateAccessor(DBACCESSOR_ROWDATA, ccDBBind.GetColumns(), ccDBBind.GetColumnData(), 0, &hAccessor, nullptr);

		if(FAILED(hr))
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccIAccessor.Pointer(), IID_IAccessor), __T("create HACCESSOR failed"));
	}

	// 取得數據資料
	{
		HRESULT hr = S_OK;
		HROW *phRow = nullptr; // 數據行HANDLE列表
		unsigned long ulRowCount = 0; // 總行數計數
		unsigned long ulRowObtained = 0; // 目前取得的數據行數

		while(hr == S_OK)
		{
			// 循序讀取數據
			hr = ccIRowset.Pointer()->GetNextRows(DB_NULL_HCHAPTER, 0, MSSQL_ROWREADCOUNT, &ulRowObtained, &phRow);

			if(hr == S_OK || hr == DB_S_ENDOFROWSET)
			{
				for(unsigned long ulCount = 0; ulCount < ulRowObtained; ulCount++, ulRowCount++)
				{
					char *pData = nstdnew char [ccDBBind.GetRowSize()]; // 建立儲存數據的記憶體

					if(pData == nullptr)
					{
						hr = E_OUTOFMEMORY; // 記憶體不足!
						break;
					}//if

					memset(pData, 0, ccDBBind.GetRowSize());
					ccIRowset.Pointer()->GetData(phRow[ulCount], hAccessor, static_cast<void *>(pData)); // 把讀取出來的數據存入結果數據儲存資料

					for(unsigned long ulColumn = 0; ulColumn < ccDBBind.GetColumns(); ++ulColumn)
					{
						if(pDBStore)
							pDBStore->Add(ulRowCount, ccDBBind.GetColumnName(ulColumn), pData + ccDBBind.GetValueOfs(ulColumn));
					}//for

					delete [] pData; // 釋放儲存數據的記憶體
				}//for

				// 釋放數據
				if(ulRowObtained > 0)
					ccIRowset.Pointer()->ReleaseRows(ulRowObtained, phRow, nullptr, nullptr, nullptr);

				CoTaskMemFree(phRow);
				phRow = nullptr;
			}//if
		}//while

		// 如果結果不是成功或是讀取資料完畢的話, 就輸出錯誤
		if(hr != S_OK && hr != DB_S_ENDOFROWSET)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("read data from IRowset failed"));
	}

	ccIAccessor.Pointer()->ReleaseAccessor(hAccessor, nullptr); // 釋放訪問器HANDLE

	return true;
}
//-----------------------------------------------------------------------------
C_ErrorMSSQL::C_ErrorMSSQL(IN IUnknown *object, IN REFIID refiid) : m_szError(MSSQLError(object, refiid)) {}
//-----------------------------------------------------------------------------
C_ErrorMSSQL::~C_ErrorMSSQL() {}
//-----------------------------------------------------------------------------
C_ErrorMSSQL::operator estring () const
{
	return m_szError;
}
//-----------------------------------------------------------------------------
C_DBMSSQLBind::C_DBMSSQLBind() : m_pBindData(nullptr), m_ulColumns(0), m_ulRowSize(0) {}
//-----------------------------------------------------------------------------
C_DBMSSQLBind::~C_DBMSSQLBind()
{
	if(m_pBindData == nullptr)
		return;

	delete [] m_pBindData;
	m_pBindData = nullptr;
}
//-----------------------------------------------------------------------------
// 建立綁定欄位資料
bool C_DBMSSQLBind::Create(IN C_ICom<IColumnsInfo> &ccIColumnsInfo)
{
	if(ccIColumnsInfo == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("column info null"));

	DBCOLUMNINFO *pColumnData = nullptr; // 欄位訊息指標
	unsigned long ulColumns = 0; // 欄位數量
	LPWSTR pStr = nullptr; // 不明用途字串暫存區

	// 取得欄位訊息
	HRESULT hr = ccIColumnsInfo.Pointer()->GetColumnInfo(&ulColumns, &pColumnData, &pStr);

	if(FAILED(hr) || pColumnData == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccIColumnsInfo.Pointer(), IID_IColumnsInfo), __T("column data failed"));

	if(ulColumns <= 0)
	{
		CoTaskMemFree(pColumnData); // 釋放記憶體
		CoTaskMemFree(pStr); // 釋放記憶體

		return C_NOutput::Instance().Error(ERRORNSTD, __T("column data empty"));
	}//if

	if(m_pBindData)
	{
		delete [] m_pBindData;
		m_pBindData = nullptr;
	}//if

	DBBINDING *pTemp = nstdnew DBBINDING [sizeof(DBBINDING) * ulColumns];

	if(pTemp == nullptr)
	{
		CoTaskMemFree(pColumnData); // 釋放記憶體
		CoTaskMemFree(pStr); // 釋放記憶體

		return C_NOutput::Instance().Error(ERRORNSTD, __T("create bind data failed"));
	}//if

	m_pBindData = pTemp;
	m_ulColumns = ulColumns;

	unsigned long ulColumnSize = 0; // 欄位長度
	unsigned long ulColumnOfs = 0; // 欄位位移值
	unsigned long ulCount = 0;

	// 建立綁定欄位訊息
	for(ulCount = 0; ulCount < m_ulColumns; ++ulCount)
	{
		// 取得欄位大小
		switch(pColumnData[ulCount].wType)
		{
		case DBTYPE_EMPTY:
		case DBTYPE_NULL:
		case DBTYPE_I1: // 有符號字元
		case DBTYPE_I2: // 有符號短整數
		case DBTYPE_I4: // 有符號整數
		case DBTYPE_I8: // 有符號長整數
		case DBTYPE_UI1: // 無符號字元
		case DBTYPE_UI2: // 無符號短整數
		case DBTYPE_UI4: // 無符號整數
		case DBTYPE_UI8: // 無符號長整數
		case DBTYPE_R4: // 單精度浮點數
		case DBTYPE_R8: // 雙精度浮點數
		case DBTYPE_BOOL: // 布林值
		case DBTYPE_CY: // 貨幣值
		case DBTYPE_ERROR: // 32位元錯誤碼
			ulColumnSize = (25 + 1) * sizeof(char);
			break;

		case DBTYPE_DECIMAL: // 有固定精度與小數位數的數值
		case DBTYPE_NUMERIC: // 有固定精度與小數位數的數值
		case DBTYPE_GUID: // 索引值
		case DBTYPE_DATE: // 日期
		case DBTYPE_DBDATE: // 日期
		case DBTYPE_DBTIME: // 時間
		case DBTYPE_DBTIMESTAMP: // 日期/時間戳記
			ulColumnSize = (50 + 1) * sizeof(char);
			break;

		case DBTYPE_BYTES: // 二進位陣列
			ulColumnSize = (pColumnData[ulCount].ulColumnSize * 2 + 1) * sizeof(char);
			break;

		case DBTYPE_BSTR: // UNICODE字串
		case DBTYPE_WSTR: // UNICODE字串
			ulColumnSize = (pColumnData[ulCount].ulColumnSize + 1) * sizeof(WCHAR);
			break;

		case DBTYPE_STR: // 字串
			ulColumnSize = (pColumnData[ulCount].ulColumnSize + 1) * sizeof(char);
			break;

		default:
			ulColumnSize = MSSQL_COLUMNSIZEMAX;
			break;
		}//switch

		ulColumnSize = std::min(ulColumnSize, static_cast<unsigned long>(MSSQL_COLUMNSIZEMAX));

		// 新增欄位名稱
		m_ColumnName.push_back(pColumnData[ulCount].pwszName);
		// 綁定欄位資料
		m_pBindData[ulCount].wType = DBTYPE_STR; // 欄位類型, 在此一律指定為字串類型
		m_pBindData[ulCount].cbMaxLen = ulColumnSize; // 欄位大小
		m_pBindData[ulCount].iOrdinal = pColumnData[ulCount].iOrdinal; // 欄位在結果集中序號
		m_pBindData[ulCount].bPrecision = pColumnData[ulCount].bPrecision; // 精度
		m_pBindData[ulCount].bScale = pColumnData[ulCount].bScale; // 小數位數
		m_pBindData[ulCount].dwPart = DBPART_STATUS | DBPART_LENGTH | DBPART_VALUE; // 要求傳回數據時要給予欄位狀態, 欄位長度, 欄位值
		m_pBindData[ulCount].obStatus = ulColumnOfs; // 擺放數據時的狀態位移值
		m_pBindData[ulCount].obLength = ulColumnOfs + sizeof(DBSTATUS); // 擺放數據時的長度位移值
		m_pBindData[ulCount].obValue = ulColumnOfs + sizeof(DBSTATUS) + sizeof(ULONG); // 擺放數據時的資料位移值
		m_pBindData[ulCount].pTypeInfo = nullptr;
		m_pBindData[ulCount].pObject = nullptr;
		m_pBindData[ulCount].pBindExt = nullptr;
		m_pBindData[ulCount].dwMemOwner = DBMEMOWNER_CLIENTOWNED; // 指定取得的資料記憶體由誰負責管理, 在此指定由我們的元件管理
		m_pBindData[ulCount].eParamIO = DBPARAMIO_NOTPARAM;
		m_pBindData[ulCount].dwFlags = 0;
		// 計算下個欄位的開始位移(欄位值位移 + 欄位大小)
		ulColumnOfs = m_pBindData[ulCount].obValue + m_pBindData[ulCount].cbMaxLen;
		// 位移對齊8
		ulColumnOfs = ROUNDUP(ulColumnOfs, 8);
	}//for

	m_ulRowSize = ulColumnOfs; // 設定一行記錄所需的大小
	CoTaskMemFree(pColumnData); // 釋放記憶體
	CoTaskMemFree(pStr); // 釋放記憶體

	return true;
}
//-----------------------------------------------------------------------------
// 取得綁定欄位列表指標
const DBBINDING *C_DBMSSQLBind::GetColumnData() const
{
	return m_pBindData;
}
//-----------------------------------------------------------------------------
// 取得綁定欄位的名稱
nstring C_DBMSSQLBind::GetColumnName(IN unsigned long ulColumnID) const
{
	return (ulColumnID < m_ColumnName.size()) ? m_ColumnName[ulColumnID].t_str() : nullptr;
}
//-----------------------------------------------------------------------------
// 取得綁定欄位的資料位移值
unsigned long C_DBMSSQLBind::GetValueOfs(IN unsigned long ulColumnID) const
{
	return (ulColumnID < m_ulColumns) ? m_pBindData[ulColumnID].obValue : 0;
}
//-----------------------------------------------------------------------------
// 取得綁定欄位數量
unsigned long C_DBMSSQLBind::GetColumns() const
{
	return m_ulColumns;
}
//-----------------------------------------------------------------------------
// 取得一行記錄所需的大小
unsigned long C_DBMSSQLBind::GetRowSize() const
{
	return m_ulRowSize;
}
//-----------------------------------------------------------------------------
// 對資料庫連線
bool C_DBMSSQL::DBConnect(IN const nstring &szDBAddr, IN const nstring &szDBName, IN const nstring &szUserID, IN const nstring &szPassword, IN bool bReConnect)
{
	if(m_ccCommand != nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("already connect"));

	m_szDBAddr = szDBAddr;
	m_szDBName = szDBName;
	m_szUserID = szUserID;
	m_szPassword = szPassword;
	m_bReconnect = bReConnect;
	m_ulUpdateTime = 0;

	// 第一次連線
	_Connect(m_ccCommand, m_szDBAddr, m_szDBName, m_szUserID, m_szPassword);

	// 如果連線失敗而且有設定重連
	while(m_ccCommand == nullptr && m_bReconnect)
	{
		// 繼續連線
		_Connect(m_ccCommand, m_szDBAddr, m_szDBName, m_szUserID, m_szPassword);
		Sleep(MSSQL_RETRYWAITTIME);
	}//while

	return m_ccCommand != nullptr;
}
//-----------------------------------------------------------------------------
// 對資料庫斷線
bool C_DBMSSQL::DBDisconnect()
{
	_Disconnect(m_ccCommand); // 對資料庫斷線
	m_szDBAddr.clear();
	m_szDBName.clear();
	m_szUserID.clear();
	m_szPassword.clear();
	m_bReconnect = false;
	m_ulUpdateTime = 0;

	return true;
}
//-----------------------------------------------------------------------------
// 定時處理
bool C_DBMSSQL::DBProcess()
{
	unsigned long ulNowTime = timeGetTime();

	if(ulNowTime > m_ulUpdateTime)
		return true;

	m_ulUpdateTime = ulNowTime + MSSQL_HEARTBEATTIME;

	// 檢查是否斷線了
	if(DBIsConnect())
		return true;

	// 如果沒有設定重連就結束
	if(m_bReconnect == false)
		return true;

	_Disconnect(m_ccCommand); // 對資料庫斷線
	_Connect(m_ccCommand, m_szDBAddr, m_szDBName, m_szUserID, m_szPassword); // 重新連線

	return true;
}
//-----------------------------------------------------------------------------
// 與資料庫是否連線中
bool C_DBMSSQL::DBIsConnect()
{
	return _Execute(m_ccCommand, m_ulUpdateTime, __T("select 1"), nullptr);
}
//-----------------------------------------------------------------------------
// 執行命令
bool C_DBMSSQL::DBExecute(IN const nstring &szCommand, OUT C_DBStore *pStore)
{
	return _Execute(m_ccCommand, m_ulUpdateTime, szCommand, pStore);
}
//-----------------------------------------------------------------------------
// 取得資料庫位址
nstring C_DBMSSQL::DBAddr() const
{
	return m_szDBAddr;
}
//-----------------------------------------------------------------------------
// 取得資料庫名稱
nstring C_DBMSSQL::DBName() const
{
	return m_szDBName;
}
//-----------------------------------------------------------------------------
C_DBMSSQL::C_DBMSSQL() : C_DBase(C_DBMSSQL::m_szType), m_bReconnect(false), m_ulUpdateTime(0) {}
//-----------------------------------------------------------------------------
C_DBMSSQL::~C_DBMSSQL()
{
	DBDisconnect();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------