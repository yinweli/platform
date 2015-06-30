/**
 * @file control.h
 * @note ����ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef __CONTROL
#define __CONTROL
//-----------------------------------------------------------------------------
/**
 * @brief �������O
 */
class C_Control
{
private:
	//-------------------------------------
	C_Console m_ccData; ///< ����x����
	std::set<cstring> m_Target; ///< �ؼЦC��
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_Control();
	virtual ~C_Control();
	//-------------------------------------
	/**
	 * @brief �w�ɳB�z
	 */
	void Process();
	/**
	 * @brief �]�w���D�r��
	 * @param szTitle ��Ʀr��
	 */
	void Set(IN const cstring &szTitle);
	/**
	 * @brief ���o���O�r��
	 * @return ���O�r��
	 */
	cstring Get();
	/**
	 * @brief �ˬd�O�_���ثe���D�r��
	 * @param szTitle ��Ʀr��
	 * @return true��ܬO, false�h�_
	 */
	bool Chk(IN const cstring &szTitle) const;
	/**
	 * @brief ���o�ؼЦC��
	 * @return �ؼЦC��
	 */
	std::set<cstring> Target() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------