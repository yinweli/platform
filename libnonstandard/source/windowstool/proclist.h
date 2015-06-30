/**
 * @file proclist.h
 * @note �B�z�{�ǦC�����O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _PROCLIST
#define _PROCLIST
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �B�z�{�Ǹ�T���c
 * @ingroup proclist
 */
struct S_Process
{
	unsigned long ulProcessID; ///< �B�z�{�Ǳ���N�X
	unsigned long ulParentProcessID; ///< ���B�z�{�Ǳ���N�X
	unsigned long ulThreads; ///< �B�z�{�Ǿ֦���������ƶq
	nstring szExeFile; ///< �����ɦW��

	S_Process(IN PROCESSENTRY32 &r);
};
//-----------------------------------------------------------------------------
/**
 * @brief �B�z�{�ǦC�����O
 * @ingroup proclist
 */
class C_ProcList
{
private:
	//-------------------------------------
	std::vector<S_Process> m_Process; ///< �B�z�{�Ǹ�T�C��
	//-------------------------------------

public:
	//-------------------------------------
	typedef std::vector<S_Process>::const_iterator const_iterator; ///< �B�z�{�Ǹ�T�C���N�����O
	//-------------------------------------

public:
	//-------------------------------------
	C_ProcList();
	virtual ~C_ProcList();
	//-------------------------------------
	/**
	 * @brief ��l��
	 * @return true��ܰ��榨�\, false�h�_
	 */
	bool Initialize();
	/**
	 * @brief ���o�C��}�Y���N��
	 * @return ���N��
	 */
	C_ProcList::const_iterator Begin() const;
	/**
	 * @brief ���o�C�������N��
	 * @return ���N��
	 */
	C_ProcList::const_iterator End() const;
	/**
	 * @brief ���o�ƶq
	 * @return �ƶq
	 */
	unsigned long Size() const;
	/**
	 * @brief �ˬd�O�_����
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