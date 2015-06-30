//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xclient.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 開始recv
void C_XClient::RecvStart(IN SOCKET Socket)
{
	if(m_ccKernal.IOCP() == INVALID_HANDLE_VALUE)
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

	// 檢查接收旗標, 必須關閉中
	if(ccUnit->Recv())
		return;

	// 建立重疊物件
	S_XOverlapped *pOverlapped = m_ccListOverlapped.Add(ENUM_XOverlapped_Recv, Socket);

	if(pOverlapped == nullptr)
		return;

	WSABUF sWSABuf;

	sWSABuf.buf = pOverlapped->cBuffer;
	sWSABuf.len = sizeof(pOverlapped->cBuffer);

	// 啟動recv
	if(m_ccAPI.Recv(Socket, sWSABuf, *pOverlapped) == false)
	{
		C_NOutput::Instance().Error(ERRORNSTD, __T("start failed"));
		m_ccAPI.ReleaseSocket(Socket);
		m_ccListConnect.Set(Socket, INVALID_SOCKET);
		m_ccListNotice.AddDisconnect(Socket); // 斷線通知由recv錯誤時發出
		m_ccListUnit.Del(Socket);
		m_ccListOverlapped.Del(pOverlapped->emType, pOverlapped->Socket);

		return;
	}//if

	ccUnit->Recv(true); // 開啟接收旗標, 直到 RecvFinish 被呼叫時才會關閉接收旗標
}
//-----------------------------------------------------------------------------
// 結束recv
void C_XClient::RecvFinish(IN S_XOverlapped &sOverlapped, IN unsigned long ulBytes, IN bool bResult)
{
	// 處理失敗或是客戶端斷線
	if(bResult == false || ulBytes <= 0)
	{
		m_ccListConnect.Set(sOverlapped.Socket, INVALID_SOCKET);
		m_ccListNotice.AddDisconnect(sOverlapped.Socket); // 斷線通知由recv錯誤時發出
		m_ccListUnit.Del(sOverlapped.Socket);
		m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);

		return;
	}//if

	// 鎖定傳輸單元
	C_XUnitLock ccUnit = m_ccListUnit.Lock(sOverlapped.Socket);

	if(ccUnit)
	{
		// 將接收資料加入接收列表中
		if(ccUnit->AddRecv(sOverlapped.cBuffer, ulBytes))
			m_ccKernal.RecordRecv(ulBytes);

		ccUnit->Recv(false); // 關閉接收旗標, RecvStart 開啟旗標, 直到這裡關閉
	}//if

	m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------