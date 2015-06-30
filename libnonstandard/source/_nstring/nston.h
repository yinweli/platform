/**
 * @file nston.h
 * @note 字串轉換數值
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _NSTON
#define _NSTON
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#ifndef UNICODE
#undef nton
#define nton ston ///< 將字串轉換成..., 在unicode編譯時, nton相當於wton, 否則就是ston @ingroup nston
#else
#undef nton
#define nton wton ///< 將字串轉換成..., 在unicode編譯時, nton相當於wton, 否則就是ston @ingroup nston
#endif
//-----------------------------------------------------------------------------
/**
 * @brief 將字串轉換成 bool
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT bool &r);
/**
 * @brief 將字串轉換成 bool, 寬字元版本
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT bool &r);
/**
 * @brief 將字串轉換成 char
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT char &r);
/**
 * @brief 將字串轉換成 char, 寬字元版本
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT char &r);
/**
 * @brief 將字串轉換成 unsigned char
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT unsigned char &r);
/**
 * @brief 將字串轉換成 unsigned char, 寬字元版本
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT unsigned char &r);
/**
 * @brief 將字串轉換成 short
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT short &r);
/**
 * @brief 將字串轉換成 short, 寬字元版本
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT short &r);
/**
 * @brief 將字串轉換成 unsigned short
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT unsigned short &r);
/**
 * @brief 將字串轉換成 unsigned short, 寬字元版本
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT unsigned short &r);
/**
 * @brief 將字串轉換成 long
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT long &r);
/**
 * @brief 將字串轉換成 long, 寬字元版本
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT long &r);
/**
 * @brief 將字串轉換成 unsigned long
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT unsigned long &r);
/**
 * @brief 將字串轉換成 unsigned long, 寬字元版本
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT unsigned long &r);
/**
 * @brief 將字串轉換成 int
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT int &r);
/**
 * @brief 將字串轉換成 int, 寬字元版本
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT int &r);
/**
 * @brief 將字串轉換成 unsigned int
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT unsigned int &r);
/**
 * @brief 將字串轉換成 unsigned long, 寬字元版本
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT unsigned int &r);
/**
 * @brief 將字串轉換成 __int64
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT __int64 &r);
/**
 * @brief 將字串轉換成 __int64, 寬字元版本
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT __int64 &r);
/**
 * @brief 將字串轉換成 unsigned __int64
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT unsigned __int64 &r);
/**
 * @brief 將字串轉換成 unsigned long, 寬字元版本
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT unsigned __int64 &r);
/**
 * @brief 將字串轉換成 float
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT float &r);
/**
 * @brief 將字串轉換成 float, 寬字元版本
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT float &r);
/**
 * @brief 將字串轉換成 double
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT double &r);
/**
 * @brief 將字串轉換成 double, 寬字元版本
 * @param s 字串
 * @param r 轉換結果
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT double &r);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------