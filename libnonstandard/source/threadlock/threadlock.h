/**
 * @file threadlock.h
 * @note ������P�B�����O
 * @author yinweli
 */
/**
 * @page �p��ϥ�threadlock
 * threadlock�Ω��������P�B��۰ʤƤu��\n\n
 * �b�n��w���a��H�P�B����Ь��Ѽƫإ� C_ThreadLock ����N�i�H�F\n\n
 * --------------------------------------------------\n
 * Header           : threadlock.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref threadlock\n
 */
/** @defgroup threadlock */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _THREADLOCK
#define _THREADLOCK
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ������P�B�����O
 * @ingroup threadlock
 */
class C_ThreadLock
{
private:
	//-------------------------------------
	CRITICAL_SECTION *m_pLock; ///< �P�B�����
	//-------------------------------------

public:
	//-------------------------------------
	C_ThreadLock(IN CRITICAL_SECTION *pLock);
	C_ThreadLock(IN const CRITICAL_SECTION *pLock);
	virtual ~C_ThreadLock();
	//-------------------------------------
	/**
	 * @brief �Ѷ}�P�B��
	 */
	void Unlock();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------