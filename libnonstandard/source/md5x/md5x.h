/**
 * @file md5x.h
 * @note MD5�s�X�t�C�禡
 * @author yinweli
 */
/**
 * @page �p��ϥ�md5x
 * md5x�����禡�Ω�MD5�s�X\n\n
 * --------------------------------------------------\n
 * Header           : md5x.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref md5x
 */
/** @defgroup md5x */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _MD5X
#define _MD5X
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#define MD5CODE_SIZE 16 ///< MD5�s�X���G���� @ingroup md5x
//-----------------------------------------------------------------------------
/**
 * @brief MD5�s�X���G���c
 * @ingroup md5x
 */
struct S_MD5Code
{
	unsigned char MD5Code[MD5CODE_SIZE]; ///< MD5�s�X���G�}�C
	nstring szMD5Code; ///< MD5�s�X���G�r��

	S_MD5Code();
};
//-----------------------------------------------------------------------------
/**
 * @brief ���oMD5�s�X
 * @param p �n�s�X����ƫ���
 * @param uiSize ��ƪ���
 * @return �s�X���G
 * @ingroup md5x
 */
S_MD5Code GetMD5Code(IN const void *p, IN unsigned int uiSize);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
