//-----------------------------------------------------------------------------
#include "memoryleak.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 設定除錯功能函式
void InitMemDbg(IN const nstring &szFilePath)
{
#ifdef _DEBUG
	// 寫入除錯旗標值
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	HANDLE hDumpFile = INVALID_HANDLE_VALUE;

	// 建立記憶體警告輸出到文件
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
			_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE); // 設定將警告輸出到文件
			_CrtSetReportFile(_CRT_WARN, hDumpFile); // 設定輸出的文件Handle
		}//if
	}

	// 建立記憶體錯誤輸出到文件
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
			_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE); // 設定將錯誤輸出到文件
			_CrtSetReportFile(_CRT_ERROR, hDumpFile); // 設定輸出的文件Handle
		}//if
	}
#endif
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------