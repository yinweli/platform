/**
 * @file nscase.h
 * @note �r��j�p�g�ഫ
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
 * @brief ���o�j�p�g���઺�r��
 * @param c ��J�r��
 * @ingroup nscase
 */
char reverse(IN char c);
/**
 * @brief ���o�j�p�g���઺�r��, �e�r������
 * @param c ��J�r��
 * @ingroup nscase
 */
wchar_t wreverse(IN wchar_t c);
/**
 * @brief ���o�ഫ���p�g���r��
 * @param szInput ��J�r��
 * @return ���G�r��
 * @ingroup nscase
 */
std::string nslower(IN const std::string &szInput);
/**
 * @brief ���o�ഫ���p�g���r��, �e�r������
 * @param szInput ��J�r��
 * @return ���G�r��
 * @ingroup nscase
 */
std::wstring nslower(IN const std::wstring &szInput);
/**
 * @brief ���o�ഫ���j�g���r��
 * @param szInput ��J�r��
 * @return ���G�r��
 * @ingroup nscase
 */
std::string nsupper(IN const std::string &szInput);
/**
 * @brief ���o�ഫ���j�g���r��, �e�r������
 * @param szInput ��J�r��
 * @return ���G�r��
 * @ingroup nscase
 */
std::wstring nsupper(IN const std::wstring &szInput);
/**
 * @brief ���o�ഫ���j�p�g���઺�r��
 * @param szInput ��J�r��
 * @return ���G�r��
 * @ingroup nscase
 */
std::string nseverse(IN const std::string &szInput);
/**
 * @brief ���o�ഫ���j�p�g���઺�r��, �e�r������
 * @param szInput ��J�r��
 * @return ���G�r��
 * @ingroup nscase
 */
std::wstring nseverse(IN const std::wstring &szInput);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------