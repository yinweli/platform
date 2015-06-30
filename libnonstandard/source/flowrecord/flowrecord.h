/**
 * @file flowrecord.h
 * @note 流量紀錄類別
 * @author yinweli
 */
/**
 * @page 如何使用flowrecord
 * flowrecord用於紀錄執行時間內值的變化狀況\n
 * 可觀測到的包括值的總量, 以及值的每秒變化\n\n
 * 首先建立一個實體使用 C_FlowRecord 宣告如下\n\n
 * C_FlowRecord ccFlowRecord;\n\n
 * 然後在記錄時呼叫 C_FlowRecord.Record() 函式紀錄值的增加量\n
 * 呼叫 C_FlowRecord.ValueTotal() 可取得值總量\n
 * 呼叫 C_FlowRecord.ValueRecord() 可取得值的每秒變化\n
 * 注意!值的每秒變化, 是在收集5秒的資料以後才會開始有紀錄\n\n
 * --------------------------------------------------\n
 * Header           : flowrecord.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref flowrecord
 */
/** @defgroup flowrecord */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _FLOWRECORD
#define _FLOWRECORD
//-----------------------------------------------------------------------------
#pragma comment(lib, "winmm.lib")
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 流量紀錄類別
 * @ingroup flowrecord
 */
class C_FlowRecord
{
private:
	//-------------------------------------
	unsigned long m_ulUpdateTime; ///< 下次更新時間
	unsigned long m_ulValueTotal; ///< 總流量值
	unsigned long m_ulValueRecord; ///< 紀錄流量值
	unsigned long m_ulValueTemp; ///< 暫存流量值
	//-------------------------------------

public:
	//-------------------------------------
	C_FlowRecord();
	virtual ~C_FlowRecord();
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
	 * @brief 新增紀錄
	 * @param lValue 流量值
	 */
	void Record(IN long lValue);
	/**
	 * @brief 取得總流量值
	 * @return 總流量值
	 */
	unsigned long ValueTotal() const;
	/**
	 * @brief 取得紀錄流量值
	 * @return 紀錄流量值
	 */
	unsigned long ValueRecord() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------