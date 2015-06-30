/**
 * @file debugtool.h
 * @note 除錯系列函式
 * @author yinweli
 */
/**
 * @page 如何使用debugtool
 * debugtool內的函式用於除錯\n\n
 * --------------------------------------------------\n
 * Header           : debugtool.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref debugtool
 */
/** @defgroup debugtool */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _DEBUGTOOL
#define _DEBUGTOOL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\_nstroutf\_nstroutf.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 輸出字串到除錯視窗
 * @param szData 輸出字串
 * @ingroup debugtool
 */
void xOutputDebugString(IN const nstring &szData);
/**
 * @brief 將HRESULT錯誤代碼轉換為字串
 * @param hr HRESULT錯誤代碼
 * @return 錯誤字串
 * @ingroup debugtool
 */
nstring HRESULTtoString(IN HRESULT hr);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------