/**
 * @file inifile.h
 * @note ini檔案讀取類別
 * @author yinweli
 */
/**
 * @page 如何使用inifile
 * inifile用於ini檔案操作\n\n
 * 首先建立一個實體使用 C_IniFile 宣告如下\n\n
 * C_IniFile ccIni;\n\n
 * 接著呼叫 C_IniFile.Initialize() 函式把想要讀取的ini檔案加入類別中\n
 * 然後就可以呼叫 C_IniFile.Get() 函式來取得ini中的設定值\n\n
 * --------------------------------------------------\n
 * Header           : inifile.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref inifile
 */
/** @defgroup inifile */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _INIFILE
#define _INIFILE
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\argument\argument.h"
#include "..\filetool\filetool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ini不存在錯誤類別
 * @ingroup inifile
 */
class C_ErrorIniNotExist : public C_ErrorBase
{
private:
	//-------------------------------------
	estring m_szError; ///< 錯誤字串
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorIniNotExist(IN const nstring &filepath);
	virtual ~C_ErrorIniNotExist();
	//-------------------------------------
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief ini讀取錯誤類別
 * @ingroup inifile
 */
class C_ErrorIniNotFound : public C_ErrorBase
{
private:
	//-------------------------------------
	estring m_szError; ///< 錯誤字串
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorIniNotFound(IN const nstring &filepath, IN const nstring &section, IN const estring &key);
	virtual ~C_ErrorIniNotFound();
	//-------------------------------------
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 取得設定值
 * @param szFilePath 檔名路徑
 * @param szSection 區段名稱
 * @param szKey 索引名稱
 * @param ccValue 設定值
 * @return true表示成功, false則否
 */
bool GetIniValue(IN const nstring &szFilePath, IN const nstring &szSection, IN const nstring &szKey, OUT C_Argu &ccValue);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------