//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xserver.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 伺服器IOCP執行緒
unsigned int __stdcall XThreadServerIOCP(IN void *pParam)
{
	// 建立執行緒物件
	C_ThreadObj ccThreadObj(pParam);

	if(ccThreadObj == false)
		return 0;

	C_Argu ccServer;

	if(ccThreadObj.GetParam(XSOCKET_TPARAM_SERVER, ccServer) == false)
		return 0;

	C_XServer *pServer = reinterpret_cast<C_XServer *>(static_cast<int>(ccServer)); // 取得伺服器指標

	if(pServer == nullptr)
		return 0;

	unsigned long ulBytes = 0; // 傳輸大小
	unsigned long ulKey = 0; // 執行鍵值
	S_XOverlapped *pOverlapped = nullptr; // 重疊物件指標

	while(ccThreadObj.IsShutdown() == false)
	{
		C_Argu ccThread;

		if(ccThreadObj.GetParam(XSOCKET_TPARAM_THREAD, ccThread) == false)
		{
			Sleep(100);
			continue;
		}//if

		if(static_cast<ENUM_XThread>(static_cast<int>(ccThread)) != ENUM_XThread_Normal)
		{
			Sleep(100);
			continue;
		}//if

		pServer->ServerIOCP(pOverlapped, ulBytes, GetQueuedCompletionStatus(pServer->m_ccKernal.IOCP(), &ulBytes, &ulKey, reinterpret_cast<LPOVERLAPPED *>(&pOverlapped), INFINITE) == TRUE);
	}//while

	return 0;
}
//-----------------------------------------------------------------------------
// 伺服器處理執行緒
unsigned int __stdcall XThreadServerProc(IN void *pParam)
{
	// 建立執行緒物件
	C_ThreadObj ccThreadObj(pParam);

	if(ccThreadObj == false)
		return 0;

	C_Argu ccServer;

	if(ccThreadObj.GetParam(XSOCKET_TPARAM_SERVER, ccServer) == false)
		return 0;

	C_XServer *pServer = reinterpret_cast<C_XServer *>(static_cast<int>(ccServer)); // 取得伺服器指標

	if(pServer == nullptr)
		return 0;

	while(ccThreadObj.IsShutdown() == false)
	{
		C_Argu ccThread;

		if(ccThreadObj.GetParam(XSOCKET_TPARAM_THREAD, ccThread) == false)
		{
			Sleep(100);
			continue;
		}//if

		if(static_cast<ENUM_XThread>(static_cast<int>(ccThread)) != ENUM_XThread_Normal)
		{
			Sleep(100);
			continue;
		}//if

		pServer->ServerProc();
		Sleep(10);
	}//while

	return 0;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------