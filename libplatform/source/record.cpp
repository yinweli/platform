//-----------------------------------------------------------------------------
#include "_include.h"
#include "record.h"
//-----------------------------------------------------------------------------
C_Record::C_Record()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_Record::~C_Record()
{
	Clear();
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 清除全部
void C_Record::Clear()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	m_Data.clear();
}
//-----------------------------------------------------------------------------
// 網路紀錄
void C_Record::Record(IN LibCSNStandard::Packet ^Packet, IN const cstring &szSource, IN const cstring &szTatget, IN unsigned long ulSize)
{
	_G_();

	if(Packet == nullptr)
		return;

	if(szSource.empty())
		return;

	if(szTatget.empty())
		return;

	C_RecordKey ccKey((System::Object ^)Packet, szSource, szTatget);
	C_ThreadLock ccLock(&m_csCommon);
	std::map<C_RecordKey, C_RecordData>::iterator Itor = m_Data.find(ccKey);

	if(Itor == m_Data.end())
		Itor = insertmap(m_Data, ccKey, C_RecordData());

	if(Itor != m_Data.end())
		Itor->second.Add(ulSize);
}
//-----------------------------------------------------------------------------
// 取得紀錄列表
std::map<C_RecordKey, C_RecordData> C_Record::Record() const
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	return m_Data;
}
//-----------------------------------------------------------------------------