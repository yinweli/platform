/**
 * @file progress.h
 * @note �i�׭p�����O
 * @author yinweli
 */
/**
 * @page �p��ϥ�progress
 * progress�Ω�i�׭p��, �ǵ۶}�l��, ������, �{�b�Ȫ��p��, �̫���o�i�צʤ���\n\n
 * �����إߤ@�ӹ���ϥ� C_Progress �ŧi�p�U\n\n
 * C_Progress ccProg;\n\n
 * ���۩I�s C_Progress.SetValue() �禡�]�w�i�ת��}�l�ȻP������\n
 * �b��������i�H�I�s C_Progress.SetNow(), C_Progress.AddNow(), C_Progress.SubNow() �禡�ӳ]�w�{�b��\n
 * �I�s C_Progress.GetProgressValue() �i�H���o�ثe���ʤ���i�׭�\n
 * �b����ɭY C_Progress.SetNow(), C_Progress.AddNow(), C_Progress.SubNow() �Q�I�s, �h�|�@�_�I�s C_Progress.Process() �禡\n
 * �ϥΪ̥i�H�h�����禡�ӹ�@�ۤv����s�禡\n\n
 * --------------------------------------------------\n
 * Header           : progress.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref progress
 */
/** @defgroup progress */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _PROGRESS
#define _PROGRESS
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �i�׭p�����O
 * @ingroup progress
 */
class C_Progress
{
protected:
	//-------------------------------------
	int m_iStart; ///< �}�l��
	int m_iEnd; ///< ������
	int m_iNow; ///< �{�b��
	//-------------------------------------

public:
	//-------------------------------------
	C_Progress();
	C_Progress(IN int iStart, IN int iEnd, IN int iNow);
	virtual ~C_Progress();
	//-------------------------------------
	/**
	 * @brief �����M��
	 */
	void Clear();
	/**
	 * @brief �]�w�}�l��, ������
	 * @param iStart �}�l��
	 * @param iEnd ������
	 */
	void SetValue(IN int iStart, IN int iEnd);
	/**
	 * @brief �]�w�{�b��
	 * @param iNow �{�b��
	 */
	void SetNow(IN int iNow);

	/**
	 * @brief �W�[�{�b��
	 * @param iNow �{�b��
	 */
	void AddNow(IN int iNow);
	/**
	 * @brief ��ֲ{�b��
	 * @param iNow �{�b��
	 */
	void SubNow(IN int iNow);
	/**
	 * @brief ���o�{�b��
	 * @return �{�b��
	 */
	int GetNow() const;
	/**
	 * @brief ���o�ʤ���i�׭�
	 * @note �p�⤽���� (�{�b�� - �}�l��) / (������ - �}�l��) * 100\n�Ǧ^�ȷ|���p���I
	 * @return �ʤ���i�׭�
	 */
	float GetProgressValue() const;
	//-------------------------------------
	/**
	 * @brief �i�ק�s�禡
	 * @note ���禡�|�b C_Progress.SetNow(), C_Progress.AddNow(), C_Progress.SubNow() ����ɳQ�I�s
	 */
	virtual void Process() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------