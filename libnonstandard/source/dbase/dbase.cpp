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
// ���Ʈw�s�u
bool C_DBase::Connect(IN const nstring &szDBAddr, IN const nstring &szDBName, IN const nstring &szUserID, IN const nstring &szPassword, IN bool bReConnect)
{
	C_ThreadLock ccLock(&m_csCommon);

	return DBConnect(szDBAddr, szDBName, szUserID, szPassword, bReConnect);
}
//-----------------------------------------------------------------------------
// ���Ʈw�_�u
void C_DBase::Disconnect()
{
	C_ThreadLock ccLock(&m_csCommon);

	DBDisconnect();
}
//-----------------------------------------------------------------------------
// �w�ɳB�z
void C_DBase::Process()
{
	C_ThreadLock ccLock(&m_csCommon);

	DBProcess();
}
//-----------------------------------------------------------------------------
// �P��Ʈw�O�_�s�u��
bool C_DBase::IsConnect()
{
	C_ThreadLock ccLock(&m_csCommon);

	return DBIsConnect();
}
//-----------------------------------------------------------------------------
// ����R�O
bool C_DBase::Execute(IN const nstring &szCommand)
{
	C_ThreadLock ccLock(&m_csCommon);

	return DBExecute(szCommand);
}
//-----------------------------------------------------------------------------
// ����R�O
bool C_DBase::Execute(IN const nstring &szCommand, OUT C_DBStore &ccStore)
{
	C_ThreadLock ccLock(&m_csCommon);

	return DBExecute(szCommand, &ccStore);
}
//-----------------------------------------------------------------------------
// ���o��Ʈw��}
nstring C_DBase::Addr() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return DBAddr();
}
//-----------------------------------------------------------------------------
// ���o��Ʈw�W��
nstring C_DBase::Name() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return DBName();
}
//-----------------------------------------------------------------------------
// ���o��Ʈw���A�r��
nstring C_DBase::Type() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_szType;
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------