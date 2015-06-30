/**
 * @file memorytool.h
 * @note 記憶體工具系列函式
 * @author yinweli
 */
/**
 * @page 如何使用memorytool
 * memorytool內的函式用於記憶體操作\n\n
 * --------------------------------------------------\n
 * Header           : memorytool.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref memorytool
 */
/** @defgroup memorytool */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _MEMORYTOOL
#define _MEMORYTOOL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#define ROUNDUP(s, a) (((unsigned long)(s) + ((a) - 1)) &~ ((a) - 1)) ///< 計算s值對齊a值後的巨集 @ingroup memorytool
//-----------------------------------------------------------------------------
/**
 * @brief 異常避免函式
 * @note 避免Debug模式下使用了太多次 new / malloc 之後造成不正常的異常, 只有VC++6.0以下會造成此錯誤\n
 *       但是使用_CrtSetBreakAlloc的功能會失效
 * @ingroup memorytool
 */
void AvoidAllocMemoryAbnormal();
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------