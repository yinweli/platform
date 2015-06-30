/**
 * @file nsconv.h
 * @note 字串單字元與寬字元轉換
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _NSCONV
#define _NSCONV
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#ifndef UNICODE
#define nsconvn nsconvna ///< 轉換System::String為C++字串定義, 在unicode編譯時, nsconvn相當於nsconvaw, 否則就是nsconvna @ingroup nsconv
#else
#define nsconvn nsconvaw ///< 轉換System::String為C++字串定義, 在unicode編譯時, nsconvn相當於nsconvaw, 否則就是nsconvna @ingroup nsconv
#endif
//-----------------------------------------------------------------------------
/**
 * @brief 轉換std::string為std::wstring
 * @param szInput 輸入字串
 * @return 輸出字串
 * @ingroup nsconv
 */
std::wstring nsconv(IN const std::string &szInput);
/**
 * @brief 轉換std::wstring為std::string
 * @param szInput 輸入字串
 * @return 輸出字串
 * @ingroup nsconv
 */
std::string nsconv(IN const std::wstring &szInput);
/**
 * @brief 轉換System::String為std::string
 * @param szInput 輸入字串
 * @return 輸出字串
 * @ingroup nsconv
 */
std::string nsconvna(IN System::String ^szInput);
/**
 * @brief 轉換System::String為std::wstring
 * @param szInput 輸入字串
 * @return 輸出字串
 * @ingroup nsconv
 */
std::wstring nsconvaw(IN System::String ^szInput);
/**
 * @brief 轉換std::string為System::String
 * @param szInput 輸入字串
 * @return 輸出字串
 * @ingroup nsconv
 */
System::String ^nsconvc(IN const std::string &szInput);
/**
 * @brief 轉換std::wstring為System::String
 * @param szInput 輸入字串
 * @return 輸出字串
 * @ingroup nsconv
 */
System::String ^nsconvc(IN const std::wstring &szInput);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------