//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xlistnotice.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_XComplete::C_XComplete() : m_pData(nullptr), m_ulSize(0) {};
//-----------------------------------------------------------------------------
C_XComplete::C_XComplete(IN const void *data, IN unsigned long size) : m_pData(data), m_ulSize(size) {}
//-----------------------------------------------------------------------------
C_XComplete::~C_XComplete() {}
//-----------------------------------------------------------------------------
// ����
void C_XComplete::Release()
{
	delete [] m_pData;
	m_pData = nullptr;
	m_ulSize = 0;
}
//-----------------------------------------------------------------------------
// ���o��ƫ���
const void *C_XComplete::Data() const
{
	return m_pData;
}
//-----------------------------------------------------------------------------
// ���o��ƪ���
unsigned long C_XComplete::Size() const
{
	return m_ulSize;
}
//-----------------------------------------------------------------------------
// �ˬd�O�_����
bool C_XComplete::Empty() const
{
	return m_pData == nullptr;
}
//-----------------------------------------------------------------------------
C_XNotice::C_XNotice() : m_ulTime(0), m_emType(ENUM_XNotice_NULL), m_Socket(INVALID_SOCKET) {}
//-----------------------------------------------------------------------------
C_XNotice::C_XNotice(IN ENUM_XNotice type, IN SOCKET s) : m_ulTime(timeGetTime()), m_emType(type), m_Socket(s) {}
//-----------------------------------------------------------------------------
C_XNotice::C_XNotice(IN ENUM_XNotice type, IN SOCKET s, IN const C_XComplete &complete) : m_ulTime(timeGetTime()), m_emType(type), m_Socket(s), m_ccComplete(complete) {}
//-----------------------------------------------------------------------------
C_XNotice::~C_XNotice() {}
//-----------------------------------------------------------------------------
// ���o���ͮɶ�
unsigned long C_XNotice::Time() const
{
	return m_ulTime;
}
//-----------------------------------------------------------------------------
// ���o�q���C�|
ENUM_XNotice C_XNotice::Type() const
{
	return m_emType;
}
//-----------------------------------------------------------------------------
// ���oSocketID
SOCKET C_XNotice::Socket() const
{
	return m_Socket;
}
//-----------------------------------------------------------------------------
// ���o������ƪ���
C_XComplete C_XNotice::Complete() const
{
	return m_ccComplete;
}
//-----------------------------------------------------------------------------
// �ˬd�O�_����
bool C_XNotice::Empty() const
{
	return m_emType == ENUM_XNotice_NULL;
}
//-----------------------------------------------------------------------------
C_XListNotice::C_XListNotice()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_XListNotice::~C_XListNotice()
{
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// �M������
void C_XListNotice::Clear()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Notice.clear();
}
//-----------------------------------------------------------------------------
// �s�W�s�u�����q��
void C_XListNotice::AddConnect(IN SOCKET Socket)
{
	if(Socket == INVALID_SOCKET)
		return;

	C_ThreadLock ccLock(&m_csCommon);

	m_Notice.push_back(C_XNotice(ENUM_XNotice_Connect, Socket));
}
//-----------------------------------------------------------------------------
// �s�W�_�u�����q��
void C_XListNotice::AddDisconnect(IN SOCKET Socket)
{
	if(Socket == INVALID_SOCKET)
		return;

	C_ThreadLock ccLock(&m_csCommon);

	m_Notice.push_back(C_XNotice(ENUM_XNotice_Disconnect, Socket));
}
//-----------------------------------------------------------------------------
// �s�W������Ƴq��
void C_XListNotice::AddReceive(IN SOCKET Socket, IN const C_XComplete &ccComplete)
{
	if(Socket == INVALID_SOCKET)
		return;

	if(ccComplete.Empty())
		return;

	C_ThreadLock ccLock(&m_csCommon);

	m_Notice.push_back(C_XNotice(ENUM_XNotice_Receive, Socket, ccComplete));
}
//-----------------------------------------------------------------------------
// ���o�q������C��
std::vector<C_XNotice> C_XListNotice::List(IN unsigned long ulMax)
{
	std::vector<C_XNotice> Result;
	C_ThreadLock ccLock(&m_csCommon);

	while(m_Notice.empty() == false && Result.size() < ulMax)
	{
		Result.push_back(m_Notice.front());
		m_Notice.pop_front();
	}//while

	return Result;
}
//-----------------------------------------------------------------------------
// ���o�q���ƶq
unsigned long C_XListNotice::Size() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_Notice.size();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------