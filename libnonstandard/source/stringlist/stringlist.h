/**
 * @file stringlist.h
 * @note 文字檔案讀取器
 * @author yinweli
 */
/**
 * @page 如何使用stringlist
 * stringlist主要是提供純文字檔的讀取, 新增, 存檔的功能\n\n
 * 類別內是以一行作為儲存單位, 請不要對用 C_StringList.GetLine() 函式取到的字串做任何修改\n
 * 這個類別的存檔與讀檔都是以"純"文字進行, 目前不支援讀取Unicode格式檔案\n
 * 當然你還是可以存其他文字進去, 但是請在 C_StringList.AddLine() 時算好該字串的長度\n
 * 存檔與讀檔時請輸入完整的路徑與檔名, 副檔名\n\n
 * --------------------------------------------------\n
 * Header           : stringlist.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref stringlist
 */
/** @defgroup stringlist */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _STRINGLIST
#define _STRINGLIST
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\filetool\filetool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 文字檔案讀取器類別
 * @ingroup stringlist
 */
class C_StringList
{
private:
	//-----------------------------------
	bool m_bLoadFile; ///< 讀取檔案旗標
	std::list<nstring> m_StringList; ///< 字串列表
	//-----------------------------------

public:
	//-----------------------------------
	typedef std::list<nstring>::const_iterator const_iterator; ///< 字串列表迭代器型別
	//-----------------------------------

public:
	//-----------------------------------
	C_StringList();
	virtual ~C_StringList();
	//-----------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 取得讀取檔案旗標
	 */
	bool IsLoad() const;
	//-----------------------------------
	/**
	 * @brief 加入一行
	 * @param szInput 要加入的字串
	 * @param ulPos 要加入的位置
	 */
	void AddLine(IN const TCHAR *szInput, IN unsigned long ulPos = ULONG_MAX);
	/**
	 * @brief 加入一行到文件的最底端
	 * @param szInput 要加入的格式化字串, 與 printf 的格式一致
	 * @param ... 參數列表
	 */
	void AddLineEx(IN const TCHAR *szInput, ...);
	/**
	 * @brief 刪除一行
	 * @param ulPos 要刪除的位置
	 */
	void DelLine(IN unsigned long ulPos);
	/**
	 * @brief 取得一行
	 * @param ulPos 要取得的位置
	 * @return 字串
	 */
	const TCHAR *GetLine(IN unsigned long ulPos) const;
	/**
	 * @brief 取得一行
	 * @param ulPos 要取得的位置
	 * @return 字串
	 */
	nstring GetLineStr(IN unsigned long ulPos) const;
	/**
	 * @brief 取得一行的字數
	 * @param ulPos 要取得的位置
	 * @return 字數
	 */
	unsigned long GetLineLen(IN unsigned long ulPos) const;
	/**
	 * @brief 取得行數
	 * @return 總行數
	 */
	unsigned long GetLineCount() const;
	/**
	 * @brief 取得字串列表開頭迭代器
	 * @return 字串列表迭代器
	 */
	C_StringList::const_iterator Begin() const;
	/**
	 * @brief 取得字串列表結尾迭代器
	 * @return 字串列表迭代器
	 */
	C_StringList::const_iterator End() const;
	//-----------------------------------
	/**
	 * @brief 存檔
	 * @param szFilePath 要存檔的檔名路徑
	 * @param bAppend 是否是添加模式, true表示存檔時會把內容添加到檔案之後, false則否
	 * @param bAutoWrap 是否自動換行
	 * @param ulPos 存檔的開始位置
	 * @param ulLines 存檔的行數
	 * @return true表示存檔成功, false則否
	 */
	bool Save(IN const nstring &szFilePath, IN bool bAppend, IN bool bAutoWrap, IN unsigned long ulPos, IN unsigned long ulLines);
	/**
	 * @brief 存檔
	 * @param szFilePath 要存檔的檔名路徑
	 * @param bAppend 是否是添加模式, true表示存檔時會把內容添加到檔案之後, false則否
	 * @param bAutoWrap 是否自動換行
	 * @return true表示存檔成功, false則否
	 */
	bool Save(IN const nstring &szFilePath, IN bool bAppend, IN bool bAutoWrap);
	/**
	 * @brief 讀檔
	 * @param szFilePath 要讀檔的檔名路徑
	 * @return true表示讀檔成功, false則否
	 */
	bool Load(IN const nstring &szFilePath);
	//-----------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------