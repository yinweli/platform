//-----------------------------------------------------------------------------
#include "benchmark.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_Benchmark::C_Benchmark() : m_ulCount(0), m_ulFPS(0), m_ulTotal(0), m_ulLongest(0), m_ulLast(0), m_ulStart1(0), m_ulStart2(0) {}
//-----------------------------------------------------------------------------
C_Benchmark::~C_Benchmark() {}
//-----------------------------------------------------------------------------
// �M������
void C_Benchmark::Clear()
{
	m_ulCount = 0;
	m_ulFPS = 0;
	m_ulTotal = 0;
	m_ulLongest = 0;
	m_ulLast = 0;
	m_ulStart1 = 0;
	m_ulStart2 = 0;
}
//-----------------------------------------------------------------------------
// �w�ɳB�z
void C_Benchmark::Process()
{
	unsigned long ulTime = timeGetTime();
	unsigned long ulDiff = ulTime - m_ulStart2;

	if(ulDiff < 3000) // FPS�C�T��p��@��
		return; 

	m_ulFPS = static_cast<unsigned long>(static_cast<double>(m_ulCount - m_ulLast) / static_cast<double>(ulDiff) * 1000.0f);
	m_ulLast = m_ulCount;
	m_ulStart2 = ulTime;
}
//-----------------------------------------------------------------------------
// �}�l�O��
void C_Benchmark::Start()
{
	m_ulStart1 = timeGetTime();
}
//-----------------------------------------------------------------------------
// �����O��
void C_Benchmark::End()
{
	unsigned long ulTime = timeGetTime() - m_ulStart1;

	m_ulCount++;
	m_ulTotal += ulTime;
	m_ulLongest = std::max(m_ulLongest, ulTime);
	m_ulStart1 = 0;
}
//-----------------------------------------------------------------------------
// ���o�`���榸��
unsigned long C_Benchmark::Count() const
{
	return m_ulCount;
}
//-----------------------------------------------------------------------------
// ���o�C����榸��
unsigned long C_Benchmark::FPS() const
{
	return m_ulFPS;
}
//-----------------------------------------------------------------------------
// ���o�`����ɶ�
unsigned long C_Benchmark::Total() const
{
	return m_ulTotal;
}
//-----------------------------------------------------------------------------
// ���o�̪�����ɶ�
unsigned long C_Benchmark::Longest() const
{
	return m_ulLongest;
}
//-----------------------------------------------------------------------------
// ���o��������ɶ�
unsigned long C_Benchmark::Average() const
{
	return m_ulCount > 0 ? m_ulTotal / m_ulCount : 0;
}
//-----------------------------------------------------------------------------
C_BenchmarkObj::C_BenchmarkObj(IN C_Benchmark &benchmark) : m_pBenchmark(&benchmark)
{
	if(m_pBenchmark)
		m_pBenchmark->Start();
}
//-----------------------------------------------------------------------------
C_BenchmarkObj::C_BenchmarkObj(IN C_Benchmark *benchmark) : m_pBenchmark(benchmark)
{
	if(m_pBenchmark)
		m_pBenchmark->Start();
}
//-----------------------------------------------------------------------------
C_BenchmarkObj::~C_BenchmarkObj()
{
	if(m_pBenchmark)
	{
		m_pBenchmark->End();
		m_pBenchmark = nullptr;
	}//if
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------