/**
 * @file curlbase.h
 * @note curl基礎類別
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CURLBASE
#define _CURLBASE
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 初始化curl
 * @ingroup curl
 */
void CURLInitialize();
/**
 * @brief 釋放curl
 * @ingroup curl
 */
void CURLRelease();
//-----------------------------------------------------------------------------
/**
 * @brief curl錯誤類別
 * @ingroup curl
 */
class C_ErrorCURL : public C_ErrorBase
{
private:
	//-------------------------------------
	nstring m_szError; ///< 錯誤字串
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorCURL(IN CURLcode code);
	C_ErrorCURL(IN CURLMcode code);
	C_ErrorCURL(IN CURLFORMcode code);
	virtual ~C_ErrorCURL();
	//-------------------------------------
	operator bool () const;
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief curl基礎類別
 * @ingroup curl
 */
class C_CURLBase
{
private:
	//-------------------------------------
	CURL *m_pCURL; ///< curl handle
	//-------------------------------------

public:
	//-------------------------------------
	C_CURLBase();
	virtual ~C_CURLBase();
	//-------------------------------------
	operator CURL * () const;
	//-------------------------------------
	/**
	 * @brief 設定curl
	 * @param emOption 選項列舉
	 * @param ulValue 選項內容
	 * @return true表示成功, false則否
	 */
	bool Option(IN CURLoption emOption, IN unsigned long ulValue);
	/**
	 * @brief 設定curl
	 * @param emOption 選項列舉
	 * @param szValue 選項內容
	 * @return true表示成功, false則否
	 */
	bool Option(IN CURLoption emOption, IN const nstring &szValue);
	/**
	 * @brief 執行curl
	 * @return true表示成功, false則否
	 */
	bool Perform();
	/**
	 * @brief 取得輸入字串的URL編碼字串
	 * @param szInput 輸入字串
	 * @return URL編碼字串
	 */
	nstring URLEncode(IN const nstring &szInput);
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------