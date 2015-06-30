/**
 * @file benchmark.h
 * @note �į����O
 * @author yinweli
 */
/**
 * @page �p��ϥ�benchmark
 * benchmark�Ω�O���Y�q�{������ɶ�, �åB�i�H���o�`���榸��, �C����榸��, �`����ɶ�, �̪�����ɶ�, ��������ɶ�����T\n\n
 * �����إ� C_Benchmark ����\n\n
 * C_Benchmark ccBenchmark;\n\n
 * �M��b�Q�n�O���į઺�{���X���q�}�Y�B, �إ� C_BenchmarkObj ����\n\n
 * C_BenchmarkObj ccBenchmarkObj(ccBenchmark);\n\n
 * ����T�O C_BenchmarkObj �b�Q�n�O���į઺�{���X���q�����B�Q�Ѻc, ���q�į�����N�����F\n
 * ����d��:\n\n
 * {\n
 * C_BenchmarkObj ccBenchmarkObj(ccBenchmark); // �}�l�O��\n
 * \n
 * ... �n�Q�O���į઺�{���X���q ...\n
 * } // �����O��\n\n
 * �̫�n�O�o�w�ɩI�s C_Benchmark.Process() �禡\n\n
 * --------------------------------------------------\n
 * Header           : benchmark.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref benchmark
 */
/** @defgroup benchmark */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _BENCHMARK
#define _BENCHMARK
//-----------------------------------------------------------------------------
#pragma comment(lib, "winmm.lib")
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �į����O
 * @ingroup benchmark
 */
class C_Benchmark
{
private:
	//-------------------------------------
	unsigned long m_ulCount; ///< �`���榸��
	unsigned long m_ulFPS; ///< �C����榸��
	unsigned long m_ulTotal; ///< �`����ɶ�
	unsigned long m_ulLongest; ///< �̪�����ɶ�
	unsigned long m_ulLast; ///< �W�����榸��
	unsigned long m_ulStart1; ///< �}�l����ɶ� - �榸�����ϥ�
	unsigned long m_ulStart2; ///< �}�l����ɶ� - �d������ϥ�
	//-------------------------------------

public:
	//-------------------------------------
	C_Benchmark();
	virtual ~C_Benchmark();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �w�ɳB�z
	 */
	void Process();
	/**
	 * @brief �}�l�O��
	 */
	void Start();
	/**
	 * @brief �����O��
	 */
	void End();
	/**
	 * @brief ���o�`���榸��
	 * @return �`���榸��
	 */
	unsigned long Count() const;
	/**
	 * @brief ���o�C����榸��
	 * @return �C����榸��
	 */
	unsigned long FPS() const;
	/**
	 * @brief ���o�`����ɶ�
	 * @return �`����ɶ�
	 */
	unsigned long Total() const;
	/**
	 * @brief ���o�̪�����ɶ�
	 * @return �̪�����ɶ�
	 */
	unsigned long Longest() const;
	/**
	 * @brief ���o��������ɶ�
	 * @return ��������ɶ�
	 */
	unsigned long Average() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �į������
 * @note ��ڥΩ�b�{���X�����J�į���������O\n
 *       �����O�ŧi�ɥN��}�l�O���Y�q�{������ɶ�\n
 *       �����O�Q�Ѻc�ɥN�����O���Y�q�{������ɶ�, �åB�|�p����榸��, ��������ɶ�, �̪�����ɶ�\n
 *       �ŧi�ɥ�����J C_Benchmark �����ХH�ΥN���q�{������ɶ����O���W��
 * @ingroup benchmark
 */
class C_BenchmarkObj
{
private:
	//-------------------------------------
	C_Benchmark *m_pBenchmark; ///< �į����
	//-------------------------------------

public:
	//-------------------------------------
	C_BenchmarkObj(IN C_Benchmark &benchmark);
	C_BenchmarkObj(IN C_Benchmark *benchmark);
	virtual ~C_BenchmarkObj();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------