//-----------------------------------------------------------------------------
#include "systemtool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 執行程序
bool ExecuteProcess(IN const nstring &szCmdLine, IN const nstring &szCurrentDirectory)
{
	if(szCmdLine.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("command empty"));

	STARTUPINFO sStartupInfo;
	PROCESS_INFORMATION sProcessInfo;

	ZeroMemory(&sStartupInfo, sizeof(sStartupInfo));
	ZeroMemory(&sProcessInfo, sizeof(sProcessInfo));
	sStartupInfo.cb = sizeof(sStartupInfo);

	if(CreateProcess(nullptr, const_cast<TCHAR *>(szCmdLine.c_str()), nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, szCurrentDirectory.c_str(), &sStartupInfo, &sProcessInfo) == FALSE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("execute failed(") + szCmdLine + __T(")"));

	// 將取得的處理程序控制代碼與執行緒控制代碼關閉
	CloseHandle(sProcessInfo.hThread);
	CloseHandle(sProcessInfo.hProcess);

	return true;
}
//-----------------------------------------------------------------------------
// 關閉程序
void CloseProcess(IN unsigned long ulProcessID)
{
	HANDLE h = OpenProcess(PROCESS_TERMINATE, FALSE, ulProcessID);

	if(h != nullptr)
		TerminateProcess(h, 0);

	CloseHandle(h);
}
//-----------------------------------------------------------------------------
// 取得執行緒執行時間
bool GetRunTime(IN unsigned long ulThreadID, OUT __int64 &i64KernelTime, OUT __int64 &i64UserTime)
{
	C_WHandle ccThread = OpenThread(THREAD_QUERY_INFORMATION, FALSE, ulThreadID);

	if(ccThread == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("thread null"));

	FILETIME tCreateTime, tExitTime, tKernelTime, tUserTime;

	if(GetThreadTimes(static_cast<HANDLE>(ccThread), &tCreateTime, &tExitTime, &tKernelTime, &tUserTime) == FALSE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("get thread runtime failed"));

	i64KernelTime = (Int64ShllMod32(tKernelTime.dwHighDateTime, 32) | tKernelTime.dwLowDateTime);
	i64UserTime = (Int64ShllMod32(tUserTime.dwHighDateTime, 32) | tUserTime.dwLowDateTime);

	return true;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------