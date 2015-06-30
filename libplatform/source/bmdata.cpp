//-----------------------------------------------------------------------------
#include "_include.h"
#include "bmdata.h"
//-----------------------------------------------------------------------------
C_BMObj::C_BMObj() : m_pBMData(nullptr) {}
//-----------------------------------------------------------------------------
C_BMObj::C_BMObj(IN C_BMData &bmdata, IN const C_BMDataKey &key) : m_pBMData(&bmdata), m_ccKey(key)
{
	if(m_pBMData)
		m_pBMData->Start(m_ccKey);
}
//-----------------------------------------------------------------------------
C_BMObj::~C_BMObj()
{
	if(m_pBMData)
		m_pBMData->End(m_ccKey);
}
//-----------------------------------------------------------------------------
C_BMData::C_BMData()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_BMData::~C_BMData()
{
	Clear();
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 清除全部
void C_BMData::Clear()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	m_Data.clear();
}
//-----------------------------------------------------------------------------
// 定時處理
void C_BMData::Process()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Data.begin(), m_Data.end(), [] (std::map<C_BMDataKey, C_Benchmark>::value_type &Itor) { Itor.second.Process(); });
}
//-----------------------------------------------------------------------------
// 開始記錄
void C_BMData::Start(IN const C_BMDataKey &ccKey)
{
	_G_();

	if(ccKey == false)
		return;

	C_ThreadLock ccLock(&m_csCommon);
	std::map<C_BMDataKey, C_Benchmark>::iterator Itor = m_Data.find(ccKey);

	if(Itor == m_Data.end())
		Itor = insertmap(m_Data, ccKey, C_Benchmark());

	if(Itor != m_Data.end())
		Itor->second.Start();
}
//-----------------------------------------------------------------------------
// 結束記錄
void C_BMData::End(IN const C_BMDataKey &ccKey)
{
	_G_();

	if(ccKey == false)
		return;

	C_ThreadLock ccLock(&m_csCommon);
	std::map<C_BMDataKey, C_Benchmark>::iterator Itor = m_Data.find(ccKey);

	if(Itor != m_Data.end())
		Itor->second.End();
}
//-----------------------------------------------------------------------------
// 取得紀錄列表
std::map<cstring, S_RecordBMData> C_BMData::Record(IN const cstring &szServer) const
{
	_G_();

	std::map<cstring, S_RecordBMData> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Data.begin(), m_Data.end(), [&szServer, &Result] (const std::map<C_BMDataKey, C_Benchmark>::value_type &Itor) { if(Itor.first.Server() == szServer) Result[Itor.first.Key()] = S_RecordBMData(Itor.second); });

	return Result;
}
//-----------------------------------------------------------------------------