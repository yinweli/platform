/**
 * @file heaplist.h
 * @note ��n�C�����O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _HEAPLIST
#define _HEAPLIST
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ��n��T���c
 * @ingroup heaplist
 */
struct S_Heap
{
	unsigned long ulHandle; ///< ��n��(heap block)������N�X
	unsigned long ulProcessID; ///< ����n�����ݳB�z�{�Ǳ���N�X
	unsigned long ulAddress; ///< ��n�����}�l��}
	unsigned long ulSize; ///< ��n�����j�p, ���:bytes
	unsigned long ulFlag; ///< ��n�������A, ���H�U�T�ت��A : LF32_FIXED ����n���L�k�Q����, LF32_FREE ����n�����ϥ�, LF32_MOVEABLE ����n���i�Q����

	S_Heap(IN HEAPENTRY32 &r);
};
//-----------------------------------------------------------------------------
/**
 * @brief ��n�C�����O
 * @ingroup heaplist
 */
class C_HeapList
{
private:
	//-------------------------------------
	std::vector<S_Heap> m_Heap; ///< ��n��T�C��
	//-------------------------------------

public:
	//-------------------------------------
	typedef std::vector<S_Heap>::const_iterator const_iterator; ///< ��n��T�C���N�����O
	//-------------------------------------

public:
	//-------------------------------------
	C_HeapList();
	virtual ~C_HeapList();
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
	C_HeapList::const_iterator Begin() const;
	/**
	 * @brief ���o�C�������N��
	 * @return ���N��
	 */
	C_HeapList::const_iterator End() const;
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