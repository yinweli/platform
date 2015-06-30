//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xlistunit.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_XUnitLock::C_XUnitLock() : m_pUnit(nullptr), m_pLock(nullptr) {}
//-----------------------------------------------------------------------------
C_XUnitLock::C_XUnitLock(IN const C_XUnit *unit) : m_pUnit(const_cast<C_XUnit *>(unit)), m_pLock(const_cast<CRITICAL_SECTION *>(unit ? &unit->m_csCommon : nullptr))
{
	if(m_pLock)
		EnterCriticalSection(m_pLock);
}
//-----------------------------------------------------------------------------
C_XUnitLock::~C_XUnitLock()
{
	UnLock();
}
//-----------------------------------------------------------------------------
C_XUnitLock::operator bool () const
{
	return m_pUnit && m_pLock;
}
//-----------------------------------------------------------------------------
C_XUnit *C_XUnitLock::operator -> ()
{
	return m_pUnit;
}
//-----------------------------------------------------------------------------
// 解鎖傳輸單元
void C_XUnitLock::UnLock()
{
	if(m_pLock)
	{
		LeaveCriticalSection(m_pLock);
		m_pUnit = nullptr;
		m_pLock = nullptr;
	}//if
}
//-----------------------------------------------------------------------------
C_XUnit::C_XUnit() : m_bRunning(false), m_bRecv(false), m_bSend(false), m_bDisconnect(false)
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_XUnit::~C_XUnit()
{
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 清除全部
void C_XUnit::Clear()
{
	m_ListRecv.Clear();
	m_ListSend.Clear();
	m_bRunning = false;
	m_bRecv = false;
	m_bSend = false;
	m_bDisconnect = false;
}
//-----------------------------------------------------------------------------
// 新增接收資料
bool C_XUnit::AddRecv(IN const void *pData, IN unsigned long ulSize)
{
	return m_bRunning && m_bDisconnect == false ? m_ListRecv.Add(pData, ulSize) : false;
}
//-----------------------------------------------------------------------------
// 取得接收資料
C_XRecv C_XUnit::GetRecv()
{
	return m_bRunning ? m_ListRecv.Get() : C_XRecv();
}
//-----------------------------------------------------------------------------
// 取得接收資料是否為空
bool C_XUnit::RecvEmpty() const
{
	return m_ListRecv.Size() == 0;
}
//-----------------------------------------------------------------------------
// 新增傳送資料
bool C_XUnit::AddSend(IN const void *pData, IN unsigned long ulSize)
{
	return m_bRunning && m_bDisconnect == false ? m_ListSend.Add(pData, ulSize) : false;
}
//-----------------------------------------------------------------------------
// 取得傳送資料
C_XSend C_XUnit::GetSend()
{
	return m_bRunning ? m_ListSend.Get() : C_XSend();
}
//-----------------------------------------------------------------------------
// 取得傳送資料是否為空
bool C_XUnit::SendEmpty() const
{
	return m_ListSend.Size() == 0;
}
//-----------------------------------------------------------------------------
// 設定連線位址
void C_XUnit::Address(IN const sockaddr &sAddress)
{
	memcpy(&m_sAddress, &sAddress, sizeof(m_sAddress));
}
//-----------------------------------------------------------------------------
// 取得連線位址
void C_XUnit::Address(OUT nstring &szIP, OUT unsigned long &ulPort) const
{
	szIP = C_NString(inet_ntoa(m_sAddress.sin_addr));
	ulPort = m_sAddress.sin_port;
}
//-----------------------------------------------------------------------------
// 設定執行旗標
void C_XUnit::Running(IN bool bEnable)
{
	m_bRunning = bEnable;
}
//-----------------------------------------------------------------------------
// 取得執行旗標
bool C_XUnit::Running() const
{
	return m_bRunning;
}
//-----------------------------------------------------------------------------
// 設定接收旗標
void C_XUnit::Recv(IN bool bEnable)
{
	m_bRecv = bEnable;
}
//-----------------------------------------------------------------------------
// 取得接收旗標
bool C_XUnit::Recv() const
{
	return m_bRecv;
}
//-----------------------------------------------------------------------------
// 設定傳送旗標
void C_XUnit::Send(IN bool bEnable)
{
	m_bSend = bEnable;
}
//-----------------------------------------------------------------------------
// 取得傳送旗標
bool C_XUnit::Send() const
{
	return m_bSend;
}
//-----------------------------------------------------------------------------
// 設定斷線旗標
void C_XUnit::Disconnect(IN bool bEnable)
{
	m_bDisconnect = bEnable;
}
//-----------------------------------------------------------------------------
// 取得斷線旗標
bool C_XUnit::Disconnect() const
{
	return m_bDisconnect;
}
//-----------------------------------------------------------------------------
C_XListUnit::C_XListUnit()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_XListUnit::~C_XListUnit()
{
	Clear();
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 清除全部
void C_XListUnit::Clear()
{
	C_ThreadLock ccLock(&m_csCommon);

	for(std::map<SOCKET, C_XUnit *>::value_type &Itor : m_Unit)
	{
		if(Itor.second)
		{
			C_XUnitLock ccUnit(Itor.second);

			ccUnit.UnLock();

			delete Itor.second;
		}//if
	}//for

	m_Unit.clear();
}
//-----------------------------------------------------------------------------
// 新增傳輸單元
bool C_XListUnit::Add(IN SOCKET Socket)
{
	if(Socket == INVALID_SOCKET)
		return false;

	C_ThreadLock ccLock(&m_csCommon);

	if(m_Unit.find(Socket) != m_Unit.end())
		return false;

	C_XUnit *pUnit = nstdnew C_XUnit();

	if(pUnit == nullptr)
		return false;

	m_Unit[Socket] = pUnit;

	return true;
}
//-----------------------------------------------------------------------------
// 刪除傳輸單元
void C_XListUnit::Del(IN SOCKET Socket)
{
	C_ThreadLock ccLock(&m_csCommon);

	std::map<SOCKET, C_XUnit *>::iterator Itor = m_Unit.find(Socket);

	if(Itor == m_Unit.end())
		return;

	if(Itor->second == nullptr)
		return;

	C_XUnitLock ccUnit(Itor->second);

	ccUnit.UnLock();
	delete Itor->second;
	m_Unit.erase(Itor);
}
//-----------------------------------------------------------------------------
// 檢查傳輸單元是否存在
bool C_XListUnit::IsExist(IN SOCKET Socket) const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_Unit.find(Socket) != m_Unit.end();
}
//-----------------------------------------------------------------------------
// 鎖定傳輸單元
C_XUnitLock C_XListUnit::Lock(IN SOCKET Socket) const
{
	C_ThreadLock ccLock(&m_csCommon);

	std::map<SOCKET, C_XUnit *>::const_iterator Itor = m_Unit.find(Socket);

	return Itor != m_Unit.end() ? Itor->second : nullptr;
}
//-----------------------------------------------------------------------------
// 取得全部傳輸單元數量
unsigned long C_XListUnit::Size() const
{
	C_ThreadLock ccLock(&m_csCommon);

	return m_Unit.size();
}
//-----------------------------------------------------------------------------
// 取得詳細傳輸單元數量
unsigned long C_XListUnit::Size(IN bool bRunning) const
{
	C_ThreadLock ccLock(&m_csCommon);

	return std::count_if(m_Unit.begin(), m_Unit.end(), [bRunning] (const std::map<SOCKET, C_XUnit *>::value_type &Itor) { return Itor.second && Itor.second->Running() == bRunning; });
}
//-----------------------------------------------------------------------------
// 取得全部SocketID列表
std::set<SOCKET> C_XListUnit::SocketList() const
{
	std::set<SOCKET> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Unit.begin(), m_Unit.end(), [&Result] (const std::map<SOCKET, C_XUnit *>::value_type &Itor) { Result.insert(Itor.first); });

	return Result;
}
//-----------------------------------------------------------------------------
// 取得處理SocketID列表
std::set<SOCKET> C_XListUnit::SocketProcess() const
{
	std::set<SOCKET> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Unit.begin(), m_Unit.end(), [&Result] (const std::map<SOCKET, C_XUnit *>::value_type &Itor) { if(Itor.second && Itor.second->Running()) Result.insert(Itor.first); });

	return Result;
}
//-----------------------------------------------------------------------------
// 取得斷線SocketID列表
std::set<SOCKET> C_XListUnit::SocketDisconnect() const
{
	std::set<SOCKET> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Unit.begin(), m_Unit.end(), [&Result] (const std::map<SOCKET, C_XUnit *>::value_type &Itor) { if(Itor.second && Itor.second->Disconnect() && Itor.second->RecvEmpty() && Itor.second->SendEmpty()) Result.insert(Itor.first); });

	return Result;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------