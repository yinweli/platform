/**
 * @file taskinterval.h
 * @note 間隔任務類別
 * @author yinweli
 */
/**
 * @page 如何使用taskinterval
 * taskinterval用來管理執行需要每隔多久就執行處理的函式\n\n
 * 使用時先建立 C_TaskIntervalList 類別的實體, 然後定時呼叫 C_TaskIntervalList.Process() 函式讓它持續運作\n
 * 要新增間隔任務時, 先準備好要執行的函式, 這個函式的原型定義在 C_TaskIntervalGeneral::LPFN_Process 以及 C_TaskIntervalTemplate::LPFN_Process 中, 事實上這兩個定義是一樣的\n
 * 一個正確的函式將會長的像這樣\n\n
 * void 函式名稱()\n\n
 * 這個函式是全域函式, 類別成員函式, 類別成員靜態函式都可以\n\n
 * 呼叫 C_TaskIntervalList.Add() 函式來新增間隔任務\n
 * 呼叫 C_TaskIntervalList.Del() 函式來刪除間隔任務\n
 * 呼叫 C_TaskIntervalList.Set() 函式來設定間隔任務的間隔時間\n\n
 * --------------------------------------------------\n
 * Header           : taskinterval.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref taskinterval
 */
/** @defgroup taskinterval */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _TASKINTERVAL
#define _TASKINTERVAL
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
 * @brief 基礎間隔任務類別
 * @ingroup taskinterval
 */
class C_TaskInterval
{
protected:
	//-------------------------------------
	unsigned long m_ulInterval; ///< 間隔時間
	unsigned long m_ulTimeNext; ///< 下次時間
	//-------------------------------------

public:
	//-------------------------------------
	C_TaskInterval(IN unsigned long interval);
	virtual ~C_TaskInterval();
	//-------------------------------------
	/**
	 * @brief 設定間隔時間
	 * @param ulInterval 間隔時間
	 */
	void Set(IN unsigned long ulInterval);
	/**
	 * @brief 檢查是否執行
	 * @return true表示執行, false則否
	 */
	bool Check();
	/**
	 * @brief 取得間隔時間
	 * @return 間隔時間
	 */
	unsigned long Interval() const;
	//-------------------------------------
	/**
	 * @brief 定時處理
	 */
	virtual void Process() = 0;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 一般間隔任務類別
 * @ingroup taskinterval
 */
class C_TaskIntervalGeneral : public C_TaskInterval
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
	C_TaskIntervalGeneral(IN unsigned long interval, IN LPFN_Process process) : C_TaskInterval(interval), m_pfProcess(process) {};
	virtual ~C_TaskIntervalGeneral() {}
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
 * @brief 泛形間隔任務類別
 * @ingroup taskinterval
 */
template<typename _Obj> class C_TaskIntervalTemplate : public C_TaskInterval
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
	C_TaskIntervalTemplate(IN unsigned long interval, IN _Obj &object, IN LPFN_Process process) : C_TaskInterval(interval), m_pObject(&object), m_pfProcess(process) {};
	virtual ~C_TaskIntervalTemplate() {};
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
 * @brief 間隔任務列表類別
 * @ingroup taskinterval
 */
class C_TaskIntervalList
{
private:
	//-------------------------------------
	std::map<nstring, C_TaskInterval *> m_Task; ///< 間隔任務列表 <間隔任務名稱, 間隔任務指標>
	//-------------------------------------

public:
	//-------------------------------------
	C_TaskIntervalList();
	virtual ~C_TaskIntervalList();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 定時處理
	 */
	void Process();
	/**
	 * @brief 新增間隔任務(靜態函式版本)
	 * @param szName 間隔任務名稱
	 * @param ulInterval 間隔時間, 單位是毫秒
	 * @param pfProcess 處理函式指標
	 * @return true表示成功, false則否
	 */
	bool Add(IN const nstring &szName, IN unsigned long ulInterval, IN C_TaskIntervalGeneral::LPFN_Process pfProcess)
	{
		if(szName.empty())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

		if(pfProcess == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("process null(") + szName + __T(")"));

		if(m_Task.find(szName) != m_Task.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + szName + __T(")"));

		C_TaskInterval *pProcess = nstdnew C_TaskIntervalGeneral(ulInterval, pfProcess);

		if(pProcess == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create task failed(") + szName + __T(")"));

		m_Task[szName] = pProcess;

		return true;
	};
	/**
	 * @brief 新增間隔任務(成員函式版本)
	 * @param szName 間隔任務名稱
	 * @param ulInterval 間隔時間, 單位是毫秒
	 * @param Object 處理物件
	 * @param pfProcess 處理函式指標
	 * @return true表示成功, false則否
	 */
	template<typename _Obj> bool Add(IN const nstring &szName, IN unsigned long ulInterval, IN _Obj &Object, IN typename C_TaskIntervalTemplate<_Obj>::LPFN_Process pfProcess)
	{
		if(szName.empty())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

		if(pfProcess == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("process null(") + szName + __T(")"));

		if(m_Task.find(szName) != m_Task.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + szName + __T(")"));

		C_TaskInterval *pProcess = nstdnew C_TaskIntervalTemplate<_Obj>(ulInterval, Object, pfProcess);

		if(pProcess == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create task failed(") + szName + __T(")"));

		m_Task[szName] = pProcess;

		return true;
	};
	/**
	 * @brief 刪除間隔任務
	 * @param szName 間隔任務名稱
	 */
	void Del(IN const nstring &szName);
	/**
	 * @brief 設定間隔時間
	 * @param szName 間隔任務名稱
	 * @param ulInterval 間隔時間, 單位是毫秒
	 */
	void Set(IN const nstring &szName, IN unsigned long ulInterval);
	/**
	 * @brief 取得間隔時間
	 * @param szName 間隔任務名稱
	 * @return 間隔時間
	 */
	unsigned long Get(IN const nstring &szName) const;
	/**
	 * @brief 取得間隔任務列表
	 * @return 間隔任務列表
	 */
	std::set<nstring> List() const;
	/**
	 * @brief 取得數量
	 * @return 數量
	 */
	unsigned long Size() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------