/**
 * @file nsedit.h
 * @note 字串編輯
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _NSEDIT
#define _NSEDIT
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 取得字串, 如果輸入字串頭部不是指定字串, 就插入指定字串到頭部
 * @param szInput 輸入字串
 * @param szKey 指定字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::string insthand(IN const std::string &szInput, IN const std::string &szKey);
/**
 * @brief 取得字串, 如果輸入字串頭部不是指定字串, 就插入指定字串到頭部, 寬字元版本
 * @param szInput 輸入字串
 * @param szKey 指定字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::wstring insthand(IN const std::wstring &szInput, IN const std::wstring &szKey);
/**
 * @brief 取得字串, 如果字串尾部不是指定字串, 就插入指定字串到尾部
 * @param szInput 輸入字串
 * @param szKey 指定字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::string insttail(IN const std::string &szInput, IN const std::string &szKey);
/**
 * @brief 取得字串, 如果字串尾部不是指定字串, 就插入指定字串到尾部, 寬字元版本
 * @param szInput 輸入字串
 * @param szKey 指定字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::wstring insttail(IN const std::wstring &szInput, IN const std::wstring &szKey);
/**
 * @brief 取得字串, 如果字串頭尾不是指定字串, 就插入指定字串到頭尾
 * @param szInput 輸入字串
 * @param szKey 指定字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::string insthandtail(IN const std::string &szInput, IN const std::string &szKey);
/**
 * @brief 取得字串, 如果字串頭尾不是指定字串, 就插入指定字串到頭尾, 寬字元版本
 * @param szInput 輸入字串
 * @param szKey 指定字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::wstring insthandtail(IN const std::wstring &szInput, IN const std::wstring &szKey);
/**
 * @brief 取得字串, 如果字串頭部是指定字串, 就從頭部去除指定字串
 * @param szInput 輸入字串
 * @param szKey 指定字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::string trimhand(IN const std::string &szInput, IN const std::string &szKey);
/**
 * @brief 取得字串, 如果字串頭部是指定字串, 就從頭部去除指定字串, 寬字元版本
 * @param szInput 輸入字串
 * @param szKey 指定字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::wstring trimhand(IN const std::wstring &szInput, IN const std::wstring &szKey);
/**
 * @brief 取得字串, 如果字串尾部是指定字串, 就從尾部去除指定字串
 * @param szInput 輸入字串
 * @param szKey 指定字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::string trimtail(IN const std::string &szInput, IN const std::string &szKey);
/**
 * @brief 取得字串, 如果字串尾部是指定字串, 就從尾部去除指定字串, 寬字元版本
 * @param szInput 輸入字串
 * @param szKey 指定字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::wstring trimtail(IN const std::wstring &szInput, IN const std::wstring &szKey);
/**
 * @brief 取得字串, 如果字串頭尾是指定字串, 就從頭尾去除指定字串
 * @param szInput 輸入字串
 * @param szKey 指定字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::string trimhandtail(IN const std::string &szInput, IN const std::string &szKey);
/**
 * @brief 取得字串, 如果字串頭尾是指定字串, 就從頭尾去除指定字串, 寬字元版本
 * @param szInput 輸入字串
 * @param szKey 指定字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::wstring trimhandtail(IN const std::wstring &szInput, IN const std::wstring &szKey);
/**
 * @brief 取得去除字串頭部空白後的字串
 * @param szInput 輸入字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::string trimhandspace(IN const std::string &szInput);
/**
 * @brief 取得去除字串頭部空白後的字串, 寬字元版本
 * @param szInput 輸入字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::wstring trimhandspace(IN const std::wstring &szInput);
/**
 * @brief 取得去除字串尾部空白後的字串
 * @param szInput 輸入字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::string trimtailspace(IN const std::string &szInput);
/**
 * @brief 取得去除字串尾部空白後的字串, 寬字元版本
 * @param szInput 輸入字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::wstring trimtailspace(IN const std::wstring &szInput);
/**
 * @brief 取得去除字串頭尾空白後的字串
 * @param szInput 輸入字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::string trimhandtailspace(IN const std::string &szInput);
/**
 * @brief 取得去除字串頭尾空白後的字串, 寬字元版本
 * @param szInput 輸入字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::wstring trimhandtailspace(IN const std::wstring &szInput);
/**
 * @brief 取得截去指定字元後的字串
 * @param szInput 輸入字串
 * @param Key 指定字元
 * @return 結果字串
 * @ingroup nsedit
 */
std::string nstruncate(IN const std::string &szInput, IN std::string::value_type Key);
/**
 * @brief 取得截去指定字元後的字串, 寬字元版本
 * @param szInput 輸入字串
 * @param Key 指定字元
 * @return 結果字串
 * @ingroup nsedit
 */
std::wstring nstruncate(IN const std::wstring &szInput, IN std::wstring::value_type Key);
/**
 * @brief 取得取代後的字串
 * @param szInput 輸入字串
 * @param szKey 指定字元
 * @param szReplace 取代字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::string nsreplace(IN const std::string &szInput, IN const std::string &szKey, IN const std::string &szReplace);
/**
 * @brief 取得取代後的字串, 寬字元版本
 * @param szInput 輸入字串
 * @param szKey 指定字元
 * @param szReplace 取代字串
 * @return 結果字串
 * @ingroup nsedit
 */
std::wstring nsreplace(IN const std::wstring &szInput, IN const std::wstring &szKey, IN const std::wstring &szReplace);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------