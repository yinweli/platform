/**
 * @file json.h
 * @note json類別
 * @author yinweli
 */
/**
 * @page 如何使用json
 * 這是個使用json(JavaScript Object Notation)格式的字串分析元件\n\n
 * 首先建立一個實體使用 C_Json 宣告如下\n\n
 * C_Json ccJson;\n\n
 * 然後呼叫 C_Json.Import() 匯入json格式字串\n
 * 或是呼叫 C_Json.Export() 匯出json格式字串\n
 * 若要新增資料, 就呼叫 C_Json.Add() 系列函式\n
 * 若要刪除資料, 就呼叫 C_Json.Del() 函式\n
 * 若要取得資料, 就呼叫 C_Json.Get() 系列函式\n
 * 如果繁體中文輸入了"許功蓋育"等字(事實上有很多字都會這樣)將會造成錯誤\n
 * 如果接收json字串的是C#程式, 則字串中如果有"\\"也會造成錯誤\n\n
 * --------------------------------------------------\n
 * Header           : json.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref json
 */
/** @defgroup json */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _JSON
#define _JSON
//-----------------------------------------------------------------------------
#ifdef _DEBUG
#pragma comment(lib, "..\\libthirdparty\\jsoncpp-1.0.0\\vc2013_lib_debug\\lib_json.lib")
#else
#pragma comment(lib, "..\\libthirdparty\\jsoncpp-1.0.0\\vc2013_lib_release\\lib_json.lib")
#endif
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\..\..\libthirdparty\jsoncpp-1.0.0\include\json.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief json類別
 * @ingroup json
 */
class C_Json
{
private:
	//-------------------------------------
	Json::Value m_Value; ///< json資料物件
	//-------------------------------------

public:
	//-------------------------------------
	C_Json();
	C_Json(IN const C_Json &data);
	virtual ~C_Json();
	//-------------------------------------
	C_Json &operator = (IN const C_Json &ccJson);
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 匯入字串
	 * @param szJson 字串
	 * @return true表示成功, false則否
	 */
	bool Import(IN const std::string &szJson);
	/**
	 * @brief 匯出字串
	 * @return json格式字串
	 */
	std::string Export() const;
	/**
	 * @brief 匯出字串 - 風格化字串
	 * @return json格式字串
	 */
	std::string ExportStyled() const;
	/**
	 * @brief 匯出字串 - 快速字串
	 * @return json格式字串
	 */
	std::string ExportFast() const;
	/**
	 * @brief 新增成員
	 * @param szName 成員名稱
	 * @param value 值
	 */
	void Add(IN const nstring &szName, IN bool value);
	/**
	 * @brief 新增成員
	 * @param szName 成員名稱
	 * @param value 值
	 */
	void Add(IN const nstring &szName, IN char value);
	/**
	 * @brief 新增成員
	 * @param szName 成員名稱
	 * @param value 值
	 */
	void Add(IN const nstring &szName, IN unsigned char value);
	/**
	 * @brief 新增成員
	 * @param szName 成員名稱
	 * @param value 值
	 */
	void Add(IN const nstring &szName, IN short value);
	/**
	 * @brief 新增成員
	 * @param szName 成員名稱
	 * @param value 值
	 */
	void Add(IN const nstring &szName, IN unsigned short value);
	/**
	 * @brief 新增成員
	 * @param szName 成員名稱
	 * @param value 值
	 */
	void Add(IN const nstring &szName, IN long value);
	/**
	 * @brief 新增成員
	 * @param szName 成員名稱
	 * @param value 值
	 */
	void Add(IN const nstring &szName, IN unsigned long value);
	/**
	 * @brief 新增成員
	 * @param szName 成員名稱
	 * @param value 值
	 */
	void Add(IN const nstring &szName, IN int value);
	/**
	 * @brief 新增成員
	 * @param szName 成員名稱
	 * @param value 值
	 */
	void Add(IN const nstring &szName, IN unsigned int value);
	/**
	 * @brief 新增成員
	 * @param szName 成員名稱
	 * @param value 值
	 */
	void Add(IN const nstring &szName, IN float value);
	/**
	 * @brief 新增成員
	 * @param szName 成員名稱
	 * @param value 值
	 */
	void Add(IN const nstring &szName, IN double value);
	/**
	 * @brief 新增成員
	 * @param szName 成員名稱
	 * @param value 值
	 */
	void Add(IN const nstring &szName, IN const std::string &value);
	/**
	 * @brief 新增成員
	 * @param szName 成員名稱
	 * @param value 值
	 */
	void Add(IN const nstring &szName, IN const std::wstring &value);
	/**
	 * @brief 新增陣列成員
	 * @param szName 成員名稱
	 * @param array 值陣列
	 */
	void Add(IN const nstring &szName, IN const std::vector<bool> &array);
	/**
	 * @brief 新增陣列成員
	 * @param szName 成員名稱
	 * @param array 值陣列
	 */
	void Add(IN const nstring &szName, IN const std::vector<char> &array);
	/**
	 * @brief 新增陣列成員
	 * @param szName 成員名稱
	 * @param array 值陣列
	 */
	void Add(IN const nstring &szName, IN const std::vector<unsigned char> &array);
	/**
	 * @brief 新增陣列成員
	 * @param szName 成員名稱
	 * @param array 值陣列
	 */
	void Add(IN const nstring &szName, IN const std::vector<short> &array);
	/**
	 * @brief 新增陣列成員
	 * @param szName 成員名稱
	 * @param array 值陣列
	 */
	void Add(IN const nstring &szName, IN const std::vector<unsigned short> &array);
	/**
	 * @brief 新增陣列成員
	 * @param szName 成員名稱
	 * @param array 值陣列
	 */
	void Add(IN const nstring &szName, IN const std::vector<long> &array);
	/**
	 * @brief 新增陣列成員
	 * @param szName 成員名稱
	 * @param array 值陣列
	 */
	void Add(IN const nstring &szName, IN const std::vector<unsigned long> &array);
	/**
	 * @brief 新增陣列成員
	 * @param szName 成員名稱
	 * @param array 值陣列
	 */
	void Add(IN const nstring &szName, IN const std::vector<int> &array);
	/**
	 * @brief 新增陣列成員
	 * @param szName 成員名稱
	 * @param array 值陣列
	 */
	void Add(IN const nstring &szName, IN const std::vector<unsigned int> &array);
	/**
	 * @brief 新增陣列成員
	 * @param szName 成員名稱
	 * @param array 值陣列
	 */
	void Add(IN const nstring &szName, IN const std::vector<float> &array);
	/**
	 * @brief 新增陣列成員
	 * @param szName 成員名稱
	 * @param array 值陣列
	 */
	void Add(IN const nstring &szName, IN const std::vector<double> &array);
	/**
	 * @brief 新增陣列成員
	 * @param szName 成員名稱
	 * @param array 值陣列
	 */
	void Add(IN const nstring &szName, IN const std::vector<std::string> &array);
	/**
	 * @brief 新增陣列成員
	 * @param szName 成員名稱
	 * @param array 值陣列
	 */
	void Add(IN const nstring &szName, IN const std::vector<std::wstring> &array);
	/**
	 * @brief 刪除成員
	 * @param szName 成員名稱
	 */
	void Del(IN const nstring &szName);
	/**
	 * @brief 取得成員
	 * @param szName 成員名稱
	 * @param value 值
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT bool &value) const;
	/**
	 * @brief 取得成員
	 * @param szName 成員名稱
	 * @param value 值
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT char &value) const;
	/**
	 * @brief 取得成員
	 * @param szName 成員名稱
	 * @param value 值
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT unsigned char &value) const;
	/**
	 * @brief 取得成員
	 * @param szName 成員名稱
	 * @param value 值
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT short &value) const;
	/**
	 * @brief 取得成員
	 * @param szName 成員名稱
	 * @param value 值
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT unsigned short &value) const;
	/**
	 * @brief 取得成員
	 * @param szName 成員名稱
	 * @param value 值
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT long &value) const;
	/**
	 * @brief 取得成員
	 * @param szName 成員名稱
	 * @param value 值
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT unsigned long &value) const;
	/**
	 * @brief 取得成員
	 * @param szName 成員名稱
	 * @param value 值
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT int &value) const;
	/**
	 * @brief 取得成員
	 * @param szName 成員名稱
	 * @param value 值
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT unsigned int &value) const;
	/**
	 * @brief 取得成員
	 * @param szName 成員名稱
	 * @param value 值
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT float &value) const;
	/**
	 * @brief 取得成員
	 * @param szName 成員名稱
	 * @param value 值
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT double &value) const;
	/**
	 * @brief 取得成員
	 * @param szName 成員名稱
	 * @param value 值
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT std::string &value) const;
	/**
	 * @brief 取得成員
	 * @param szName 成員名稱
	 * @param value 值
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT std::wstring &value) const;
	/**
	 * @brief 取得陣列成員
	 * @param szName 成員名稱
	 * @param value 值陣列
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT std::vector<bool> &value) const;
	/**
	 * @brief 取得陣列成員
	 * @param szName 成員名稱
	 * @param value 值陣列
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT std::vector<char> &value) const;
	/**
	 * @brief 取得陣列成員
	 * @param szName 成員名稱
	 * @param value 值陣列
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT std::vector<unsigned char> &value) const;
	/**
	 * @brief 取得陣列成員
	 * @param szName 成員名稱
	 * @param value 值陣列
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT std::vector<short> &value) const;
	/**
	 * @brief 取得陣列成員
	 * @param szName 成員名稱
	 * @param value 值陣列
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT std::vector<unsigned short> &value) const;
	/**
	 * @brief 取得陣列成員
	 * @param szName 成員名稱
	 * @param value 值陣列
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT std::vector<long> &value) const;
	/**
	 * @brief 取得陣列成員
	 * @param szName 成員名稱
	 * @param value 值陣列
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT std::vector<unsigned long> &value) const;
	/**
	 * @brief 取得陣列成員
	 * @param szName 成員名稱
	 * @param value 值陣列
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT std::vector<int> &value) const;
	/**
	 * @brief 取得陣列成員
	 * @param szName 成員名稱
	 * @param value 值陣列
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT std::vector<unsigned int> &value) const;
	/**
	 * @brief 取得陣列成員
	 * @param szName 成員名稱
	 * @param value 值陣列
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT std::vector<float> &value) const;
	/**
	 * @brief 取得陣列成員
	 * @param szName 成員名稱
	 * @param value 值陣列
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT std::vector<double> &value) const;
	/**
	 * @brief 取得陣列成員
	 * @param szName 成員名稱
	 * @param value 值陣列
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT std::vector<std::string> &value) const;
	/**
	 * @brief 取得陣列成員
	 * @param szName 成員名稱
	 * @param value 值陣列
	 * @return true表示成功, false則否
	 */
	bool Get(IN const nstring &szName, OUT std::vector<std::wstring> &value) const;
	/**
	 * @brief 以字串型態取得成員
	 * @param szName 成員名稱
	 * @return 結果字串
	 */
	std::string ToString(IN const nstring &szName) const;
	/**
	 * @brief 以字串型態取得成員
	 * @param szName 成員名稱
	 * @return 結果字串
	 */
	std::wstring ToWString(IN const nstring &szName) const;
	/**
	 * @brief 以字串型態取得陣列成員
	 * @param szName 成員名稱
	 * @param ulIndex 索引值
	 * @return 結果字串
	 */
	std::string ToString(IN const nstring &szName, IN unsigned long ulIndex) const;
	/**
	 * @brief 以字串型態取得陣列成員
	 * @param szName 成員名稱
	 * @param ulIndex 索引值
	 * @return 結果字串
	 */
	std::wstring ToWString(IN const nstring &szName, IN unsigned long ulIndex) const;
	/**
	 * @brief 取得成員型態
	 * @param szName 成員名稱
	 */
	Json::ValueType Type(IN const nstring &szName) const;
	/**
	 * @brief 檢查成員是否存在
	 * @param szName 成員名稱
	 * @return true表示存在, false則否
	 */
	bool IsExist(IN const nstring &szName) const;
	/**
	 * @brief 檢查是否為空
	 * @return true表示為空, false則否
	 */
	bool Empty() const;
	/**
	 * @brief 取得json資料物件名稱列表
	 * @return 名稱列表
	 */
	std::vector<nstring> Member() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------