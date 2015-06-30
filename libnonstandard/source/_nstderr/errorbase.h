/**
 * @file errorbase.h
 * @note ��¦���~���O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _ERRORBASE
#define _ERRORBASE
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#ifndef UNICODE
typedef std::string estring; ///< ���~�r�ꫬ�O�w�q, �bunicode�sĶ��, estring�۷��std::wstring, �_�h�N�Ostd::string @ingroup nstderror
#else
typedef std::wstring estring; ///< ���~�r�ꫬ�O�w�q, �bunicode�sĶ��, estring�۷��std::wstring, �_�h�N�Ostd::string @ingroup nstderror
#endif
//-----------------------------------------------------------------------------
/**
 * @brief ��¦���~���O
 * @ingroup nstderror
 */
class C_ErrorBase
{
public:
	//-------------------------------------
	virtual ~C_ErrorBase();
	//-------------------------------------
	virtual operator estring () const = 0;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------