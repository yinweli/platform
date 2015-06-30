/**
 * @file memoryleak.h
 * @note 記憶體洩漏除錯設定函式
 * @author yinweli
 */
/**
 * @page 如何使用memoryleak
 * memoryleak內的函式用於設定記憶體洩漏紀錄目的地\n
 * 在程式開始的地方(通常是 main() 函式的開頭)呼叫 InitMemDbg() 函式來設定輸出的記錄文件位置\n
 * 預設的輸出的記錄文件位置在與執行檔同目錄底下的 memoryleak_warning.log 與 memoryleak_error.log\n
 * 這個記憶體洩漏紀錄的功能只在debug版本下有效\n\n
 * --------------------------------------------------\n
 * Header           : memoryleak.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref memoryleak
 */
/** @defgroup memoryleak */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _MEMORYLEAK
#define _MEMORYLEAK
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 設定記憶體洩漏除錯功能函式
 * @param szFilePath 記錄文件路徑
 * @ingroup memoryleak
 */
void InitMemDbg(IN const nstring &szFilePath = __T(""));
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------