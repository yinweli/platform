//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xlistrecv.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_XRecv::C_XRecv() : m_pData(nullptr), m_ulSize(0), m_ulRecv(0) {}
//-----------------------------------------------------------------------------
C_XRecv::~C_XRecv() {}
//-----------------------------------------------------------------------------
C_XRecv::operator C_XComplete () const
{
	return C_XComplete(m_pData, m_ulSize);
}
//-----------------------------------------------------------------------------
// 初始化
bool C_XRecv::Initialize(IN unsigned long ulSize)
{
	if(ulSize <= 0)
		return false;

	if(m_pData != nullptr)
		return false;

	m_pData = reinterpret_cast<void *>(nstdnew char [ulSize]);

	if(m_pData == nullptr)
		return false;

	m_ulSize = ulSize;
	m_ulRecv = 0;

	return true;
}
//-----------------------------------------------------------------------------
// 釋放
void C_XRecv::Release()
{
	delete [] m_pData;
	m_pData = nullptr;
	m_ulSize = 0;
	m_ulRecv = 0;
}
//-----------------------------------------------------------------------------
// 新增資料
void C_XRecv::Add(IN C_XPoint &ccPoint)
{
	// 如果指標器已到結尾, 就結束了
	if(ccPoint.IsOver())
		return;

	// 如果資料指標是空的, 就結束了
	if(m_pData == nullptr)
		return;

	// 如果接收資料已滿, 就結束了
	if(m_ulSize <= m_ulRecv)
		return;

	// 計算要複製進去的長度
	unsigned long ulCopy = std::min(m_ulSize - m_ulRecv, ccPoint.Less());

	// 複製資料
	memcpy(reinterpret_cast<char *>(m_pData) + m_ulRecv, ccPoint.Offset(ulCopy), ulCopy);

	// 增加接收長度
	m_ulRecv += ulCopy;
}
//-----------------------------------------------------------------------------
// 檢查是否為空
bool C_XRecv::Empty() const
{
	return m_pData == nullptr || m_ulSize <= 0;
}
//-----------------------------------------------------------------------------
// 檢查是否完成
bool C_XRecv::IsComplete() const
{
	return m_ulSize <= m_ulRecv;
}
//-----------------------------------------------------------------------------
C_XListRecv::C_XListRecv() {}
//-----------------------------------------------------------------------------
C_XListRecv::~C_XListRecv()
{
	Clear();
}
//-----------------------------------------------------------------------------
// 清除全部
void C_XListRecv::Clear()
{
	std::for_each(m_Recv.begin(), m_Recv.end(), [] (std::deque<C_XRecv>::value_type &Itor) { Itor.Release(); });
	m_Recv.clear();
}
//-----------------------------------------------------------------------------
// 新增資料
bool C_XListRecv::Add(IN const void *pData, IN unsigned long ulSize)
{
	if(pData == nullptr)
		return false;

	if(ulSize <= 0)
		return false;

	// 建立指標器物件
	C_XPoint ccPoint(pData, ulSize);

	// 開始循環新增資料
	// 如果接收列表為空或是最後一個接收物件已滿, 就表示要建立一個新的接收物件, 要新增的資料開頭就應該是新的接收物件的資料長度
	// 如果接收列表不為空或是最後一個接收物件未滿, 就表示要複製資料到接收物件
	while(ccPoint.IsOver() == false)
	{
		if(m_Recv.empty() || m_Recv.back().IsComplete())
		{
			C_XRecv ccRecv;

			// 初始化接收物件
			if(ccRecv.Initialize(*(reinterpret_cast<const x_head *>(ccPoint.Offset(sizeof(x_head))))) == false)
				return false;

			m_Recv.push_back(ccRecv);
		}//if

		m_Recv.back().Add(ccPoint);
	}//while

	return true;
}
//-----------------------------------------------------------------------------
// 取得接收資料物件
C_XRecv C_XListRecv::Get()
{
	// 如果沒有接收資料就結束
	if(m_Recv.empty())
		return C_XRecv();

	// 如果最前面的接收資料尚未完成就結束
	if(m_Recv.front().IsComplete() == false)
		return C_XRecv();

	C_XRecv ccRecv = m_Recv.front();

	m_Recv.pop_front();

	return ccRecv;
}
//-----------------------------------------------------------------------------
// 取得接收資料數量
unsigned long C_XListRecv::Size() const
{
	return m_Recv.size();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------