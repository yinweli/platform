//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xclient.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 客戶端IOCP執行緒
unsigned int __stdcall XThreadClientIOCP(IN void *pParam)
{
	// 建立執行緒物件
	C_ThreadObj ccThreadObj(pParam);

	if(ccThreadObj == false)
		return 0;

	C_Argu ccClient;

	if(ccThreadObj.GetParam(XSOCKET_TPARAM_CLIENT, ccClient) == false)
		return 0;

	C_XClient *pClient = reinterpret_cast<C_XClient *>(static_cast<int>(ccClient)); // 取得客戶端指標

	if(pClient == nullptr)
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

		pClient->ClientIOCP(pOverlapped, ulBytes, GetQueuedCompletionStatus(pClient->m_ccKernal.IOCP(), &ulBytes, &ulKey, reinterpret_cast<LPOVERLAPPED *>(&pOverlapped), INFINITE) == TRUE);
	}//while

	return 0;
}
//-----------------------------------------------------------------------------
// 客戶端處理執行緒
unsigned int __stdcall XThreadClientProc(IN void *pParam)
{
	// 建立執行緒物件
	C_ThreadObj ccThreadObj(pParam);

	if(ccThreadObj == false)
		return 0;

	C_Argu ccClient;

	if(ccThreadObj.GetParam(XSOCKET_TPARAM_CLIENT, ccClient) == false)
		return 0;

	C_XClient *pClient = reinterpret_cast<C_XClient *>(static_cast<int>(ccClient)); // 取得客戶端指標

	if(pClient == nullptr)
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

		pClient->ClientProc();
		Sleep(10);
	}//while

	return 0;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------