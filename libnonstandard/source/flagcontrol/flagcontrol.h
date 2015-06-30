/**
 * @file flagcontrol.h
 * @note �X�б������O
 * @author yinweli
 */
/**
 * @page �p��ϥ�flagcontrol
 * flagcontrol�Ω�H�줸�����ާ@�O����\n\n
 * �����إߤ@�ӹ���ϥ� C_FlagCtrl �ŧi�p�U\n\n
 * C_FlagCtrl ccFlag;\n\n
 * �M��ǳƤ@���O����ӵ��X�б���ϥ�\n\n
 * char cFlag[1024]; // �b���ϥΤFchar�}�C, ����ڤW�u�n��������, ���򫬺A���i�H\n\n
 * ���۩I�s C_FlagCtrl.Initialize() �禡��l�ƺX�б������O\n\n
 * ccFlag.Initialize((void *)cFlag, 1024 * 8); // �]��1byte = 8bit, �ҥH�i����X���`�Ƭ� 1024 * 8\n\n
 * ������N�i�H�I�s�X�оާ@�禡�ӹ惡�O���鰵�X�б���F\n\n
 * --------------------------------------------------\n
 * Header           : flagcontrol.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref flagcontrol
 */
/** @defgroup flagcontrol */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _FLAGCONTROL
#define _FLAGCONTROL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\bittool\bittool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
class C_FlagCtrlRef;
//-----------------------------------------------------------------------------
/**
 * @brief �X�б������O
 * @note �o�����O�����ä��t�x�s�X�Ъ��O����, ���u�O��ϥΪ̷Q�n���Ӱ��X�Ъ��O������и�X�мƶq�O���U��, �M�ᴣ�Ѥ@�t�C�禡�ӹ惡���Ы��V���O���鰵�X�оާ@\n
 *       ���O�����ާ@�禡�Ψ쪺�X�мƶq/�X�Ц�m, ��쳣�Obit\n
 *       �Ҧp �X�мƶq = 8, �N�O8bit, �]�N�O1Byte\n\n
 * @ingroup flagcontrol
 */
class C_FlagCtrl
{
private:
	//-------------------------------------
	void *m_pData; ///< �X�а}�C����
	unsigned long m_ulSize; ///< �X�мƶq
	//-------------------------------------

public:
	//-------------------------------------
	C_FlagCtrl(IN void *pData = nullptr, IN unsigned long ulSize = 0);
	virtual ~C_FlagCtrl();
	//-------------------------------------
	/**
	 * @brief ��l��
	 * @param pData �Ω�X�б���O�������, �p�G��nullptr, �N�|�Ϧ����O���ާ@�禡�S���ĪG(���O���|�y���{�����~)
	 * @param ulSize �X�мƶq, �p�G�W�L�F�O���饻������ڤj�p, �i��|�y���~�g, ���Obit
	 */
	void Initialize(IN void *pData, IN unsigned long ulSize);
	/**
	 * @brief �]�w�X��
	 * @param ulPos �X�Ц�m, ���Obit
	 * @param b ��
	 * @return true��ܳ]�w���\, false�h�_
	 */
	bool Flag(IN unsigned long ulPos, IN bool b);
	/**
	 * @brief �N�Ҧ��X�ФϦV
	 * @return true��ܳ]�w���\, false�h�_
	 */
	bool Flip();
	/**
	 * @brief �N���w�X�ФϦV
	 * @param ulPos �X�Ц�m, ���Obit
	 * @return true��ܳ]�w���\, false�h�_
	 */
	bool Flip(IN unsigned long ulPos);
	/**
	 * @brief �N�Ҧ��X�г]��true
	 * @return true��ܳ]�w���\, false�h�_
	 */
	bool Set();
	/**
	 * @brief �N���w�X�г]��true
	 * @param ulPos �X�Ц�m, ���Obit
	 * @return true��ܳ]�w���\, false�h�_
	 */
	bool Set(IN unsigned long ulPos);
	/**
	 * @brief �N�Ҧ��X�г]��false
	 * @return true��ܳ]�w���\, false�h�_
	 */
	bool Reset();
	/**
	 * @brief �N���w�X�г]��false
	 * @param ulPos �X�Ц�m, ���Obit
	 * @return true��ܳ]�w���\, false�h�_
	 */
	bool Reset(IN unsigned long ulPos);
	/**
	 * @brief ���o���w�X�Э�
	 * @param ulPos �X�Ц�m, ���Obit
	 * @return �X�Э�
	 */
	bool Test(IN unsigned long ulPos) const;
	/**
	 * @brief �ˬd�Ҧ��X�Ф��O�_���]��true��
	 * @return true��ܺX�Ф���true���X��, false�h�_
	 */
	bool Any() const;
	/**
	 * @brief �ˬd�Ҧ��X�Ф��O�_���]��false��
	 * @return true��ܺX�Ф���false���X��, false�h�_
	 */
	bool Anyf() const;
	/**
	 * @brief �ˬd�Ҧ��X�Ф��O�_����false
	 * @return true��ܺX�Х���false, false�h�_
	 */
	bool None() const;
	/**
	 * @brief �N�ƭȼg�J�X��
	 * @param ulPos �X�Ц�m, ���Obit
	 * @param ulSize �ϥΪ��X�мƶq
	 * @param iValue �ƭ�
	 * @return true��ܼg�J���\, false�h�_
	 */
	bool SetValue(IN unsigned long ulPos, IN unsigned long ulSize, IN int iValue);
	/**
	 * @brief �q�X��Ū���ƭ�
	 * @param ulPos �X�Ц�m, ���Obit
	 * @param ulSize �ϥΪ��X�мƶq
	 * @return �ƭ�
	 */
	int GetValue(IN unsigned long ulPos, IN unsigned long ulSize) const;
	/**
	 * @brief ���o�]��true���X�мƶq
	 * @return �]��true���X�мƶq
	 */
	unsigned long Count() const;
	/**
	 * @brief ���o�X�мƶq
	 * @return �X�мƶq
	 */
	unsigned long Size() const;
	// [] �B��l
	bool operator [] (IN unsigned long ulPos) const;
	// [] �B��l
	C_FlagCtrlRef operator [] (IN unsigned long ulPos);
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �X�г]�m���O
 * @note �o�O�Ω� C_FlagCtrl �� [] �B��l ���Ǧ^�����O, �ϥΪ̤��|�ݭn�ŧi�����O
 * @ingroup flagcontrol
 */
class C_FlagCtrlRef
{
private:
	//-------------------------------------
	C_FlagCtrl *pFlag; ///< �X�б������O
	unsigned long ulPos; ///< �X�Ц�m
	//-------------------------------------

public:
	//-------------------------------------
	C_FlagCtrlRef(IN C_FlagCtrl *p = nullptr, IN unsigned long s = 0);
	virtual ~C_FlagCtrlRef();
	//-------------------------------------
	/**
	 * @brief �N�X�ФϦV
	 * @return true��ܳ]�w���\, false�h�_
	 */
	bool Flip();
	/**
	 * @brief �N�X�г]��true
	 * @return true��ܳ]�w���\, false�h�_
	 */
	bool Set();
	/**
	 * @brief �N�X�г]��false
	 * @return true��ܳ]�w���\, false�h�_
	 */
	bool Reset();
	/**
	 * @brief ���o�X�Э�
	 * @return �X�Э�
	 */
	bool Test() const;
	// =  �B��l
	C_FlagCtrlRef &operator = (IN bool b);
	// =  �B��l
	C_FlagCtrlRef &operator = (IN const C_FlagCtrlRef &r);
	// bool�૬�B��l
	operator bool () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------