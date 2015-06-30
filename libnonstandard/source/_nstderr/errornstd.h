/**
 * @file errornstd.h
 * @note 錯誤訊息類別
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
#define ERRORNSTD _NSTD::C_ErrorNSTD(__LINE__, __FILEX__, __FUNCTIONX__) ///< 取得錯誤訊息物件 @ingroup nstderror
//-----------------------------------------------------------------------------
/**
 * @brief 錯誤訊息類別
 * @ingroup nstderror
 */
class C_ErrorNSTD : public C_ErrorBase
{
private:
	//-------------------------------------
	unsigned long m_ulLine; ///< 行號
	estring m_szFile; ///< 檔案名稱
	estring m_szFunc; ///< 函式名稱
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