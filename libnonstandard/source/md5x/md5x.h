/**
 * @file md5x.h
 * @note MD5編碼系列函式
 * @author yinweli
 */
/**
 * @page 如何使用md5x
 * md5x內的函式用於MD5編碼\n\n
 * --------------------------------------------------\n
 * Header           : md5x.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref md5x
 */
/** @defgroup md5x */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _MD5X
#define _MD5X
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#define MD5CODE_SIZE 16 ///< MD5編碼結果長度 @ingroup md5x
//-----------------------------------------------------------------------------
/**
 * @brief MD5編碼結果結構
 * @ingroup md5x
 */
struct S_MD5Code
{
	unsigned char MD5Code[MD5CODE_SIZE]; ///< MD5編碼結果陣列
	nstring szMD5Code; ///< MD5編碼結果字串

	S_MD5Code();
};
//-----------------------------------------------------------------------------
/**
 * @brief 取得MD5編碼
 * @param p 要編碼的資料指標
 * @param uiSize 資料長度
 * @return 編碼結果
 * @ingroup md5x
 */
S_MD5Code GetMD5Code(IN const void *p, IN unsigned int uiSize);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
