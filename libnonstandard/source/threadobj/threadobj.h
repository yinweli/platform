/**
 * @file threadobj.h
 * @note 執行緒類別
 * @author yinweli
 */
/**
 * @page 如何使用threadobj
 * threadobj用於執行緒的關閉控制\n\n
 * 在建立執行緒前, 先建立 C_ThreadMgr 物件, 然後呼叫 C_ThreadMgr.Create() 函式來建立執行緒\n
 * 接著在執行緒函式的最前面以傳入的執行參數建立 C_ThreadObj 物件\n
 * 執行緒執行期間可以呼叫 C_ThreadObj.IsShutdown() 來確定是否有通知要關閉執行緒\n
 * 其他執行緒(或是主執行緒)可以呼叫 C_ThreadMgr.Shutdown() 來關閉這個管理器底下的執行緒\n
 * 當執行緒結束導致 C_ThreadObj 物件解構時會通知 C_ThreadMgr 有個執行緒已經結束\n
 * 但是要注意, 如果管理器比其管理的物件還要早被解構, 就會造成程式錯誤\n\n
 * --------------------------------------------------\n
 * Header           : thread.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref threadobj\n
 */
/** @defgroup threadobj */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _THREADOBJ
#define _THREADOBJ
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\argument\argument.h"
#include "..\threadlock\threadlock.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
class C_ThreadMgr;
//-----------------------------------------------------------------------------
/**
 * @brief 執行緒類別
 * @ingroup threadobj
 */
class C_ThreadObj
{
private:
	//-------------------------------------
	C_ThreadMgr *m_pThreadMgr; ///< 執行緒管理器指標
	unsigned long m_ulThreadID; ///< 執行緒編號
	//-------------------------------------

public:
	//-------------------------------------
	C_ThreadObj(IN void *param);
	virtual ~C_ThreadObj();
	//-------------------------------------
	operator bool () const;
	//-------------------------------------
	/**
	 * @brief 清除參數
	 */
	void ClrParam();
	/**
	 * @brief 設定參數
	 * @param szName 參數名稱
	 * @param ccParam 參數值
	 */
	void SetParam(IN const nstring &szName, IN const C_Argu &ccParam);
	/**
	 * @brief 刪除參數
	 * @param szName 參數名稱
	 */
	void DelParam(IN const nstring &szName);
	/**
	 * @brief 取得參數
	 * @param szName 參數名稱
	 * @param ccParam 參數值
	 * @return true表示成功, false則否
	 */
	bool GetParam(IN const nstring &szName, OUT C_Argu &ccParam) const;
	/**
	 * @brief 是否要關閉執行緒
	 * @return true表示要關閉執行緒, false則否
	 */
	bool IsShutdown() const;
	/**
	 * @brief 取得執行緒編號
	 * @return 執行緒編號
	 */
	unsigned long ThreadID() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 管理器類別
 * @ingroup threadobj
 */
class C_ThreadMgr
{
	//-------------------------------------
	friend class C_ThreadObj;
	//-------------------------------------

private:
	//-------------------------------------
	std::map<unsigned long, bool> m_Thread; ///< 執行緒編號列表 <執行緒編號, 關閉旗標>
	std::map<nstring, C_Argu> m_Param; ///< 參數列表
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

private:
	//-------------------------------------
	/**
	 * @brief 新增執行緒編號
	 * @param ulThreadID 執行緒編號
	 */
	void AddThreadID(IN unsigned long ulThreadID);
	/**
	 * @brief 刪除執行緒編號
	 * @param ulThreadID 執行緒編號
	 */
	void DelThreadID(IN unsigned long ulThreadID);
	/**
	 * @brief 取得執行旗標
	 * @param ulThreadID 執行緒編號
	 * @return true表示繼續執行, false則否
	 */
	bool IsShutdown(IN unsigned long ulThreadID) const;
	//-------------------------------------

public:
	//-------------------------------------
	typedef unsigned (__stdcall *LPFN_Thread) (void *); ///< 執行緒函式指標形態
	//-------------------------------------

public:
	//-------------------------------------
	C_ThreadMgr();
	virtual ~C_ThreadMgr();
	//-------------------------------------
	/**
	 * @brief 建立執行緒
	 * @param pfThread 執行緒函式指標
	 * @return true表示建立成功, false則否
	 */
	bool Create(IN LPFN_Thread pfThread);
	/**
	 * @brief 關閉執行緒
	 */
	void Shutdown();
	/**
	 * @brief 關閉執行緒
	 * @param ulThreadID 執行緒編號
	 */
	void Shutdown(IN unsigned long ulThreadID);
	/**
	 * @brief 清除參數
	 */
	void ClrParam();
	/**
	 * @brief 設定參數
	 * @param szName 參數名稱
	 * @param ccParam 參數值
	 */
	void SetParam(IN const nstring &szName, IN const C_Argu &ccParam);
	/**
	 * @brief 刪除參數
	 * @param szName 參數名稱
	 */
	void DelParam(IN const nstring &szName);
	/**
	 * @brief 取得參數
	 * @param szName 參數名稱
	 * @param ccParam 參數值
	 * @return true表示成功, false則否
	 */
	bool GetParam(IN const nstring &szName, OUT C_Argu &ccParam) const;
	/**
	 * @brief 取得執行緒列表
	 * @return 執行緒列表
	 */
	std::set<unsigned long> List() const;
	/**
	 * @brief 取得執行緒數量
	 * @return 執行緒數量
	 */
	unsigned long Size() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------