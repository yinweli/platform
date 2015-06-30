//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xlistsend.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_XSend::C_XSend() : m_pData(nullptr), m_ulSize(0) {}
//-----------------------------------------------------------------------------
C_XSend::~C_XSend() {}
//-----------------------------------------------------------------------------
C_XSend::operator WSABUF () const
{
	WSABUF sWSABuf;

	sWSABuf.buf = reinterpret_cast<char *>(m_pData);
	sWSABuf.len = m_ulSize;

	return sWSABuf;
}
//-----------------------------------------------------------------------------
// ��l��
bool C_XSend::Initialize(IN const void *pData, IN unsigned long ulSize)
{
	if(pData == nullptr)
		return false;

	if(ulSize <= 0)
		return false;

	if(ulSize >= XSOCKET_PACKETSIZE)
		return false;

	if(m_pData != nullptr)
		return false;

	unsigned long ulTemp = ulSize + sizeof(x_head);
	char *pTemp = nstdnew char [ulTemp];

	if(pTemp == nullptr)
		return false;

	memset(pTemp, 0, ulTemp); // �M�ŰO����
	memcpy(pTemp, reinterpret_cast<const void *>(&ulSize), sizeof(x_head)); // �[�J���Y
	memcpy(pTemp + sizeof(x_head), pData, ulSize); // �ƻs���

	m_pData = pTemp;
	m_ulSize = ulTemp;

	return true;
}
//-----------------------------------------------------------------------------
// ����
void C_XSend::Release()
{
	delete [] m_pData;
	m_pData = nullptr;
	m_ulSize = 0;
}
//-----------------------------------------------------------------------------
// �ˬd�O�_����
bool C_XSend::Empty() const
{
	return m_pData == nullptr || m_ulSize <= 0;
}
//-----------------------------------------------------------------------------
C_XListSend::C_XListSend() {}
//-----------------------------------------------------------------------------
C_XListSend::~C_XListSend()
{
	Clear();
}
//-----------------------------------------------------------------------------
// �M������
void C_XListSend::Clear()
{
	std::for_each(m_Send.begin(), m_Send.end(), [] (std::deque<C_XSend>::value_type &Itor) { Itor.Release(); });
	m_Send.clear();
}
//-----------------------------------------------------------------------------
// �s�W�ǰe���
bool C_XListSend::Add(IN const void *pData, IN unsigned long ulSize)
{
	if(pData == nullptr)
		return false;

	if(ulSize <= 0)
		return false;

	C_XSend ccSend;

	// ��l�ƶǰe����
	if(ccSend.Initialize(pData, ulSize) == false)
		return false;

	m_Send.push_back(ccSend);

	return true;
}
//-----------------------------------------------------------------------------
// ���o�ǰe��ƪ���
C_XSend C_XListSend::Get()
{
	// �p�G�S��������ƴN����
	if(m_Send.empty())
		return C_XSend();

	C_XSend ccSend = m_Send.front();

	m_Send.pop_front();

	return ccSend;
}
//-----------------------------------------------------------------------------
// ���o�ǰe��Ƽƶq
unsigned long C_XListSend::Size() const
{
	return m_Send.size();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------