/**
 * @file actualkeycodes.h
 * @note ��L���y�t�C�禡
 * @author yinweli
 */
/**
 * @page �p��ϥ�actualkeycodes
 * actualkeycodes�Ω���o�ثe��L���U�F���ӫ��s\n\n
 * �I�s getakcode() �άO getakcodee() �o2�Ө禡�䤤����, �P�_���o�� ENUM_AKCodes �P�_�N�i���D�ثe��L���U���O���ӫ��s\n\n
 * --------------------------------------------------\n
 * Header           : actualkeycodes.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref actualkeycodes
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
 * @brief �ۭq��L���y�X�C�|
 * @ingroup actualkeycodes
 */
enum ENUM_AKCodes
{
	ENUM_AKCodes_NULL = 0, ///< �����L���s �L
	ENUM_AKCodes_0, ///< �����L���s 0
	ENUM_AKCodes_1, ///< �����L���s 1
	ENUM_AKCodes_2, ///< �����L���s 2
	ENUM_AKCodes_3, ///< �����L���s 3
	ENUM_AKCodes_4, ///< �����L���s 4
	ENUM_AKCodes_5, ///< �����L���s 5
	ENUM_AKCodes_6, ///< �����L���s 6
	ENUM_AKCodes_7, ///< �����L���s 7
	ENUM_AKCodes_8, ///< �����L���s 8
	ENUM_AKCodes_9, ///< �����L���s 9
	ENUM_AKCodes_A, ///< �����L���s A
	ENUM_AKCodes_B, ///< �����L���s B
	ENUM_AKCodes_C, ///< �����L���s C
	ENUM_AKCodes_D, ///< �����L���s D
	ENUM_AKCodes_E, ///< �����L���s E
	ENUM_AKCodes_F, ///< �����L���s F
	ENUM_AKCodes_G, ///< �����L���s G
	ENUM_AKCodes_H, ///< �����L���s H
	ENUM_AKCodes_I, ///< �����L���s I
	ENUM_AKCodes_J, ///< �����L���s J
	ENUM_AKCodes_K, ///< �����L���s K
	ENUM_AKCodes_L, ///< �����L���s L
	ENUM_AKCodes_M, ///< �����L���s M
	ENUM_AKCodes_N, ///< �����L���s N
	ENUM_AKCodes_O, ///< �����L���s O
	ENUM_AKCodes_P, ///< �����L���s P
	ENUM_AKCodes_Q, ///< �����L���s Q
	ENUM_AKCodes_R, ///< �����L���s R
	ENUM_AKCodes_S, ///< �����L���s S
	ENUM_AKCodes_T, ///< �����L���s T
	ENUM_AKCodes_U, ///< �����L���s U
	ENUM_AKCodes_V, ///< �����L���s V
	ENUM_AKCodes_W, ///< �����L���s W
	ENUM_AKCodes_X, ///< �����L���s X
	ENUM_AKCodes_Y, ///< �����L���s Y
	ENUM_AKCodes_Z, ///< �����L���s Z
	ENUM_AKCodes_a, ///< �����L���s a
	ENUM_AKCodes_b, ///< �����L���s b
	ENUM_AKCodes_c, ///< �����L���s c
	ENUM_AKCodes_d, ///< �����L���s d
	ENUM_AKCodes_e, ///< �����L���s e
	ENUM_AKCodes_f, ///< �����L���s f
	ENUM_AKCodes_g, ///< �����L���s g
	ENUM_AKCodes_h, ///< �����L���s h
	ENUM_AKCodes_i, ///< �����L���s i
	ENUM_AKCodes_j, ///< �����L���s j
	ENUM_AKCodes_k, ///< �����L���s k
	ENUM_AKCodes_l, ///< �����L���s l
	ENUM_AKCodes_m, ///< �����L���s m
	ENUM_AKCodes_n, ///< �����L���s n
	ENUM_AKCodes_o, ///< �����L���s o
	ENUM_AKCodes_p, ///< �����L���s p
	ENUM_AKCodes_q, ///< �����L���s q
	ENUM_AKCodes_r, ///< �����L���s r
	ENUM_AKCodes_s, ///< �����L���s s
	ENUM_AKCodes_t, ///< �����L���s t
	ENUM_AKCodes_u, ///< �����L���s u
	ENUM_AKCodes_v, ///< �����L���s v
	ENUM_AKCodes_w, ///< �����L���s w
	ENUM_AKCodes_x, ///< �����L���s x
	ENUM_AKCodes_y, ///< �����L���s y
	ENUM_AKCodes_z, ///< �����L���s z
	ENUM_AKCodes_SYM21, ///< �����L���s !
	ENUM_AKCodes_SYM22, ///< �����L���s "
	ENUM_AKCodes_SYM23, ///< �����L���s #
	ENUM_AKCodes_SYM24, ///< �����L���s $
	ENUM_AKCodes_SYM25, ///< �����L���s %
	ENUM_AKCodes_SYM26, ///< �����L���s &
	ENUM_AKCodes_SYM27, ///< �����L���s '
	ENUM_AKCodes_SYM28, ///< �����L���s (
	ENUM_AKCodes_SYM29, ///< �����L���s )
	ENUM_AKCodes_SYM2A, ///< �����L���s *
	ENUM_AKCodes_SYM2B, ///< �����L���s +
	ENUM_AKCodes_SYM2C, ///< �����L���s ,
	ENUM_AKCodes_SYM2D, ///< �����L���s -
	ENUM_AKCodes_SYM2E, ///< �����L���s .
	ENUM_AKCodes_SYM2F, ///< �����L���s /
	ENUM_AKCodes_SYM3A, ///< �����L���s :
	ENUM_AKCodes_SYM3B, ///< �����L���s ;
	ENUM_AKCodes_SYM3C, ///< �����L���s <
	ENUM_AKCodes_SYM3D, ///< �����L���s =
	ENUM_AKCodes_SYM3E, ///< �����L���s >
	ENUM_AKCodes_SYM3F, ///< �����L���s ?
	ENUM_AKCodes_SYM40, ///< �����L���s @
	ENUM_AKCodes_SYM5B, ///< �����L���s [
	ENUM_AKCodes_SYM5C, ///< �����L���s '\'
	ENUM_AKCodes_SYM5D, ///< �����L���s ]
	ENUM_AKCodes_SYM5E, ///< �����L���s ^
	ENUM_AKCodes_SYM5F, ///< �����L���s _
	ENUM_AKCodes_SYM60, ///< �����L���s `
	ENUM_AKCodes_SYM7B, ///< �����L���s {
	ENUM_AKCodes_SYM7C, ///< �����L���s |
	ENUM_AKCodes_SYM7D, ///< �����L���s }
	ENUM_AKCodes_SYM7E, ///< �����L���s ~
	ENUM_AKCodes_SPACE, ///< �����L���s Space
	ENUM_AKCodes_BACKSPACE, ///< �����L���s Backspace
	ENUM_AKCodes_TAB, ///< �����L���s Tab
	ENUM_AKCodes_ENTER, ///< �����L���s Enter
	ENUM_AKCodes_ESC, ///< �����L���s Esc
	ENUM_AKCodes_F1, ///< �����L���s F1
	ENUM_AKCodes_F2, ///< �����L���s F2
	ENUM_AKCodes_F3, ///< �����L���s F3
	ENUM_AKCodes_F4, ///< �����L���s F4
	ENUM_AKCodes_F5, ///< �����L���s F5
	ENUM_AKCodes_F6, ///< �����L���s F6
	ENUM_AKCodes_F7, ///< �����L���s F7
	ENUM_AKCodes_F8, ///< �����L���s F8
	ENUM_AKCodes_F9, ///< �����L���s F9
	ENUM_AKCodes_F10, ///< �����L���s F10
	ENUM_AKCodes_F11, ///< �����L���s F11
	ENUM_AKCodes_F12, ///< �����L���s F12
	ENUM_AKCodes_HOME, ///< �����L���s Home
	ENUM_AKCodes_END, ///< �����L���s End
	ENUM_AKCodes_INSERT, ///< �����L���s Insert
	ENUM_AKCodes_DELETE, ///< �����L���s Delete
	ENUM_AKCodes_PAGEUP, ///< �����L���s PageUp
	ENUM_AKCodes_PAGEDOWN, ///< �����L���s PageDown
	ENUM_AKCodes_UP, ///< �����L���s ��V��W
	ENUM_AKCodes_DOWN, ///< �����L���s ��V��U
	ENUM_AKCodes_LEFT, ///< �����L���s ��V�䥪
	ENUM_AKCodes_RIGHT, ///< �����L���s ��V��k

	ENUM_AKCodes_FORCE_DWORD = ENUM_FORCE_DWORD, 
};
//-----------------------------------------------------------------------------
/**
 * @brief �����L���y�X�ഫ���ۭq��L���y�X�C�|
 * @note �o�Ө禡�Ω�q _getch/_getche �禡���^�ǭȤ��R�X�ثe��L���U�F���ӫ��s
 * @param ik1 �ϥ� _getch/_getche �禡���o���Ĥ@����L���y�X
 * @param ik2 �ϥ� _getch/_getche �禡���o���ĤG����L���y�X
 * @return �ۭq��L���y�X�C�|
 * @ingroup actualkeycodes
 */
ENUM_AKCodes convakcode(IN int ik1, IN int ik2);
/**
 * @brief ���o��L���y���G, ��J���r�����|�X�{�bconsole�����W
 * @return �ثe��L���U����L���y�X�C�|
 * @ingroup actualkeycodes
 */
ENUM_AKCodes getakcode();
/**
 * @brief ���o��L���y���G, ��J���r���|�X�{�bconsole�����W
 * @return �ثe��L���U����L���y�X�C�|
 * @ingroup actualkeycodes
 */
ENUM_AKCodes getakcodee();
/**
 * @brief ���o�ۭq��L���y�X�C�|���y�z�r��
 * @param emAkCode �ۭq��L���y�X�C�|
 * @return �y�z�r��
 * @ingroup actualkeycodes
 */
nstring akcodestr(IN ENUM_AKCodes emAkCode);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------