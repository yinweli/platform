/**
 * @file nsedit.h
 * @note �r��s��
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
 * @brief ���o�r��, �p�G��J�r���Y�����O���w�r��, �N���J���w�r����Y��
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::string insthand(IN const std::string &szInput, IN const std::string &szKey);
/**
 * @brief ���o�r��, �p�G��J�r���Y�����O���w�r��, �N���J���w�r����Y��, �e�r������
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::wstring insthand(IN const std::wstring &szInput, IN const std::wstring &szKey);
/**
 * @brief ���o�r��, �p�G�r��������O���w�r��, �N���J���w�r������
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::string insttail(IN const std::string &szInput, IN const std::string &szKey);
/**
 * @brief ���o�r��, �p�G�r��������O���w�r��, �N���J���w�r������, �e�r������
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::wstring insttail(IN const std::wstring &szInput, IN const std::wstring &szKey);
/**
 * @brief ���o�r��, �p�G�r���Y�����O���w�r��, �N���J���w�r����Y��
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::string insthandtail(IN const std::string &szInput, IN const std::string &szKey);
/**
 * @brief ���o�r��, �p�G�r���Y�����O���w�r��, �N���J���w�r����Y��, �e�r������
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::wstring insthandtail(IN const std::wstring &szInput, IN const std::wstring &szKey);
/**
 * @brief ���o�r��, �p�G�r���Y���O���w�r��, �N�q�Y���h�����w�r��
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::string trimhand(IN const std::string &szInput, IN const std::string &szKey);
/**
 * @brief ���o�r��, �p�G�r���Y���O���w�r��, �N�q�Y���h�����w�r��, �e�r������
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::wstring trimhand(IN const std::wstring &szInput, IN const std::wstring &szKey);
/**
 * @brief ���o�r��, �p�G�r������O���w�r��, �N�q�����h�����w�r��
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::string trimtail(IN const std::string &szInput, IN const std::string &szKey);
/**
 * @brief ���o�r��, �p�G�r������O���w�r��, �N�q�����h�����w�r��, �e�r������
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::wstring trimtail(IN const std::wstring &szInput, IN const std::wstring &szKey);
/**
 * @brief ���o�r��, �p�G�r���Y���O���w�r��, �N�q�Y���h�����w�r��
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::string trimhandtail(IN const std::string &szInput, IN const std::string &szKey);
/**
 * @brief ���o�r��, �p�G�r���Y���O���w�r��, �N�q�Y���h�����w�r��, �e�r������
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::wstring trimhandtail(IN const std::wstring &szInput, IN const std::wstring &szKey);
/**
 * @brief ���o�h���r���Y���ťի᪺�r��
 * @param szInput ��J�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::string trimhandspace(IN const std::string &szInput);
/**
 * @brief ���o�h���r���Y���ťի᪺�r��, �e�r������
 * @param szInput ��J�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::wstring trimhandspace(IN const std::wstring &szInput);
/**
 * @brief ���o�h���r������ťի᪺�r��
 * @param szInput ��J�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::string trimtailspace(IN const std::string &szInput);
/**
 * @brief ���o�h���r������ťի᪺�r��, �e�r������
 * @param szInput ��J�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::wstring trimtailspace(IN const std::wstring &szInput);
/**
 * @brief ���o�h���r���Y���ťի᪺�r��
 * @param szInput ��J�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::string trimhandtailspace(IN const std::string &szInput);
/**
 * @brief ���o�h���r���Y���ťի᪺�r��, �e�r������
 * @param szInput ��J�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::wstring trimhandtailspace(IN const std::wstring &szInput);
/**
 * @brief ���o�I�h���w�r���᪺�r��
 * @param szInput ��J�r��
 * @param Key ���w�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::string nstruncate(IN const std::string &szInput, IN std::string::value_type Key);
/**
 * @brief ���o�I�h���w�r���᪺�r��, �e�r������
 * @param szInput ��J�r��
 * @param Key ���w�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::wstring nstruncate(IN const std::wstring &szInput, IN std::wstring::value_type Key);
/**
 * @brief ���o���N�᪺�r��
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @param szReplace ���N�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::string nsreplace(IN const std::string &szInput, IN const std::string &szKey, IN const std::string &szReplace);
/**
 * @brief ���o���N�᪺�r��, �e�r������
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @param szReplace ���N�r��
 * @return ���G�r��
 * @ingroup nsedit
 */
std::wstring nsreplace(IN const std::wstring &szInput, IN const std::wstring &szKey, IN const std::wstring &szReplace);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------