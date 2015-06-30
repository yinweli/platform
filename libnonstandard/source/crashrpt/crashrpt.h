/**
 * @file crashrpt.h
 * @note 崩潰報告
 * @author yinweli
 */
/**
 * @page 如何使用crashrpt
 * http://crashrpt.sourceforge.net/docs/html/index.html
 * \n\n
 * --------------------------------------------------\n
 * Header           : crashrpt.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref crashrpt
 */
/** @defgroup crashrpt */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CRASHRPT
#define _CRASHRPT
//-----------------------------------------------------------------------------
#ifdef _DEBUG
#pragma comment(lib, "..\\libthirdparty\\crashrpt 1.4.2\\vc2013_lib_debug\\CrashRpt1402d.lib")
#else
#pragma comment(lib, "..\\libthirdparty\\crashrpt 1.4.2\\vc2013_lib_release\\CrashRpt1402.lib")
#endif
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\..\..\libthirdparty\crashrpt 1.4.2\include\CrashRpt.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------