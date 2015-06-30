/**
 * @file mathtool.h
 * @note 數學系列函式
 * @author yinweli
 */
/**
 * @page 如何使用mathtool
 * mathtool內的函式用於數學計算\n\n
 * --------------------------------------------------\n
 * Header           : mathtool.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref mathtool
 */
/** @defgroup mathtool */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _MATHTOOL
#define _MATHTOOL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 校正float轉換為int型態時會有1的誤差
 * @note 只有在 VC++6.0 版本下才需要此函式校正轉換誤差
 * @param f 浮點數
 * @return 校正後的整數
 * @ingroup mathtool
 */
int float2int(IN float f);
/**
 * @brief 取得不重複隨機排列列表
 * @note 會把 iMin ~ iMax 之間的所有數字拿來隨機排列
 * @param iMin 亂數最小值
 * @param iMax 亂數最大值
 * @return RandList 結果列表
 * @ingroup mathtool
 */
std::vector<int> uniquerandlist(IN int iMin, IN int iMax);
/**
 * @brief 取得指定範圍內的亂數(範圍從 0 ~ RAND_MAX)
 * @param iMin 亂數最小值
 * @param iMax 亂數最大值
 * @return 亂數值
 * @ingroup mathtool
 */
int rangerand(IN int iMin, IN int iMax);
/**
 * @brief 設定亂數種子64位元版本
 * @param ui64Seed 亂數種子
 * @ingroup mathtool
 */
void srand64(unsigned __int64 ui64Seed);
/**
 * @brief 取得亂數64位元版本
 * @note 最大值為 RAND_MAX64
 * @return 亂數值
 * @ingroup mathtool
 */
unsigned __int64 rand64();
/**
 * @brief 取得__int64型態絕對值
 * @param i 值
 * @return 絕對值
 * @ingroup mathtool
 */
unsigned __int64 abs64(IN __int64 i);
/**
 * @brief 取得以2為底數的log結果
 * @param f 數值
 * @return 結果
 * @ingroup mathtool
 */
double log2(double f);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------