//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xlistunit.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_XUnitLock::C_XUnitLock() : m_pUnit(nullptr), m_pLock(nullptr) {}
//-----------------------------------------------------------------------------
C_XUnitLock::C_XUnitLock(IN const C_XUnit *unit) : m_pUnit(const_cast<C_XUnit *>(unit)), m_pLock(const_cast<CRITICAL_SECTION *>(unit ? &unit->m_csCommon : nullptr))
{
	if(m_pLock)
		EnterCriticalSection(m_pLock);
}
//-----------------------------------------------------------------------------
C_XUnitLock::~C_XUnitLock()
{
	UnLock();
}
//-----------------------------------------------------------------------------
C_XUnitLock::operator bool () const
{
	return m_pUnit && m_pLock;
}
//-----------------------------------------------------------------------------
C_XUnit *C_XUnitLock::operator -> ()
{
	return m_pUnit;
}
//-----------------------------------------------------------------------------
// ����ǿ�椸
void C_XUnitLock::UnLock()
{
	if(m_pLock)
	{
		LeaveCriticalSection(m_pLock);
		m_pUnit = nullptr;
		m_pLock = nullptr;
	}//if
}
//-----------------------------------------------------------------------------
C_XUnit::C_XUnit() : m_bRunning(false), m_bRecv(false), m_bSend(false), m_bDisconnect(false)
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_XUnit::~C_XUnit()
{
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// �M������
void C_XUnit::Clear()
{
	m_ListRecv.Clear();
	m_ListSend.Clear();
	m_bRunning = false;
	m_bRecv = false;
	m_bSend = false;
	m_bDisconnect = false;
}
//-----------------------------------------------------------------------------
// �s�W�������
bool C_XUnit::AddRecv(IN const void *pData, IN unsigned long ulSize)
{
	return m_bRunning && m_bDisconnect == false ? m_ListRecv.Add(pData, ulSize) : false;
}
//-----------------------------------------------------------------------------
// ���o�������
C_XRecv C_XUnit::GetRecv()
{
	return m_bRunning ? m_ListRecv.Get() : C_XRecv();
}
//-----------------------------------------------------------------------------
// ���o������ƬO�_����
bool C_XUnit::RecvEmpty() const
{
	return m_ListRecv.Size() == 0;
}
//-----------------------------------------------------------------------------
// �s�W�ǰe���
bool C_XUnit::AddSend(IN const void *pData, IN unsigned long ulSize)
{
	return m_bRunning && m_bDisconnect == false ? m_ListSend.Add(pData, ulSize) : false;
}
//-----------------------------------------------------------------------------
// ���o�ǰe���
C_XSend C_XUnit::GetSend()
{
	return m_bRunning ? m_ListSend.Get() : C_XSend();
}
//-----------------------------------------------------------------------------
// ���o�ǰe��ƬO�_����
bool C_XUnit::SendEmpty() const
{
	return m_ListSend.Size() == 0;
}
//-----------------------------------------------------------------------------
// �]�w�s�u��}
void C_XUnit::Address(IN const sockaddr &sAddress)
{
	memcpy(&m_sAddress, &sAddress, sizeof(m_sAddress));
}
//-----------------------------------------------------------------------------
// ���o�s�u��}
void C_XUnit::Address(OUT nstring &szIP, OUT unsigned long &ulPort) const
{
	szIP = C_NString(inet_ntoa(m_sAddress.sin_addr));
	ulPort = m_sAddress.sin_port;
}
//-----------------------------------------------------------------------------
// �]�w����X��
void C_XUnit::Running(IN bool bEnable)
{
	m_bRunning = bEnable;
}
//-----------------------------------------------------------------------------
// ���o����X��
bool C_XUnit::Running() const
{
	return m_bRunning;
}
//-----------------------------------------------------------------------------
// �]�w�����X��
void C_XUnit::Recv(IN bool bEnable)
{
	m_bRecv = bEnable;
}
//-----------------------------------------------------------------------------
// ���o�����X��
bool C_XUnit::Recv() const
{
	return m_bRecv;
}
//-----------------------------------------------------------------------------
// �]�w�ǰe�X��
void C_XUnit::Send(IN bool bEnable)
{
	m_bSend = bEnable;
}
//-----------------------------------------------------------------------------
// ���o�ǰe�X��
bool C_XUnit::Send() const
{
	return m_bSend;
}
//-----------------------------------------------------------------------------
// �]�w�_�u�X��
void C_XUnit::Disconnect(IN bool bEnable)
{
	m_bDisconnect = bEnable;
}
//-----------------------------------------------------------------------------
// ���o�_�u�X��
bool C_XUnit::Disconnect() const
{
	return m_bDisconnect;
}
//-----------------------------------------------------------------------------
C_XListUnit::C_XListUnit()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_XListUnit::~C_XListUnit()
{
	Clear();
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// �M������
void C_XListUnit::Clear()
{
	C_ThreadLock ccLock(&m_csCommon);

	for(std::map<SOCKET, C_XUnit *>::value_type &Itor : m_Unit)
	{
		if(Itor.second)
		{
			C_XUnitLock ccUnit(Itor.second);

			ccUnit.UnLock();

			delete Itor.second;
		}//if
	}//for

	m_Unit.clear();
}
//-----------------------------------------------------------------------------
// �s�W�ǿ�椸
bool C_XListUnit::Add(IN SOCKET Socket)
{
	if(Socket == INVALID_SOCKET)
		return false;

	C_ThreadLock ccLock(&m_csCommon);

	if(m_Unit.find(Socket) != m_Unit.end())
		return false;

	C_XUnit *pUnit = nstdnew C_XUnit();

	if(pUnit == nullptr)
		return false;

	m_Unit[Socket] = pUnit;

	return true;
}
//-----------------------------------------------------------------------------
// �R���ǿ�椸
void C_XListUnit::Del(IN SOCKET Socket)
{
	C_ThreadLock ccLock(&m_csCommon);

	std::map<SOCKET, C_XUnit *>::iterator Itor = m_Unit.find(Socket);

	if(Itor == m_Unit.end())
		return;

	if(Itor->second == nullptr)
		return;

	C_XUnitLock ccUnit(Itor->second);

	ccUnit.UnLock();
	delete Itor->second;
	m_Unit.erase(Itor);
}
//-----------------------------------------------------------------------------
// �ˬd�ǿ�椸�O�_�s�b
bool C_XListUnit::IsExist(IN SOCKET Socket) const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_Unit.find(Socket) != m_Unit.end();
}
//-----------------------------------------------------------------------------
// ��w�ǿ�椸
C_XUnitLock C_XListUnit::Lock(IN SOCKET Socket) const
{
	C_ThreadLock ccLock(&m_csCommon);

	std::map<SOCKET, C_XUnit *>::const_iterator Itor = m_Unit.find(Socket);

	return Itor != m_Unit.end() ? Itor->second : nullptr;
}
//-----------------------------------------------------------------------------
// ���o�����ǿ�椸�ƶq
unsigned long C_XListUnit::Size() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_Unit.size();
}
//-----------------------------------------------------------------------------
// ���o�ԲӶǿ�椸�ƶq
unsigned long C_XListUnit::Size(IN bool bRunning) const
{
	C_ThreadLock ccLock(&m_csCommon);

	return std::count_if(m_Unit.begin(), m_Unit.end(), [bRunning] (const std::map<SOCKET, C_XUnit *>::value_type &Itor) { return Itor.second && Itor.second->Running() == bRunning; });
}
//-----------------------------------------------------------------------------
// ���o����SocketID�C��
std::set<SOCKET> C_XListUnit::SocketList() const
{
	std::set<SOCKET> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Unit.begin(), m_Unit.end(), [&Result] (const std::map<SOCKET, C_XUnit *>::value_type &Itor) { Result.insert(Itor.first); });

	return Result;
}
//-----------------------------------------------------------------------------
// ���o�B�zSocketID�C��
std::set<SOCKET> C_XListUnit::SocketProcess() const
{
	std::set<SOCKET> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Unit.begin(), m_Unit.end(), [&Result] (const std::map<SOCKET, C_XUnit *>::value_type &Itor) { if(Itor.second && Itor.second->Running()) Result.insert(Itor.first); });

	return Result;
}
//-----------------------------------------------------------------------------
// ���o�_�uSocketID�C��
std::set<SOCKET> C_XListUnit::SocketDisconnect() const
{
	std::set<SOCKET> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Unit.begin(), m_Unit.end(), [&Result] (const std::map<SOCKET, C_XUnit *>::value_type &Itor) { if(Itor.second && Itor.second->Disconnect() && Itor.second->RecvEmpty() && Itor.second->SendEmpty()) Result.insert(Itor.first); });

	return Result;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------