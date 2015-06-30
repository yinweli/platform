//-----------------------------------------------------------------------------
#include "dbsqlite.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// ANSI�PUNICODE��������������
#ifndef UNICODE
#define SQLITE_ERRMSG(db) sqlite3_errmsg(db)
#define SQLITE_OPEN(name, db) sqlite3_open(name, db)
#define SQLITE_CLOSE(db) sqlite3_close(db)
#define SQLITE_EXEC(db, sql, byte, stmt, tail) sqlite3_prepare_v2(db, sql, byte, stmt, tail)
#define SQLITE_STEP(stmt) sqlite3_step(stmt)
#define SQLITE_FINALIZE(stmt) sqlite3_finalize(stmt)
#define SQLITE_COLCOUNT(stmt) sqlite3_column_count(stmt)
#define SQLITE_COLNAME(stmt, n) sqlite3_column_name(stmt, n)
#define SQLITE_COLTEXT(stmt, n) sqlite3_column_text(stmt, n)
#else
#define SQLITE_ERRMSG(db) reinterpret_cast<const wchar_t *>(sqlite3_errmsg16(db))
#define SQLITE_OPEN(name, db) sqlite3_open16(reinterpret_cast<const void *>(name), db)
#define SQLITE_CLOSE(db) sqlite3_close(db)
#define SQLITE_EXEC(db, sql, byte, stmt, tail) sqlite3_prepare16_v2(db, sql, byte, stmt, tail)
#define SQLITE_STEP(stmt) sqlite3_step(stmt)
#define SQLITE_FINALIZE(stmt) sqlite3_finalize(stmt)
#define SQLITE_COLCOUNT(stmt) sqlite3_column_count(stmt)
#define SQLITE_COLNAME(stmt, n) reinterpret_cast<const wchar_t *>(sqlite3_column_name16(stmt, n))
#define SQLITE_COLTEXT(stmt, n) reinterpret_cast<const wchar_t *>(sqlite3_column_text16(stmt, n))
#endif
//-----------------------------------------------------------------------------
const nstring C_DBSQLite::m_szType = __T("sqlite");
//-----------------------------------------------------------------------------
C_ErrorSQLite::C_ErrorSQLite(IN sqlite3 *sqlite) : m_szError(sqlite ? nstring(SQLITE_ERRMSG(sqlite)) : __T("")) {}
//-----------------------------------------------------------------------------
C_ErrorSQLite::~C_ErrorSQLite() {}
//-----------------------------------------------------------------------------
C_ErrorSQLite::operator estring () const
{
	return m_szError;
}
//-----------------------------------------------------------------------------
// ���Ʈw�s�u
bool C_DBSQLite::DBConnect(IN const nstring &szDBAddr, IN const nstring &szDBName, IN const nstring &szUserID, IN const nstring &szPassword, IN bool bReConnect)
{
	if(m_pDBObj != nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("already open"));

	m_szDBAddr = szDBAddr;
	m_szDBName = szDBName;

	nstring szName = m_szDBAddr + __T("(") + m_szDBName + __T(")");

	// �}�Ҹ�Ʈw, �p�G�S�����w��Ʈw�W��, �N�ϥΰO�����Ʈw
	if(SQLITE_OPEN(szName.empty() ? __T(":memory:") : szName.c_str(), &m_pDBObj) != SQLITE_OK)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorSQLite(m_pDBObj), __T("open failed"));

	return true;
}
//-----------------------------------------------------------------------------
// ���Ʈw�_�u
bool C_DBSQLite::DBDisconnect()
{
	if(m_pDBObj == nullptr)
		return true;

	// ������Ʈw
	if(SQLITE_CLOSE(m_pDBObj) != SQLITE_OK)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorSQLite(m_pDBObj), __T("close failed"));

	m_pDBObj = nullptr;

	return true;
}
//-----------------------------------------------------------------------------
// �w�ɳB�z
bool C_DBSQLite::DBProcess()
{
	return true;
}
//-----------------------------------------------------------------------------
// �P��Ʈw�O�_�s�u��
bool C_DBSQLite::DBIsConnect()
{
	return m_pDBObj != nullptr;
}
//-----------------------------------------------------------------------------
// ����R�O
bool C_DBSQLite::DBExecute(IN const nstring &szCommand, OUT C_DBStore *pStore)
{
	if(m_pDBObj == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("disconnect"));

	if(szCommand.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("command null"));

	if(pStore)
		pStore->Clear(); // �M�����G����

	sqlite3_stmt *pStmt = nullptr; // �n���檺SQL�y�y���
	const void *pCmdPos = reinterpret_cast<const void *>(szCommand.c_str()); // �ثe�R�O�r������}
	const void *pCmdEnd = reinterpret_cast<const char *>(pCmdPos)+nsbytes(szCommand); // �����R�O�r������}

	while(pCmdPos < pCmdEnd)
	{
		// ���R�y�y
		{
			if(SQLITE_EXEC(m_pDBObj, pCmdPos, -1, &pStmt, &pCmdPos) != SQLITE_OK)
				return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorSQLite(m_pDBObj), szCommand);
		}

		// ����y�y, ���o���浲�G
		{
			unsigned long ulLine = 0; // �渹
			int iResult; // ����Ǧ^��
			const TCHAR *szColName, *szColText;

			while((iResult = SQLITE_STEP(pStmt)) == SQLITE_ROW)
			{
				for(int i = 0, iMax = SQLITE_COLCOUNT(pStmt); i < iMax; ++i)
				{
					szColName = SQLITE_COLNAME(pStmt, i);
					szColText = SQLITE_COLTEXT(pStmt, i);

					if(pStore)
						pStore->Add(ulLine, szColName ? szColName : __T(""), szColText ? szColText : __T(""));
				}//for

				++ulLine;
			}//while

			if(iResult != SQLITE_DONE)
				return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorSQLite(m_pDBObj), szCommand);
		}

		// �����d��
		if(SQLITE_FINALIZE(pStmt) != SQLITE_OK)
			return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorSQLite(m_pDBObj), szCommand);
	}//while

	return true;
}
//-----------------------------------------------------------------------------
// ���o��Ʈw��}
nstring C_DBSQLite::DBAddr() const
{
	return m_szDBAddr;
}
//-----------------------------------------------------------------------------
// ���o��Ʈw�W��
nstring C_DBSQLite::DBName() const
{
	return m_szDBName;
}
//-----------------------------------------------------------------------------
C_DBSQLite::C_DBSQLite() : C_DBase(C_DBSQLite::m_szType), m_pDBObj(nullptr) {}
//-----------------------------------------------------------------------------
C_DBSQLite::~C_DBSQLite()
{
	DBDisconnect();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------