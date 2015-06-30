/**
 * @file errornstd.h
 * @note ���~�T�����O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _ERRORNSTD
#define _ERRORNSTD
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#define ERRORNSTD _NSTD::C_ErrorNSTD(__LINE__, __FILEX__, __FUNCTIONX__) ///< ���o���~�T������ @ingroup nstderror
//-----------------------------------------------------------------------------
/**
 * @brief ���~�T�����O
 * @ingroup nstderror
 */
class C_ErrorNSTD : public C_ErrorBase
{
private:
	//-------------------------------------
	unsigned long m_ulLine; ///< �渹
	estring m_szFile; ///< �ɮצW��
	estring m_szFunc; ///< �禡�W��
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorNSTD(IN unsigned long line, IN const estring &file, IN const estring &func);
	virtual ~C_ErrorNSTD();
	//-------------------------------------
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------