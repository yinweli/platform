/**
 * @file progress.h
 * @note 進度計算類別
 * @author yinweli
 */
/**
 * @page 如何使用progress
 * progress用於進度計算, 藉著開始值, 結束值, 現在值的計算, 最後取得進度百分比\n\n
 * 首先建立一個實體使用 C_Progress 宣告如下\n\n
 * C_Progress ccProg;\n\n
 * 接著呼叫 C_Progress.SetValue() 函式設定進度的開始值與結束值\n
 * 在執行期中可以呼叫 C_Progress.SetNow(), C_Progress.AddNow(), C_Progress.SubNow() 函式來設定現在值\n
 * 呼叫 C_Progress.GetProgressValue() 可以取得目前的百分比進度值\n
 * 在執行時若 C_Progress.SetNow(), C_Progress.AddNow(), C_Progress.SubNow() 被呼叫, 則會一起呼叫 C_Progress.Process() 函式\n
 * 使用者可以多載此函式來實作自己的更新函式\n\n
 * --------------------------------------------------\n
 * Header           : progress.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref progress
 */
/** @defgroup progress */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _PROGRESS
#define _PROGRESS
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 進度計算類別
 * @ingroup progress
 */
class C_Progress
{
protected:
	//-------------------------------------
	int m_iStart; ///< 開始值
	int m_iEnd; ///< 結束值
	int m_iNow; ///< 現在值
	//-------------------------------------

public:
	//-------------------------------------
	C_Progress();
	C_Progress(IN int iStart, IN int iEnd, IN int iNow);
	virtual ~C_Progress();
	//-------------------------------------
	/**
	 * @brief 全部清除
	 */
	void Clear();
	/**
	 * @brief 設定開始值, 結束值
	 * @param iStart 開始值
	 * @param iEnd 結束值
	 */
	void SetValue(IN int iStart, IN int iEnd);
	/**
	 * @brief 設定現在值
	 * @param iNow 現在值
	 */
	void SetNow(IN int iNow);

	/**
	 * @brief 增加現在值
	 * @param iNow 現在值
	 */
	void AddNow(IN int iNow);
	/**
	 * @brief 減少現在值
	 * @param iNow 現在值
	 */
	void SubNow(IN int iNow);
	/**
	 * @brief 取得現在值
	 * @return 現在值
	 */
	int GetNow() const;
	/**
	 * @brief 取得百分比進度值
	 * @note 計算公式為 (現在值 - 開始值) / (結束值 - 開始值) * 100\n傳回值會有小數點
	 * @return 百分比進度值
	 */
	float GetProgressValue() const;
	//-------------------------------------
	/**
	 * @brief 進度更新函式
	 * @note 此函式會在 C_Progress.SetNow(), C_Progress.AddNow(), C_Progress.SubNow() 執行時被呼叫
	 */
	virtual void Process() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------