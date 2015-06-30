/**
 * @file noutput.h
 * @note ���~��X���O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _NOUTPUT
#define _NOUTPUT
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#define NOUTPUT_MAX 4096 ///< ���~�T���̤j�ƶq @ingroup nstderror
//-----------------------------------------------------------------------------
/**
 * @brief ���~��X���O
 * @ingroup nstderror
 */
class C_NOutput
{
private:
	//-------------------------------------
	std::deque<estring> m_Data; ///< ���~�T���C��
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_NOutput();
	virtual ~C_NOutput();
	//-------------------------------------
	/**
	 * @brief ���o���~��X����
	 * @return ���~��X����
	 */
	static C_NOutput &Instance();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief ���~��X
	 * @param szError ���~�r��
	 * @return �u�|�Ǧ^false
	 */
	bool Error(IN const estring &szError);
	/**
	 * @brief ���~��X
	 * @param ccError ���~�T������
	 * @param szError ���~�r��
	 * @return �u�|�Ǧ^false
	 */
	bool Error(IN const C_ErrorNSTD &ccError, IN const estring &szError);
	/**
	 * @brief ���~��X
	 * @param ccError ���~�T������
	 * @param ccErrorExt �B�~���~����
	 * @return �u�|�Ǧ^false
	 */
	bool Error(IN const C_ErrorNSTD &ccError, IN const C_ErrorBase &ccErrorExt);
	/**
	 * @brief ���~��X
	 * @param ccError ���~�T������
	 * @param ccErrorExt �B�~���~����
	 * @param szError ���~�r��
	 * @return �u�|�Ǧ^false
	 */
	bool Error(IN const C_ErrorNSTD &ccError, IN const C_ErrorBase &ccErrorExt, IN const estring &szError);
	/**
	 * @brief ���o���~�T��
	 * @return ���~�T��
	 */
	estring Get();
	/**
	 * @brief ���o�O�_����
	 * @return true��ܬ���, false�h�_
	 */
	bool Empty() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------