//-----------------------------------------------------------------------------
#include "flowrecord.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
#define FLOWRECORD_INTERVAL 5 // 更新間隔
#define FLOWRECORD_TIMEUNIT 1000 // 時間單位
//-----------------------------------------------------------------------------
// 安全的增/減值計算
unsigned long SafeCalculate(IN unsigned long ulRValue, IN unsigned lLValue)
{
	if(lLValue == 0)
		return ulRValue;

	if(lLValue > 0)
		return (ulRValue > (UINT_MAX - lLValue)) ? ulRValue : ulRValue + lLValue;
	else
		return (ulRValue >= lLValue) ? ulRValue - lLValue : 0;
}
//-----------------------------------------------------------------------------
C_FlowRecord::C_FlowRecord() : m_ulUpdateTime(0), m_ulValueTotal(0), m_ulValueRecord(0), m_ulValueTemp(0) {}
//-----------------------------------------------------------------------------
C_FlowRecord::~C_FlowRecord() {}
//-----------------------------------------------------------------------------
// 清除全部
void C_FlowRecord::Clear()
{
	m_ulUpdateTime = 0;
	m_ulValueTotal = 0;
	m_ulValueRecord = 0;
	m_ulValueTemp = 0;
}
//-----------------------------------------------------------------------------
// 定時處理
void C_FlowRecord::Process()
{
	unsigned long ulTime = timeGetTime();

	if(ulTime < m_ulUpdateTime)
		return;

	m_ulUpdateTime = ulTime + FLOWRECORD_INTERVAL * FLOWRECORD_TIMEUNIT;
	m_ulValueRecord = m_ulValueTemp / FLOWRECORD_INTERVAL;
	m_ulValueTemp = 0;
}
//-----------------------------------------------------------------------------
// 新增紀錄
void C_FlowRecord::Record(IN long lValue)
{
	m_ulValueTotal = SafeCalculate(m_ulValueTotal, lValue);
	m_ulValueTemp = SafeCalculate(m_ulValueTemp, lValue);
	Process(); // 新增紀錄的時候也要處理一次, 保持數據是最新狀態
}
//-----------------------------------------------------------------------------
// 取得總流量值
unsigned long C_FlowRecord::ValueTotal() const
{
	return m_ulValueTotal;
}
//-----------------------------------------------------------------------------
// 取得紀錄流量值
unsigned long C_FlowRecord::ValueRecord() const
{
	(const_cast<C_FlowRecord *>(this))->Process(); // 取得紀錄的時候也要處理一次, 保持數據是最新狀態

	return m_ulValueRecord;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------