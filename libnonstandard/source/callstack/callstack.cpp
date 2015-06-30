//-----------------------------------------------------------------------------
#include "callstack.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 取得函式的位址
int GetCallFuncAddr(IN int iAddrs)
{
	int iCallFuncAddr = *(int *)(iAddrs - 4) + iAddrs;
	int iOffset;

	// iCallFuncAddr > 0x80000000 can cause the ''can not read the memory'' error!
	if((DWORD)iCallFuncAddr > 0x80000000)
		return 0;

	// Jump over the JMP instruction to the real address of function
	while(*(BYTE *)iCallFuncAddr == 0xE9)
	{
		iOffset = iCallFuncAddr + 1;
		iCallFuncAddr = *(int *)(iOffset) + (iCallFuncAddr + 5);
	}//while

	return iCallFuncAddr;
}
//-----------------------------------------------------------------------------
// 取得函式的參數數量
int GetFuncArgNum(IN int iAddrs)
{
	return (*(WORD *)iAddrs == 0xC483) ? (*(BYTE *)(iAddrs + 2) >> 2) : 0;
}
//-----------------------------------------------------------------------------
// 取得函式的參數
int GetFuncArgVal(IN int iebp, IN int iPos)
{
	return *(int *)(iebp + ((iPos + 2) << 2));
}
//-----------------------------------------------------------------------------
// 取得指定ebp的函式資訊
void GetCallFuncInfo(IN HANDLE hProcess, IN int iebp, OUT S_CallStack *pInfo)
{
	if(pInfo == NULL)
		return;

	BYTE sSymbol[1024];
	IMAGEHLP_LINE sLine;
	DWORD dwDisp;

	pInfo->Init();
	memset(sSymbol, 0, sizeof(sSymbol));
	memset(&sLine, 0, sizeof(sLine));
	((PIMAGEHLP_SYMBOL)sSymbol)->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
	((PIMAGEHLP_SYMBOL)sSymbol)->MaxNameLength = sizeof(sSymbol) - sizeof(IMAGEHLP_SYMBOL);
	sLine.SizeOfStruct = sizeof(sLine);

	// 取得函式位址
	int iRetAddr = *(int *)(iebp + 4);
	int iCallFuncAddr = GetCallFuncAddr(iRetAddr);

	// 取得函式的各種資訊
	if(SymGetSymFromAddr(hProcess, (DWORD)iCallFuncAddr, &dwDisp, (PIMAGEHLP_SYMBOL)sSymbol) == FALSE)
		return;

	if(SymGetLineFromAddr(hProcess, (DWORD)iRetAddr, &dwDisp, &sLine) == FALSE)
		return;

	pInfo->szFileName = C_NString(sLine.FileName).t_str();
	pInfo->dwLine = sLine.LineNumber;
	pInfo->dwDisp = dwDisp;
	pInfo->szFuncName = C_NString(((PIMAGEHLP_SYMBOL)sSymbol)->Name).t_str();

	for(int i = 0, iMax = GetFuncArgNum(iRetAddr); i < iMax; ++i)
		pInfo->ArgsList.push_back(GetFuncArgVal(iebp, i));
}
//-----------------------------------------------------------------------------
// 初始化結構
void S_CallStack::Init()
{
	szFileName = __T("");
	dwLine = 0;
	dwDisp = 0;
	szFuncName = __T("");
	ArgsList.clear();
}
//-----------------------------------------------------------------------------
// Callstack追蹤
void CallStackTrace(OUT std::vector<S_CallStack> &CallStack)
{
	CallStack.clear();

	// 取得程式的ProcessID
	HANDLE hProcess = (HANDLE)GetCurrentProcessId();

	// 初始化及讀取符號表
	SymSetOptions(SYMOPT_UNDNAME | SYMOPT_LOAD_LINES);

	if(SymInitialize(hProcess, NULL, TRUE) == FALSE)
		return;

	int iSave_ebp, iNow_ebp;

	// 取得現在的ebp
	__asm
	{
		mov iNow_ebp, ebp
	}

	iSave_ebp = *(int *)iNow_ebp;

	// 開始循序取得Callstack資訊
	S_CallStack sCallStack;

	while(iSave_ebp != 0)
	{
		GetCallFuncInfo(hProcess, iNow_ebp, &sCallStack);

		if(sCallStack.szFuncName.size() > 0)
			CallStack.push_back(sCallStack);

		// 取得下一個ebp
		iNow_ebp = iSave_ebp;
		iSave_ebp = *(int *)iSave_ebp;
	}//while

	SymCleanup(hProcess);
}
//-----------------------------------------------------------------------------
// Callstack追蹤, 輸出到記錄檔案
void CallStackTrace(OUT const nstring &szFilePath)
{
	std::vector<S_CallStack> CallStack;
	nstring szParam;

	// 取得Callstack追蹤資訊
	CallStackTrace(CallStack);

	nstring szFileName;

	szFileName += szFilePath;
	szFileName += szFileName.empty() ? __T("") : __T("\\");
	szFileName += __T("callstack.log");

	// 寫入檔案
	fwritestr(szFileName, true, __T("********************************************************************************\n"));
	fwritestr(szFileName, true, __T("*  call stack log file\n"));
	fwritestr(szFileName, true, __T("*  log time : %s\n"), TimeStringLocal().c_str());
	fwritestr(szFileName, true, __T("********************************************************************************\n"));

	std::vector<S_CallStack>::iterator Itor = CallStack.begin();

	while(Itor != CallStack.end())
	{
		// 組合參數字串
		szParam = __T("");

		for(std::vector<S_CallStack>::size_type i = 0, iMax = (*Itor).ArgsList.size(); i < iMax; ++i)
		{
			addprintf(szParam, __T("0x%08x"), (*Itor).ArgsList[i]);

			if(i < (*Itor).ArgsList.size() - 1)
				szParam += __T(", ");
		}//for

		// 寫入檔案
		fwritestr(szFileName, true, __T("%s(line %u + %u bytes) %s(%s)\n"), (*Itor).szFileName.c_str(), (*Itor).dwLine, (*Itor).dwDisp, (*Itor).szFuncName.c_str(), szParam.c_str());
		++Itor;
	}//while
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------