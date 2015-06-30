/**
 * @file taskschedule.h
 * @note 排程任務類別
 * @author yinweli
 */
/**
 * @page 如何使用taskschedule
 * taskschedule用來管理執行需要定時執行處理的函式\n\n
 * 使用時先建立 C_TaskScheduleList 類別的實體, 然後定時呼叫 C_TaskScheduleList.Process() 函式讓它持續運作\n
 * 要新增排程任務時, 先準備好要執行的函式, 這個函式的原型定義在 C_TaskScheduleGeneral::LPFN_Process 以及 C_TaskScheduleTemplate::LPFN_Process 中, 事實上這兩個定義是一樣的\n
 * 一個正確的函式將會長的像這樣\n\n
 * void 函式名稱()\n\n
 * 這個函式是全域函式, 類別成員函式, 類別成員靜態函式都可以\n\n
 * 呼叫 C_TaskScheduleList.Add() 函式來新增排程任務\n
 * 呼叫 C_TaskScheduleList.Del() 函式來刪除排程任務\n
 * 呼叫 C_TaskScheduleList.Set() 函式來設定排程任務的排程時間\n\n
 * --------------------------------------------------\n
 * Header           : taskschedule.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref taskschedule
 */
/** @defgroup taskschedule */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _TASKSCHEDULE
#define _TASKSCHEDULE
//-----------------------------------------------------------------------------
#pragma comment(lib, "winmm.lib")
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 製造時間字串
 * @param lYear 年, -1表示每年執行
 * @param lMonth 月(1 ~ 12), -1表示每月執行
 * @param lMDay 日(1 ~ 31), -1表示每日執行
 * @param lWDay 周(0 ~ 6, 0表示是週日, 1表示是週一, 依此類推), 周只有在日為-1的時候才可以使用, -1表示每周幾執行
 * @param lHour 時(0 ~ 23), -1表示每時執行
 * @param lMin 分(0 ~ 59), -1表示每分執行
 * @param lSec 秒(0 ~ 59), -1表示每秒執行
 * @return 時間字串
 * @ingroup taskschedule
 */
nstring MakeSchedule(IN long lYear, IN long lMonth, IN long lMDay, IN long lWDay, IN long lHour, IN long lMin, IN long lSec);
/**
 * @brief 製造時間字串, 格式會與過濾字串一致
 * @param lYear 年, -1表示每年執行
 * @param lMonth 月(1 ~ 12), -1表示每月執行
 * @param lMDay 日(1 ~ 31), -1表示每日執行
 * @param lWDay 周(0 ~ 6, 0表示是週日, 1表示是週一, 依此類推), 周只有在日為-1的時候才可以使用, -1表示每周幾執行
 * @param lHour 時(0 ~ 23), -1表示每時執行
 * @param lMin 分(0 ~ 59), -1表示每分執行
 * @param lSec 秒(0 ~ 59), -1表示每秒執行
 * @param szFilter 過濾字串
 * @return 時間字串
 * @ingroup taskschedule
 */
nstring MakeSchedule(IN long lYear, IN long lMonth, IN long lMDay, IN long lWDay, IN long lHour, IN long lMin, IN long lSec, IN const nstring &szFilter);
//-----------------------------------------------------------------------------
/**
 * @brief 基礎排程任務類別
 * @ingroup taskschedule
 */
class C_TaskSchedule
{
protected:
	//-------------------------------------
	nstring m_szSchedule; ///< 排程時間字串, 時間格式 year/month/mday/wday/hour/min/sec
	bool m_bBlock; ///< 阻擋旗標
	//-------------------------------------

public:
	//-------------------------------------
	C_TaskSchedule(IN const nstring &schedule);
	virtual ~C_TaskSchedule();
	//-------------------------------------
	/**
	 * @brief 設定排程時間
	 * @param szSchedule 排程時間字串
	 */
	void Set(IN const nstring &szSchedule);
	/**
	 * @brief 檢查是否執行
	 * @return true表示執行, false則否
	 */
	bool Check();
	/**
	 * @brief 取得排程時間
	 * @return 排程時間字串
	 */
	nstring Schedule() const;
	//-------------------------------------
	/**
	 * @brief 定時處理
	 */
	virtual void Process() = 0;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 一般排程任務類別
 * @ingroup taskschedule
 */
class C_TaskScheduleGeneral : public C_TaskSchedule
{
public:
	//-------------------------------------
	typedef void (*LPFN_Process) (); ///< 處理函式指標
	//-------------------------------------

private:
	//-------------------------------------
	LPFN_Process m_pfProcess; ///< 處理函式指標
	//-------------------------------------

public:
	//-------------------------------------
	C_TaskScheduleGeneral(IN const nstring &schedule, IN LPFN_Process process) : C_TaskSchedule(schedule), m_pfProcess(process) {};
	virtual ~C_TaskScheduleGeneral() {};
	//-------------------------------------
	/**
	 * @brief 定時處理
	 */
	void Process()
	{
		if(m_pfProcess == nullptr)
			return;

		if(Check() == false)
			return;

		m_pfProcess();
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 泛形排程任務類別
 * @ingroup taskschedule
 */
template<typename _Obj> class C_TaskScheduleTemplate : public C_TaskSchedule
{
public:
	//-------------------------------------
	typedef void (_Obj::*LPFN_Process) (); ///< 處理函式指標
	//-------------------------------------

private:
	//-------------------------------------
	_Obj *m_pObject; ///< 處理物件指標
	LPFN_Process m_pfProcess; ///< 處理函式指標
	//-------------------------------------

public:
	//-------------------------------------
	C_TaskScheduleTemplate(IN const nstring &schedule, IN _Obj &object, IN LPFN_Process process) : C_TaskSchedule(schedule), m_pObject(&object), m_pfProcess(process) {};
	virtual ~C_TaskScheduleTemplate() {};
	//-------------------------------------
	/**
	 * @brief 定時處理
	 */
	void Process()
	{
		if(m_pObject == nullptr)
			return;

		if(m_pfProcess == nullptr)
			return;

		if(Check() == false)
			return;

		(m_pObject->*m_pfProcess)();
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 排程任務列表類別
 * @ingroup taskschedule
 */
class C_TaskScheduleList
{
private:
	//-------------------------------------
	std::map<nstring, C_TaskSchedule *> m_Task; ///< 排程任務列表 <排程任務名稱, 排程任務指標>
	//-------------------------------------

public:
	//-------------------------------------
	C_TaskScheduleList();
	virtual ~C_TaskScheduleList();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 新增排程任務(靜態函式版本)
	 * @param szName 排程任務名稱
	 * @param lYear 年, -1表示每年執行
	 * @param lMonth 月(1 ~ 12), -1表示每月執行
	 * @param lMDay 日(1 ~ 31), -1表示每日執行
	 * @param lWDay 周(0 ~ 6, 0表示是週日, 1表示是週一, 依此類推), 周只有在日為-1的時候才可以使用, -1表示每周幾執行
	 * @param lHour 時(0 ~ 23), -1表示每時執行
	 * @param lMin 分(0 ~ 59), -1表示每分執行
	 * @param lSec 秒(0 ~ 59), -1表示每秒執行
	 * @param pfProcess 處理函式指標
	 * @return true表示成功, false則否
	 */
	bool Add(IN const nstring &szName, IN long lYear, IN long lMonth, IN long lMDay, IN long lWDay, IN long lHour, IN long lMin, IN long lSec, IN C_TaskScheduleGeneral::LPFN_Process pfProcess)
	{
		if(szName.empty())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

		if(pfProcess == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("process null(") + szName + __T(")"));

		if(m_Task.find(szName) != m_Task.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + szName + __T(")"));

		C_TaskSchedule *pProcess = nstdnew C_TaskScheduleGeneral(MakeSchedule(lYear, lMonth, lMDay, lWDay, lHour, lMin, lSec), pfProcess);

		if(pProcess == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create task failed(") + szName + __T(")"));

		m_Task[szName] = pProcess;

		return true;
	};
	/**
	 * @brief 新增排程任務(成員函式版本)
	 * @param szName 排程任務名稱
	 * @param lYear 年, -1表示每年執行
	 * @param lMonth 月(1 ~ 12), -1表示每月執行
	 * @param lMDay 日(1 ~ 31), -1表示每日執行
	 * @param lWDay 周(0 ~ 6, 0表示是週日, 1表示是週一, 依此類推), 周只有在日為-1的時候才可以使用, -1表示每周幾執行
	 * @param lHour 時(0 ~ 23), -1表示每時執行
	 * @param lMin 分(0 ~ 59), -1表示每分執行
	 * @param lSec 秒(0 ~ 59), -1表示每秒執行
	 * @param Object 處理物件
	 * @param pfProcess 處理函式指標
	 * @return true表示成功, false則否
	 */
	template<typename _Obj> bool Add(IN const nstring &szName, IN long lYear, IN long lMonth, IN long lMDay, IN long lWDay, IN long lHour, IN long lMin, IN long lSec, IN _Obj &Object, IN typename C_TaskScheduleTemplate<_Obj>::LPFN_Process pfProcess)
	{
		if(szName.empty())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

		if(pfProcess == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("process null(") + szName + __T(")"));

		if(m_Task.find(szName) != m_Task.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + szName + __T(")"));

		C_TaskSchedule *pProcess = nstdnew C_TaskScheduleTemplate<_Obj>(MakeSchedule(lYear, lMonth, lMDay, lWDay, lHour, lMin, lSec), Object, pfProcess);

		if(pProcess == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create task failed(") + szName + __T(")"));

		m_Task[szName] = pProcess;

		return true;
	};
	/**
	 * @brief 刪除排程任務
	 * @param szName 排程任務名稱
	 */
	void Del(IN const nstring &szName);
	/**
	 * @brief 設定排程時間
	 * @param szName 排程任務名稱
	 * @param lYear 年, -1表示每年執行
	 * @param lMonth 月(1 ~ 12), -1表示每月執行
	 * @param lMDay 日(1 ~ 31), -1表示每日執行
	 * @param lWDay 周(0 ~ 6, 0表示是週日, 1表示是週一, 依此類推), 周只有在日為-1的時候才可以使用, -1表示每周幾執行
	 * @param lHour 時(0 ~ 23), -1表示每時執行
	 * @param lMin 分(0 ~ 59), -1表示每分執行
	 * @param lSec 秒(0 ~ 59), -1表示每秒執行
	 */
	void Set(IN const nstring &szName, IN long lYear, IN long lMonth, IN long lMDay, IN long lWDay, IN long lHour, IN long lMin, IN long lSec);
	/**
	 * @brief 定時處理
	 */
	void Process();
	/**
	 * @brief 取得排程任務列表
	 * @return 排程任務列表
	 */
	std::map<nstring, nstring> List() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------