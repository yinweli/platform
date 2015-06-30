/**
 * @file systemtool.h
 * @note 系統處理系列函式
 * @author yinweli
 */
/**
 * @page 如何使用systemtool
 * systemtool內的函式用於系統處理\n\n
 * --------------------------------------------------\n
 * Header           : systemtool.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref systemtool
 */
/** @defgroup systemtool */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _SYSTEMTOOL
#define _SYSTEMTOOL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\whandle\whandle.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 執行程序
 * @note 會以控制台模式執行程序
 * @param szCmdLine 命令行字串, 內容包括執行檔名稱, 帶入的參數
 * @param szCurrentDirectory 執行檔路徑
 * @return true表示成功, false則否
 * @ingroup systemtool
 */
bool ExecuteProcess(IN const nstring &szCmdLine, IN const nstring &szCurrentDirectory);
/**
 * @brief 關閉程序
 * @param ulProcessID 要關閉的處理程序控制代碼
 * @ingroup systemtool
 */
void CloseProcess(IN unsigned long ulProcessID);
/**
 * @brief 取得執行緒執行時間
 * @note 注意取回的時間單位是100奈秒, 把此值除以10000就會變成毫秒
 * @param ulThreadID 執行緒編號
 * @param i64KernelTime 核心模式執行時間, 單位是100奈秒
 * @param i64UserTime 使用者模式執行時間, 單位是100奈秒
 * @ingroup systemtool
 */
bool GetRunTime(IN unsigned long ulThreadID, OUT __int64 &i64KernelTime, OUT __int64 &i64UserTime);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------