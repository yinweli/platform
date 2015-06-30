//-----------------------------------------------------------------------------
#include "windowstool.h"
#include "heaplist.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
S_Heap::S_Heap(IN HEAPENTRY32 &r) : ulHandle(reinterpret_cast<unsigned long>(r.hHandle)), ulProcessID(r.th32ProcessID), ulAddress(r.dwAddress), ulSize(r.dwBlockSize), ulFlag(r.dwFlags) {}
//-----------------------------------------------------------------------------
C_HeapList::C_HeapList() {}
//-----------------------------------------------------------------------------
C_HeapList::~C_HeapList() {}
//-----------------------------------------------------------------------------
// 初始化
bool C_HeapList::Initialize(IN unsigned long ulProcessID)
{
	m_Heap.clear();

	C_WHandle ccSnap = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, ulProcessID); // 取得處理程序中堆積的快照

	if(ccSnap == INVALID_HANDLE_VALUE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("CreateToolhelp32Snapshot failed"));

	HEAPLIST32 sHeapList;

	ZeroMemory(&sHeapList, sizeof(sHeapList));
	sHeapList.dwSize = sizeof(sHeapList);

	// 取得第一個堆積列表資訊
	if(Heap32ListFirst(static_cast<HANDLE>(ccSnap), &sHeapList) == FALSE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("Heap32ListFirst failed"));

	HEAPENTRY32 sHeap;

	// 依序取得堆積列表資訊
	do
	{
		ZeroMemory(&sHeap, sizeof(sHeap));
		sHeap.dwSize = sizeof(sHeap);

		// 取得第一個堆積資訊
		if(Heap32First(&sHeap, ulProcessID, sHeapList.th32HeapID) == FALSE)
			continue;

		do
		{
			m_Heap.push_back(S_Heap(sHeap));
		} while(Heap32Next(&sHeap) == TRUE);
	} while(Heap32ListNext(static_cast<HANDLE>(ccSnap), &sHeapList) == TRUE);

	return true;
}
//-----------------------------------------------------------------------------
// 取得列表開頭迭代器
C_HeapList::const_iterator C_HeapList::Begin() const
{
	return m_Heap.begin();
}
//-----------------------------------------------------------------------------
// 取得列表結尾迭代器
C_HeapList::const_iterator C_HeapList::End() const
{
	return m_Heap.end();
}
//-----------------------------------------------------------------------------
// 取得數量
unsigned long C_HeapList::Size() const
{
	return m_Heap.size();
}
//-----------------------------------------------------------------------------
// 檢查是否為空
bool C_HeapList::Empty() const
{
	return m_Heap.empty();
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------