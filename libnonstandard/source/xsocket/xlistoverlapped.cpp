//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xlistoverlapped.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
S_XOverlapped::S_XOverlapped() : emType(ENUM_XOverlapped_NULL), Socket(INVALID_SOCKET)
{
	memset(&sOverlapped, 0, sizeof(sOverlapped));
	memset(cBuffer, 0, sizeof(cBuffer));
}
//-----------------------------------------------------------------------------
S_XOverlapped::S_XOverlapped(IN ENUM_XOverlapped type, IN SOCKET socket) : emType(type), Socket(socket)
{
	memset(&sOverlapped, 0, sizeof(sOverlapped));
	memset(cBuffer, 0, sizeof(cBuffer));
}
//-----------------------------------------------------------------------------
S_XOverlapped::operator OVERLAPPED & ()
{
	return reinterpret_cast<OVERLAPPED &>(*this);
}
//-----------------------------------------------------------------------------
S_XOverlapped::operator OVERLAPPED * ()
{
	return reinterpret_cast<OVERLAPPED *>(this);
}
//-----------------------------------------------------------------------------
bool S_XOverlapped::operator < (IN const S_XOverlapped &rhs) const
{
	return emType == rhs.emType ? Socket < rhs.Socket : emType < rhs.emType;
}
//-----------------------------------------------------------------------------
C_XListOverlapped::C_XListOverlapped()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_XListOverlapped::~C_XListOverlapped()
{
	Clear();
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 清除全部
void C_XListOverlapped::Clear()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Overlapped.clear();
}
//-----------------------------------------------------------------------------
// 新增重疊物件
S_XOverlapped *C_XListOverlapped::Add(IN ENUM_XOverlapped emType, IN SOCKET Socket)
{
	if(emType == ENUM_XOverlapped_NULL)
		return nullptr;

	if(Socket == INVALID_SOCKET)
		return nullptr;

	S_XOverlapped sOverlapped(emType, Socket);
	C_ThreadLock ccLock(&m_csCommon);

	if(m_Overlapped.find(sOverlapped) != m_Overlapped.end())
		return nullptr;

	std::pair<std::set<S_XOverlapped>::iterator, bool> Result = m_Overlapped.insert(sOverlapped);

	if(Result.second == false)
		return nullptr;

	return const_cast<S_XOverlapped *>(&(*Result.first));
}
//-----------------------------------------------------------------------------
// 刪除重疊物件
void C_XListOverlapped::Del(IN ENUM_XOverlapped emType, IN SOCKET Socket)
{
	C_ThreadLock ccLock(&m_csCommon);

	m_Overlapped.erase(S_XOverlapped(emType, Socket));
}
//-----------------------------------------------------------------------------
// 取得重疊物件數量
unsigned long C_XListOverlapped::Size() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_Overlapped.size();
}
//-----------------------------------------------------------------------------
// 取得指定重疊類型物件數量
unsigned long C_XListOverlapped::Size(IN ENUM_XOverlapped emType) const
{
	C_ThreadLock ccLock(&m_csCommon);

	return std::count_if(m_Overlapped.begin(), m_Overlapped.end(), [emType] (const std::set<S_XOverlapped>::value_type &Itor) { return Itor.emType == emType; });
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------