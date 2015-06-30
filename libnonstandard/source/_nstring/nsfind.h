/**
 * @file nsfind.h
 * @note 字串搜尋
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _NSFIND
#define _NSFIND
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 檢查指定字串是否有出現
 * @param szInput 輸入字串
 * @param szKey 指定字串
 * @return true表示有出現, false則否
 * @ingroup nsfind
 */
bool strfind(IN char *szInput, IN const char *szKey);
/**
 * @brief 檢查指定字串是否有出現, 寬字元版本
 * @param szInput 輸入字串
 * @param szKey 指定字串
 * @return true表示有出現, false則否
 * @ingroup nsfind
 */
bool strfind(IN wchar_t *szInput, IN const wchar_t *szKey);
/**
 * @brief 檢查指定字串是否有出現
 * @param szInput 輸入字串
 * @param szKey 指定字串
 * @return true表示有出現, false則否
 * @ingroup nsfind
 */
bool strfind(IN std::string &szInput, IN const char *szKey);
/**
 * @brief 檢查指定字串是否有出現, 寬字元版本
 * @param szInput 輸入字串
 * @param szKey 指定字串
 * @return true表示有出現, false則否
 * @ingroup nsfind
 */
bool strfind(IN std::wstring &szInput, IN const wchar_t *szKey);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------