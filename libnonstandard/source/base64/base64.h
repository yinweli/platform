/**
 * @file base64.h
 * @note base64�s�ѽX���O
 * @author yinweli
 */
/**
 * @page �p��ϥ�base64
 * base64�ΨӳB�zbase64�s�X�P�ѽX\n\n
 * --------------------------------------------------\n
 * Header           : base64.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref base64
 */
/** @defgroup base64 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _BASE64
#define _BASE64
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief base64�s�ѽX���O
 * @ingroup base64
 */
class C_Base64
{
private:
	//-------------------------------------
	static const char m_Padding; ///< ��R�r��
	static const char m_Encode[]; ///< �s�X��
	static const char m_Decode[]; ///< �ѽX��
	static const int m_Mod[]; ///< ���ƪ�
	//-------------------------------------

public:
	//-------------------------------------
	/**
	 * @brief base64�s�X
	 * @param szData �r��
	 * @return ���G�r��
	 */
	nstring Encode(IN const nstring &szData) const;
	/**
	 * @brief base64�ѽX
	 * @param szData �r��
	 * @return ���G�r��
	 */
	nstring Decode(IN const nstring &szData) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------