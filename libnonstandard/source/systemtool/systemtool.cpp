//-----------------------------------------------------------------------------
#include "systemtool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// ����{��
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

	// �N���o���B�z�{�Ǳ���N�X�P���������N�X����
	CloseHandle(sProcessInfo.hThread);
	CloseHandle(sProcessInfo.hProcess);

	return true;
}
//-----------------------------------------------------------------------------
// �����{��
void CloseProcess(IN unsigned long ulProcessID)
{
	HANDLE h = OpenProcess(PROCESS_TERMINATE, FALSE, ulProcessID);

	if(h != nullptr)
		TerminateProcess(h, 0);

	CloseHandle(h);
}
//-----------------------------------------------------------------------------
// ���o���������ɶ�
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