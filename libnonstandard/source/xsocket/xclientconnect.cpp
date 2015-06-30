//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xclient.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 開始connect
void C_XClient::ConnectStart(IN const C_IPData &ccIPData)
{
	if(ccIPData.Empty())
		return;

	if(m_ccKernal.IOCP() == INVALID_HANDLE_VALUE)
		return;

	if(m_ccThreadMgr.Size() <= 0)
		return;

	SOCKET Socket = INVALID_SOCKET;
	S_XAddr sAddrHost, sAddrBind;

	// 建立位址結構
	if(m_ccAPI.GetHostAddrInfo(ccIPData, sAddrHost) == false)
		return;

	// 建立新的Socket
	if(m_ccAPI.CreateSocket(sAddrHost, Socket) == false)
		return;

	// 設定連線
	m_ccListConnect.Set(ccIPData, Socket);

	// 建立綁定位址結構
	if(m_ccAPI.GetBindAddrInfo(sAddrBind) == false)
	{
		m_ccAPI.ReleaseSocket(Socket);
		m_ccListConnect.Set(Socket, INVALID_SOCKET);

		return;
	}//if

	// 綁定SocketID
	if(m_ccAPI.BindSocket(Socket, sAddrBind) == false)
	{
		m_ccAPI.ReleaseSocket(Socket);
		m_ccListConnect.Set(Socket, INVALID_SOCKET);

		return;
	}//if

	// 建立傳輸單元
	if(m_ccListUnit.Add(Socket) == false)
	{
		m_ccAPI.ReleaseSocket(Socket);
		m_ccListConnect.Set(Socket, INVALID_SOCKET);

		return;
	}//if

	// 鎖定傳輸單元
	C_XUnitLock ccUnit = m_ccListUnit.Lock(Socket);

	if(ccUnit == false)
	{
		m_ccAPI.ReleaseSocket(Socket);
		m_ccListConnect.Set(Socket, INVALID_SOCKET);
		m_ccListUnit.Del(Socket);

		return;
	}//if

	// 建立重疊物件
	S_XOverlapped *pOverlapped = m_ccListOverlapped.Add(ENUM_XOverlapped_Connect, Socket);

	if(pOverlapped == nullptr)
	{
		m_ccAPI.ReleaseSocket(Socket);
		m_ccListConnect.Set(Socket, INVALID_SOCKET);
		m_ccListUnit.Del(Socket);

		return;
	}//if

	m_ccAPI.AssociateIOCompletionPort(m_ccKernal.IOCP(), Socket, 0);

	// 啟動connect
	if(m_ccAPI.Connect(Socket, &sAddrHost.sAddr, sAddrHost.ulAddrLen, *pOverlapped) == false)
	{
		C_NOutput::Instance().Error(ERRORNSTD, __T("start failed"));
		m_ccAPI.ReleaseSocket(Socket);
		m_ccListConnect.Set(Socket, INVALID_SOCKET);
		m_ccListUnit.Del(Socket);
		m_ccListOverlapped.Del(pOverlapped->emType, pOverlapped->Socket);

		return;
	}//if
}
//-----------------------------------------------------------------------------
// 結束connect
void C_XClient::ConnectFinish(IN S_XOverlapped &sOverlapped, IN unsigned long ulBytes, IN bool bResult)
{
	if(bResult == false)
	{
		m_ccListConnect.Set(sOverlapped.Socket, INVALID_SOCKET);
		m_ccListUnit.Del(sOverlapped.Socket);
		m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);

		return;
	}//if

	// 完成connect
	if(m_ccAPI.ConnectContext(sOverlapped.Socket) == false)
	{
		m_ccListConnect.Set(sOverlapped.Socket, INVALID_SOCKET);
		m_ccListUnit.Del(sOverlapped.Socket);
		m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);

		return;
	}//if

	// 鎖定傳輸單元
	C_XUnitLock ccUnit = m_ccListUnit.Lock(sOverlapped.Socket);

	if(ccUnit == false)
	{
		m_ccListConnect.Set(sOverlapped.Socket, INVALID_SOCKET);
		m_ccListUnit.Del(sOverlapped.Socket);
		m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);

		return;
	}//if

	ccUnit->Running(true);
	m_ccListNotice.AddConnect(sOverlapped.Socket);
	m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------