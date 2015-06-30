/**
 * @file nstox.h
 * @note 计锣传﹃
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _NSTOX
#define _NSTOX
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#ifndef UNICODE
#undef ntox
#define ntox ntos ///< 盢...锣传Θ﹃, unicode絪亩, ntox讽ntow, 玥碞琌ntos @ingroup nstox
#define ntob ntobs ///< 盢じ计锣传Θじ﹃, unicode絪亩, ntob讽ntobw, 玥碞琌ntobs @ingroup nstox
#else
#undef ntox
#define ntox ntow ///< 盢...锣传Θ﹃, unicode絪亩, ntox讽ntow, 玥碞琌ntos @ingroup nstox
#define ntob ntobw ///< 盢じ计锣传Θじ﹃, unicode絪亩, ntob讽ntobw, 玥碞琌ntobs @ingroup nstox
#endif
//-----------------------------------------------------------------------------
#define noct(x) ntox(x, 8) ///< 盢计锣传8秈﹃
#define nhex(x) ntox(x, 16) ///< 盢计锣传16秈﹃
//-----------------------------------------------------------------------------
/**
 * @brief 盢 bool 锣传Θ﹃
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::string ntos(IN bool x, IN int radix = 10);
/**
 * @brief 盢 bool 锣传Θ﹃, 糴じセ
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::wstring ntow(IN bool x, IN int radix = 10);
/**
 * @brief 盢 char 锣传Θ﹃
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::string ntos(IN char x, IN int radix = 10);
/**
 * @brief 盢 char 锣传Θ﹃, 糴じセ
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::wstring ntow(IN char x, IN int radix = 10);
/**
 * @brief 盢 unsigned char 锣传Θ﹃
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::string ntos(IN unsigned char x, IN int radix = 10);
/**
 * @brief 盢 unsigned char 锣传Θ﹃, 糴じセ
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::wstring ntow(IN unsigned char x, IN int radix = 10);
/**
 * @brief 盢 short 锣传Θ﹃
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::string ntos(IN short x, IN int radix = 10);
/**
 * @brief 盢 short 锣传Θ﹃, 糴じセ
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::wstring ntow(IN short x, IN int radix = 10);
/**
 * @brief 盢 unsigned short 锣传Θ﹃
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::string ntos(IN unsigned short x, IN int radix = 10);
/**
 * @brief 盢 unsigned short 锣传Θ﹃, 糴じセ
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::wstring ntow(IN unsigned short x, IN int radix = 10);
/**
 * @brief 盢 long 锣传Θ﹃
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::string ntos(IN long x, IN int radix = 10);
/**
 * @brief 盢 long 锣传Θ﹃, 糴じセ
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::wstring ntow(IN long x, IN int radix = 10);
/**
 * @brief 盢 unsigned long 锣传Θ﹃
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::string ntos(IN unsigned long x, IN int radix = 10);
/**
 * @brief 盢 unsigned long 锣传Θ﹃, 糴じセ
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::wstring ntow(IN unsigned long x, IN int radix = 10);
/**
 * @brief 盢 int 锣传Θ﹃
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::string ntos(IN int x, IN int radix = 10);
/**
 * @brief 盢 int 锣传Θ﹃, 糴じセ
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::wstring ntow(IN int x, IN int radix = 10);
/**
 * @brief 盢 unsigned int 锣传Θ﹃
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::string ntos(IN unsigned int x, IN int radix = 10);
/**
 * @brief 盢 unsigned int 锣传Θ﹃, 糴じセ
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::wstring ntow(IN unsigned int x, IN int radix = 10);
/**
 * @brief 盢 __int64 锣传Θ﹃
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::string ntos(IN __int64 x, IN int radix = 10);
/**
 * @brief 盢 __int64 锣传Θ﹃, 糴じセ
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::wstring ntow(IN __int64 x, IN int radix = 10);
/**
 * @brief 盢 unsigned __int64 锣传Θ﹃
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::string ntos(IN unsigned __int64 x, IN int radix = 10);
/**
 * @brief 盢 unsigned __int64 锣传Θ﹃, 糴じセ
 * @param x 计
 * @param radix 膀计(2 ~ 36)
 * @return ﹃
 * @ingroup nstox
 */
std::wstring ntow(IN unsigned __int64 x, IN int radix = 10);
/**
 * @brief 盢 float 锣传Θ﹃
 * @param x 计
 * @param count ﹃璶陪ボ计碭
 * @return ﹃
 * @ingroup nstox
 */
std::string ntos(IN float x, IN int count);
/**
 * @brief 盢 float 锣传Θ﹃, 糴じセ
 * @param x 计
 * @param count ﹃璶陪ボ计碭
 * @return ﹃
 * @ingroup nstox
 */
std::wstring ntow(IN float x, IN int count);
/**
 * @brief 盢 float 锣传Θ﹃
 * @param x 计
 * @return ﹃
 * @ingroup nstox
 */
std::string ntos(IN float x);
/**
 * @brief 盢 float 锣传Θ﹃, 糴じセ
 * @param x 计
 * @return ﹃
 * @ingroup nstox
 */
std::wstring ntow(IN float x);
/**
 * @brief 盢 double 锣传Θ﹃
 * @param x 计
 * @param count ﹃璶陪ボ计碭
 * @return ﹃
 * @ingroup nstox
 */
std::string ntos(IN double x, IN int count);
/**
 * @brief 盢 double 锣传Θ﹃, 糴じセ
 * @param x 计
 * @param count ﹃璶陪ボ计碭
 * @return ﹃
 * @ingroup nstox
 */
std::wstring ntow(IN double x, IN int count);
/**
 * @brief 盢 double 锣传Θ﹃
 * @param x 计
 * @return ﹃
 * @ingroup nstox
 */
std::string ntos(IN double x);
/**
 * @brief 盢 double 锣传Θ﹃, 糴じセ
 * @param x 计
 * @return ﹃
 * @ingroup nstox
 */
std::wstring ntow(IN double x);
/**
 * @brief 盢じ计锣传Θじ﹃
 * @param bytes じ
 * @return じ﹃
 * @ingroup nstox
 */
std::string ntobs(IN unsigned int bytes);
/**
 * @brief 盢じ计锣传Θじ﹃, 糴じセ
 * @param bytes じ
 * @return じ﹃
 * @ingroup nstox
 */
std::wstring ntobw(IN unsigned int bytes);
/**
 * @brief 盢じ计锣传Θじ﹃
 * @param bytes じ
 * @return じ﹃
 * @ingroup nstox
 */
std::string ntobs(IN unsigned __int64 bytes);
/**
 * @brief 盢じ计锣传Θじ﹃, 糴じセ
 * @param bytes じ
 * @return じ﹃
 * @ingroup nstox
 */
std::wstring ntobw(IN unsigned __int64 bytes);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------