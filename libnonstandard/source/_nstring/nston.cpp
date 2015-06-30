//-----------------------------------------------------------------------------
#include "_nstring.h"
#include "nston.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ bool
void ston(IN const std::string &s, OUT bool &r)
{
	r = atol(s.c_str()) ? true : false;
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ bool, 糴じセ
void wton(IN const std::wstring &s, OUT bool &r)
{
	r = _wtol(s.c_str()) ? true : false;
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ char
void ston(IN const std::string &s, OUT char &r)
{
	r = static_cast<char>(atol(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ char, 糴じセ
void wton(IN const std::wstring &s, OUT char &r)
{
	r = static_cast<char>(_wtol(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ unsigned char
void ston(IN const std::string &s, OUT unsigned char &r)
{
	r = static_cast<unsigned char>(atol(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ unsigned char, 糴じセ
void wton(IN const std::wstring &s, OUT unsigned char &r)
{
	r = static_cast<unsigned char>(_wtol(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ short
void ston(IN const std::string &s, OUT short &r)
{
	r = static_cast<short>(atol(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ short, 糴じセ
void wton(IN const std::wstring &s, OUT short &r)
{
	r = static_cast<short>(_wtol(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ unsigned short
void ston(IN const std::string &s, OUT unsigned short &r)
{
	r = static_cast<unsigned short>(atol(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ unsigned short, 糴じセ
void wton(IN const std::wstring &s, OUT unsigned short &r)
{
	r = static_cast<unsigned short>(_wtol(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ long
void ston(IN const std::string &s, OUT long &r)
{
	r = atol(s.c_str());
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ long, 糴じセ
void wton(IN const std::wstring &s, OUT long &r)
{
	r = _wtol(s.c_str());
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ unsigned long
void ston(IN const std::string &s, OUT unsigned long &r)
{
	r = static_cast<unsigned long>(atol(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ unsigned long, 糴じセ
void wton(IN const std::wstring &s, OUT unsigned long &r)
{
	r = static_cast<unsigned long>(_wtol(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ int
void ston(IN const std::string &s, OUT int &r)
{
	r = static_cast<int>(atol(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ int, 糴じセ
void wton(IN const std::wstring &s, OUT int &r)
{
	r = static_cast<int>(_wtol(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ unsigned int
void ston(IN const std::string &s, OUT unsigned int &r)
{
	r = static_cast<unsigned int>(atol(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ unsigned long, 糴じセ
void wton(IN const std::wstring &s, OUT unsigned int &r)
{
	r = static_cast<unsigned int>(_wtol(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ __int64
void ston(IN const std::string &s, OUT __int64 &r)
{
	r = _atoi64(s.c_str());
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ __int64, 糴じセ
void wton(IN const std::wstring &s, OUT __int64 &r)
{
	r = _wtoi64(s.c_str());
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ unsigned __int64
void ston(IN const std::string &s, OUT unsigned __int64 &r)
{
	r = static_cast<unsigned __int64>(_atoi64(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ unsigned long, 糴じセ
void wton(IN const std::wstring &s, OUT unsigned __int64 &r)
{
	r = static_cast<unsigned __int64>(_wtoi64(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ float
void ston(IN const std::string &s, OUT float &r)
{
	r = static_cast<float>(atof(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ float, 糴じセ
void wton(IN const std::wstring &s, OUT float &r)
{
	r = static_cast<float>(_wtof(s.c_str()));
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ double
void ston(IN const std::string &s, OUT double &r)
{
	r = atof(s.c_str());
}
//-----------------------------------------------------------------------------
// 盢﹃锣传Θ double, 糴じセ
void wton(IN const std::wstring &s, OUT double &r)
{
	r = _wtof(s.c_str());
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------