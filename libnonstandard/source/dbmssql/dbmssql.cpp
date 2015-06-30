//-----------------------------------------------------------------------------
#include "dbmssql.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
#define MSSQL_COLUMNSIZEMAX 4096 // ���j�p�̤j��
#define MSSQL_ROWREADCOUNT 100 // �C��Ū���ƾڦ��
#define MSSQL_RETRYWAITTIME 10000 // ���s���ݮɶ�(�@��)
#define MSSQL_HEARTBEATTIME 10000 // �O���P���A���s�u���߸��d�ߵo�e�ɶ�(�@��)
//-----------------------------------------------------------------------------
const nstring C_DBMSSQL::m_szType = __T("mssql");
//-----------------------------------------------------------------------------
// ���oMSSQL���~
nstring MSSQLError(IN IUnknown *pObject, IN REFIID Interface)
{
	if(pObject == nullptr)
		return __T("");

	C_ICom<ISupportErrorInfo> ccISupportErrorInfo; // �ˬd�O�_�䴩���o���~������

	if(FAILED(pObject->QueryInterface(IID_ISupportErrorInfo, (void **)ccISupportErrorInfo.PPointer())))
		return __T("interface failed");

	if(ccISupportErrorInfo == nullptr)
		return __T("interface null");

	if(FAILED(ccISupportErrorInfo.Pointer()->InterfaceSupportsErrorInfo(Interface)))
		return __T("interface not support error info");

	C_ICom<IErrorInfo> ccIErrorInfoAll; // �ΨӨ��o���~������

	// ���o���~
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
// ���Ʈw�s�u
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

	// �إ߳s�u�r��
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

	C_ICom<IDataInitialize> ccIDataInitialize; // ��ƨӷ�����

	// �إ߸�ƨӷ�����
	{
		HRESULT hr = CoCreateInstance(CLSID_MSDAINITIALIZE, nullptr, CLSCTX_INPROC_SERVER, IID_IDataInitialize, (void **)ccIDataInitialize.PPointer());

		if(FAILED(hr) || ccIDataInitialize == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create IDataInitialize failed"));
	}

	C_ICom<IDBInitialize> ccIDBInitialize; // ��Ʈw�s������

	// �إ߸�Ʈw�s������
	{
		HRESULT hr = ccIDataInitialize.Pointer()->GetDataSource(nullptr, CLSCTX_INPROC_SERVER, szConnect.w_str(), IID_IDBInitialize, (IUnknown **)ccIDBInitialize.PPointer());

		if(FAILED(hr) || ccIDBInitialize == nullptr)
		{
			if(hr == 0x80040154) // �S���w�˥��T������ SQL Server Native Client ���~
				return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccIDataInitialize.Pointer(), IID_IDataInitialize), __T("create IDBInitialize failed, please install SQL Server Native Client (sqlncli.msi)"));
			else
				return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccIDataInitialize.Pointer(), IID_IDataInitialize), __T("create IDBInitialize failed"));
		}//if
	}

	// �s�u���Ʈw
	{
		HRESULT hr = ccIDBInitialize.Pointer()->Initialize();

		if(FAILED(hr))
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccIDBInitialize.Pointer(), IID_IDBInitialize), __T("connect to database failed"));
	}

	C_ICom<IDBCreateSession> ccIDBCreateSession; // �ưȹ�H����

	// ���o�ưȹ�H����
	{
		HRESULT hr = ccIDBInitialize.Pointer()->QueryInterface(IID_IDBCreateSession, (void **)ccIDBCreateSession.PPointer());

		if(FAILED(hr) || ccIDBCreateSession == nullptr)
		{
			C_ErrorMSSQL ccError(ccIDBInitialize.Pointer(), IID_IDBInitialize);

			ccIDBInitialize.Pointer()->Uninitialize(); // ���Ʈw�_�u

			return C_NOutput::Instance().Error(ERRORNSTD, ccError, __T("create IDBCreateSession failed"));
		}//if
	}

	C_ICom<IDBCreateCommand> ccDBCreateCommand; // �إߩR�O����

	// ���o�إߩR�O����
	{
		HRESULT hr = ccIDBCreateSession.Pointer()->CreateSession(nullptr, IID_IDBCreateCommand, (IUnknown **)ccDBCreateCommand.PPointer());

		if(FAILED(hr) || ccDBCreateCommand == nullptr)
		{
			C_ErrorMSSQL ccError(ccIDBCreateSession.Pointer(), IID_IDBCreateSession);

			ccIDBInitialize.Pointer()->Uninitialize(); // ���Ʈw�_�u

			return C_NOutput::Instance().Error(ERRORNSTD, ccError, __T("create IDBCreateCommand failed"));
		}//if
	}

	// ���o����R�O����
	{
		HRESULT hr = ccDBCreateCommand.Pointer()->CreateCommand(nullptr, IID_ICommandText, (IUnknown **)ccCommand.PPointer());

		if(FAILED(hr) || ccCommand == nullptr)
		{
			C_ErrorMSSQL ccError(ccDBCreateCommand.Pointer(), IID_IDBCreateCommand);

			ccIDBInitialize.Pointer()->Uninitialize(); // ���Ʈw�_�u

			return C_NOutput::Instance().Error(ERRORNSTD, ccError, __T("create ICommandText failed"));
		}//if
	}

	return true;
}
//-----------------------------------------------------------------------------
// ���Ʈw�_�u
bool _Disconnect(IN C_ICom<ICommandText> &ccCommand)
{
	if(ccCommand == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("already disconnect"));

	C_ICom<IGetDataSource> ccIGetDataSource; // �d�߸�ƨӷ�����

	// �q����R�O�������o�d�߸�ƨӷ�����
	{
		HRESULT hr = ccCommand.Pointer()->GetDBSession(IID_IGetDataSource, (IUnknown **)ccIGetDataSource.PPointer());

		if(FAILED(hr) || ccIGetDataSource == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccCommand.Pointer(), IID_ICommandText), __T("create IGetDataSource failed"));
	}

	C_ICom<IDBInitialize> ccIDBInitialize; // ��ƨӷ�����

	// �q�d�߸�ƨӷ��������o��ƨӷ�����
	{
		HRESULT hr = ccIGetDataSource.Pointer()->GetDataSource(IID_IDBInitialize, (IUnknown **)ccIDBInitialize.PPointer());

		if(FAILED(hr) || ccIDBInitialize == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccIGetDataSource.Pointer(), IID_IGetDataSource), __T("create IDBInitialize failed"));
	}

	ccCommand.DelData(); // �������R�O����
	ccIDBInitialize.Pointer()->Uninitialize(); // ���Ʈw�_�u

	return true;
}
//-----------------------------------------------------------------------------
// �����Ʈw�y�k
bool _Execute(IN C_ICom<ICommandText> &ccCommand, IN unsigned long &ulUpdateTime, IN const nstring &szCommand, IN C_DBStore *pDBStore)
{
	if(ccCommand == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("disconnect"));

	if(szCommand.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("command null"));

	if(pDBStore)
		pDBStore->Clear(); // �M�����G����

	// �]�w�n���檺SQL�y�y
	{
		HRESULT hr = ccCommand.Pointer()->SetCommandText(DBGUID_DEFAULT, C_NString(szCommand).w_str());

		if(FAILED(hr))
			return C_NOutput::Instance().Error(ERRORNSTD, __T("set command text failed"));
	}

	C_ICom<IRowset> ccIRowset; // ���G������

	// ����! ���o���G��
	{
		HRESULT hr = ccCommand.Pointer()->Execute(nullptr, IID_IRowset, nullptr, nullptr, (IUnknown **)ccIRowset.PPointer());

		if(FAILED(hr))
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccCommand.Pointer(), IID_ICommandText), szCommand);

		ulUpdateTime = timeGetTime() + MSSQL_HEARTBEATTIME; // ���m�߸��d�߮ɶ�
	}

	// �p�G�����d�ߨS�����G�N����
	if(ccIRowset == nullptr)
		return true;

	C_ICom<IColumnsInfo> ccIColumnsInfo; // ���T������

	// ���o���T������
	{
		HRESULT hr = ccIRowset.Pointer()->QueryInterface(IID_IColumnsInfo, (void **)ccIColumnsInfo.PPointer());

		if(FAILED(hr) || ccIColumnsInfo == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccIRowset.Pointer(), IID_IRowset), __T("get IColumnsInfo failed"));
	}

	C_DBMSSQLBind ccDBBind; // �j�w�����

	// �إ߸j�w�����
	if(ccDBBind.Create(ccIColumnsInfo) == false)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create column info failed"));

	C_ICom<IAccessor> ccIAccessor; // �X�ݾ�����

	// ���o�X�ݾ�����
	{
		HRESULT hr = ccIRowset.Pointer()->QueryInterface(IID_IAccessor, (void **)ccIAccessor.PPointer());

		if(FAILED(hr) || ccIAccessor == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccIRowset.Pointer(), IID_IRowset), __T("get IAccessor failed"));
	}

	HACCESSOR hAccessor; // �X�ݾ�HANDLE

	// �إ߳X�ݾ�HANDLE
	{
		HRESULT hr = ccIAccessor.Pointer()->CreateAccessor(DBACCESSOR_ROWDATA, ccDBBind.GetColumns(), ccDBBind.GetColumnData(), 0, &hAccessor, nullptr);

		if(FAILED(hr))
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccIAccessor.Pointer(), IID_IAccessor), __T("create HACCESSOR failed"));
	}

	// ���o�ƾڸ��
	{
		HRESULT hr = S_OK;
		HROW *phRow = nullptr; // �ƾڦ�HANDLE�C��
		unsigned long ulRowCount = 0; // �`��ƭp��
		unsigned long ulRowObtained = 0; // �ثe���o���ƾڦ��

		while(hr == S_OK)
		{
			// �`��Ū���ƾ�
			hr = ccIRowset.Pointer()->GetNextRows(DB_NULL_HCHAPTER, 0, MSSQL_ROWREADCOUNT, &ulRowObtained, &phRow);

			if(hr == S_OK || hr == DB_S_ENDOFROWSET)
			{
				for(unsigned long ulCount = 0; ulCount < ulRowObtained; ulCount++, ulRowCount++)
				{
					char *pData = nstdnew char [ccDBBind.GetRowSize()]; // �إ��x�s�ƾڪ��O����

					if(pData == nullptr)
					{
						hr = E_OUTOFMEMORY; // �O���餣��!
						break;
					}//if

					memset(pData, 0, ccDBBind.GetRowSize());
					ccIRowset.Pointer()->GetData(phRow[ulCount], hAccessor, static_cast<void *>(pData)); // ��Ū���X�Ӫ��ƾڦs�J���G�ƾ��x�s���

					for(unsigned long ulColumn = 0; ulColumn < ccDBBind.GetColumns(); ++ulColumn)
					{
						if(pDBStore)
							pDBStore->Add(ulRowCount, ccDBBind.GetColumnName(ulColumn), pData + ccDBBind.GetValueOfs(ulColumn));
					}//for

					delete [] pData; // �����x�s�ƾڪ��O����
				}//for

				// ����ƾ�
				if(ulRowObtained > 0)
					ccIRowset.Pointer()->ReleaseRows(ulRowObtained, phRow, nullptr, nullptr, nullptr);

				CoTaskMemFree(phRow);
				phRow = nullptr;
			}//if
		}//while

		// �p�G���G���O���\�άOŪ����Ƨ�������, �N��X���~
		if(hr != S_OK && hr != DB_S_ENDOFROWSET)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("read data from IRowset failed"));
	}

	ccIAccessor.Pointer()->ReleaseAccessor(hAccessor, nullptr); // ����X�ݾ�HANDLE

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
// �إ߸j�w�����
bool C_DBMSSQLBind::Create(IN C_ICom<IColumnsInfo> &ccIColumnsInfo)
{
	if(ccIColumnsInfo == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("column info null"));

	DBCOLUMNINFO *pColumnData = nullptr; // ���T������
	unsigned long ulColumns = 0; // ���ƶq
	LPWSTR pStr = nullptr; // �����γ~�r��Ȧs��

	// ���o���T��
	HRESULT hr = ccIColumnsInfo.Pointer()->GetColumnInfo(&ulColumns, &pColumnData, &pStr);

	if(FAILED(hr) || pColumnData == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMSSQL(ccIColumnsInfo.Pointer(), IID_IColumnsInfo), __T("column data failed"));

	if(ulColumns <= 0)
	{
		CoTaskMemFree(pColumnData); // ����O����
		CoTaskMemFree(pStr); // ����O����

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
		CoTaskMemFree(pColumnData); // ����O����
		CoTaskMemFree(pStr); // ����O����

		return C_NOutput::Instance().Error(ERRORNSTD, __T("create bind data failed"));
	}//if

	m_pBindData = pTemp;
	m_ulColumns = ulColumns;

	unsigned long ulColumnSize = 0; // ������
	unsigned long ulColumnOfs = 0; // ���첾��
	unsigned long ulCount = 0;

	// �إ߸j�w���T��
	for(ulCount = 0; ulCount < m_ulColumns; ++ulCount)
	{
		// ���o���j�p
		switch(pColumnData[ulCount].wType)
		{
		case DBTYPE_EMPTY:
		case DBTYPE_NULL:
		case DBTYPE_I1: // ���Ÿ��r��
		case DBTYPE_I2: // ���Ÿ��u���
		case DBTYPE_I4: // ���Ÿ����
		case DBTYPE_I8: // ���Ÿ������
		case DBTYPE_UI1: // �L�Ÿ��r��
		case DBTYPE_UI2: // �L�Ÿ��u���
		case DBTYPE_UI4: // �L�Ÿ����
		case DBTYPE_UI8: // �L�Ÿ������
		case DBTYPE_R4: // ���ׯB�I��
		case DBTYPE_R8: // ����ׯB�I��
		case DBTYPE_BOOL: // ���L��
		case DBTYPE_CY: // �f����
		case DBTYPE_ERROR: // 32�줸���~�X
			ulColumnSize = (25 + 1) * sizeof(char);
			break;

		case DBTYPE_DECIMAL: // ���T�w��׻P�p�Ʀ�ƪ��ƭ�
		case DBTYPE_NUMERIC: // ���T�w��׻P�p�Ʀ�ƪ��ƭ�
		case DBTYPE_GUID: // ���ޭ�
		case DBTYPE_DATE: // ���
		case DBTYPE_DBDATE: // ���
		case DBTYPE_DBTIME: // �ɶ�
		case DBTYPE_DBTIMESTAMP: // ���/�ɶ��W�O
			ulColumnSize = (50 + 1) * sizeof(char);
			break;

		case DBTYPE_BYTES: // �G�i��}�C
			ulColumnSize = (pColumnData[ulCount].ulColumnSize * 2 + 1) * sizeof(char);
			break;

		case DBTYPE_BSTR: // UNICODE�r��
		case DBTYPE_WSTR: // UNICODE�r��
			ulColumnSize = (pColumnData[ulCount].ulColumnSize + 1) * sizeof(WCHAR);
			break;

		case DBTYPE_STR: // �r��
			ulColumnSize = (pColumnData[ulCount].ulColumnSize + 1) * sizeof(char);
			break;

		default:
			ulColumnSize = MSSQL_COLUMNSIZEMAX;
			break;
		}//switch

		ulColumnSize = std::min(ulColumnSize, static_cast<unsigned long>(MSSQL_COLUMNSIZEMAX));

		// �s�W���W��
		m_ColumnName.push_back(pColumnData[ulCount].pwszName);
		// �j�w�����
		m_pBindData[ulCount].wType = DBTYPE_STR; // �������, �b���@�߫��w���r������
		m_pBindData[ulCount].cbMaxLen = ulColumnSize; // ���j�p
		m_pBindData[ulCount].iOrdinal = pColumnData[ulCount].iOrdinal; // ���b���G�����Ǹ�
		m_pBindData[ulCount].bPrecision = pColumnData[ulCount].bPrecision; // ���
		m_pBindData[ulCount].bScale = pColumnData[ulCount].bScale; // �p�Ʀ��
		m_pBindData[ulCount].dwPart = DBPART_STATUS | DBPART_LENGTH | DBPART_VALUE; // �n�D�Ǧ^�ƾڮɭn������쪬�A, ������, ����
		m_pBindData[ulCount].obStatus = ulColumnOfs; // �\��ƾڮɪ����A�첾��
		m_pBindData[ulCount].obLength = ulColumnOfs + sizeof(DBSTATUS); // �\��ƾڮɪ����צ첾��
		m_pBindData[ulCount].obValue = ulColumnOfs + sizeof(DBSTATUS) + sizeof(ULONG); // �\��ƾڮɪ���Ʀ첾��
		m_pBindData[ulCount].pTypeInfo = nullptr;
		m_pBindData[ulCount].pObject = nullptr;
		m_pBindData[ulCount].pBindExt = nullptr;
		m_pBindData[ulCount].dwMemOwner = DBMEMOWNER_CLIENTOWNED; // ���w���o����ưO����ѽ֭t�d�޲z, �b�����w�ѧڭ̪�����޲z
		m_pBindData[ulCount].eParamIO = DBPARAMIO_NOTPARAM;
		m_pBindData[ulCount].dwFlags = 0;
		// �p��U����쪺�}�l�첾(���Ȧ첾 + ���j�p)
		ulColumnOfs = m_pBindData[ulCount].obValue + m_pBindData[ulCount].cbMaxLen;
		// �첾���8
		ulColumnOfs = ROUNDUP(ulColumnOfs, 8);
	}//for

	m_ulRowSize = ulColumnOfs; // �]�w�@��O���һݪ��j�p
	CoTaskMemFree(pColumnData); // ����O����
	CoTaskMemFree(pStr); // ����O����

	return true;
}
//-----------------------------------------------------------------------------
// ���o�j�w���C�����
const DBBINDING *C_DBMSSQLBind::GetColumnData() const
{
	return m_pBindData;
}
//-----------------------------------------------------------------------------
// ���o�j�w��쪺�W��
nstring C_DBMSSQLBind::GetColumnName(IN unsigned long ulColumnID) const
{
	return (ulColumnID < m_ColumnName.size()) ? m_ColumnName[ulColumnID].t_str() : nullptr;
}
//-----------------------------------------------------------------------------
// ���o�j�w��쪺��Ʀ첾��
unsigned long C_DBMSSQLBind::GetValueOfs(IN unsigned long ulColumnID) const
{
	return (ulColumnID < m_ulColumns) ? m_pBindData[ulColumnID].obValue : 0;
}
//-----------------------------------------------------------------------------
// ���o�j�w���ƶq
unsigned long C_DBMSSQLBind::GetColumns() const
{
	return m_ulColumns;
}
//-----------------------------------------------------------------------------
// ���o�@��O���һݪ��j�p
unsigned long C_DBMSSQLBind::GetRowSize() const
{
	return m_ulRowSize;
}
//-----------------------------------------------------------------------------
// ���Ʈw�s�u
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

	// �Ĥ@���s�u
	_Connect(m_ccCommand, m_szDBAddr, m_szDBName, m_szUserID, m_szPassword);

	// �p�G�s�u���ѦӥB���]�w���s
	while(m_ccCommand == nullptr && m_bReconnect)
	{
		// �~��s�u
		_Connect(m_ccCommand, m_szDBAddr, m_szDBName, m_szUserID, m_szPassword);
		Sleep(MSSQL_RETRYWAITTIME);
	}//while

	return m_ccCommand != nullptr;
}
//-----------------------------------------------------------------------------
// ���Ʈw�_�u
bool C_DBMSSQL::DBDisconnect()
{
	_Disconnect(m_ccCommand); // ���Ʈw�_�u
	m_szDBAddr.clear();
	m_szDBName.clear();
	m_szUserID.clear();
	m_szPassword.clear();
	m_bReconnect = false;
	m_ulUpdateTime = 0;

	return true;
}
//-----------------------------------------------------------------------------
// �w�ɳB�z
bool C_DBMSSQL::DBProcess()
{
	unsigned long ulNowTime = timeGetTime();

	if(ulNowTime > m_ulUpdateTime)
		return true;

	m_ulUpdateTime = ulNowTime + MSSQL_HEARTBEATTIME;

	// �ˬd�O�_�_�u�F
	if(DBIsConnect())
		return true;

	// �p�G�S���]�w���s�N����
	if(m_bReconnect == false)
		return true;

	_Disconnect(m_ccCommand); // ���Ʈw�_�u
	_Connect(m_ccCommand, m_szDBAddr, m_szDBName, m_szUserID, m_szPassword); // ���s�s�u

	return true;
}
//-----------------------------------------------------------------------------
// �P��Ʈw�O�_�s�u��
bool C_DBMSSQL::DBIsConnect()
{
	return _Execute(m_ccCommand, m_ulUpdateTime, __T("select 1"), nullptr);
}
//-----------------------------------------------------------------------------
// ����R�O
bool C_DBMSSQL::DBExecute(IN const nstring &szCommand, OUT C_DBStore *pStore)
{
	return _Execute(m_ccCommand, m_ulUpdateTime, szCommand, pStore);
}
//-----------------------------------------------------------------------------
// ���o��Ʈw��}
nstring C_DBMSSQL::DBAddr() const
{
	return m_szDBAddr;
}
//-----------------------------------------------------------------------------
// ���o��Ʈw�W��
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