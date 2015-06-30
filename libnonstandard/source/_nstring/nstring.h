/**
 * @file nstring.h
 * @note �r��B�z���O
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
typedef std::string nstring; ///< STL�r�ꫬ�O�w�q, �bunicode�sĶ��, nstring�۷��std::wstring, �_�h�N�Ostd::string @ingroup nstring
#else
typedef std::wstring nstring; ///< STL�r�ꫬ�O�w�q, �bunicode�sĶ��, nstring�۷��std::wstring, �_�h�N�Ostd::string @ingroup nstring
#endif
//-----------------------------------------------------------------------------
/**
 * @brief �r��B�z���O
 * @note C_NString �O�Ӧr��e��, �Ω� char *, wchar_t *, std::string, std::wstring, _bstr_t �������r���ഫ\n
 *       �t�~�]���ѹB��l�䴩�r��զX, ���, �]��
 * @ingroup nstring
 */
class C_NString
{
private:
	//-------------------------------------
#ifndef UNICODE
	std::string m_szString_m; ///< �D�n�r��
	std::wstring m_szString_s; ///< ���n�r��
#else
	std::wstring m_szString_m; ///< �D�n�r��
	std::string m_szString_s; ///< ���n�r��
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
	// �૬�B��l
	operator std::string () const;
	operator std::wstring () const;
	operator _bstr_t () const;
	// << �B��l
	C_NString &operator << (IN const C_NString &sz);
	C_NString &operator << (IN const char *sz);
	C_NString &operator << (IN const wchar_t *sz);
	C_NString &operator << (IN const std::string &sz);
	C_NString &operator << (IN const std::wstring &sz);
	C_NString &operator << (IN const _bstr_t &sz);
	// = �B��l
	C_NString &operator = (IN const C_NString &sz);
	C_NString &operator = (IN const char *sz);
	C_NString &operator = (IN const wchar_t *sz);
	C_NString &operator = (IN const std::string &sz);
	C_NString &operator = (IN const std::wstring &sz);
	C_NString &operator = (IN const _bstr_t &sz);
	// += �B��l
	C_NString &operator += (IN const C_NString &sz);
	C_NString &operator += (IN const char *sz);
	C_NString &operator += (IN const wchar_t *sz);
	C_NString &operator += (IN const std::string &sz);
	C_NString &operator += (IN const std::wstring &sz);
	C_NString &operator += (IN const _bstr_t &sz);
	// < �B��l
	bool operator < (IN const C_NString &sz) const;
	bool operator < (IN const char *sz) const;
	bool operator < (IN const wchar_t *sz) const;
	bool operator < (IN const std::string &sz) const;
	bool operator < (IN const std::wstring &sz) const;
	bool operator < (IN const _bstr_t &sz) const;
	// > �B��l
	bool operator > (IN const C_NString &sz) const;
	bool operator > (IN const char *sz) const;
	bool operator > (IN const wchar_t *sz) const;
	bool operator > (IN const std::string &sz) const;
	bool operator > (IN const std::wstring &sz) const;
	bool operator > (IN const _bstr_t &sz) const;
	// <= �B��l
	bool operator <= (IN const C_NString &sz) const;
	bool operator <= (IN const char *sz) const;
	bool operator <= (IN const wchar_t *sz) const;
	bool operator <= (IN const std::string &sz) const;
	bool operator <= (IN const std::wstring &sz) const;
	bool operator <= (IN const _bstr_t &sz) const;
	// >= �B��l
	bool operator >= (IN const C_NString &sz) const;
	bool operator >= (IN const char *sz) const;
	bool operator >= (IN const wchar_t *sz) const;
	bool operator >= (IN const std::string &sz) const;
	bool operator >= (IN const std::wstring &sz) const;
	bool operator >= (IN const _bstr_t &sz) const;
	// != �B��l
	bool operator != (IN const C_NString &sz) const;
	bool operator != (IN const char *sz) const;
	bool operator != (IN const wchar_t *sz) const;
	bool operator != (IN const std::string &sz) const;
	bool operator != (IN const std::wstring &sz) const;
	bool operator != (IN const _bstr_t &sz) const;
	// == �B��l
	bool operator == (IN const C_NString &sz) const;
	bool operator == (IN const char *sz) const;
	bool operator == (IN const wchar_t *sz) const;
	bool operator == (IN const std::string &sz) const;
	bool operator == (IN const std::wstring &sz) const;
	bool operator == (IN const _bstr_t &sz) const;
	/**
	 * @brief �ƻs��char�r��}�C
	 * @param sz �ؼЦr��
	 * @param ulInputSize �ؼЦr�����, �i�H�ϥ�_countof()�o��
	 */
	void copyto(OUT char *sz, IN unsigned long ulInputSize) const;
	/**
	 * @brief �ƻs��wchar_t�r��}�C
	 * @param sz �ؼЦr��
	 * @param ulInputSize �ؼЦr�����, �i�H�ϥ�_countof()�o��
	 */
	void copyto(OUT wchar_t *sz, IN unsigned long ulInputSize) const;
	/**
	 * @brief �H char * �Ҧ����o�x�s���r��
	 * @return �r�����
	 */
	const char *c_str() const;
	/**
	 * @brief �H wchar_t * �Ҧ����o�x�s���r��
	 * @return �r�����
	 */
	const wchar_t *w_str() const;
	/**
	 * @brief �H TCHAR * �Ҧ����o�x�s���r��
	 * @return �r�����
	 */
	const TCHAR *t_str() const;
	/**
	 * @brief ���o�r�����
	 * @return �r�����
	 */
	std::string::size_type size() const;
	/**
	 * @brief ���o�r��O�_����
	 * @return true��ܦr�ꬰ��, false�h�_
	 */
	bool empty() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------