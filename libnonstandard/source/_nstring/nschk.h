/**
 * @file nschk.h
 * @note ﹃浪琩
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _NSCHK
#define _NSCHK
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 浪琩┮Τじ琌常琌璣ゅ
 * @param szInput ﹃
 * @return trueボ常琌璣ゅ, false玥
 * @ingroup nschk
 */
bool alphachk(IN const std::string &szInput);
/**
 * @brief 浪琩┮Τじ琌常琌璣ゅ, 糴じセ
 * @param szInput ﹃
 * @return trueボ常琌璣ゅ, false玥
 * @ingroup nschk
 */
bool alphachk(IN const std::wstring &szInput);
/**
 * @brief 浪琩┮Τじ琌常琌计
 * @param szInput ﹃
 * @return trueボ常琌计, false玥
 * @ingroup nschk
 */
bool digitchk(IN const std::string &szInput);
/**
 * @brief 浪琩┮Τじ琌常琌计, 糴じセ
 * @param szInput ﹃
 * @return trueボ常琌计, false玥
 * @ingroup nschk
 */
bool digitchk(IN const std::wstring &szInput);
/**
 * @brief 浪琩┮Τじ琌常琌璣ゅ籔计
 * @param szInput ﹃
 * @return trueボ常琌璣ゅ籔计, false玥
 * @ingroup nschk
 */
bool alphadigitchk(IN const std::string &szInput);
/**
 * @brief 浪琩┮Τじ琌常琌璣ゅ籔计, 糴じセ
 * @param szInput ﹃
 * @return trueボ常琌璣ゅ籔计, false玥
 * @ingroup nschk
 */
bool alphadigitchk(IN const std::wstring &szInput);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------