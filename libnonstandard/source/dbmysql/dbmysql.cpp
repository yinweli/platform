//-----------------------------------------------------------------------------
#include "dbmysql.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
#define MYSQL_RETRYWAITTIME 10000 // 重連等待時間(毫秒)
#define MYSQL_HEARTBEATTIME 10000 // 保持與伺服器連線的心跳查詢發送時間(毫秒)
//-----------------------------------------------------------------------------
const nstring C_DBMySQL::m_szType = __T("mysql");
//-----------------------------------------------------------------------------
C_ErrorMySQL::C_ErrorMySQL(IN MYSQL *mysql) : m_szError(mysql ? static_cast<nstring>(C_NString(mysql_error(mysql))) : __T("")) {}
//-----------------------------------------------------------------------------
C_ErrorMySQL::~C_ErrorMySQL() {}
//-----------------------------------------------------------------------------
C_ErrorMySQL::operator estring () const
{
	return m_szError;
}
//-----------------------------------------------------------------------------
// 對資料庫連線
bool C_DBMySQL::DBConnect(IN const nstring &szDBAddr, IN const nstring &szDBName, IN const nstring &szUserID, IN const nstring &szPassword, IN bool bReConnect)
{
	if(m_pMySQL != nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("already connect"));

	m_szDBAddr = szDBAddr;
	m_szDBName = szDBName;
	m_szUserID = szUserID;
	m_szPassword = szPassword;
	m_bReconnect = bReConnect;
	m_ulUpdateTime = 0;

	if(m_szDBAddr.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("dbattr null"));

	if(m_szDBName.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("dbname null"));

	if(m_szUserID.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("userid null"));

	if(m_pMySQL == nullptr)
	{
		m_pMySQL = mysql_init(nullptr);

		if(m_pMySQL == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("mysql init failed"));
	}
	else
	{
		if(mysql_ping(m_pMySQL) == 0)
			return true;
	}//if

	if(mysql_real_connect(m_pMySQL, C_NString(m_szDBAddr).c_str(), C_NString(m_szUserID).c_str(), C_NString(m_szPassword).c_str(), C_NString(m_szDBName).c_str(), 0, nullptr, 0) == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMySQL(m_pMySQL), __T("connect failed"));

	if(mysql_options(m_pMySQL, MYSQL_OPT_RECONNECT, static_cast<const void *>(&m_bReconnect)) != 0)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMySQL(m_pMySQL), __T("set reconnect failed"));

	return true;
}
//-----------------------------------------------------------------------------
// 對資料庫斷線
bool C_DBMySQL::DBDisconnect()
{
	if(m_pMySQL)
	{
		mysql_close(m_pMySQL);
		m_pMySQL = nullptr;
	}//if

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
bool C_DBMySQL::DBProcess()
{
	unsigned long ulNowTime = timeGetTime();

	if(ulNowTime > m_ulUpdateTime)
		return true;

	m_ulUpdateTime = ulNowTime + MYSQL_HEARTBEATTIME;
	DBIsConnect(); // 檢查是否斷線了

	return true;
}
//-----------------------------------------------------------------------------
// 與資料庫是否連線中
bool C_DBMySQL::DBIsConnect()
{
	return m_pMySQL ? mysql_ping(m_pMySQL) == 0 : false;
}
//-----------------------------------------------------------------------------
// 執行命令
bool C_DBMySQL::DBExecute(IN const nstring &szCommand, OUT C_DBStore *pStore)
{
	if(m_pMySQL == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("disconnect"));

	if(szCommand.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("command null"));

	if(pStore)
		pStore->Clear(); // 清除結果物件

	// 執行語句
	{
		std::string szSQLCommand = C_NString(szCommand);

		if(mysql_real_query(m_pMySQL, szSQLCommand.c_str(), szSQLCommand.size()) != 0)
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMySQL(m_pMySQL), szCommand);

		m_ulUpdateTime = timeGetTime() + MYSQL_HEARTBEATTIME; // 重置心跳查詢時間
	}

	// 如果此次查詢沒有結果就結束
	if(mysql_field_count(m_pMySQL) <= 0)
		return true;

	// 如果沒有結果物件指標就結束
	if(pStore == nullptr)
		return true;

	// 取得結果資料
	{
		// 取得結果集
		MYSQL_RES *pResult = mysql_store_result(m_pMySQL);

		if(pResult == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMySQL(m_pMySQL), __T("get result failed"));

		// 取得欄位名稱列表
		MYSQL_FIELD *pColumn = mysql_fetch_fields(pResult);

		if(pColumn == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMySQL(m_pMySQL), __T("get field failed"));

		// 建立欄位名稱列表
		std::vector<nstring> ColumnName;

		for(unsigned long ulCount = 0, ulMax = mysql_num_fields(pResult); ulCount < ulMax; ++ulCount)
			ColumnName.push_back(C_NString(pColumn[ulCount].name).t_str());

		MYSQL_ROW RowData = nullptr;
		unsigned long ulLine = 0;
		unsigned long ulColumn = 0;
		unsigned long ulColumnMax = ColumnName.size();

		// 取得資料
		while((RowData = mysql_fetch_row(pResult)) != nullptr)
		{
			for(ulColumn = 0; ulColumn < ulColumnMax; ++ulColumn)
				pStore->Add(ulLine, ColumnName[ulColumn], RowData[ulColumn] ? RowData[ulColumn] : "");

			++ulLine;
		}//while

		mysql_free_result(pResult);
	}

	return true;
}
//-----------------------------------------------------------------------------
// 取得資料庫位址
nstring C_DBMySQL::DBAddr() const
{
	return m_szDBAddr;
}
//-----------------------------------------------------------------------------
// 取得資料庫名稱
nstring C_DBMySQL::DBName() const
{
	return m_szDBName;
}
//-----------------------------------------------------------------------------
C_DBMySQL::C_DBMySQL() : C_DBase(C_DBMySQL::m_szType), m_pMySQL(nullptr), m_bReconnect(false) {}
//-----------------------------------------------------------------------------
C_DBMySQL::~C_DBMySQL()
{
	DBDisconnect();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------