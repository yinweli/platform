/**
 * @file nstring.h
 * @note 字串處理類別
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _nstring
#define _nstring
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#ifndef UNICODE
typedef std::string nstring; ///< STL字串型別定義, 在unicode編譯時, nstring相當於std::wstring, 否則就是std::string @ingroup nstring
#else
typedef std::wstring nstring; ///< STL字串型別定義, 在unicode編譯時, nstring相當於std::wstring, 否則就是std::string @ingroup nstring
#endif
//-----------------------------------------------------------------------------
/**
 * @brief 字串處理類別
 * @note C_NString 是個字串容器, 用於 char *, wchar_t *, std::string, std::wstring, _bstr_t 之間的字串轉換\n
 *       另外也提供運算子支援字串組合, 比較, 設值
 * @ingroup nstring
 */
class C_NString
{
private:
	//-------------------------------------
#ifndef UNICODE
	std::string m_szString_m; ///< 主要字串
	std::wstring m_szString_s; ///< 次要字串
#else
	std::wstring m_szString_m; ///< 主要字串
	std::string m_szString_s; ///< 次要字串
#endif
	//-------------------------------------

public:
	//-------------------------------------
	C_NString();
	C_NString(IN const C_NString &sz);
	C_NString(IN const char *sz);
	C_NString(IN const wchar_t *sz);
	C_NString(IN const std::string &sz);
	C_NString(IN const std::wstring &sz);
	C_NString(IN const _bstr_t &sz);
	virtual ~C_NString();
	//-------------------------------------
	// 轉型運算子
	operator std::string () const;
	operator std::wstring () const;
	operator _bstr_t () const;
	// << 運算子
	C_NString &operator << (IN const C_NString &sz);
	C_NString &operator << (IN const char *sz);
	C_NString &operator << (IN const wchar_t *sz);
	C_NString &operator << (IN const std::string &sz);
	C_NString &operator << (IN const std::wstring &sz);
	C_NString &operator << (IN const _bstr_t &sz);
	// = 運算子
	C_NString &operator = (IN const C_NString &sz);
	C_NString &operator = (IN const char *sz);
	C_NString &operator = (IN const wchar_t *sz);
	C_NString &operator = (IN const std::string &sz);
	C_NString &operator = (IN const std::wstring &sz);
	C_NString &operator = (IN const _bstr_t &sz);
	// += 運算子
	C_NString &operator += (IN const C_NString &sz);
	C_NString &operator += (IN const char *sz);
	C_NString &operator += (IN const wchar_t *sz);
	C_NString &operator += (IN const std::string &sz);
	C_NString &operator += (IN const std::wstring &sz);
	C_NString &operator += (IN const _bstr_t &sz);
	// < 運算子
	bool operator < (IN const C_NString &sz) const;
	bool operator < (IN const char *sz) const;
	bool operator < (IN const wchar_t *sz) const;
	bool operator < (IN const std::string &sz) const;
	bool operator < (IN const std::wstring &sz) const;
	bool operator < (IN const _bstr_t &sz) const;
	// > 運算子
	bool operator > (IN const C_NString &sz) const;
	bool operator > (IN const char *sz) const;
	bool operator > (IN const wchar_t *sz) const;
	bool operator > (IN const std::string &sz) const;
	bool operator > (IN const std::wstring &sz) const;
	bool operator > (IN const _bstr_t &sz) const;
	// <= 運算子
	bool operator <= (IN const C_NString &sz) const;
	bool operator <= (IN const char *sz) const;
	bool operator <= (IN const wchar_t *sz) const;
	bool operator <= (IN const std::string &sz) const;
	bool operator <= (IN const std::wstring &sz) const;
	bool operator <= (IN const _bstr_t &sz) const;
	// >= 運算子
	bool operator >= (IN const C_NString &sz) const;
	bool operator >= (IN const char *sz) const;
	bool operator >= (IN const wchar_t *sz) const;
	bool operator >= (IN const std::string &sz) const;
	bool operator >= (IN const std::wstring &sz) const;
	bool operator >= (IN const _bstr_t &sz) const;
	// != 運算子
	bool operator != (IN const C_NString &sz) const;
	bool operator != (IN const char *sz) const;
	bool operator != (IN const wchar_t *sz) const;
	bool operator != (IN const std::string &sz) const;
	bool operator != (IN const std::wstring &sz) const;
	bool operator != (IN const _bstr_t &sz) const;
	// == 運算子
	bool operator == (IN const C_NString &sz) const;
	bool operator == (IN const char *sz) const;
	bool operator == (IN const wchar_t *sz) const;
	bool operator == (IN const std::string &sz) const;
	bool operator == (IN const std::wstring &sz) const;
	bool operator == (IN const _bstr_t &sz) const;
	/**
	 * @brief 複製到char字串陣列
	 * @param sz 目標字串
	 * @param ulInputSize 目標字串長度, 可以使用_countof()得到
	 */
	void copyto(OUT char *sz, IN unsigned long ulInputSize) const;
	/**
	 * @brief 複製到wchar_t字串陣列
	 * @param sz 目標字串
	 * @param ulInputSize 目標字串長度, 可以使用_countof()得到
	 */
	void copyto(OUT wchar_t *sz, IN unsigned long ulInputSize) const;
	/**
	 * @brief 以 char * 模式取得儲存的字串
	 * @return 字串指標
	 */
	const char *c_str() const;
	/**
	 * @brief 以 wchar_t * 模式取得儲存的字串
	 * @return 字串指標
	 */
	const wchar_t *w_str() const;
	/**
	 * @brief 以 TCHAR * 模式取得儲存的字串
	 * @return 字串指標
	 */
	const TCHAR *t_str() const;
	/**
	 * @brief 取得字串長度
	 * @return 字串長度
	 */
	std::string::size_type size() const;
	/**
	 * @brief 取得字串是否為空
	 * @return true表示字串為空, false則否
	 */
	bool empty() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------