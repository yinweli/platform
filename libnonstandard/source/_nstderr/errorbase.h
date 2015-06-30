/**
 * @file errorbase.h
 * @note 基礎錯誤類別
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
typedef std::string estring; ///< 錯誤字串型別定義, 在unicode編譯時, estring相當於std::wstring, 否則就是std::string @ingroup nstderror
#else
typedef std::wstring estring; ///< 錯誤字串型別定義, 在unicode編譯時, estring相當於std::wstring, 否則就是std::string @ingroup nstderror
#endif
//-----------------------------------------------------------------------------
/**
 * @brief 基礎錯誤類別
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