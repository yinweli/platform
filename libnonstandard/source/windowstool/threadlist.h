/**
 * @file threadlist.h
 * @note ������C�����O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _THREADLIST
#define _THREADLIST
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �������T���c
 * @ingroup threadlist
 */
struct S_Thread
{
	unsigned long ulThreadID; ///< �����������N�X
	unsigned long ulProcessID; ///< ����������ݳB�z�{�Ǳ���N�X
	long lPriority; ///< ������u���h��

	S_Thread(IN THREADENTRY32 &r);
};
//-----------------------------------------------------------------------------
/**
 * @brief ������C�����O
 * @ingroup threadlist
 */
class C_ThreadList
{
private:
	//-------------------------------------
	std::vector<S_Thread> m_Thread; ///< �������T�C��
	//-------------------------------------

public:
	//-------------------------------------
	typedef std::vector<S_Thread>::const_iterator const_iterator; ///< �������T�C���N�����O
	//-------------------------------------

public:
	//-------------------------------------
	C_ThreadList();
	virtual ~C_ThreadList();
	//-------------------------------------
	/**
	 * @brief ��l��
	 * @param ulProcessID �B�z�{�Ǳ���N�X
	 * @return true��ܰ��榨�\, false�h�_
	 */
	bool Initialize(IN unsigned long ulProcessID = GetCurrentProcessId());
	/**
	 * @brief ���o�C��}�Y���N��
	 * @return ���N��
	 */
	C_ThreadList::const_iterator Begin() const;
	/**
	 * @brief ���o�C�������N��
	 * @return ���N��
	 */
	C_ThreadList::const_iterator End() const;
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