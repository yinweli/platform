/**
 * @file actualkeycodes.h
 * @note 鍵盤掃描系列函式
 * @author yinweli
 */
/**
 * @page 如何使用actualkeycodes
 * actualkeycodes用於取得目前鍵盤按下了哪個按鈕\n\n
 * 呼叫 getakcode() 或是 getakcodee() 這2個函式其中之ㄧ, 判斷取得的 ENUM_AKCodes 判斷就可知道目前鍵盤按下的是哪個按鈕\n\n
 * --------------------------------------------------\n
 * Header           : actualkeycodes.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref actualkeycodes
 */
/** @defgroup actualkeycodes */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _ACTUALKEYCODES
#define _ACTUALKEYCODES
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 自訂鍵盤掃描碼列舉
 * @ingroup actualkeycodes
 */
enum ENUM_AKCodes
{
	ENUM_AKCodes_NULL = 0, ///< 表示鍵盤按鈕 無
	ENUM_AKCodes_0, ///< 表示鍵盤按鈕 0
	ENUM_AKCodes_1, ///< 表示鍵盤按鈕 1
	ENUM_AKCodes_2, ///< 表示鍵盤按鈕 2
	ENUM_AKCodes_3, ///< 表示鍵盤按鈕 3
	ENUM_AKCodes_4, ///< 表示鍵盤按鈕 4
	ENUM_AKCodes_5, ///< 表示鍵盤按鈕 5
	ENUM_AKCodes_6, ///< 表示鍵盤按鈕 6
	ENUM_AKCodes_7, ///< 表示鍵盤按鈕 7
	ENUM_AKCodes_8, ///< 表示鍵盤按鈕 8
	ENUM_AKCodes_9, ///< 表示鍵盤按鈕 9
	ENUM_AKCodes_A, ///< 表示鍵盤按鈕 A
	ENUM_AKCodes_B, ///< 表示鍵盤按鈕 B
	ENUM_AKCodes_C, ///< 表示鍵盤按鈕 C
	ENUM_AKCodes_D, ///< 表示鍵盤按鈕 D
	ENUM_AKCodes_E, ///< 表示鍵盤按鈕 E
	ENUM_AKCodes_F, ///< 表示鍵盤按鈕 F
	ENUM_AKCodes_G, ///< 表示鍵盤按鈕 G
	ENUM_AKCodes_H, ///< 表示鍵盤按鈕 H
	ENUM_AKCodes_I, ///< 表示鍵盤按鈕 I
	ENUM_AKCodes_J, ///< 表示鍵盤按鈕 J
	ENUM_AKCodes_K, ///< 表示鍵盤按鈕 K
	ENUM_AKCodes_L, ///< 表示鍵盤按鈕 L
	ENUM_AKCodes_M, ///< 表示鍵盤按鈕 M
	ENUM_AKCodes_N, ///< 表示鍵盤按鈕 N
	ENUM_AKCodes_O, ///< 表示鍵盤按鈕 O
	ENUM_AKCodes_P, ///< 表示鍵盤按鈕 P
	ENUM_AKCodes_Q, ///< 表示鍵盤按鈕 Q
	ENUM_AKCodes_R, ///< 表示鍵盤按鈕 R
	ENUM_AKCodes_S, ///< 表示鍵盤按鈕 S
	ENUM_AKCodes_T, ///< 表示鍵盤按鈕 T
	ENUM_AKCodes_U, ///< 表示鍵盤按鈕 U
	ENUM_AKCodes_V, ///< 表示鍵盤按鈕 V
	ENUM_AKCodes_W, ///< 表示鍵盤按鈕 W
	ENUM_AKCodes_X, ///< 表示鍵盤按鈕 X
	ENUM_AKCodes_Y, ///< 表示鍵盤按鈕 Y
	ENUM_AKCodes_Z, ///< 表示鍵盤按鈕 Z
	ENUM_AKCodes_a, ///< 表示鍵盤按鈕 a
	ENUM_AKCodes_b, ///< 表示鍵盤按鈕 b
	ENUM_AKCodes_c, ///< 表示鍵盤按鈕 c
	ENUM_AKCodes_d, ///< 表示鍵盤按鈕 d
	ENUM_AKCodes_e, ///< 表示鍵盤按鈕 e
	ENUM_AKCodes_f, ///< 表示鍵盤按鈕 f
	ENUM_AKCodes_g, ///< 表示鍵盤按鈕 g
	ENUM_AKCodes_h, ///< 表示鍵盤按鈕 h
	ENUM_AKCodes_i, ///< 表示鍵盤按鈕 i
	ENUM_AKCodes_j, ///< 表示鍵盤按鈕 j
	ENUM_AKCodes_k, ///< 表示鍵盤按鈕 k
	ENUM_AKCodes_l, ///< 表示鍵盤按鈕 l
	ENUM_AKCodes_m, ///< 表示鍵盤按鈕 m
	ENUM_AKCodes_n, ///< 表示鍵盤按鈕 n
	ENUM_AKCodes_o, ///< 表示鍵盤按鈕 o
	ENUM_AKCodes_p, ///< 表示鍵盤按鈕 p
	ENUM_AKCodes_q, ///< 表示鍵盤按鈕 q
	ENUM_AKCodes_r, ///< 表示鍵盤按鈕 r
	ENUM_AKCodes_s, ///< 表示鍵盤按鈕 s
	ENUM_AKCodes_t, ///< 表示鍵盤按鈕 t
	ENUM_AKCodes_u, ///< 表示鍵盤按鈕 u
	ENUM_AKCodes_v, ///< 表示鍵盤按鈕 v
	ENUM_AKCodes_w, ///< 表示鍵盤按鈕 w
	ENUM_AKCodes_x, ///< 表示鍵盤按鈕 x
	ENUM_AKCodes_y, ///< 表示鍵盤按鈕 y
	ENUM_AKCodes_z, ///< 表示鍵盤按鈕 z
	ENUM_AKCodes_SYM21, ///< 表示鍵盤按鈕 !
	ENUM_AKCodes_SYM22, ///< 表示鍵盤按鈕 "
	ENUM_AKCodes_SYM23, ///< 表示鍵盤按鈕 #
	ENUM_AKCodes_SYM24, ///< 表示鍵盤按鈕 $
	ENUM_AKCodes_SYM25, ///< 表示鍵盤按鈕 %
	ENUM_AKCodes_SYM26, ///< 表示鍵盤按鈕 &
	ENUM_AKCodes_SYM27, ///< 表示鍵盤按鈕 '
	ENUM_AKCodes_SYM28, ///< 表示鍵盤按鈕 (
	ENUM_AKCodes_SYM29, ///< 表示鍵盤按鈕 )
	ENUM_AKCodes_SYM2A, ///< 表示鍵盤按鈕 *
	ENUM_AKCodes_SYM2B, ///< 表示鍵盤按鈕 +
	ENUM_AKCodes_SYM2C, ///< 表示鍵盤按鈕 ,
	ENUM_AKCodes_SYM2D, ///< 表示鍵盤按鈕 -
	ENUM_AKCodes_SYM2E, ///< 表示鍵盤按鈕 .
	ENUM_AKCodes_SYM2F, ///< 表示鍵盤按鈕 /
	ENUM_AKCodes_SYM3A, ///< 表示鍵盤按鈕 :
	ENUM_AKCodes_SYM3B, ///< 表示鍵盤按鈕 ;
	ENUM_AKCodes_SYM3C, ///< 表示鍵盤按鈕 <
	ENUM_AKCodes_SYM3D, ///< 表示鍵盤按鈕 =
	ENUM_AKCodes_SYM3E, ///< 表示鍵盤按鈕 >
	ENUM_AKCodes_SYM3F, ///< 表示鍵盤按鈕 ?
	ENUM_AKCodes_SYM40, ///< 表示鍵盤按鈕 @
	ENUM_AKCodes_SYM5B, ///< 表示鍵盤按鈕 [
	ENUM_AKCodes_SYM5C, ///< 表示鍵盤按鈕 '\'
	ENUM_AKCodes_SYM5D, ///< 表示鍵盤按鈕 ]
	ENUM_AKCodes_SYM5E, ///< 表示鍵盤按鈕 ^
	ENUM_AKCodes_SYM5F, ///< 表示鍵盤按鈕 _
	ENUM_AKCodes_SYM60, ///< 表示鍵盤按鈕 `
	ENUM_AKCodes_SYM7B, ///< 表示鍵盤按鈕 {
	ENUM_AKCodes_SYM7C, ///< 表示鍵盤按鈕 |
	ENUM_AKCodes_SYM7D, ///< 表示鍵盤按鈕 }
	ENUM_AKCodes_SYM7E, ///< 表示鍵盤按鈕 ~
	ENUM_AKCodes_SPACE, ///< 表示鍵盤按鈕 Space
	ENUM_AKCodes_BACKSPACE, ///< 表示鍵盤按鈕 Backspace
	ENUM_AKCodes_TAB, ///< 表示鍵盤按鈕 Tab
	ENUM_AKCodes_ENTER, ///< 表示鍵盤按鈕 Enter
	ENUM_AKCodes_ESC, ///< 表示鍵盤按鈕 Esc
	ENUM_AKCodes_F1, ///< 表示鍵盤按鈕 F1
	ENUM_AKCodes_F2, ///< 表示鍵盤按鈕 F2
	ENUM_AKCodes_F3, ///< 表示鍵盤按鈕 F3
	ENUM_AKCodes_F4, ///< 表示鍵盤按鈕 F4
	ENUM_AKCodes_F5, ///< 表示鍵盤按鈕 F5
	ENUM_AKCodes_F6, ///< 表示鍵盤按鈕 F6
	ENUM_AKCodes_F7, ///< 表示鍵盤按鈕 F7
	ENUM_AKCodes_F8, ///< 表示鍵盤按鈕 F8
	ENUM_AKCodes_F9, ///< 表示鍵盤按鈕 F9
	ENUM_AKCodes_F10, ///< 表示鍵盤按鈕 F10
	ENUM_AKCodes_F11, ///< 表示鍵盤按鈕 F11
	ENUM_AKCodes_F12, ///< 表示鍵盤按鈕 F12
	ENUM_AKCodes_HOME, ///< 表示鍵盤按鈕 Home
	ENUM_AKCodes_END, ///< 表示鍵盤按鈕 End
	ENUM_AKCodes_INSERT, ///< 表示鍵盤按鈕 Insert
	ENUM_AKCodes_DELETE, ///< 表示鍵盤按鈕 Delete
	ENUM_AKCodes_PAGEUP, ///< 表示鍵盤按鈕 PageUp
	ENUM_AKCodes_PAGEDOWN, ///< 表示鍵盤按鈕 PageDown
	ENUM_AKCodes_UP, ///< 表示鍵盤按鈕 方向鍵上
	ENUM_AKCodes_DOWN, ///< 表示鍵盤按鈕 方向鍵下
	ENUM_AKCodes_LEFT, ///< 表示鍵盤按鈕 方向鍵左
	ENUM_AKCodes_RIGHT, ///< 表示鍵盤按鈕 方向鍵右

	ENUM_AKCodes_FORCE_DWORD = ENUM_FORCE_DWORD, 
};
//-----------------------------------------------------------------------------
/**
 * @brief 實際鍵盤掃描碼轉換成自訂鍵盤掃描碼列舉
 * @note 這個函式用於從 _getch/_getche 函式的回傳值分析出目前鍵盤按下了哪個按鈕
 * @param ik1 使用 _getch/_getche 函式取得的第一個鍵盤掃描碼
 * @param ik2 使用 _getch/_getche 函式取得的第二個鍵盤掃描碼
 * @return 自訂鍵盤掃描碼列舉
 * @ingroup actualkeycodes
 */
ENUM_AKCodes convakcode(IN int ik1, IN int ik2);
/**
 * @brief 取得鍵盤掃描結果, 鍵入的字元不會出現在console視窗上
 * @return 目前鍵盤按下的鍵盤掃描碼列舉
 * @ingroup actualkeycodes
 */
ENUM_AKCodes getakcode();
/**
 * @brief 取得鍵盤掃描結果, 鍵入的字元會出現在console視窗上
 * @return 目前鍵盤按下的鍵盤掃描碼列舉
 * @ingroup actualkeycodes
 */
ENUM_AKCodes getakcodee();
/**
 * @brief 取得自訂鍵盤掃描碼列舉的描述字串
 * @param emAkCode 自訂鍵盤掃描碼列舉
 * @return 描述字串
 * @ingroup actualkeycodes
 */
nstring akcodestr(IN ENUM_AKCodes emAkCode);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------