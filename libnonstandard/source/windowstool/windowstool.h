/**
 * @file windowstool.h
 * @note 視窗工具
 * @author yinweli
 */
/**
 * @page 如何使用windowstool
 * windowstool可分為以下幾部分:\n\n
 * @subpage 堆積列表類別\n
 * @subpage 模組列表類別\n
 * @subpage 處理程序列表類別\n
 * @subpage 執行緒列表類別\n
 * @subpage 視窗資訊列表類別\n
 * --------------------------------------------------\n
 * Header           : windowstool.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref heaplist\n
 * 詳細說明請參照 @ref modulelist\n
 * 詳細說明請參照 @ref proclist\n
 * 詳細說明請參照 @ref threadlist\n
 * 詳細說明請參照 @ref winlist\n
 */
/**
 * @page 堆積列表類別
 * 此類別用於取得指定處理程序中的堆積資訊\n\n
 * 首先以 C_HeapList 建立實體\n\n
 * C_HeapList ccHeapList;\n\n
 * 然後呼叫 C_HeapList.Initialize() 函式來初始化類別, 如果不填寫參數, 就以目前的處理程序控制代碼為查詢對象\n
 * 之後就可以呼叫 C_HeapList.Begin(), C_HeapList.End() 來取得資料\n\n
 * 詳細說明請參照 @ref heaplist
 */
/**
 * @page 模組列表類別
 * 此類別用於取得指定處理程序中的模組資訊\n\n
 * 首先以 C_ModuleList 建立實體\n\n
 * C_ModuleList ccModuleList;\n\n
 * 然後呼叫 C_ModuleList.Initialize() 函式來初始化類別, 如果不填寫參數, 就以目前的處理程序控制代碼為查詢對象\n
 * 之後就可以呼叫 C_ModuleList.Begin(), C_ModuleList.End() 來取得資料\n\n
 * 詳細說明請參照 @ref modulelist
 */
/**
 * @page 處理程序列表類別
 * 此類別用於取得所有處理程序資訊\n\n
 * 首先以 C_ProcList 建立實體\n\n
 * C_ProcList ccProcList;\n\n
 * 然後呼叫 C_ProcList.Initialize() 函式來初始化類別\n
 * 之後就可以呼叫 C_ProcList.Begin(), C_ProcList.End() 來取得資料\n\n
 * 詳細說明請參照 @ref proclist
 */
/**
 * @page 執行緒列表類別
 * 此類別用於取得指定處理程序中的執行緒資訊\n\n
 * 首先以 C_ThreadList 建立實體\n\n
 * C_ThreadList ccThreadList;\n\n
 * 然後呼叫 C_ThreadList.Initialize() 函式來初始化類別, 如果不填寫參數, 就以目前的處理程序控制代碼為查詢對象\n
 * 之後就可以呼叫 C_ThreadList.Begin(), C_ThreadList.End() 來取得資料\n\n
 * 詳細說明請參照 @ref threadlist
 */
/**
 * @page 視窗資訊列表類別
 * 此類別用於取得所有視窗資訊\n\n
 * 首先以 C_WinList 建立實體\n\n
 * C_WinList ccWinList;\n\n
 * 然後呼叫 C_WinList.Initialize() 函式來初始化類別\n
 * 之後就可以呼叫 C_WinList.Begin(), C_WinList.End() 來取得資料\n\n
 * 詳細說明請參照 @ref winlist
 */
/** @defgroup heaplist */
/** @defgroup modulelist */
/** @defgroup proclist */
/** @defgroup threadlist */
/** @defgroup winlist */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _WINDOWSTOOL
#define _WINDOWSTOOL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\whandle\whandle.h"
//-----------------------------------------------------------------------------
#include "heaplist.h"
#include "modulelist.h"
#include "proclist.h"
#include "threadlist.h"
#include "winlist.h"
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------