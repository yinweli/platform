//-----------------------------------------------------------------------------
#include "taskinterval.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_TaskInterval::C_TaskInterval(IN unsigned long interval) : m_ulInterval(interval), m_ulTimeNext(0) {}
//-----------------------------------------------------------------------------
C_TaskInterval::~C_TaskInterval() {}
//-----------------------------------------------------------------------------
// �]�w���j�ɶ�
void C_TaskInterval::Set(IN unsigned long ulInterval)
{
	m_ulInterval = ulInterval;
}
//-----------------------------------------------------------------------------
// �ˬd�O�_����
bool C_TaskInterval::Check()
{
	unsigned long ulTimeNow = timeGetTime();

	if(m_ulTimeNext > ulTimeNow)
		return false;

	m_ulTimeNext = ulTimeNow + m_ulInterval;

	return true;
}
//-----------------------------------------------------------------------------
// ���o���j�ɶ�
unsigned long C_TaskInterval::Interval() const
{
	return m_ulInterval;
}
//-----------------------------------------------------------------------------
C_TaskIntervalList::C_TaskIntervalList() {}
//-----------------------------------------------------------------------------
C_TaskIntervalList::~C_TaskIntervalList()
{
	Clear();
}
//-----------------------------------------------------------------------------
// �M������
void C_TaskIntervalList::Clear()
{
	std::for_each(m_Task.begin(), m_Task.end(), [] (std::map<nstring, C_TaskInterval *>::value_type &Itor) { if(Itor.second) delete Itor.second; });
	m_Task.clear();
}
//-----------------------------------------------------------------------------
// �w�ɳB�z
void C_TaskIntervalList::Process()
{
	std::for_each(m_Task.begin(), m_Task.end(), [] (std::map<nstring, C_TaskInterval *>::value_type &Itor) { if(Itor.second) Itor.second->Process(); });
}
//-----------------------------------------------------------------------------
// �R�����j����
void C_TaskIntervalList::Del(IN const nstring &szName)
{
	std::map<nstring, C_TaskInterval *>::iterator Itor = m_Task.find(szName);

	if(Itor == m_Task.end())
		return;

	if(Itor->second)
		delete Itor->second;

	m_Task.erase(Itor);
}
//-----------------------------------------------------------------------------
// �]�w���j�ɶ�
void C_TaskIntervalList::Set(IN const nstring &szName, IN unsigned long ulInterval)
{
	std::map<nstring, C_TaskInterval *>::iterator Itor = m_Task.find(szName);

	if(Itor == m_Task.end())
		return;

	if(Itor->second == nullptr)
		return;

	Itor->second->Set(ulInterval);
}
//-----------------------------------------------------------------------------
// ���o���j�ɶ�
unsigned long C_TaskIntervalList::Get(IN const nstring &szName) const
{
	std::map<nstring, C_TaskInterval *>::const_iterator Itor = m_Task.find(szName);

	if(Itor == m_Task.end())
		return 0;

	if(Itor->second == nullptr)
		return 0;

	return Itor->second->Interval();
}
//-----------------------------------------------------------------------------
// ���o���j���ȦC��
std::set<nstring> C_TaskIntervalList::List() const
{
	std::set<nstring> Result;

	std::for_each(m_Task.begin(), m_Task.end(), [&Result] (const std::map<nstring, C_TaskInterval *>::value_type &Itor) { Result.insert(Itor.first); });

	return Result;
}
//-----------------------------------------------------------------------------
// ���o�ƶq
unsigned long C_TaskIntervalList::Size() const
{
	return m_Task.size();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------