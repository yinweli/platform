//-----------------------------------------------------------------------------
#include "flowrecord.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
#define FLOWRECORD_INTERVAL 5 // ��s���j
#define FLOWRECORD_TIMEUNIT 1000 // �ɶ����
//-----------------------------------------------------------------------------
// �w�����W/��ȭp��
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
// �M������
void C_FlowRecord::Clear()
{
	m_ulUpdateTime = 0;
	m_ulValueTotal = 0;
	m_ulValueRecord = 0;
	m_ulValueTemp = 0;
}
//-----------------------------------------------------------------------------
// �w�ɳB�z
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
// �s�W����
void C_FlowRecord::Record(IN long lValue)
{
	m_ulValueTotal = SafeCalculate(m_ulValueTotal, lValue);
	m_ulValueTemp = SafeCalculate(m_ulValueTemp, lValue);
	Process(); // �s�W�������ɭԤ]�n�B�z�@��, �O���ƾڬO�̷s���A
}
//-----------------------------------------------------------------------------
// ���o�`�y�q��
unsigned long C_FlowRecord::ValueTotal() const
{
	return m_ulValueTotal;
}
//-----------------------------------------------------------------------------
// ���o�����y�q��
unsigned long C_FlowRecord::ValueRecord() const
{
	(const_cast<C_FlowRecord *>(this))->Process(); // ���o�������ɭԤ]�n�B�z�@��, �O���ƾڬO�̷s���A

	return m_ulValueRecord;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------