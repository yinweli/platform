/**
 * @file windowstool.h
 * @note �����u��
 * @author yinweli
 */
/**
 * @page �p��ϥ�windowstool
 * windowstool�i�����H�U�X����:\n\n
 * @subpage ��n�C�����O\n
 * @subpage �ҲզC�����O\n
 * @subpage �B�z�{�ǦC�����O\n
 * @subpage ������C�����O\n
 * @subpage ������T�C�����O\n
 * --------------------------------------------------\n
 * Header           : windowstool.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref heaplist\n
 * �Բӻ����аѷ� @ref modulelist\n
 * �Բӻ����аѷ� @ref proclist\n
 * �Բӻ����аѷ� @ref threadlist\n
 * �Բӻ����аѷ� @ref winlist\n
 */
/**
 * @page ��n�C�����O
 * �����O�Ω���o���w�B�z�{�Ǥ�����n��T\n\n
 * �����H C_HeapList �إ߹���\n\n
 * C_HeapList ccHeapList;\n\n
 * �M��I�s C_HeapList.Initialize() �禡�Ӫ�l�����O, �p�G����g�Ѽ�, �N�H�ثe���B�z�{�Ǳ���N�X���d�߹�H\n
 * ����N�i�H�I�s C_HeapList.Begin(), C_HeapList.End() �Ө��o���\n\n
 * �Բӻ����аѷ� @ref heaplist
 */
/**
 * @page �ҲզC�����O
 * �����O�Ω���o���w�B�z�{�Ǥ����Ҳո�T\n\n
 * �����H C_ModuleList �إ߹���\n\n
 * C_ModuleList ccModuleList;\n\n
 * �M��I�s C_ModuleList.Initialize() �禡�Ӫ�l�����O, �p�G����g�Ѽ�, �N�H�ثe���B�z�{�Ǳ���N�X���d�߹�H\n
 * ����N�i�H�I�s C_ModuleList.Begin(), C_ModuleList.End() �Ө��o���\n\n
 * �Բӻ����аѷ� @ref modulelist
 */
/**
 * @page �B�z�{�ǦC�����O
 * �����O�Ω���o�Ҧ��B�z�{�Ǹ�T\n\n
 * �����H C_ProcList �إ߹���\n\n
 * C_ProcList ccProcList;\n\n
 * �M��I�s C_ProcList.Initialize() �禡�Ӫ�l�����O\n
 * ����N�i�H�I�s C_ProcList.Begin(), C_ProcList.End() �Ө��o���\n\n
 * �Բӻ����аѷ� @ref proclist
 */
/**
 * @page ������C�����O
 * �����O�Ω���o���w�B�z�{�Ǥ����������T\n\n
 * �����H C_ThreadList �إ߹���\n\n
 * C_ThreadList ccThreadList;\n\n
 * �M��I�s C_ThreadList.Initialize() �禡�Ӫ�l�����O, �p�G����g�Ѽ�, �N�H�ثe���B�z�{�Ǳ���N�X���d�߹�H\n
 * ����N�i�H�I�s C_ThreadList.Begin(), C_ThreadList.End() �Ө��o���\n\n
 * �Բӻ����аѷ� @ref threadlist
 */
/**
 * @page ������T�C�����O
 * �����O�Ω���o�Ҧ�������T\n\n
 * �����H C_WinList �إ߹���\n\n
 * C_WinList ccWinList;\n\n
 * �M��I�s C_WinList.Initialize() �禡�Ӫ�l�����O\n
 * ����N�i�H�I�s C_WinList.Begin(), C_WinList.End() �Ө��o���\n\n
 * �Բӻ����аѷ� @ref winlist
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