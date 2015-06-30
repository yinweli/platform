/**
 * @file _nstroutf
 * @note �榡�Ʀr�����O
 * @author yinweli
 */
/**
 * @page �p��ϥ�_nstroutf
 * _nstroutf�O�Ω���o�榡�Ʀr�ꪺ���O\n\n
 * �`�N! �r�ꤤ�N�L�k��X { �P } �Ÿ�\n\n
 * �榡�ƻy�k�� {[�X�ЦC][�e��]}\n
 * [�X�ЦC] :\n
 * o : �p�G�O�ƭ�, �H8�i���X\n
 * x : �p�G�O�ƭ�, �H�p�g16�i���X\n
 * X : �p�G�O�ƭ�, �H�j�g16�i���X\n
 * L : �a�����\n
 * R : �a�k���(�w�]��)\n
 * 0 : �a�k�����, �ťժ�������0\n
 * [�e��] :\n
 * ��X���e��\n\n
 * �Ҧp : {} {10} {+10} {-10} { 10} {-010}\n\n
 * --------------------------------------------------\n
 * Header           : _nstroutf.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref _nstroutf
 */
/** @defgroup _nstroutf */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _SPRINTF
#define _SPRINTF
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#define nsoutf(format) C_NStrOutf(format) ///< �榡�Ʀr�����O���O�W���� @ingroup _nstroutf
//-----------------------------------------------------------------------------
/**
 * @brief �榡�Ʀr�����O
 * @ingroup _nstroutf
 */
class C_NStrOutf
{
private:
	//-------------------------------------
	nstring m_szFormat; ///< �榡�r��
	std::vector<nstring> m_Data; ///< ��ƦC��
	//-------------------------------------

public:
	//-------------------------------------
	C_NStrOutf(IN const nstring &format);
	virtual ~C_NStrOutf();
	//-------------------------------------
	operator nstring () const;
	//-------------------------------------
	// << �B��l
	C_NStrOutf &operator << (IN bool v);
	C_NStrOutf &operator << (IN char v);
	C_NStrOutf &operator << (IN unsigned char v);
	C_NStrOutf &operator << (IN short v);
	C_NStrOutf &operator << (IN unsigned short v);
	C_NStrOutf &operator << (IN long v);
	C_NStrOutf &operator << (IN unsigned long v);
	C_NStrOutf &operator << (IN int v);
	C_NStrOutf &operator << (IN unsigned int v);
	C_NStrOutf &operator << (IN __int64 v);
	C_NStrOutf &operator << (IN unsigned __int64 v);
	C_NStrOutf &operator << (IN float v);
	C_NStrOutf &operator << (IN double v);
	C_NStrOutf &operator << (IN const char *v);
	C_NStrOutf &operator << (IN const wchar_t *v);
	C_NStrOutf &operator << (IN const std::string &v);
	C_NStrOutf &operator << (IN const std::wstring &v);
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------