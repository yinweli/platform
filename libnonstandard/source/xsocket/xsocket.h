/**
 * @file xsocket.h
 * @note IOCP網路元件
 * @author yinweli
 */
/**
 * @page 如何使用xsocket
 * xsocket是使用IOCP為核心的網路元件\n\n
 * 伺服器建立方法:\n
 * 首先呼叫 XSocketInitialize() 函式來初始化Winsock, 當沒有網路物件存在時可以呼叫 XSocketRelease() 函式來釋放Winsock\n
 * 然後建立一個實體使用 C_XServer 宣告如下\n\n
 * C_XServer ccServer;\n\n
 * 然後呼叫 C_XServer.Start() 來啟動伺服器\n
 * 然後呼叫 C_XServer.AddSocketNormal() 與 C_XServer.AddSocketExtra() 來新增連線(如果沒呼叫, 會造成客戶端無法連線)\n
 * 結束時呼叫 C_XServer.Stop() 來停止伺服器\n
 * 傳送封包到客戶端要呼叫 C_XServer.Send()\n
 * 中斷與客戶端的連線呼叫 C_XServer.Disconnect()\n
 * 如果要知道是否有封包接收完成的話, 呼叫 C_XServer.Notice() 來取得完成物件, 通過檢查完成物件是否有資料來確定封包是否已經接收完畢\n
 * 如果需要取得完成物件內包含的封包資料, 呼叫 C_XNotice.Complete() 來取得封包資料物件\n
 * 當使用完此封包資料物件後, 請呼叫 C_XComplete.Release() 來釋放記憶體\n
 * 伺服器的可連線數取決於歷次 C_XServer.AddSocketNormal() 呼叫的新增連線總數, 注意這個連線總數只能增加, 不能減少\n\n
 * 客戶端建立方法:\n
 * 首先呼叫 XSocketInitialize() 函式來初始化Winsock, 當沒有網路物件存在時可以呼叫 XSocketRelease() 函式來釋放Winsock\n
 * 然後建立一個實體使用 C_XClient 宣告如下\n\n
 * C_XClient ccClient;\n\n
 * 然後呼叫 C_XClient.Start() 來連線到伺服器, 如果想要連線到多個伺服器, 可以用不同的位址多次呼叫這個函式\n
 * 結束時呼叫 C_XClient.Stop() 來停止連線\n
 * 傳送封包到伺服器要呼叫 C_XClient.Send()\n
 * 如果要知道是否有封包接收完成的話, 呼叫 C_XClient.Notice() 來取得完成物件, 通過檢查完成物件是否有資料來確定封包是否已經接收完畢\n
 * 當使用完此封包資料物件後, 請呼叫 C_XComplete.Release() 來釋放記憶體\n\n
 * --------------------------------------------------\n
 * Header           : xsocket.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref xapi\n
 * 詳細說明請參照 @ref xlist\n
 * 詳細說明請參照 @ref xserver\n
 * 詳細說明請參照 @ref xclient\n
 */
/** @defgroup xapi */
/** @defgroup xlist */
/** @defgroup xserver */
/** @defgroup xclient */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XSOCKET
#define _XSOCKET
//-----------------------------------------------------------------------------
#pragma comment(lib, "mswsock.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ws2_32.lib")
//-----------------------------------------------------------------------------
#define _WINSOCK2_ ///< 定義使用 winsock2.h 而不使用 windows.h
//#define XSOCKET_DEBUG ///< 除錯用定義
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\_ntime\_ntime.h"
#include "..\benchmark\benchmark.h"
#include "..\flowrecord\flowrecord.h"
#include "..\ipdata\ipdata.h"
#include "..\threadlock\threadlock.h"
#include "..\threadobj\threadobj.h"
//-----------------------------------------------------------------------------
#include "xapi.h"
#include "xerror.h"
#include "xlistconnect.h"
#include "xlistnotice.h"
#include "xlistoverlapped.h"
#include "xlistrecv.h"
#include "xlistsend.h"
#include "xlistunit.h"
//-----------------------------------------------------------------------------
#include "xclient.h"
#include "xserver.h"
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------