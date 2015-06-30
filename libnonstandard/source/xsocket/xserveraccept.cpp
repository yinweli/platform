//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xserver.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 開始accept
void C_XServer::AcceptStart()
{
	if(m_ccKernal.IOCP() == INVALID_HANDLE_VALUE)
		return;

	if(m_ccKernal.Socket() == INVALID_SOCKET)
		return;

	if(m_ccThreadMgr.Size() <= 0)
		return;

	SOCKET Socket = INVALID_SOCKET;

	// 建立新的Socket
	if(m_ccAPI.CreateSocket(m_ccKernal.Addr(), Socket) == false)
		return;

	// 建立傳輸單元
	if(m_ccListUnit.Add(Socket) == false)
	{
		m_ccAPI.ReleaseSocket(Socket);

		return;
	}//if

	// 鎖定傳輸單元
	C_XUnitLock ccUnit = m_ccListUnit.Lock(Socket);

	if(ccUnit == false)
	{
		m_ccAPI.ReleaseSocket(Socket);

		return;
	}//if

	// 建立重疊物件
	S_XOverlapped *pOverlapped = m_ccListOverlapped.Add(ENUM_XOverlapped_Accept, Socket);

	if(pOverlapped == nullptr)
	{
		m_ccAPI.ReleaseSocket(Socket);
		m_ccListUnit.Del(Socket);

		return;
	}//if

	// 啟動accept
	if(m_ccAPI.Accept(m_ccKernal.Socket(), pOverlapped->Socket, reinterpret_cast<void *>(pOverlapped->cBuffer), *pOverlapped) == false)
	{
		C_NOutput::Instance().Error(ERRORNSTD, __T("start failed"));
		m_ccAPI.ReleaseSocket(Socket);
		m_ccListUnit.Del(Socket);
		m_ccListOverlapped.Del(pOverlapped->emType, pOverlapped->Socket);

		return;
	}//if

	m_ccAPI.AssociateIOCompletionPort(m_ccKernal.IOCP(), Socket, 0);
}
//-----------------------------------------------------------------------------
// 結束accept
void C_XServer::AcceptFinish(IN S_XOverlapped &sOverlapped, IN unsigned long ulBytes, IN bool bResult)
{
	SOCKET SocketServer = m_ccKernal.Socket();
	sockaddr sAddrServer; // 伺服器位址結構
	sockaddr sAddrClient; // 客戶端位址結構

	if(bResult == false)
	{
		m_ccListUnit.Del(sOverlapped.Socket);
		m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);

		return;
	}//if

	// 取得連線位址
	if(m_ccAPI.GetAcceptSockAddr(reinterpret_cast<void *>(sOverlapped.cBuffer), sAddrServer, sAddrClient) == false)
	{
		m_ccListUnit.Del(sOverlapped.Socket);
		m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);

		return;
	}//if

	// 完成accept
	if(m_ccAPI.AcceptContext(SocketServer, sOverlapped.Socket) == false)
	{
		m_ccListUnit.Del(sOverlapped.Socket);
		m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);

		return;
	}//if

	// 鎖定傳輸單元
	C_XUnitLock ccUnit = m_ccListUnit.Lock(sOverlapped.Socket);

	if(ccUnit == false)
	{
		m_ccListUnit.Del(sOverlapped.Socket);
		m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);

		return;
	}//if

	ccUnit->Address(sAddrClient);
	ccUnit->Running(true);
	m_ccListNotice.AddConnect(sOverlapped.Socket);
	m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------