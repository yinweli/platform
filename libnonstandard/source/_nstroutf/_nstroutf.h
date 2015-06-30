/**
 * @file _nstroutf
 * @note 格式化字串類別
 * @author yinweli
 */
/**
 * @page 如何使用_nstroutf
 * _nstroutf是用於取得格式化字串的類別\n\n
 * 注意! 字串中將無法輸出 { 與 } 符號\n\n
 * 格式化語法為 {[旗標列][寬度]}\n
 * [旗標列] :\n
 * o : 如果是數值, 以8進位輸出\n
 * x : 如果是數值, 以小寫16進位輸出\n
 * X : 如果是數值, 以大寫16進位輸出\n
 * L : 靠左對齊\n
 * R : 靠右對齊(預設值)\n
 * 0 : 靠右對齊時, 空白的部分補0\n
 * [寬度] :\n
 * 輸出的寬度\n\n
 * 例如 : {} {10} {+10} {-10} { 10} {-010}\n\n
 * --------------------------------------------------\n
 * Header           : _nstroutf.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref _nstroutf
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
#define nsoutf(format) C_NStrOutf(format) ///< 格式化字串類別的別名巨集 @ingroup _nstroutf
//-----------------------------------------------------------------------------
/**
 * @brief 格式化字串類別
 * @ingroup _nstroutf
 */
class C_NStrOutf
{
private:
	//-------------------------------------
	nstring m_szFormat; ///< 格式字串
	std::vector<nstring> m_Data; ///< 資料列表
	//-------------------------------------

public:
	//-------------------------------------
	C_NStrOutf(IN const nstring &format);
	virtual ~C_NStrOutf();
	//-------------------------------------
	operator nstring () const;
	//-------------------------------------
	// << 運算子
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