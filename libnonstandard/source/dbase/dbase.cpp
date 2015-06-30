//-----------------------------------------------------------------------------
#include "dbase.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
C_DBase::C_DBase(IN const nstring &type) : m_szType(type)
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_DBase::~C_DBase()
{
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 對資料庫連線
bool C_DBase::Connect(IN const nstring &szDBAddr, IN const nstring &szDBName, IN const nstring &szUserID, IN const nstring &szPassword, IN bool bReConnect)
{
	C_ThreadLock ccLock(&m_csCommon);

	return DBConnect(szDBAddr, szDBName, szUserID, szPassword, bReConnect);
}
//-----------------------------------------------------------------------------
// 對資料庫斷線
void C_DBase::Disconnect()
{
	C_ThreadLock ccLock(&m_csCommon);

	DBDisconnect();
}
//-----------------------------------------------------------------------------
// 定時處理
void C_DBase::Process()
{
	C_ThreadLock ccLock(&m_csCommon);

	DBProcess();
}
//-----------------------------------------------------------------------------
// 與資料庫是否連線中
bool C_DBase::IsConnect()
{
	C_ThreadLock ccLock(&m_csCommon);

	return DBIsConnect();
}
//-----------------------------------------------------------------------------
// 執行命令
bool C_DBase::Execute(IN const nstring &szCommand)
{
	C_ThreadLock ccLock(&m_csCommon);

	return DBExecute(szCommand);
}
//-----------------------------------------------------------------------------
// 執行命令
bool C_DBase::Execute(IN const nstring &szCommand, OUT C_DBStore &ccStore)
{
	C_ThreadLock ccLock(&m_csCommon);

	return DBExecute(szCommand, &ccStore);
}
//-----------------------------------------------------------------------------
// 取得資料庫位址
nstring C_DBase::Addr() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return DBAddr();
}
//-----------------------------------------------------------------------------
// 取得資料庫名稱
nstring C_DBase::Name() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return DBName();
}
//-----------------------------------------------------------------------------
// 取得資料庫型態字串
nstring C_DBase::Type() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_szType;
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------