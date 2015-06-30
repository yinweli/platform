/**
 * @file memoryleak.h
 * @note �O���鬪�|�����]�w�禡
 * @author yinweli
 */
/**
 * @page �p��ϥ�memoryleak
 * memoryleak�����禡�Ω�]�w�O���鬪�|�����ت��a\n
 * �b�{���}�l���a��(�q�`�O main() �禡���}�Y)�I�s InitMemDbg() �禡�ӳ]�w��X���O������m\n
 * �w�]����X���O������m�b�P�����ɦP�ؿ����U�� memoryleak_warning.log �P memoryleak_error.log\n
 * �o�ӰO���鬪�|�������\��u�bdebug�����U����\n\n
 * --------------------------------------------------\n
 * Header           : memoryleak.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref memoryleak
 */
/** @defgroup memoryleak */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _MEMORYLEAK
#define _MEMORYLEAK
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �]�w�O���鬪�|�����\��禡
 * @param szFilePath �O�������|
 * @ingroup memoryleak
 */
void InitMemDbg(IN const nstring &szFilePath = __T(""));
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------