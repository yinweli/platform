//-----------------------------------------------------------------------------
#include "_nstring.h"
#include "nstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
#ifdef UNICODE
//-----------------------------------------------------------------------------
C_NString::C_NString() {}
//-----------------------------------------------------------------------------
C_NString::C_NString(IN const C_NString &sz) : m_szString_m(sz.m_szString_m) {}
//-----------------------------------------------------------------------------
C_NString::C_NString(IN const char *sz) : m_szString_m(sz ? _bstr_t(sz) : "") {}
//-----------------------------------------------------------------------------
C_NString::C_NString(IN const wchar_t *sz) : m_szString_m(sz ? sz : L"") {}
//-----------------------------------------------------------------------------
C_NString::C_NString(IN const std::string &sz) : m_szString_m(nsconv(sz)) {}
//-----------------------------------------------------------------------------
C_NString::C_NString(IN const std::wstring &sz) : m_szString_m(sz) {}
//-----------------------------------------------------------------------------
C_NString::C_NString(IN const _bstr_t &sz) : m_szString_m(static_cast<const wchar_t *>(sz)) {}
//-----------------------------------------------------------------------------
C_NString::~C_NString() {}
//-----------------------------------------------------------------------------
C_NString::operator std::string () const
{
	return nsconv(m_szString_m);
}
//-----------------------------------------------------------------------------
C_NString::operator std::wstring () const
{
	return m_szString_m;
}
//-----------------------------------------------------------------------------
C_NString::operator _bstr_t () const
{
	return m_szString_m.c_str();
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator << (IN const C_NString &sz)
{
	if(sz.empty() == false)
		m_szString_m += sz.m_szString_m;

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator << (IN const char *sz)
{
	if(sz)
		m_szString_m += nsconv(std::string(sz));

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator << (IN const wchar_t *sz)
{
	if(sz)
		m_szString_m += sz;

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator << (IN const std::string &sz)
{
	if(sz.empty() == false)
		m_szString_m += nsconv(sz);

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator << (IN const std::wstring &sz)
{
	if(sz.empty() == false)
		m_szString_m += sz;

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator << (IN const _bstr_t &sz)
{
	m_szString_m += static_cast<const wchar_t *>(sz);

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator = (IN const C_NString &sz)
{
	m_szString_m = sz.m_szString_m;

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator = (IN const char *sz)
{
	m_szString_m = sz ? nsconv(std::string(sz)) : L"";

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator = (IN const wchar_t *sz)
{
	m_szString_m = sz ? sz : L"";

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator = (IN const std::string &sz)
{
	m_szString_m = nsconv(sz);

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator = (IN const std::wstring &sz)
{
	m_szString_m = sz;

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator = (IN const _bstr_t &sz)
{
	m_szString_m = static_cast<const wchar_t *>(sz);

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator += (IN const C_NString &sz)
{
	m_szString_m += sz.m_szString_m;

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator += (IN const char *sz)
{
	if(sz)
		m_szString_m += nsconv(sz);

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator += (IN const wchar_t *sz)
{
	if(sz)
		m_szString_m = sz;

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator += (IN const std::string &sz)
{
	m_szString_m += nsconv(sz);

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator += (IN const std::wstring &sz)
{
	m_szString_m = sz;

	return *this;
}
//-----------------------------------------------------------------------------
C_NString &C_NString::operator += (IN const _bstr_t &sz)
{
	m_szString_m += static_cast<const wchar_t *>(sz);

	return *this;
}
//-----------------------------------------------------------------------------
bool C_NString::operator < (IN const C_NString &sz) const
{
	return m_szString_m < sz.m_szString_m;
}
//-----------------------------------------------------------------------------
bool C_NString::operator < (IN const char *sz) const
{
	return sz ? m_szString_m < nsconv(std::string(sz)) : false;
}
//-----------------------------------------------------------------------------
bool C_NString::operator < (IN const wchar_t *sz) const
{
	return sz ? m_szString_m < sz : false;
}
//-----------------------------------------------------------------------------
bool C_NString::operator < (IN const std::string &sz) const
{
	return m_szString_m < nsconv(sz);
}
//-----------------------------------------------------------------------------
bool C_NString::operator < (IN const std::wstring &sz) const
{
	return m_szString_m < sz;
}
//-----------------------------------------------------------------------------
bool C_NString::operator < (IN const _bstr_t &sz) const
{
	return m_szString_m < static_cast<const wchar_t *>(sz);
}
//-----------------------------------------------------------------------------
bool C_NString::operator > (IN const C_NString &sz) const
{
	return m_szString_m > sz.m_szString_m;
}
//-----------------------------------------------------------------------------
bool C_NString::operator > (IN const char *sz) const
{
	return sz ? m_szString_m > nsconv(std::string(sz)) : false;
}
//-----------------------------------------------------------------------------
bool C_NString::operator > (IN const wchar_t *sz) const
{
	return sz ? m_szString_m > sz : false;
}
//-----------------------------------------------------------------------------
bool C_NString::operator > (IN const std::string &sz) const
{
	return m_szString_m > nsconv(sz);
}
//-----------------------------------------------------------------------------
bool C_NString::operator > (IN const std::wstring &sz) const
{
	return m_szString_m > sz;
}
//-----------------------------------------------------------------------------
bool C_NString::operator > (IN const _bstr_t &sz) const
{
	return m_szString_m > static_cast<const wchar_t *>(sz);
}
//-----------------------------------------------------------------------------
bool C_NString::operator <= (IN const C_NString &sz) const
{
	return m_szString_m <= sz.m_szString_m;
}
//-----------------------------------------------------------------------------
bool C_NString::operator <= (IN const char *sz) const
{
	return sz ? m_szString_m <= nsconv(std::string(sz)) : false;
}
//-----------------------------------------------------------------------------
bool C_NString::operator <= (IN const wchar_t *sz) const
{
	return sz ? m_szString_m <= sz : false;
}
//-----------------------------------------------------------------------------
bool C_NString::operator <= (IN const std::string &sz) const
{
	return m_szString_m <= nsconv(sz);
}
//-----------------------------------------------------------------------------
bool C_NString::operator <= (IN const std::wstring &sz) const
{
	return m_szString_m <= sz;
}
//-----------------------------------------------------------------------------
bool C_NString::operator <= (IN const _bstr_t &sz) const
{
	return m_szString_m <= static_cast<const wchar_t *>(sz);
}
//-----------------------------------------------------------------------------
bool C_NString::operator >= (IN const C_NString &sz) const
{
	return m_szString_m >= sz.m_szString_m;
}
//-----------------------------------------------------------------------------
bool C_NString::operator >= (IN const char *sz) const
{
	return sz ? m_szString_m >= nsconv(std::string(sz)) : false;
}
//-----------------------------------------------------------------------------
bool C_NString::operator >= (IN const wchar_t *sz) const
{
	return sz ? m_szString_m >= sz : false;
}
//-----------------------------------------------------------------------------
bool C_NString::operator >= (IN const std::string &sz) const
{
	return m_szString_m >= nsconv(sz);
}
//-----------------------------------------------------------------------------
bool C_NString::operator >= (IN const std::wstring &sz) const
{
	return m_szString_m >= sz;
}
//-----------------------------------------------------------------------------
bool C_NString::operator >= (IN const _bstr_t &sz) const
{
	return m_szString_m >= static_cast<const wchar_t *>(sz);
}
//-----------------------------------------------------------------------------
bool C_NString::operator != (IN const C_NString &sz) const
{
	return m_szString_m != sz.m_szString_m;
}
//-----------------------------------------------------------------------------
bool C_NString::operator != (IN const char *sz) const
{
	return sz ? m_szString_m != nsconv(std::string(sz)) : false;
}
//-----------------------------------------------------------------------------
bool C_NString::operator != (IN const wchar_t *sz) const
{
	return sz ? m_szString_m != sz : false;
}
//-----------------------------------------------------------------------------
bool C_NString::operator != (IN const std::string &sz) const
{
	return m_szString_m != nsconv(sz);
}
//-----------------------------------------------------------------------------
bool C_NString::operator != (IN const std::wstring &sz) const
{
	return m_szString_m != sz;
}
//-----------------------------------------------------------------------------
bool C_NString::operator != (IN const _bstr_t &sz) const
{
	return m_szString_m != static_cast<const wchar_t *>(sz);
}
//-----------------------------------------------------------------------------
bool C_NString::operator == (IN const C_NString &sz) const
{
	return m_szString_m == sz.m_szString_m;
}
//-----------------------------------------------------------------------------
bool C_NString::operator == (IN const char *sz) const
{
	return sz ? m_szString_m == nsconv(std::string(sz)) : false;
}
//-----------------------------------------------------------------------------
bool C_NString::operator == (IN const wchar_t *sz) const
{
	return sz ? m_szString_m == sz : false;
}
//-----------------------------------------------------------------------------
bool C_NString::operator == (IN const std::string &sz) const
{
	return m_szString_m == nsconv(sz);
}
//-----------------------------------------------------------------------------
bool C_NString::operator == (IN const std::wstring &sz) const
{
	return m_szString_m == sz;
}
//-----------------------------------------------------------------------------
bool C_NString::operator == (IN const _bstr_t &sz) const
{
	return m_szString_m == static_cast<const wchar_t *>(sz);
}
//-----------------------------------------------------------------------------
// 複製到char字串陣列
void C_NString::copyto(OUT char *sz, IN unsigned long ulInputSize) const
{
	if(sz == nullptr)
		return;

	if(ulInputSize <= 0)
		return;

	strcpy_s(sz, ulInputSize, nsconv(m_szString_m).c_str());
}
//-----------------------------------------------------------------------------
// 複製到wchar_t字串陣列
void C_NString::copyto(OUT wchar_t *sz, IN unsigned long ulInputSize) const
{
	if(sz == nullptr)
		return;

	if(ulInputSize <= 0)
		return;

	wcscpy_s(sz, ulInputSize, m_szString_m.c_str());
}
//-----------------------------------------------------------------------------
// 以 char * 模式取得儲存的字串
const char *C_NString::c_str() const
{
	const_cast<C_NString *>(this)->m_szString_s = nsconv(m_szString_m);

	return m_szString_s.c_str();
}
//-----------------------------------------------------------------------------
// 以 wchar_t * 模式取得儲存的字串
const wchar_t *C_NString::w_str() const
{
	return m_szString_m.c_str();
}
//-----------------------------------------------------------------------------
// 以 TCHAR * 模式取得儲存的字串
const TCHAR *C_NString::t_str() const
{
#ifndef UNICODE
	return c_str();
#else
	return w_str();
#endif
}
//-----------------------------------------------------------------------------
// 取得字串長度
std::string::size_type C_NString::size() const
{
	return m_szString_m.size();
}
//-----------------------------------------------------------------------------
// 取得字串是否為空
bool C_NString::empty() const
{
	return m_szString_m.empty();
}
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------