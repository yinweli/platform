/**
 * @file _nstderr.h
 * @note NonStandardLib�����~���O
 * @author yinweli
 */
/**
 * @page �p��ϥ�_nstderr
 * C_ErrorBase ���O�O��¦�����~���O, �l�ͪ����~���O���o�~�ӥ�\n
 * C_ErrorNSTD ���O�O���Ѱ����m�T�������~���O\n
 * C_ErrorWin ���O�O����Windows���~�T�������~���O\n
 * C_NOutput ���O�O�ϥ� C_ErrorBase ���O�ӿ�X���~�����O\n\n
 * ��o�Ϳ��~��, �I�s C_NOutput::Instance().Error() �禡�ӰO�����~\n
 * C_NOutput ���O���������~�O���W����, ������W�L NOUTPUT_MAX �ӿ��~, �N�|�q�ª����~�}�l��������\n
 * �ϥΪ̥i�H�I�s C_NOutput::Instance().Get() �禡�Ө��o���~\n\n
 * --------------------------------------------------\n
 * Header           : _nstderr.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref nstderror\n
 */
/** @defgroup nstderror */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef __NSTDERR
#define __NSTDERR
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_ntime\_ntime.h"
//-----------------------------------------------------------------------------
#include "errorbase.h"
#include "errornstd.h"
#include "errorwin.h"
#include "noutput.h"
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------