/**
 * @file flowrecord.h
 * @note �y�q�������O
 * @author yinweli
 */
/**
 * @page �p��ϥ�flowrecord
 * flowrecord�Ω��������ɶ����Ȫ��ܤƪ��p\n
 * �i�[���쪺�]�A�Ȫ��`�q, �H�έȪ��C���ܤ�\n\n
 * �����إߤ@�ӹ���ϥ� C_FlowRecord �ŧi�p�U\n\n
 * C_FlowRecord ccFlowRecord;\n\n
 * �M��b�O���ɩI�s C_FlowRecord.Record() �禡�����Ȫ��W�[�q\n
 * �I�s C_FlowRecord.ValueTotal() �i���o���`�q\n
 * �I�s C_FlowRecord.ValueRecord() �i���o�Ȫ��C���ܤ�\n
 * �`�N!�Ȫ��C���ܤ�, �O�b����5����ƥH��~�|�}�l������\n\n
 * --------------------------------------------------\n
 * Header           : flowrecord.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref flowrecord
 */
/** @defgroup flowrecord */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _FLOWRECORD
#define _FLOWRECORD
//-----------------------------------------------------------------------------
#pragma comment(lib, "winmm.lib")
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �y�q�������O
 * @ingroup flowrecord
 */
class C_FlowRecord
{
private:
	//-------------------------------------
	unsigned long m_ulUpdateTime; ///< �U����s�ɶ�
	unsigned long m_ulValueTotal; ///< �`�y�q��
	unsigned long m_ulValueRecord; ///< �����y�q��
	unsigned long m_ulValueTemp; ///< �Ȧs�y�q��
	//-------------------------------------

public:
	//-------------------------------------
	C_FlowRecord();
	virtual ~C_FlowRecord();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �w�ɳB�z
	 */
	void Process();
	/**
	 * @brief �s�W����
	 * @param lValue �y�q��
	 */
	void Record(IN long lValue);
	/**
	 * @brief ���o�`�y�q��
	 * @return �`�y�q��
	 */
	unsigned long ValueTotal() const;
	/**
	 * @brief ���o�����y�q��
	 * @return �����y�q��
	 */
	unsigned long ValueRecord() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------