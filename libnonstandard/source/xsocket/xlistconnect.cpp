//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xlistconnect.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
S_XConnect::S_XConnect() : Socket(INVALID_SOCKET) {}
//-----------------------------------------------------------------------------
S_XConnect::S_XConnect(IN const C_IPData &ipdata) : ccIPData(ipdata), Socket(INVALID_SOCKET) {}
//-----------------------------------------------------------------------------
C_XListConnect::C_XListConnect()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_XListConnect::~C_XListConnect()
{
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// �M������
void C_XListConnect::Clear()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Connect.clear();
}
//-----------------------------------------------------------------------------
// �s�W�s�u
void C_XListConnect::Add(IN const C_IPData &ccIPData)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Connect.push_back(S_XConnect(ccIPData));
}
//-----------------------------------------------------------------------------
// �]�w�s�u
void C_XListConnect::Set(IN const C_IPData &ccIPData, IN SOCKET Socket)
{
	C_ThreadLock ccLock(&m_csCommon);

	std::vector<S_XConnect>::iterator Itor = std::find_if(m_Connect.begin(), m_Connect.end(), [ccIPData] (const std::vector<S_XConnect>::value_type &Itor) { return Itor.ccIPData == ccIPData && Itor.Socket == INVALID_SOCKET; });

	if(Itor != m_Connect.end())
		Itor->Socket = Socket;
}
//-----------------------------------------------------------------------------
// �]�w�s�u
void C_XListConnect::Set(IN SOCKET SocketOld, IN SOCKET SocketNew)
{
	C_ThreadLock ccLock(&m_csCommon);

	std::vector<S_XConnect>::iterator Itor = std::find_if(m_Connect.begin(), m_Connect.end(), [SocketOld] (const std::vector<S_XConnect>::value_type &Itor) { return Itor.Socket == SocketOld; });

	if(Itor != m_Connect.end())
		Itor->Socket = SocketNew;
}
//-----------------------------------------------------------------------------
// �R���s�u
void C_XListConnect::Del(IN SOCKET Socket)
{
	if(Socket == INVALID_SOCKET)
		return;

	C_ThreadLock ccLock(&m_csCommon);

	m_Connect.erase(std::remove_if(m_Connect.begin(), m_Connect.end(), [Socket] (const std::vector<S_XConnect>::value_type &Itor) { return Itor.Socket == Socket; }), m_Connect.end());
}
//-----------------------------------------------------------------------------
// ���o��}����
C_IPData C_XListConnect::IPData(IN SOCKET Socket) const
{
	C_ThreadLock ccLock(&m_csCommon);
	std::vector<S_XConnect>::const_iterator Itor = std::find_if(m_Connect.begin(), m_Connect.end(), [Socket] (const std::vector<S_XConnect>::value_type &Itor) { return Itor.Socket == Socket; });

	return Itor != m_Connect.end() ? Itor->ccIPData : C_IPData();
}
//-----------------------------------------------------------------------------
// ���o�s�u�ƶq
unsigned long C_XListConnect::Size() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_Connect.size();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------