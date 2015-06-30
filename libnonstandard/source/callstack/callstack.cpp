//-----------------------------------------------------------------------------
#include "callstack.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// ���o�禡����}
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
// ���o�禡���ѼƼƶq
int GetFuncArgNum(IN int iAddrs)
{
	return (*(WORD *)iAddrs == 0xC483) ? (*(BYTE *)(iAddrs + 2) >> 2) : 0;
}
//-----------------------------------------------------------------------------
// ���o�禡���Ѽ�
int GetFuncArgVal(IN int iebp, IN int iPos)
{
	return *(int *)(iebp + ((iPos + 2) << 2));
}
//-----------------------------------------------------------------------------
// ���o���webp���禡��T
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

	// ���o�禡��}
	int iRetAddr = *(int *)(iebp + 4);
	int iCallFuncAddr = GetCallFuncAddr(iRetAddr);

	// ���o�禡���U�ظ�T
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
// ��l�Ƶ��c
void S_CallStack::Init()
{
	szFileName = __T("");
	dwLine = 0;
	dwDisp = 0;
	szFuncName = __T("");
	ArgsList.clear();
}
//-----------------------------------------------------------------------------
// Callstack�l��
void CallStackTrace(OUT std::vector<S_CallStack> &CallStack)
{
	CallStack.clear();

	// ���o�{����ProcessID
	HANDLE hProcess = (HANDLE)GetCurrentProcessId();

	// ��l�Ƥ�Ū���Ÿ���
	SymSetOptions(SYMOPT_UNDNAME | SYMOPT_LOAD_LINES);

	if(SymInitialize(hProcess, NULL, TRUE) == FALSE)
		return;

	int iSave_ebp, iNow_ebp;

	// ���o�{�b��ebp
	__asm
	{
		mov iNow_ebp, ebp
	}

	iSave_ebp = *(int *)iNow_ebp;

	// �}�l�`�Ǩ��oCallstack��T
	S_CallStack sCallStack;

	while(iSave_ebp != 0)
	{
		GetCallFuncInfo(hProcess, iNow_ebp, &sCallStack);

		if(sCallStack.szFuncName.size() > 0)
			CallStack.push_back(sCallStack);

		// ���o�U�@��ebp
		iNow_ebp = iSave_ebp;
		iSave_ebp = *(int *)iSave_ebp;
	}//while

	SymCleanup(hProcess);
}
//-----------------------------------------------------------------------------
// Callstack�l��, ��X��O���ɮ�
void CallStackTrace(OUT const nstring &szFilePath)
{
	std::vector<S_CallStack> CallStack;
	nstring szParam;

	// ���oCallstack�l�ܸ�T
	CallStackTrace(CallStack);

	nstring szFileName;

	szFileName += szFilePath;
	szFileName += szFileName.empty() ? __T("") : __T("\\");
	szFileName += __T("callstack.log");

	// �g�J�ɮ�
	fwritestr(szFileName, true, __T("********************************************************************************\n"));
	fwritestr(szFileName, true, __T("*  call stack log file\n"));
	fwritestr(szFileName, true, __T("*  log time : %s\n"), TimeStringLocal().c_str());
	fwritestr(szFileName, true, __T("********************************************************************************\n"));

	std::vector<S_CallStack>::iterator Itor = CallStack.begin();

	while(Itor != CallStack.end())
	{
		// �զX�ѼƦr��
		szParam = __T("");

		for(std::vector<S_CallStack>::size_type i = 0, iMax = (*Itor).ArgsList.size(); i < iMax; ++i)
		{
			addprintf(szParam, __T("0x%08x"), (*Itor).ArgsList[i]);

			if(i < (*Itor).ArgsList.size() - 1)
				szParam += __T(", ");
		}//for

		// �g�J�ɮ�
		fwritestr(szFileName, true, __T("%s(line %u + %u bytes) %s(%s)\n"), (*Itor).szFileName.c_str(), (*Itor).dwLine, (*Itor).dwDisp, (*Itor).szFuncName.c_str(), szParam.c_str());
		++Itor;
	}//while
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------