//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xclient.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// �Ȥ��IOCP�����
unsigned int __stdcall XThreadClientIOCP(IN void *pParam)
{
	// �إ߰��������
	C_ThreadObj ccThreadObj(pParam);

	if(ccThreadObj == false)
		return 0;

	C_Argu ccClient;

	if(ccThreadObj.GetParam(XSOCKET_TPARAM_CLIENT, ccClient) == false)
		return 0;

	C_XClient *pClient = reinterpret_cast<C_XClient *>(static_cast<int>(ccClient)); // ���o�Ȥ�ݫ���

	if(pClient == nullptr)
		return 0;

	unsigned long ulBytes = 0; // �ǿ�j�p
	unsigned long ulKey = 0; // �������
	S_XOverlapped *pOverlapped = nullptr; // ���|�������

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
// �Ȥ�ݳB�z�����
unsigned int __stdcall XThreadClientProc(IN void *pParam)
{
	// �إ߰��������
	C_ThreadObj ccThreadObj(pParam);

	if(ccThreadObj == false)
		return 0;

	C_Argu ccClient;

	if(ccThreadObj.GetParam(XSOCKET_TPARAM_CLIENT, ccClient) == false)
		return 0;

	C_XClient *pClient = reinterpret_cast<C_XClient *>(static_cast<int>(ccClient)); // ���o�Ȥ�ݫ���

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