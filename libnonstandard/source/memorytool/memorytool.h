/**
 * @file memorytool.h
 * @note �O����u��t�C�禡
 * @author yinweli
 */
/**
 * @page �p��ϥ�memorytool
 * memorytool�����禡�Ω�O����ާ@\n\n
 * --------------------------------------------------\n
 * Header           : memorytool.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref memorytool
 */
/** @defgroup memorytool */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _MEMORYTOOL
#define _MEMORYTOOL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#define ROUNDUP(s, a) (((unsigned long)(s) + ((a) - 1)) &~ ((a) - 1)) ///< �p��s�ȹ��a�ȫ᪺���� @ingroup memorytool
//-----------------------------------------------------------------------------
/**
 * @brief ���`�קK�禡
 * @note �קKDebug�Ҧ��U�ϥΤF�Ӧh�� new / malloc ����y�������`�����`, �u��VC++6.0�H�U�|�y�������~\n
 *       ���O�ϥ�_CrtSetBreakAlloc���\��|����
 * @ingroup memorytool
 */
void AvoidAllocMemoryAbnormal();
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------