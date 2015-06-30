//-----------------------------------------------------------------------------
#include "dbmysql.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
#define MYSQL_RETRYWAITTIME 10000 // ���s���ݮɶ�(�@��)
#define MYSQL_HEARTBEATTIME 10000 // �O���P���A���s�u���߸��d�ߵo�e�ɶ�(�@��)
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
// ���Ʈw�s�u
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
// ���Ʈw�_�u
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
// �w�ɳB�z
bool C_DBMySQL::DBProcess()
{
	unsigned long ulNowTime = timeGetTime();

	if(ulNowTime > m_ulUpdateTime)
		return true;

	m_ulUpdateTime = ulNowTime + MYSQL_HEARTBEATTIME;
	DBIsConnect(); // �ˬd�O�_�_�u�F

	return true;
}
//-----------------------------------------------------------------------------
// �P��Ʈw�O�_�s�u��
bool C_DBMySQL::DBIsConnect()
{
	return m_pMySQL ? mysql_ping(m_pMySQL) == 0 : false;
}
//-----------------------------------------------------------------------------
// ����R�O
bool C_DBMySQL::DBExecute(IN const nstring &szCommand, OUT C_DBStore *pStore)
{
	if(m_pMySQL == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("disconnect"));

	if(szCommand.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("command null"));

	if(pStore)
		pStore->Clear(); // �M�����G����

	// ����y�y
	{
		std::string szSQLCommand = C_NString(szCommand);

		if(mysql_real_query(m_pMySQL, szSQLCommand.c_str(), szSQLCommand.size()) != 0)
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMySQL(m_pMySQL), szCommand);

		m_ulUpdateTime = timeGetTime() + MYSQL_HEARTBEATTIME; // ���m�߸��d�߮ɶ�
	}

	// �p�G�����d�ߨS�����G�N����
	if(mysql_field_count(m_pMySQL) <= 0)
		return true;

	// �p�G�S�����G������дN����
	if(pStore == nullptr)
		return true;

	// ���o���G���
	{
		// ���o���G��
		MYSQL_RES *pResult = mysql_store_result(m_pMySQL);

		if(pResult == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMySQL(m_pMySQL), __T("get result failed"));

		// ���o���W�٦C��
		MYSQL_FIELD *pColumn = mysql_fetch_fields(pResult);

		if(pColumn == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorMySQL(m_pMySQL), __T("get field failed"));

		// �إ����W�٦C��
		std::vector<nstring> ColumnName;

		for(unsigned long ulCount = 0, ulMax = mysql_num_fields(pResult); ulCount < ulMax; ++ulCount)
			ColumnName.push_back(C_NString(pColumn[ulCount].name).t_str());

		MYSQL_ROW RowData = nullptr;
		unsigned long ulLine = 0;
		unsigned long ulColumn = 0;
		unsigned long ulColumnMax = ColumnName.size();

		// ���o���
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
// ���o��Ʈw��}
nstring C_DBMySQL::DBAddr() const
{
	return m_szDBAddr;
}
//-----------------------------------------------------------------------------
// ���o��Ʈw�W��
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