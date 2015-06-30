/**
 * @file nstok.h
 * @note 字串分割
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _NSTOK
#define _NSTOK
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 取得字串切割結果
 * @param szInput 輸入字串
 * @param szTok 定界字串
 * @return 結果列表
 * @ingroup nstok
 */
std::vector<std::string> nstok(IN const std::string &szInput, IN const std::string &szTok);
/**
 * @brief 取得字串切割結果, 寬字元版本
 * @param szInput 輸入字串
 * @param szTok 定界字串
 * @return 結果列表
 * @ingroup nstok
 */
std::vector<std::wstring> nstok(IN const std::wstring &szInput, IN const std::wstring &szTok);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------