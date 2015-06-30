/**
 * @file xmlstring.h
 * @note XML字串表類別
 * @author yinweli
 */
/**
 * @page 如何使用xmlstring
 * xmlstring提供讀取特定格式的XML文件, 並且把文件內存的字串以編號為索引保存類別裡\n\n
 * 首先建立 C_XMLString\n\n
 * C_XMLString ccXML;\n\n
 * 然後可以重複呼叫 C_XMLString.Load() 來讀取多個XML文件\n
 * 接著呼叫 C_XMLString.Get() 以索引值與編號來取得保存的字串\n
 * 如果發生錯誤時(例如呼叫 C_XMLString.Load() 失敗)可以呼叫 C_XMLString.GetError() 取得錯誤訊息\n\n
 * XML文件的格式範例如下:\n\n
 * <test>\n
 * <str    id = "2">第一個字</str>\n
 * <key001 id = "0">第二個字</key001>\n
 * <key002 id = "1">第三個字</key002>\n
 * </test>\n
 * 跟 C_XMLString 的格式不同的是, str 可以改成其他名稱\n
 * id 代表的數字就是該字串的索引值\n
 * 字串內同時也可以填寫如 %%s, %%d 等 printf 的格式化字串\n\n
 * 最後要注意, 目前這個元件只能讀取ANSI與Unicode的檔案, 如果是UTF-8會造成錯誤
 * --------------------------------------------------\n
 * Header           : xmlstring.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref xmlstring
 */
/** @defgroup xmlstring */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XMLSTRING
#define _XMLSTRING
//-----------------------------------------------------------------------------
#ifdef _DEBUG
#pragma comment(lib, "..\\libthirdparty\\tinyxml 2.6.2\\vc2013_lib_debug\\tinyxmld.lib")
#else
#pragma comment(lib, "..\\libthirdparty\\tinyxml 2.6.2\\vc2013_lib_release\\tinyxml.lib")
#endif
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\..\..\libthirdparty\tinyxml 2.6.2\include\tinyxml.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#define XMLSTRINGID "id" ///< XML代表字串索引值的名稱 @ingroup xmlstring
//-----------------------------------------------------------------------------
/**
 * @brief XML字串表錯誤類別
 * @ingroup xmlstring
 */
class C_ErrorXMLString : public C_ErrorBase
{
private:
	//-------------------------------------
	estring m_szError; ///< 錯誤字串
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorXMLString(IN const TiXmlDocument &xmldoc);
	virtual ~C_ErrorXMLString();
	//-------------------------------------
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief XML字串表類別
 * @ingroup xmlstring
 */
class C_XMLString
{
private:
	//-------------------------------------
	std::map<nstring, nstring> m_StringList; ///< 字串列表 <字串名稱, 內容>
	std::map<nstring, nstring>::iterator m_Itor;
	//-------------------------------------

public:
	//-------------------------------------
	C_XMLString();
	virtual ~C_XMLString();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 讀取字串檔案, 可以重複載入多個檔案
	 * @param szFile 檔案路徑以及檔名
	 * @return true表示成功, false則否
	 */
	bool Load(IN const nstring &szFile);
	/**
	 * @brief 取得字串
	 * @note 此函式的索引值格式, 如下範例:\n\n
	 *       <string001>\n
	 *       <type id = "0">字串1</type>\n
	 *       <string002>\n
	 *       <type id = "1">字串2</type>\n
	 *       <string003>\n
	 *       <xxxx id = "2">字串3</xxxx>\n
	 *       </string003>\n
	 *       </string002>\n
	 *       </string001>\n\n
	 *       要取得 "字串1" 的話, 索引值必須是 "string001:type:0"\n
	 *       要取得 "字串2" 的話, 索引值必須是 "string001:string002:type:1"\n
	 *       要取得 "字串3" 的話, 索引值必須是 "string001:string002:string003:type:2"\n
	 * @param szKey 索引值
	 * @param szDefault 如果找不到字串, 傳回的字串
	 * @return 字串
	 */
	nstring Get(IN const nstring &szKey, IN const nstring &szDefault = __T("")) const;
	/**
	 * @brief 取得字串
	 * @note 此函式會把索引值列表以及編號的內容組合成類似 "string001:string002:string003:type:2" 的模式, 當作索引值去查詢字串
	 * @param KeyList 索引值列表
	 * @param iID 編號
	 * @param szDefault 如果找不到字串, 傳回的字串
	 * @return 字串
	 */
	nstring Get(IN const std::vector<nstring> &KeyList, IN int iID, IN const nstring &szDefault = __T("")) const;
	/**
	 * @brief 取得字串數量
	 * @return 字串數量
	 */
	int Size() const;
	/**
	 * @brief 重置迭代器
	 */
	void ResetItor();
	/**
	 * @brief 依序取得字串
	 * @param szKey 字串的索引值
	 * @param szString 字串
	 * @return true表示這次的取得成功, false則否
	 */
	bool GetDataByOrder(OUT nstring &szKey, OUT nstring &szString);
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------