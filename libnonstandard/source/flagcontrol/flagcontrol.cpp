//-----------------------------------------------------------------------------
#include "flagcontrol.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_FlagCtrl::C_FlagCtrl(IN void *pData, IN unsigned long ulSize) : m_pData(pData), m_ulSize(ulSize) {}
//-----------------------------------------------------------------------------
C_FlagCtrl::~C_FlagCtrl() {}
//-----------------------------------------------------------------------------
// ��l��
void C_FlagCtrl::Initialize(IN void *pData, IN unsigned long ulSize)
{
	m_pData = pData;
	m_ulSize = ulSize;
}
//-----------------------------------------------------------------------------
// �]�w�X��
bool C_FlagCtrl::Flag(IN unsigned long ulPos, IN bool b)
{
	if(m_pData == nullptr)
		return false;

	if(ulPos >= m_ulSize)
		return false;

	unsigned long uiPage = ulPos / 8;
	unsigned long uiBits = ulPos % 8;
	char *pData = (char *)m_pData + uiPage;

	*pData = bitval(*pData, static_cast<unsigned char>(uiBits), b);
	return true;
}
//-----------------------------------------------------------------------------
// �N�Ҧ��X�ФϦV
bool C_FlagCtrl::Flip()
{
	if(m_pData == nullptr)
		return false;

	unsigned long uiPage = m_ulSize / 8;
	unsigned long uiBits = m_ulSize % 8;
	char *pData = (char *)m_pData;

	for(unsigned long i = 0; i < uiPage; ++i, ++pData)
		*pData = ~(*pData);

	*pData = bitnot(*pData, static_cast<unsigned char>(uiBits));
	return true;
}
//-----------------------------------------------------------------------------
// �N���w�X�ФϦV
bool C_FlagCtrl::Flip(IN unsigned long ulPos)
{
	if(m_pData == nullptr)
		return false;

	if(ulPos >= m_ulSize)
		return false;

	unsigned long uiPage = ulPos / 8;
	unsigned long uiBits = ulPos % 8;
	char *pData = (char *)m_pData + uiPage;

	*pData = bitval(*pData, static_cast<unsigned char>(uiBits));
	return true;
}
//-----------------------------------------------------------------------------
// �N�Ҧ��X�г]��true
bool C_FlagCtrl::Set()
{
	if(m_pData == nullptr)
		return false;

	unsigned long uiPage = m_ulSize / 8;
	unsigned long uiBits = m_ulSize % 8;
	char *pData = (char *)m_pData;

	for(unsigned long i = 0; i < uiPage; ++i, ++pData)
		memset(pData, 0xff, sizeof(char));

	*pData = bitfil(*pData, static_cast<unsigned char>(uiBits), true);
	return true;
}
//-----------------------------------------------------------------------------
// �N���w�X�г]��true
bool C_FlagCtrl::Set(IN unsigned long ulPos)
{
	if(m_pData == nullptr)
		return false;

	if(ulPos >= m_ulSize)
		return false;

	unsigned long uiPage = ulPos / 8;
	unsigned long uiBits = ulPos % 8;
	char *pData = (char *)m_pData + uiPage;

	*pData = bitval(*pData, static_cast<unsigned char>(uiBits), true);
	return true;
}
//-----------------------------------------------------------------------------
// �N�Ҧ��X�г]��false
bool C_FlagCtrl::Reset()
{
	if(m_pData == nullptr)
		return false;

	unsigned long uiPage = m_ulSize / 8;
	unsigned long uiBits = m_ulSize % 8;
	char *pData = (char *)m_pData;

	for(unsigned long i = 0; i < uiPage; ++i, ++pData)
		*pData = 0;

	*pData = bitfil(*pData, static_cast<unsigned char>(uiBits), false);
	return true;
}
//-----------------------------------------------------------------------------
// �N���w�X�г]��false
bool C_FlagCtrl::Reset(IN unsigned long ulPos)
{
	if(m_pData == nullptr)
		return false;

	if(ulPos >= m_ulSize)
		return false;

	unsigned long uiPage = ulPos / 8;
	unsigned long uiBits = ulPos % 8;
	char *pData = (char *)m_pData + uiPage;

	*pData = bitval(*pData, static_cast<unsigned char>(uiBits), false);
	return true;
}
//-----------------------------------------------------------------------------
// ���o���w�X�Э�
bool C_FlagCtrl::Test(IN unsigned long ulPos) const
{
	if(m_pData == nullptr)
		return false;

	if(ulPos >= m_ulSize)
		return false;

	unsigned long uiPage = ulPos / 8;
	unsigned long uiBits = ulPos % 8;
	char *pData = (char *)m_pData + uiPage;

	return bitget(*pData, static_cast<unsigned char>(uiBits));
}
//-----------------------------------------------------------------------------
// �ˬd�Ҧ��X�Ф��O�_���]��true��
bool C_FlagCtrl::Any() const
{
	if(m_pData == nullptr)
		return false;

	unsigned long uiPage = m_ulSize / 8;
	unsigned long uiBits = m_ulSize % 8;
	char *pData = (char *)m_pData;

	for(unsigned long i = 0; i < uiPage; ++i, ++pData)
	{
		if(*pData)
			return true;
	}//for

	return bitany(*pData, static_cast<unsigned char>(uiBits));
}
//-----------------------------------------------------------------------------
// �ˬd�Ҧ��X�Ф��O�_���]��false��
bool C_FlagCtrl::Anyf() const
{
	if(m_pData == nullptr)
		return false;

	unsigned long uiPage = m_ulSize / 8;
	unsigned long uiBits = m_ulSize % 8;
	char *pData = (char *)m_pData;

	for(unsigned long i = 0; i < uiPage; ++i, ++pData)
	{
		if(~(*pData))
			return true;
	}//for

	return bitanf(*pData, static_cast<unsigned char>(uiBits));
}
//-----------------------------------------------------------------------------
// �ˬd�Ҧ��X�Ф��O�_����false
bool C_FlagCtrl::None() const
{
	return (m_pData) ? !Any() : false;
}
//-----------------------------------------------------------------------------
// �N�ȼg�J�X��
bool C_FlagCtrl::SetValue(IN unsigned long ulPos, IN unsigned long ulSize, IN int iValue)
{
	if(m_pData == nullptr)
		return false;

	if(ulPos >= m_ulSize)
		return false;

	if(ulPos + ulSize >= m_ulSize)
		return false;

	if(bitsize(iValue) > ulSize)
		return false;

	for(int i = ulSize - 1; i >= 0; i--, iValue /= 2)
	{
		if(iValue % 2)
			Set(i + ulPos);
		else 
			Reset(i + ulPos);
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// �q�X��Ū����
int C_FlagCtrl::GetValue(IN unsigned long ulPos, IN unsigned long ulSize) const
{
	if(m_pData == nullptr)
		return 0;

	if(ulPos >= m_ulSize)
		return 0;

	if(ulPos + ulSize >= m_ulSize)
		return 0;

	int iValue = 0;

	for(unsigned long i = 0; i < ulSize; ++i)
	{
		iValue <<= 1;

		if(Test(i + ulPos))
			iValue |= 1;
	}//for

	return iValue;
}
//-----------------------------------------------------------------------------
// ���o�]��true���X�мƶq
unsigned long C_FlagCtrl::Count() const
{
	if(m_pData == nullptr)
		return 0;

	unsigned long uiCount = 0;
	unsigned long uiPage = m_ulSize / 8;
	unsigned long uiBits = m_ulSize % 8;
	char *pData = (char *)m_pData;

	for(unsigned long i = 0; i < uiPage; ++i, ++pData)
		uiCount += bittcount(*pData, 8);

	uiCount += bittcount(*pData, static_cast<unsigned char>(uiBits));

	return uiCount;
}
//-----------------------------------------------------------------------------
// ���o�X�мƶq
unsigned long C_FlagCtrl::Size() const
{
	return m_ulSize;
}
//-----------------------------------------------------------------------------
// [] �B��l
bool C_FlagCtrl::operator [] (IN unsigned long ulPos) const
{
	return Test(ulPos);
}
//-----------------------------------------------------------------------------
// [] �B��l
C_FlagCtrlRef C_FlagCtrl::operator [] (IN unsigned long ulPos)
{
	return C_FlagCtrlRef(this, ulPos);
}
//-----------------------------------------------------------------------------
C_FlagCtrlRef::C_FlagCtrlRef(IN C_FlagCtrl *p, IN unsigned long s) : pFlag(p), ulPos(s) {}
//-----------------------------------------------------------------------------
C_FlagCtrlRef::~C_FlagCtrlRef() {}
//-----------------------------------------------------------------------------
// �N�X�ФϦV
bool C_FlagCtrlRef::Flip()
{
	return (pFlag) ? pFlag->Flip(ulPos) : false;
}
//-----------------------------------------------------------------------------
// �N�X�г]��true
bool C_FlagCtrlRef::Set()
{
	return (pFlag) ? pFlag->Set(ulPos) : false;
}
//-----------------------------------------------------------------------------
// �N�X�г]��false
bool C_FlagCtrlRef::Reset()
{
	return (pFlag) ? pFlag->Reset(ulPos) : false;
}
//-----------------------------------------------------------------------------
// ���o�X�Э�
bool C_FlagCtrlRef::Test() const
{
	return (pFlag) ? pFlag->Test(ulPos) : false;
}
//-----------------------------------------------------------------------------
// =  �B��l
C_FlagCtrlRef &C_FlagCtrlRef::operator = (IN bool b)
{
	if(pFlag)
		pFlag->Flag(ulPos, b);

	return *this;
}
//-----------------------------------------------------------------------------
// =  �B��l
C_FlagCtrlRef &C_FlagCtrlRef::operator = (IN const C_FlagCtrlRef &r)
{
	if(pFlag)
		pFlag->Flag(ulPos, r.Test());

	return *this;
}
//-----------------------------------------------------------------------------
// bool�૬�B��l
C_FlagCtrlRef::operator bool () const
{
	return (pFlag) ? pFlag->Test(ulPos) : false;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------