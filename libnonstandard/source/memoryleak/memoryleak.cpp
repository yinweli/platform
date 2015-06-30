//-----------------------------------------------------------------------------
#include "memoryleak.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// �]�w�����\��禡
void InitMemDbg(IN const nstring &szFilePath)
{
#ifdef _DEBUG
	// �g�J�����X�Э�
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	HANDLE hDumpFile = INVALID_HANDLE_VALUE;

	// �إ߰O����ĵ�i��X����
	{
		hDumpFile = CreateFile(nstring(szFilePath + (szFilePath.empty() ? __T("") : __T("\\")) + __T("memoryleak_warning.log")).c_str(), 
							   GENERIC_WRITE, 
							   FILE_SHARE_WRITE | FILE_SHARE_READ, 
							   nullptr, 
							   CREATE_ALWAYS, 
							   FILE_ATTRIBUTE_NORMAL, 
							   nullptr);

		if(hDumpFile != INVALID_HANDLE_VALUE)
		{
			_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE); // �]�w�Nĵ�i��X����
			_CrtSetReportFile(_CRT_WARN, hDumpFile); // �]�w��X�����Handle
		}//if
	}

	// �إ߰O������~��X����
	{
		hDumpFile = CreateFile(nstring(szFilePath + (szFilePath.empty() ? __T("") : __T("\\")) + __T("memoryleak_error.log")).c_str(), 
							   GENERIC_WRITE, 
							   FILE_SHARE_WRITE | FILE_SHARE_READ, 
							   nullptr, 
							   CREATE_ALWAYS, 
							   FILE_ATTRIBUTE_NORMAL, 
							   nullptr);

		if(hDumpFile == INVALID_HANDLE_VALUE)
		{
			_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE); // �]�w�N���~��X����
			_CrtSetReportFile(_CRT_ERROR, hDumpFile); // �]�w��X�����Handle
		}//if
	}
#endif
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------