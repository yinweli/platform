/**
 * @file nscase.h
 * @note 字串大小寫轉換
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _NSCASE
#define _NSCASE
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 取得大小寫反轉的字元
 * @param c 輸入字元
 * @ingroup nscase
 */
char reverse(IN char c);
/**
 * @brief 取得大小寫反轉的字元, 寬字元版本
 * @param c 輸入字元
 * @ingroup nscase
 */
wchar_t wreverse(IN wchar_t c);
/**
 * @brief 取得轉換為小寫的字串
 * @param szInput 輸入字串
 * @return 結果字串
 * @ingroup nscase
 */
std::string nslower(IN const std::string &szInput);
/**
 * @brief 取得轉換為小寫的字串, 寬字元版本
 * @param szInput 輸入字串
 * @return 結果字串
 * @ingroup nscase
 */
std::wstring nslower(IN const std::wstring &szInput);
/**
 * @brief 取得轉換為大寫的字串
 * @param szInput 輸入字串
 * @return 結果字串
 * @ingroup nscase
 */
std::string nsupper(IN const std::string &szInput);
/**
 * @brief 取得轉換為大寫的字串, 寬字元版本
 * @param szInput 輸入字串
 * @return 結果字串
 * @ingroup nscase
 */
std::wstring nsupper(IN const std::wstring &szInput);
/**
 * @brief 取得轉換為大小寫反轉的字串
 * @param szInput 輸入字串
 * @return 結果字串
 * @ingroup nscase
 */
std::string nseverse(IN const std::string &szInput);
/**
 * @brief 取得轉換為大小寫反轉的字串, 寬字元版本
 * @param szInput 輸入字串
 * @return 結果字串
 * @ingroup nscase
 */
std::wstring nseverse(IN const std::wstring &szInput);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------