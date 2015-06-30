/**
 * @file consoleargv.h
 * @note �D���x�{���Ѽ����O
 * @author yinweli
 */
/**
 * @page �p��ϥ�consoleargv
 * consoleargv�Ψ����UŪ���D���x�{���_�l�Ѽ�(�]�N�Omain�禡�̱a�Ӫ����ǰѼƦC)\n
 * �u�n�إ� C_ConsoleArgv �����Hmain�禡���ѼƩI�s C_ConsoleArgv.Initialize() �禡�N�i�H�F\n\n
 * --------------------------------------------------\n
 * Header           : consoleargv.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref consoleargv
 */
/** @defgroup consoleargv */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CONSOLEARGV
#define _CONSOLEARGV
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\argument\argument.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �D���x�{���Ѽ����O
 * @ingroup consoleargv
 */
class C_ConsoleArgv : public C_Argv
{
public:
	//-------------------------------------
	C_ConsoleArgv(IN unsigned long argc, IN char *argv[]);
	C_ConsoleArgv(IN unsigned long argc, IN wchar_t *argv[]);
	virtual ~C_ConsoleArgv();
	//-------------------------------------
	/**
	 * @brief ���o�����ɸ��|
	 * @return �����ɸ��|
	 */
	nstring ExePath() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------