//-----------------------------------------------------------------------------
#include "callfunclog.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
S_CallFuncLog::S_CallFuncLog() : ulLine(0) {}
//-----------------------------------------------------------------------------
S_CallFuncLog::S_CallFuncLog(IN const nstring &func, IN const nstring &file, IN unsigned long line) : szFunc(func), szFile(file), ulLine(line) {}
//-----------------------------------------------------------------------------
C_CallFuncLog::C_CallFuncLog()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_CallFuncLog::~C_CallFuncLog()
{
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 取得記錄呼叫函式指標
C_CallFuncLog &C_CallFuncLog::Instance()
{
	static C_CallFuncLog ccInstance;

	return ccInstance;
}
//-----------------------------------------------------------------------------
// 清除全部
void C_CallFuncLog::Clear()
{
	C_ThreadLock ccLock(&m_csCommon);

	m_CallList.clear();
}
//-----------------------------------------------------------------------------
// 新增紀錄
void C_CallFuncLog::Add(IN const nstring &szFuncName, IN const nstring &szFileName, IN unsigned long ulLine)
{
	C_ThreadLock ccLock(&m_csCommon);

	if(szFuncName.empty())
		return;

	if(szFileName.empty())
		return;

	m_CallList.push_back(S_CallFuncLog(szFuncName, szFileName, ulLine));

	if(m_CallList.size() >= MAX_LOGCOUNT)
		m_CallList.pop_front();
}
//-----------------------------------------------------------------------------
// 取得紀錄, 輸出到列表
void C_CallFuncLog::Get(OUT std::list<S_CallFuncLog> &CallList) const
{
	C_ThreadLock ccLock(&m_csCommon);

	CallList = m_CallList;
}
//-----------------------------------------------------------------------------
// 取得紀錄, 輸出到檔案
void C_CallFuncLog::Get(IN const nstring &szFilePath) const
{
	nstring szTemp;
	C_ThreadLock ccLock(&m_csCommon);

	szTemp += __T("********************************************************************************\n");
	szTemp += __T("*  call function log file\n");
	szTemp += nsoutf(__T("*  log time : {}\n")) << TimeStringLocal();
	szTemp += __T("********************************************************************************\n");

	std::for_each(m_CallList.begin(), m_CallList.end(), [&szTemp] (const std::list<S_CallFuncLog>::value_type &Itor) { szTemp += nsoutf(__T("{}({}):{}\n")) << Itor.szFile << Itor.ulLine << Itor.szFunc; });

	fwritestr(szFilePath + (szFilePath.empty() ? __T("") : __T("\\")) + __T("callfunction.log"), true, szTemp);
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------