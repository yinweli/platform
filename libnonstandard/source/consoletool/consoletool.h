/**
 * @file consoletool.h
 * @note console�Ҧ��u��t�C�禡
 * @author yinweli
 */
/**
 * @page �p��ϥ�consoletool
 * consoletool�����禡�Ω�console�Ҧ��U�ާ@\n\n
 * --------------------------------------------------\n
 * Header           : consoletool.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref consoletool
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
 * @brief �]�w�������D
 * @note �������D�|�p�U���\n
 *       �������D ���� [Ver:�����W��] [FileTime:�ɮ׮ɶ�] [PID:�{������s��]
 * @param szTitle �������D
 * @param szVer �����W��
 * @param szFile �ɮצW��
 * @ingroup consoletool
 */
void SetConsoleWindowTile(IN const nstring &szTitle, IN const nstring &szVer, IN const nstring &szFile);
/**
 * @brief ��X�r������
 * @note �b�ϥ� SetConsoleMousePos() �禡�]�w��Ъ����p�U, printfex() �禡�|�b�A���w����Цa�I��ܤ�r, �� printf ���|
 * @param szData ��X�r��
 * @ingroup consoletool
 */
void printfex(IN const nstring &szData);
/**
 * @brief ��X�r������, �i�H��ܤ�r�C�⪩��
 * @note �b�ϥ� SetConsoleMousePos() �禡�]�w��Ъ����p�U, printfex() �禡�|�b�A���w����Цa�I��ܤ�r, �� printf ���|\n\n
 *       ��r�C�⦳�H�U���\n\n
 *       FOREGROUND_BLUE, FOREGROUND_GREEN, FOREGROUND_RED, FOREGROUND_INTENSITY\n
 *       BACKGROUND_BLUE, BACKGROUND_GREEN, BACKGROUND_RED, BACKGROUND_INTENSITY\n
 *       FOREGROUND_INTENSITY �P BACKGROUND_INTENSITY �N���O���G, �]�N�O�e�����G�H�έI�����G\n\n
 *       �i�βզX���覡�զ���r�C��, �H�U�O�@�ǽd��\n\n
 *       �e�� �� �I�� �� : FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE\n
 *       �e�� �� �I�� �� : FOREGROUND_INTENSITY | FOREGROUND_RED\n
 *       �e�� �� �I�� �� : FOREGROUND_INTENSITY | FOREGROUND_GREEN\n
 *       �e�� �� �I�� �� : FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN\n
 *       �e�� �� �I�� �� : FOREGROUND_INTENSITY | FOREGROUND_BLUE\n
 *       �e�� �v�� �I�� �� : FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE\n
 *       �e�� �C�� �I�� �� : FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE\n
 *       �e�� �� �I�� �� : BACKGROUND_INTENSITY | BACKGROUND_INTENSITY\n
 *       �e�� �� �I�� �� : BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE\n
 *       �e�� �� �I�� �� : BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED
 * @param wColor ��r�C��
 * @param szData ��X�r��
 * @ingroup consoletool
 */
void printfex(IN unsigned short wColor, IN const nstring &szData);
/**
 * @brief ����, �M�ᵲ���{��
 * @param szInput ��������ܪ���r
 * @ingroup consoletool
 */
void PressAnyKey2Exit(IN const nstring &szInput);
/**
 * @brief �]�w��Ц�m
 * @note �u�� printfex() �禡����, �� printf �O�L�Ī�
 * @param X X�y��
 * @param Y Y�y��
 * @return true��ܳ]�m���\, false�h�_
 * @ingroup consoletool
 */
bool SetConsoleMousePos(IN short X, IN short Y);
/**
 * @brief ���o��Ц�m
 * @param X X�y��
 * @param Y Y�y��
 * @return true��ܨ��o���\, false�h�_
 * @ingroup consoletool
 */
bool GetConsoleMousePos(OUT short &X, OUT short &Y);
/**
 * @brief �M���ثe��, �åB���]��m
 * @param wPos ��m
 * @ingroup consoletool
 */
void ClearConsoleLine(IN short wPos = 0);
/**
 * @brief �N���ثe��, �åB���]��m
 * @param szInput �r��
 * @param wPos ��m
 * @ingroup consoletool
 */
void ReplaceConsoleLine(IN const nstring &szInput, IN short wPos);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------