/**
 * @file nstok.h
 * @note �r�����
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
 * @brief ���o�r����ε��G
 * @param szInput ��J�r��
 * @param szTok �w�ɦr��
 * @return ���G�C��
 * @ingroup nstok
 */
std::vector<std::string> nstok(IN const std::string &szInput, IN const std::string &szTok);
/**
 * @brief ���o�r����ε��G, �e�r������
 * @param szInput ��J�r��
 * @param szTok �w�ɦr��
 * @return ���G�C��
 * @ingroup nstok
 */
std::vector<std::wstring> nstok(IN const std::wstring &szInput, IN const std::wstring &szTok);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------