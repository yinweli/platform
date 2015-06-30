//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xserver.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 開始send
void C_XServer::SendStart(IN SOCKET Socket)
{
	if(m_ccKernal.IOCP() == INVALID_HANDLE_VALUE)
		return;

	if(m_ccKernal.Socket() == INVALID_SOCKET)
		return;

	if(m_ccThreadMgr.Size() <= 0)
		return;

	if(Socket == INVALID_SOCKET)
		return;

	// 鎖定傳輸單元
	C_XUnitLock ccUnit = m_ccListUnit.Lock(Socket);

	if(ccUnit == false)
		return;

	// 檢查傳輸單元執行旗標
	if(ccUnit->Running() == false)
		return;

	// 檢查傳送旗標, 必須關閉中
	if(ccUnit->Send())
		return;

	// 建立重疊物件
	S_XOverlapped *pOverlapped = m_ccListOverlapped.Add(ENUM_XOverlapped_Send, Socket);

	if(pOverlapped == nullptr)
		return;

	// 取得傳送物件
	C_XSend ccSend = ccUnit->GetSend();

	if(ccSend.Empty())
	{
		m_ccListOverlapped.Del(pOverlapped->emType, pOverlapped->Socket);

		return;
	}//if

	WSABUF sWSABuf = ccSend;

	// 啟動send
	if(m_ccAPI.Send(Socket, sWSABuf, *pOverlapped) == false)
	{
		ccSend.Release();
		m_ccListUnit.Del(Socket);
		m_ccListOverlapped.Del(pOverlapped->emType, pOverlapped->Socket);
		m_ccAPI.ReleaseSocket(Socket);

		return;
	}//if

	ccUnit->Send(true); // 開啟傳送旗標, 直到 SendFinish 被呼叫時才會關閉傳送旗標
	ccSend.Release();
}
//-----------------------------------------------------------------------------
// 結束send
void C_XServer::SendFinish(IN S_XOverlapped &sOverlapped, IN unsigned long ulBytes, IN bool bResult)
{
	// 處理失敗或是客戶端斷線
	if(bResult == false || ulBytes <= 0)
	{
		m_ccListUnit.Del(sOverlapped.Socket);
		m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);

		return;
	}//if

	// 鎖定傳輸單元
	C_XUnitLock ccUnit = m_ccListUnit.Lock(sOverlapped.Socket);

	if(ccUnit)
	{
		m_ccKernal.RecordSend(ulBytes);
		ccUnit->Send(false); // 關閉傳送旗標, SendStart 開啟旗標, 直到這裡關閉
	}//if

	m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------