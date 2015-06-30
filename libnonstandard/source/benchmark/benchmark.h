/**
 * @file benchmark.h
 * @note 效能類別
 * @author yinweli
 */
/**
 * @page 如何使用benchmark
 * benchmark用於記錄某段程式執行時間, 並且可以取得總執行次數, 每秒執行次數, 總執行時間, 最長執行時間, 平均執行時間等資訊\n\n
 * 首先建立 C_Benchmark 物件\n\n
 * C_Benchmark ccBenchmark;\n\n
 * 然後在想要記錄效能的程式碼片段開頭處, 建立 C_BenchmarkObj 物件\n\n
 * C_BenchmarkObj ccBenchmarkObj(ccBenchmark);\n\n
 * 之後確保 C_BenchmarkObj 在想要記錄效能的程式碼片段結尾處被解構, 此段效能紀錄就完成了\n
 * 完整範例:\n\n
 * {\n
 * C_BenchmarkObj ccBenchmarkObj(ccBenchmark); // 開始記錄\n
 * \n
 * ... 要被記錄效能的程式碼片段 ...\n
 * } // 結束記錄\n\n
 * 最後要記得定時呼叫 C_Benchmark.Process() 函式\n\n
 * --------------------------------------------------\n
 * Header           : benchmark.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref benchmark
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
 * @brief 效能類別
 * @ingroup benchmark
 */
class C_Benchmark
{
private:
	//-------------------------------------
	unsigned long m_ulCount; ///< 總執行次數
	unsigned long m_ulFPS; ///< 每秒執行次數
	unsigned long m_ulTotal; ///< 總執行時間
	unsigned long m_ulLongest; ///< 最長執行時間
	unsigned long m_ulLast; ///< 上次執行次數
	unsigned long m_ulStart1; ///< 開始執行時間 - 單次紀錄使用
	unsigned long m_ulStart2; ///< 開始執行時間 - 範圍紀錄使用
	//-------------------------------------

public:
	//-------------------------------------
	C_Benchmark();
	virtual ~C_Benchmark();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 定時處理
	 */
	void Process();
	/**
	 * @brief 開始記錄
	 */
	void Start();
	/**
	 * @brief 結束記錄
	 */
	void End();
	/**
	 * @brief 取得總執行次數
	 * @return 總執行次數
	 */
	unsigned long Count() const;
	/**
	 * @brief 取得每秒執行次數
	 * @return 每秒執行次數
	 */
	unsigned long FPS() const;
	/**
	 * @brief 取得總執行時間
	 * @return 總執行時間
	 */
	unsigned long Total() const;
	/**
	 * @brief 取得最長執行時間
	 * @return 最長執行時間
	 */
	unsigned long Longest() const;
	/**
	 * @brief 取得平均執行時間
	 * @return 平均執行時間
	 */
	unsigned long Average() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 效能紀錄器
 * @note 實際用於在程式碼中插入效能紀錄的類別\n
 *       當此類別宣告時代表開始記錄某段程式執行時間\n
 *       此類別被解構時代表結束記錄某段程式執行時間, 並且會計算執行次數, 平均執行時間, 最長執行時間\n
 *       宣告時必須輸入 C_Benchmark 的指標以及代表此段程式執行時間的記錄名稱
 * @ingroup benchmark
 */
class C_BenchmarkObj
{
private:
	//-------------------------------------
	C_Benchmark *m_pBenchmark; ///< 效能指標
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