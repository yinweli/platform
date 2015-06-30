//-----------------------------------------------------------------------------
#include "_include.h"
#include "control.h"
//-----------------------------------------------------------------------------
C_Control::C_Control()
{
	m_ccData.SetToken(__T(">"));
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_Control::~C_Control()
{
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// �w�ɳB�z
void C_Control::Process()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	m_ccData.Process();
}
//-----------------------------------------------------------------------------
// �]�w���D�r��
void C_Control::Set(IN const cstring &szTitle)
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	m_ccData.SetTitle(szTitle);
	m_Target.insert(szTitle);
}
//-----------------------------------------------------------------------------
// ���o���O�r��
cstring C_Control::Get()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	return m_ccData.GetCommand();
}
//-----------------------------------------------------------------------------
// �ˬd�O�_���ثe���D�r��
bool C_Control::Chk(IN const cstring &szTitle) const
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	return szTitle == m_ccData.GetTitle();
}
//-----------------------------------------------------------------------------
// ���o�ؼЦC��
std::set<cstring> C_Control::Target() const
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	return m_Target;
}
//-----------------------------------------------------------------------------