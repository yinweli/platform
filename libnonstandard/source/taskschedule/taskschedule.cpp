//-----------------------------------------------------------------------------
#include "taskschedule.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// �s�y�ɶ��r��
nstring MakeSchedule(IN long lYear, IN long lMonth, IN long lMDay, IN long lWDay, IN long lHour, IN long lMin, IN long lSec)
{
	nstring szSchedule;

	szSchedule += lYear != -1 ? (nsoutf(__T("{04}/")) << lYear) : nsoutf(__T("*/"));
	szSchedule += lMonth != -1 ? (nsoutf(__T("{02}/")) << lMonth) : nsoutf(__T("*/"));
	szSchedule += lMDay != -1 ? (nsoutf(__T("{02}/")) << lMDay) : nsoutf(__T("*/"));
	szSchedule += lMDay == -1 && lWDay != -1 ? (nsoutf(__T("{}/")) << lWDay) : nsoutf(__T("*/")); // �P�u���b�鬰-1���ɭԤ~�i�H�ϥ�
	szSchedule += lHour != -1 ? (nsoutf(__T("{02}/")) << lHour) : nsoutf(__T("*/"));
	szSchedule += lMin != -1 ? (nsoutf(__T("{02}/")) << lMin) : nsoutf(__T("*/"));
	szSchedule += lSec != -1 ? (nsoutf(__T("{02}/")) << lSec) : nsoutf(__T("*/"));

	return szSchedule;
}
//-----------------------------------------------------------------------------
// �s�y�ɶ��r��, �榡�|�P�L�o�r��@�P
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
// �]�w�Ƶ{�ɶ�
void C_TaskSchedule::Set(IN const nstring &szSchedule)
{
	m_szSchedule = szSchedule;
}
//-----------------------------------------------------------------------------
// �ˬd�O�_����
bool C_TaskSchedule::Check()
{
	SYSTEMTIME sTimeNow;

	GetLocalTime(&sTimeNow); // ���o�{�b�ɶ�

	nstring szTimeNow = MakeSchedule(sTimeNow.wYear, sTimeNow.wMonth, sTimeNow.wDay, sTimeNow.wDayOfWeek, sTimeNow.wHour, sTimeNow.wMinute, sTimeNow.wSecond, m_szSchedule); // �إ߲{�b�ɶ��r��

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
// ���o�Ƶ{�ɶ�
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
// �M������
void C_TaskScheduleList::Clear()
{
	std::for_each(m_Task.begin(), m_Task.end(), [] (std::map<nstring, C_TaskSchedule *>::value_type &Itor) { if(Itor.second) delete Itor.second; });
	m_Task.clear();
}
//-----------------------------------------------------------------------------
// �R���Ƶ{����
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
// �]�w�Ƶ{�ɶ�
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
// �w�ɳB�z
void C_TaskScheduleList::Process()
{
	std::for_each(m_Task.begin(), m_Task.end(), [] (std::map<nstring, C_TaskSchedule *>::value_type &Itor) { if(Itor.second) Itor.second->Process(); });
}
//-----------------------------------------------------------------------------
// ���o�Ƶ{���ȦC��
std::map<nstring, nstring> C_TaskScheduleList::List() const
{
	std::map<nstring, nstring> Result;

	std::for_each(m_Task.begin(), m_Task.end(), [&Result] (const std::map<nstring, C_TaskSchedule *>::value_type &Itor) { if(Itor.second) Result[Itor.first] = Itor.second->Schedule(); });

	return Result;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------