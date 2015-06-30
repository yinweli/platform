/**
 * @file debugtool.h
 * @note �����t�C�禡
 * @author yinweli
 */
/**
 * @page �p��ϥ�debugtool
 * debugtool�����禡�Ω󰣿�\n\n
 * --------------------------------------------------\n
 * Header           : debugtool.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref debugtool
 */
/** @defgroup debugtool */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _DEBUGTOOL
#define _DEBUGTOOL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\_nstroutf\_nstroutf.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ��X�r��찣������
 * @param szData ��X�r��
 * @ingroup debugtool
 */
void xOutputDebugString(IN const nstring &szData);
/**
 * @brief �NHRESULT���~�N�X�ഫ���r��
 * @param hr HRESULT���~�N�X
 * @return ���~�r��
 * @ingroup debugtool
 */
nstring HRESULTtoString(IN HRESULT hr);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------