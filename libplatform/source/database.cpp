//-----------------------------------------------------------------------------
#include "_include.h"
#include "database.h"
//-----------------------------------------------------------------------------
S_RecordDatabase::S_RecordDatabase() {}
//-----------------------------------------------------------------------------
S_RecordDatabase::S_RecordDatabase(IN C_DBase &dbase) : szType(dbase.Type()), szDBAddr(dbase.Addr()), szDBName(dbase.Name()) {}
//-----------------------------------------------------------------------------
C_Database::C_Database()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_Database::~C_Database()
{
	Clear();
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 清除全部
void C_Database::Clear()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Data.begin(), m_Data.end(), [] (std::map<cstring, C_DBase *>::value_type &Itor) { if(Itor.second) delete Itor.second; });
	m_Data.clear();
}
//-----------------------------------------------------------------------------
// 定時處理
void C_Database::Process()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Data.begin(), m_Data.end(), [] (std::map<cstring, C_DBase *>::value_type &Itor) { if(Itor.second) Itor.second->Process(); });
}
//-----------------------------------------------------------------------------
// 新增資料庫
bool C_Database::Add(IN const cstring &szName, IN const cstring szType, IN const cstring &szDBAddr, IN const cstring &szDBName, IN const cstring &szUserID, IN const cstring &szPassword)
{
	_G_();

	if(szName.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("not exist"));

	C_ThreadLock ccLock(&m_csCommon);

	if(m_Data.find(szName) != m_Data.end())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + szName + __T(")"));

	C_DBase *pDBase = nullptr;

	if(szType == C_DBMSSQL::m_szType)
		pDBase = nstdnew C_DBMSSQL();

	if(szType == C_DBMySQL::m_szType)
		pDBase = nstdnew C_DBMySQL();

	if(szType == C_DBSQLite::m_szType)
		pDBase = nstdnew C_DBSQLite();

	if(pDBase == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create database failed(") + szName + __T(")"));

	if(pDBase->Connect(szDBAddr, szDBName, szUserID, szPassword, true) == false)
	{
		delete pDBase;

		return C_NOutput::Instance().Error(ERRORNSTD, __T("connect to database failed(") + szName + __T(")"));
	}//if

	m_Data[szName] = pDBase;

	return true;
}
//-----------------------------------------------------------------------------
// 取得資料庫指標
C_DBase *C_Database::Get(IN const cstring &szName)
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);
	std::map<cstring, C_DBase *>::iterator Itor = m_Data.find(szName);

	return Itor != m_Data.end() ? Itor->second : nullptr;
}
//-----------------------------------------------------------------------------
// 取得紀錄列表
std::map<cstring, S_RecordDatabase> C_Database::Record() const
{
	_G_();

	std::map<cstring, S_RecordDatabase> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Data.begin(), m_Data.end(), [&Result] (const std::map<cstring, C_DBase *>::value_type &Itor) { Result[Itor.first] = Itor.second ? S_RecordDatabase(*Itor.second) : S_RecordDatabase(); });

	return Result;
}
//-----------------------------------------------------------------------------