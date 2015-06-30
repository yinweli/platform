/**
 * @file curl.h
 * @note curl類別
 * @author yinweli
 */
/**
 * @page 如何使用curl
 * curl用於與網路上的web服務溝通\n\n
 * 在使用之前需要先呼叫 CURLInitialize() 函式來初始化curl, 當程式結束前要呼叫 CURLRelease() 函式來清除curl\n
 * curl有三個主要的組件, 分別是 :\n
 * C_CURLBase 基礎的curl類別, 他事實上只封裝了 curl_easy_setopt 與 curl_easy_perform 函式, 再加上一些錯誤回報功能\n
 * C_CURLMeta 進階的curl類別, 他擁有 C_CURLBase 的功能, 加上可以取得結果物件的函式\n
 * C_CURLMulti 這是以非阻塞模式執行的多元curl類別, 它可以同時執行許多個 C_CURLMeta 物件, 同時會將執行的結果集合起來等待使用者取用\n
 * 另外還有一些其他的類別 :\n
 * C_ErrorCURL curl錯誤回報類別\n
 * C_CURLResult curl結果類別\n
 * 請參考以下說明 :\n
 * @subpage 使用C_CURLBase\n
 * @subpage 使用C_CURLMeta\n
 * @subpage 使用C_CURLMulti\n\n
 * --------------------------------------------------\n
 * Header           : curl.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref curl
 */
/** @defgroup curl */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CURL
#define _CURL
//-----------------------------------------------------------------------------
#ifdef _DEBUG
#pragma comment(lib, "..\\libthirdparty\\curl-7.39.0\\vc2013_lib_debug\\libcurld.lib")
#else
#pragma comment(lib, "..\\libthirdparty\\curl-7.39.0\\vc2013_lib_release\\libcurl.lib")
#endif
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\..\..\libthirdparty\curl-7.39.0\include\curl.h"
//-----------------------------------------------------------------------------
#include "curlbase.h"
#include "curlmeta.h"
#include "curlmulti.h"
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------