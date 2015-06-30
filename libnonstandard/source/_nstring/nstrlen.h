/**
 * @file nstrlen.h
 * @note ﹃计, 璸衡
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _NSTRLEN
#define _NSTRLEN
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 璸衡﹃计
 * @param szInput 块﹃
 * @return ﹃计
 * @ingroup nslen
 */
unsigned long nscount(IN const std::string &szInput);
/**
 * @brief 璸衡﹃计, 糴じセ
 * @param szInput 块﹃
 * @return ﹃计
 * @ingroup nslen
 */
unsigned long nscount(IN const std::wstring &szInput);
/**
 * @brief 璸衡﹃じ计
 * @param szInput 块﹃
 * @return ﹃じ计
 * @ingroup nslen
 */
unsigned long nsbytes(IN const std::string &szInput);
/**
 * @brief 璸衡﹃じ计, 糴じセ
 * @param szInput 块﹃
 * @return ﹃じ计
 * @ingroup nslen
 */
unsigned long nsbytes(IN const std::wstring &szInput);
/**
 * @brief multi-byteよΑ璸衡﹃じ计
 * @param szInput 块﹃
 * @return ﹃じ计
 * @ingroup nslen
 */
unsigned long mbbytes(IN const std::string &szInput);
/**
 * @brief multi-byteよΑ璸衡﹃じ计, 糴じセ
 * @param szInput 块﹃
 * @return ﹃じ计
 * @ingroup nslen
 */
unsigned long mbbytes(IN const std::wstring &szInput);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------