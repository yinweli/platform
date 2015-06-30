/**
 * @file nsconv.h
 * @note �r���r���P�e�r���ഫ
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
#define nsconvn nsconvna ///< �ഫSystem::String��C++�r��w�q, �bunicode�sĶ��, nsconvn�۷��nsconvaw, �_�h�N�Onsconvna @ingroup nsconv
#else
#define nsconvn nsconvaw ///< �ഫSystem::String��C++�r��w�q, �bunicode�sĶ��, nsconvn�۷��nsconvaw, �_�h�N�Onsconvna @ingroup nsconv
#endif
//-----------------------------------------------------------------------------
/**
 * @brief �ഫstd::string��std::wstring
 * @param szInput ��J�r��
 * @return ��X�r��
 * @ingroup nsconv
 */
std::wstring nsconv(IN const std::string &szInput);
/**
 * @brief �ഫstd::wstring��std::string
 * @param szInput ��J�r��
 * @return ��X�r��
 * @ingroup nsconv
 */
std::string nsconv(IN const std::wstring &szInput);
/**
 * @brief �ഫSystem::String��std::string
 * @param szInput ��J�r��
 * @return ��X�r��
 * @ingroup nsconv
 */
std::string nsconvna(IN System::String ^szInput);
/**
 * @brief �ഫSystem::String��std::wstring
 * @param szInput ��J�r��
 * @return ��X�r��
 * @ingroup nsconv
 */
std::wstring nsconvaw(IN System::String ^szInput);
/**
 * @brief �ഫstd::string��System::String
 * @param szInput ��J�r��
 * @return ��X�r��
 * @ingroup nsconv
 */
System::String ^nsconvc(IN const std::string &szInput);
/**
 * @brief �ഫstd::wstring��System::String
 * @param szInput ��J�r��
 * @return ��X�r��
 * @ingroup nsconv
 */
System::String ^nsconvc(IN const std::wstring &szInput);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------