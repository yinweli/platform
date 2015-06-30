/**
 * @file heaplist.h
 * @note 堆積列表類別
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
 * @brief 堆積資訊結構
 * @ingroup heaplist
 */
struct S_Heap
{
	unsigned long ulHandle; ///< 堆積塊(heap block)的控制代碼
	unsigned long ulProcessID; ///< 此堆積塊所屬處理程序控制代碼
	unsigned long ulAddress; ///< 堆積塊的開始位址
	unsigned long ulSize; ///< 堆積塊的大小, 單位:bytes
	unsigned long ulFlag; ///< 堆積塊的狀態, 有以下三種狀態 : LF32_FIXED 此堆積塊無法被移動, LF32_FREE 此堆積塊未使用, LF32_MOVEABLE 此堆積塊可被移動

	S_Heap(IN HEAPENTRY32 &r);
};
//-----------------------------------------------------------------------------
/**
 * @brief 堆積列表類別
 * @ingroup heaplist
 */
class C_HeapList
{
private:
	//-------------------------------------
	std::vector<S_Heap> m_Heap; ///< 堆積資訊列表
	//-------------------------------------

public:
	//-------------------------------------
	typedef std::vector<S_Heap>::const_iterator const_iterator; ///< 堆積資訊列表迭代器型別
	//-------------------------------------

public:
	//-------------------------------------
	C_HeapList();
	virtual ~C_HeapList();
	//-------------------------------------
	/**
	 * @brief 初始化
	 * @param ulProcessID 處理程序控制代碼
	 * @return true表示執行成功, false則否
	 */
	bool Initialize(IN unsigned long ulProcessID = GetCurrentProcessId());
	/**
	 * @brief 取得列表開頭迭代器
	 * @return 迭代器
	 */
	C_HeapList::const_iterator Begin() const;
	/**
	 * @brief 取得列表結尾迭代器
	 * @return 迭代器
	 */
	C_HeapList::const_iterator End() const;
	/**
	 * @brief 取得數量
	 * @return 數量
	 */
	unsigned long Size() const;
	/**
	 * @brief 檢查是否為空
	 * @return true表示為空, false則否
	 */
	bool Empty() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------