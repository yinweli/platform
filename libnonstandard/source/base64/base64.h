/**
 * @file base64.h
 * @note base64編解碼類別
 * @author yinweli
 */
/**
 * @page 如何使用base64
 * base64用來處理base64編碼與解碼\n\n
 * --------------------------------------------------\n
 * Header           : base64.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref base64
 */
/** @defgroup base64 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _BASE64
#define _BASE64
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief base64編解碼類別
 * @ingroup base64
 */
class C_Base64
{
private:
	//-------------------------------------
	static const char m_Padding; ///< 填充字元
	static const char m_Encode[]; ///< 編碼表
	static const char m_Decode[]; ///< 解碼表
	static const int m_Mod[]; ///< 除數表
	//-------------------------------------

public:
	//-------------------------------------
	/**
	 * @brief base64編碼
	 * @param szData 字串
	 * @return 結果字串
	 */
	nstring Encode(IN const nstring &szData) const;
	/**
	 * @brief base64解碼
	 * @param szData 字串
	 * @return 結果字串
	 */
	nstring Decode(IN const nstring &szData) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------