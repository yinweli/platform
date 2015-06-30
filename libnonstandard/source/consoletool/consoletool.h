/**
 * @file consoletool.h
 * @note console模式工具系列函式
 * @author yinweli
 */
/**
 * @page 如何使用consoletool
 * consoletool內的函式用於console模式下操作\n\n
 * --------------------------------------------------\n
 * Header           : consoletool.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref consoletool
 */
/** @defgroup consoletool */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CONSOLETOOL
#define _CONSOLETOOL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\_nstroutf\_nstroutf.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 設定視窗標題
 * @note 視窗標題會如下顯示\n
 *       視窗標題 註解 [Ver:版本名稱] [FileTime:檔案時間] [PID:程式執行編號]
 * @param szTitle 視窗標題
 * @param szVer 版本名稱
 * @param szFile 檔案名稱
 * @ingroup consoletool
 */
void SetConsoleWindowTile(IN const nstring &szTitle, IN const nstring &szVer, IN const nstring &szFile);
/**
 * @brief 輸出字串到視窗
 * @note 在使用 SetConsoleMousePos() 函式設定游標的狀況下, printfex() 函式會在你指定的游標地點顯示文字, 但 printf 不會
 * @param szData 輸出字串
 * @ingroup consoletool
 */
void printfex(IN const nstring &szData);
/**
 * @brief 輸出字串到視窗, 可以選擇文字顏色版本
 * @note 在使用 SetConsoleMousePos() 函式設定游標的狀況下, printfex() 函式會在你指定的游標地點顯示文字, 但 printf 不會\n\n
 *       文字顏色有以下選擇\n\n
 *       FOREGROUND_BLUE, FOREGROUND_GREEN, FOREGROUND_RED, FOREGROUND_INTENSITY\n
 *       BACKGROUND_BLUE, BACKGROUND_GREEN, BACKGROUND_RED, BACKGROUND_INTENSITY\n
 *       FOREGROUND_INTENSITY 與 BACKGROUND_INTENSITY 代表的是高亮, 也就是前景高亮以及背景高亮\n\n
 *       可用組合的方式組成文字顏色, 以下是一些範例\n\n
 *       前景 白 背景 黑 : FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE\n
 *       前景 紅 背景 黑 : FOREGROUND_INTENSITY | FOREGROUND_RED\n
 *       前景 綠 背景 黑 : FOREGROUND_INTENSITY | FOREGROUND_GREEN\n
 *       前景 黃 背景 黑 : FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN\n
 *       前景 藍 背景 黑 : FOREGROUND_INTENSITY | FOREGROUND_BLUE\n
 *       前景 洋紅 背景 黑 : FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE\n
 *       前景 青綠 背景 黑 : FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE\n
 *       前景 黑 背景 灰 : BACKGROUND_INTENSITY | BACKGROUND_INTENSITY\n
 *       前景 黑 背景 白 : BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE\n
 *       前景 紅 背景 白 : BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED
 * @param wColor 文字顏色
 * @param szData 輸出字串
 * @ingroup consoletool
 */
void printfex(IN unsigned short wColor, IN const nstring &szData);
/**
 * @brief 按鍵, 然後結束程式
 * @param szInput 結束時顯示的文字
 * @ingroup consoletool
 */
void PressAnyKey2Exit(IN const nstring &szInput);
/**
 * @brief 設定游標位置
 * @note 只對 printfex() 函式有效, 對 printf 是無效的
 * @param X X座標
 * @param Y Y座標
 * @return true表示設置成功, false則否
 * @ingroup consoletool
 */
bool SetConsoleMousePos(IN short X, IN short Y);
/**
 * @brief 取得游標位置
 * @param X X座標
 * @param Y Y座標
 * @return true表示取得成功, false則否
 * @ingroup consoletool
 */
bool GetConsoleMousePos(OUT short &X, OUT short &Y);
/**
 * @brief 清除目前行, 並且重設位置
 * @param wPos 位置
 * @ingroup consoletool
 */
void ClearConsoleLine(IN short wPos = 0);
/**
 * @brief 代替目前行, 並且重設位置
 * @param szInput 字串
 * @param wPos 位置
 * @ingroup consoletool
 */
void ReplaceConsoleLine(IN const nstring &szInput, IN short wPos);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------