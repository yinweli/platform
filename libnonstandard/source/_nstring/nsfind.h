/**
 * @file nsfind.h
 * @note �r��j�M
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
 * @brief �ˬd���w�r��O�_���X�{
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @return true��ܦ��X�{, false�h�_
 * @ingroup nsfind
 */
bool strfind(IN char *szInput, IN const char *szKey);
/**
 * @brief �ˬd���w�r��O�_���X�{, �e�r������
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @return true��ܦ��X�{, false�h�_
 * @ingroup nsfind
 */
bool strfind(IN wchar_t *szInput, IN const wchar_t *szKey);
/**
 * @brief �ˬd���w�r��O�_���X�{
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @return true��ܦ��X�{, false�h�_
 * @ingroup nsfind
 */
bool strfind(IN std::string &szInput, IN const char *szKey);
/**
 * @brief �ˬd���w�r��O�_���X�{, �e�r������
 * @param szInput ��J�r��
 * @param szKey ���w�r��
 * @return true��ܦ��X�{, false�h�_
 * @ingroup nsfind
 */
bool strfind(IN std::wstring &szInput, IN const wchar_t *szKey);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------