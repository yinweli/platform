/**
 * @file threadlock.h
 * @note 執行緒同步鎖類別
 * @author yinweli
 */
/**
 * @page 如何使用threadlock
 * threadlock用於執行緒的同步鎖自動化工具\n\n
 * 在要鎖定的地方以同步鎖指標為參數建立 C_ThreadLock 物件就可以了\n\n
 * --------------------------------------------------\n
 * Header           : threadlock.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref threadlock\n
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
 * @brief 執行緒同步鎖類別
 * @ingroup threadlock
 */
class C_ThreadLock
{
private:
	//-------------------------------------
	CRITICAL_SECTION *m_pLock; ///< 同步鎖指標
	//-------------------------------------

public:
	//-------------------------------------
	C_ThreadLock(IN CRITICAL_SECTION *pLock);
	C_ThreadLock(IN const CRITICAL_SECTION *pLock);
	virtual ~C_ThreadLock();
	//-------------------------------------
	/**
	 * @brief 解開同步鎖
	 */
	void Unlock();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------