//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xclient.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 開始通知
void C_XClient::NoticeStart(IN SOCKET Socket)
{
	// 鎖定傳輸單元
	C_XUnitLock ccUnit = m_ccListUnit.Lock(Socket);

	if(ccUnit == false)
		return;

	C_XRecv ccRecv;

	// 取得 XSOCKET_NOTICESIZE 次的完成物件, 或是取到空的完成物件就會停止
	for(unsigned long ulCount = 0; ulCount < XSOCKET_NOTICESIZE; ++ulCount)
	{
		ccRecv = ccUnit->GetRecv();

		if(ccRecv.Empty() == false)
			m_ccListNotice.AddReceive(Socket, ccRecv);
	}//for
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------