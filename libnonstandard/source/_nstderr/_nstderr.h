/**
 * @file _nstderr.h
 * @note NonStandardLib的錯誤類別
 * @author yinweli
 */
/**
 * @page 如何使用_nstderr
 * C_ErrorBase 類別是基礎的錯誤類別, 衍生的錯誤類別都得繼承它\n
 * C_ErrorNSTD 類別是提供執行位置訊息的錯誤類別\n
 * C_ErrorWin 類別是提供Windows錯誤訊息的錯誤類別\n
 * C_NOutput 類別是使用 C_ErrorBase 類別來輸出錯誤的類別\n\n
 * 當發生錯誤時, 呼叫 C_NOutput::Instance().Error() 函式來記錄錯誤\n
 * C_NOutput 類別紀錄的錯誤是有上限的, 當紀錄超過 NOUTPUT_MAX 個錯誤, 就會從舊的錯誤開始把紀錄丟棄\n
 * 使用者可以呼叫 C_NOutput::Instance().Get() 函式來取得錯誤\n\n
 * --------------------------------------------------\n
 * Header           : _nstderr.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref nstderror\n
 */
/** @defgroup nstderror */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef __NSTDERR
#define __NSTDERR
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_ntime\_ntime.h"
//-----------------------------------------------------------------------------
#include "errorbase.h"
#include "errornstd.h"
#include "errorwin.h"
#include "noutput.h"
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------