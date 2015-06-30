//-----------------------------------------------------------------------------
#include "taskschedule.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 製造時間字串
nstring MakeSchedule(IN long lYear, IN long lMonth, IN long lMDay, IN long lWDay, IN long lHour, IN long lMin, IN long lSec)
{
	nstring szSchedule;

	szSchedule += lYear != -1 ? (nsoutf(__T("{04}/")) << lYear) : nsoutf(__T("*/"));
	szSchedule += lMonth != -1 ? (nsoutf(__T("{02}/")) << lMonth) : nsoutf(__T("*/"));
	szSchedule += lMDay != -1 ? (nsoutf(__T("{02}/")) << lMDay) : nsoutf(__T("*/"));
	szSchedule += lMDay == -1 && lWDay != -1 ? (nsoutf(__T("{}/")) << lWDay) : nsoutf(__T("*/")); // 周只有在日為-1的時候才可以使用
	szSchedule += lHour != -1 ? (nsoutf(__T("{02}/")) << lHour) : nsoutf(__T("*/"));
	szSchedule += lMin != -1 ? (nsoutf(__T("{02}/")) << lMin) : nsoutf(__T("*/"));
	szSchedule += lSec != -1 ? (nsoutf(__T("{02}/")) << lSec) : nsoutf(__T("*/"));

	return szSchedule;
}
//-----------------------------------------------------------------------------
// 製造時間字串, 格式會與過濾字串一致
nstring MakeSchedule(IN long lYear, IN long lMonth, IN long lMDay, IN long lWDay, IN long lHour, IN long lMin, IN long lSec, IN const nstring &szFilter)
{
	nstring szSchedule;
	std::vector<nstring> Filter = nstok(szFilter, __T("/"));

	return Filter.size() == 7 ? MakeSchedule(Filter[0] == __T("*") ? -1 : lYear, Filter[1] == __T("*") ? -1 : lMonth, Filter[2] == __T("*") ? -1 : lMDay, Filter[3] == __T("*") ? -1 : lWDay, Filter[4] == __T("*") ? -1 : lHour, Filter[5] == __T("*") ? -1 : lMin, Filter[6] == __T("*") ? -1 : lSec) : __T("");
}
//-----------------------------------------------------------------------------
C_TaskSchedule::C_TaskSchedule(IN const nstring &schedule) : m_szSchedule(schedule), m_bBlock(false) {}
//-----------------------------------------------------------------------------
C_TaskSchedule::~C_TaskSchedule() {}
//-----------------------------------------------------------------------------
// 設定排程時間
void C_TaskSchedule::Set(IN const nstring &szSchedule)
{
	m_szSchedule = szSchedule;
}
//-----------------------------------------------------------------------------
// 檢查是否執行
bool C_TaskSchedule::Check()
{
	SYSTEMTIME sTimeNow;

	GetLocalTime(&sTimeNow); // 取得現在時間

	nstring szTimeNow = MakeSchedule(sTimeNow.wYear, sTimeNow.wMonth, sTimeNow.wDay, sTimeNow.wDayOfWeek, sTimeNow.wHour, sTimeNow.wMinute, sTimeNow.wSecond, m_szSchedule); // 建立現在時間字串

	if(szTimeNow == m_szSchedule)
	{
		if(m_bBlock)
			return false;

		m_bBlock = true;

		return true;
	}
	else
	{
		m_bBlock = false;

		return false;
	}//if
}
//-----------------------------------------------------------------------------
// 取得排程時間
nstring C_TaskSchedule::Schedule() const
{
	return m_szSchedule;
}
//-----------------------------------------------------------------------------
C_TaskScheduleList::C_TaskScheduleList() {}
//-----------------------------------------------------------------------------
C_TaskScheduleList::~C_TaskScheduleList()
{
	Clear();
}
//-----------------------------------------------------------------------------
// 清除全部
void C_TaskScheduleList::Clear()
{
	std::for_each(m_Task.begin(), m_Task.end(), [] (std::map<nstring, C_TaskSchedule *>::value_type &Itor) { if(Itor.second) delete Itor.second; });
	m_Task.clear();
}
//-----------------------------------------------------------------------------
// 刪除排程任務
void C_TaskScheduleList::Del(IN const nstring &szName)
{
	std::map<nstring, C_TaskSchedule *>::iterator Itor = m_Task.find(szName);

	if(Itor == m_Task.end())
		return;

	if(Itor->second)
		delete Itor->second;

	m_Task.erase(Itor);
}
//-----------------------------------------------------------------------------
// 設定排程時間
void C_TaskScheduleList::Set(IN const nstring &szName, IN long lYear, IN long lMonth, IN long lMDay, IN long lWDay, IN long lHour, IN long lMin, IN long lSec)
{
	std::map<nstring, C_TaskSchedule *>::iterator Itor = m_Task.find(szName);

	if(Itor == m_Task.end())
		return;

	if(Itor->second == nullptr)
		return;

	Itor->second->Set(MakeSchedule(lYear, lMonth, lMDay, lWDay, lHour, lMin, lSec));
}
//-----------------------------------------------------------------------------
// 定時處理
void C_TaskScheduleList::Process()
{
	std::for_each(m_Task.begin(), m_Task.end(), [] (std::map<nstring, C_TaskSchedule *>::value_type &Itor) { if(Itor.second) Itor.second->Process(); });
}
//-----------------------------------------------------------------------------
// 取得排程任務列表
std::map<nstring, nstring> C_TaskScheduleList::List() const
{
	std::map<nstring, nstring> Result;

	std::for_each(m_Task.begin(), m_Task.end(), [&Result] (const std::map<nstring, C_TaskSchedule *>::value_type &Itor) { if(Itor.second) Result[Itor.first] = Itor.second->Schedule(); });

	return Result;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------