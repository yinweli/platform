//-----------------------------------------------------------------------------
#include "_include.h"
#include "command.h"
//-----------------------------------------------------------------------------
C_Command::C_Command()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_Command::~C_Command()
{
	Clear();
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 清除全部
void C_Command::Clear()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Data.begin(), m_Data.end(), [] (std::map<C_CommandKey, C_CommandInterface *>::value_type &Itor) { if(Itor.second) delete Itor.second; });
	m_Data.clear();
}
//-----------------------------------------------------------------------------
// 執行命令處理
void C_Command::Execute(IN const cstring &szServer, IN C_Control &ccControl, IN C_Output &ccOutput)
{
	_G_();

	if(szServer.empty())
		return;

	if(ccControl.Chk(szServer) == false)
		return;

	std::vector<cstring> Result = ccControl.Get().split(__T(", "));

	if(Result.empty())
		return;

	C_ThreadLock ccLock(&m_csCommon);
	std::map<C_CommandKey, C_CommandInterface *>::iterator Itor = m_Data.find(C_CommandKey(szServer, Result[0]));

	if(Itor == m_Data.end())
	{
		ccOutput.Add(__T("command not exist"));
		return;
	}//if

	if(Itor->second == nullptr)
	{
		ccOutput.Add(__T("command null"));
		return;
	}//if

	ccOutput.Add(Itor->second->Execute(toargv(Result, 1)));
}
//-----------------------------------------------------------------------------
// 取得紀錄列表
std::map<cstring, cstring> C_Command::Record(IN const cstring &szServer) const
{
	_G_();

	std::map<cstring, cstring> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Data.begin(), m_Data.end(), [&szServer, &Result] (const std::map<C_CommandKey, C_CommandInterface *>::value_type &Itor) { if(Itor.first.Server() == szServer) Result[Itor.first.Key()] = Itor.second ? Itor.second->Help() : __T(""); });

	return Result;
}
//-----------------------------------------------------------------------------