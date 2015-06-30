//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xlistrecv.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_XRecv::C_XRecv() : m_pData(nullptr), m_ulSize(0), m_ulRecv(0) {}
//-----------------------------------------------------------------------------
C_XRecv::~C_XRecv() {}
//-----------------------------------------------------------------------------
C_XRecv::operator C_XComplete () const
{
	return C_XComplete(m_pData, m_ulSize);
}
//-----------------------------------------------------------------------------
// ��l��
bool C_XRecv::Initialize(IN unsigned long ulSize)
{
	if(ulSize <= 0)
		return false;

	if(m_pData != nullptr)
		return false;

	m_pData = reinterpret_cast<void *>(nstdnew char [ulSize]);

	if(m_pData == nullptr)
		return false;

	m_ulSize = ulSize;
	m_ulRecv = 0;

	return true;
}
//-----------------------------------------------------------------------------
// ����
void C_XRecv::Release()
{
	delete [] m_pData;
	m_pData = nullptr;
	m_ulSize = 0;
	m_ulRecv = 0;
}
//-----------------------------------------------------------------------------
// �s�W���
void C_XRecv::Add(IN C_XPoint &ccPoint)
{
	// �p�G���о��w�쵲��, �N�����F
	if(ccPoint.IsOver())
		return;

	// �p�G��ƫ��ЬO�Ū�, �N�����F
	if(m_pData == nullptr)
		return;

	// �p�G������Ƥw��, �N�����F
	if(m_ulSize <= m_ulRecv)
		return;

	// �p��n�ƻs�i�h������
	unsigned long ulCopy = std::min(m_ulSize - m_ulRecv, ccPoint.Less());

	// �ƻs���
	memcpy(reinterpret_cast<char *>(m_pData) + m_ulRecv, ccPoint.Offset(ulCopy), ulCopy);

	// �W�[��������
	m_ulRecv += ulCopy;
}
//-----------------------------------------------------------------------------
// �ˬd�O�_����
bool C_XRecv::Empty() const
{
	return m_pData == nullptr || m_ulSize <= 0;
}
//-----------------------------------------------------------------------------
// �ˬd�O�_����
bool C_XRecv::IsComplete() const
{
	return m_ulSize <= m_ulRecv;
}
//-----------------------------------------------------------------------------
C_XListRecv::C_XListRecv() {}
//-----------------------------------------------------------------------------
C_XListRecv::~C_XListRecv()
{
	Clear();
}
//-----------------------------------------------------------------------------
// �M������
void C_XListRecv::Clear()
{
	std::for_each(m_Recv.begin(), m_Recv.end(), [] (std::deque<C_XRecv>::value_type &Itor) { Itor.Release(); });
	m_Recv.clear();
}
//-----------------------------------------------------------------------------
// �s�W���
bool C_XListRecv::Add(IN const void *pData, IN unsigned long ulSize)
{
	if(pData == nullptr)
		return false;

	if(ulSize <= 0)
		return false;

	// �إ߫��о�����
	C_XPoint ccPoint(pData, ulSize);

	// �}�l�`���s�W���
	// �p�G�����C���ũάO�̫�@�ӱ�������w��, �N��ܭn�إߤ@�ӷs����������, �n�s�W����ƶ}�Y�N���ӬO�s���������󪺸�ƪ���
	// �p�G�����C�����ũάO�̫�@�ӱ������󥼺�, �N��ܭn�ƻs��ƨ챵������
	while(ccPoint.IsOver() == false)
	{
		if(m_Recv.empty() || m_Recv.back().IsComplete())
		{
			C_XRecv ccRecv;

			// ��l�Ʊ�������
			if(ccRecv.Initialize(*(reinterpret_cast<const x_head *>(ccPoint.Offset(sizeof(x_head))))) == false)
				return false;

			m_Recv.push_back(ccRecv);
		}//if

		m_Recv.back().Add(ccPoint);
	}//while

	return true;
}
//-----------------------------------------------------------------------------
// ���o������ƪ���
C_XRecv C_XListRecv::Get()
{
	// �p�G�S��������ƴN����
	if(m_Recv.empty())
		return C_XRecv();

	// �p�G�̫e����������Ʃ|�������N����
	if(m_Recv.front().IsComplete() == false)
		return C_XRecv();

	C_XRecv ccRecv = m_Recv.front();

	m_Recv.pop_front();

	return ccRecv;
}
//-----------------------------------------------------------------------------
// ���o������Ƽƶq
unsigned long C_XListRecv::Size() const
{
	return m_Recv.size();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------