/**
 * @file systemtool.h
 * @note �t�γB�z�t�C�禡
 * @author yinweli
 */
/**
 * @page �p��ϥ�systemtool
 * systemtool�����禡�Ω�t�γB�z\n\n
 * --------------------------------------------------\n
 * Header           : systemtool.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref systemtool
 */
/** @defgroup systemtool */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _SYSTEMTOOL
#define _SYSTEMTOOL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\whandle\whandle.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ����{��
 * @note �|�H����x�Ҧ�����{��
 * @param szCmdLine �R�O��r��, ���e�]�A�����ɦW��, �a�J���Ѽ�
 * @param szCurrentDirectory �����ɸ��|
 * @return true��ܦ��\, false�h�_
 * @ingroup systemtool
 */
bool ExecuteProcess(IN const nstring &szCmdLine, IN const nstring &szCurrentDirectory);
/**
 * @brief �����{��
 * @param ulProcessID �n�������B�z�{�Ǳ���N�X
 * @ingroup systemtool
 */
void CloseProcess(IN unsigned long ulProcessID);
/**
 * @brief ���o���������ɶ�
 * @note �`�N���^���ɶ����O100�`��, �⦹�Ȱ��H10000�N�|�ܦ��@��
 * @param ulThreadID ������s��
 * @param i64KernelTime �֤߼Ҧ�����ɶ�, ���O100�`��
 * @param i64UserTime �ϥΪ̼Ҧ�����ɶ�, ���O100�`��
 * @ingroup systemtool
 */
bool GetRunTime(IN unsigned long ulThreadID, OUT __int64 &i64KernelTime, OUT __int64 &i64UserTime);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------