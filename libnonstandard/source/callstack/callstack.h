/**
 * @file callstack.h
 * @note callstack��X�t�C�禡
 * @author yinweli
 */
/**
 * @page �p��ϥ�callstack
 * callstack�����禡�Ω�b�������Xcallstack\n\n
 * CallStackTrace() �禡���O���覡�O�q�O������禡���a�詹�W�^����main����\n
 * �Ҧp:\n\n
 * main �I�s function1\n
 * function1 �I�s function2\n
 * function2 �I�s function3\n
 * function3 �I�s function4\n
 * function4�����@�����F CallStackTrace() \n\n
 * ���G�N�|��X\n\n
 * CallStackTrace() > function4 > function3 > function2 > function1 > main\n\n
 * �o�˪����涶��\n\n
 * �S�Ҧp�W�����I�s����, ���O CallStackTrace() ��bmain����\n
 * �N�u�|��X CallStackTrace() > main �����G\n\n
 * --------------------------------------------------\n
 * Header           : callstack.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref callstack
 */
/** @defgroup callstack */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CALLSTACK
#define _CALLSTACK
//-----------------------------------------------------------------------------
#pragma comment(lib, "dbghelp.lib")
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\_ntime\_ntime.h"
#include "..\filetool\filetool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief Callstack���c
 * @ingroup callstack
 */
struct S_CallStack
{
	nstring szFileName; ///< �ɮצW��
	DWORD dwLine; ///< �渹
	DWORD dwDisp; ///< ������
	nstring szFuncName; ///< �禡�W��
	std::vector<int> ArgsList; ///< �ѼƦC��

	/**
	 * @brief ��l�Ƶ��c
	 */
	void Init();
};
//-----------------------------------------------------------------------------
/**
 * @brief Callstack�l��, ��X�쵲�c�C��
 * @param CallStack �O����X�즹�e����
 * @ingroup callstack
 */
void CallStackTrace(OUT std::vector<S_CallStack> &CallStack);
/**
 * @brief Callstack�l��, ��X��O���ɮ�
 * @note �p�G�ɮפ��s�b, �|�إߤ@��
 * @param szFilePath �O����X�즹���|���ɮ�
 * @ingroup callstack
 */
void CallStackTrace(IN const nstring &szFilePath);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------