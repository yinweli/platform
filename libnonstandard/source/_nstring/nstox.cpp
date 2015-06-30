//-----------------------------------------------------------------------------
#include "_nstring.h"
#include "nstox.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
#define TEMPSTRLEN 64 // 既﹃
//-----------------------------------------------------------------------------
// 盢 bool 锣传Θ﹃
std::string ntos(IN bool x, IN int radix)
{
	char szTemp[TEMPSTRLEN];

	_itoa_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 bool 锣传Θ﹃, 糴じセ
std::wstring ntow(IN bool x, IN int radix)
{
	wchar_t szTemp[TEMPSTRLEN];

	_itow_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 char 锣传Θ﹃
std::string ntos(IN char x, IN int radix)
{
	char szTemp[TEMPSTRLEN];

	_itoa_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 char 锣传Θ﹃, 糴じセ
std::wstring ntow(IN char x, IN int radix)
{
	wchar_t szTemp[TEMPSTRLEN];

	_itow_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 unsigned char 锣传Θ﹃
std::string ntos(IN unsigned char x, IN int radix)
{
	char szTemp[TEMPSTRLEN];

	_itoa_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 unsigned char 锣传Θ﹃, 糴じセ
std::wstring ntow(IN unsigned char x, IN int radix)
{
	wchar_t szTemp[TEMPSTRLEN];

	_itow_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 short 锣传Θ﹃
std::string ntos(IN short x, IN int radix)
{
	char szTemp[TEMPSTRLEN];

	_itoa_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 short 锣传Θ﹃, 糴じセ
std::wstring ntow(IN short x, IN int radix)
{
	wchar_t szTemp[TEMPSTRLEN];

	_itow_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 unsigned short 锣传Θ﹃
std::string ntos(IN unsigned short x, IN int radix)
{
	char szTemp[TEMPSTRLEN];

	_itoa_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 unsigned short 锣传Θ﹃, 糴じセ
std::wstring ntow(IN unsigned short x, IN int radix)
{
	wchar_t szTemp[TEMPSTRLEN];

	_itow_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 long 锣传Θ﹃
std::string ntos(IN long x, IN int radix)
{
	char szTemp[TEMPSTRLEN];

	_itoa_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 long 锣传Θ﹃, 糴じセ
std::wstring ntow(IN long x, IN int radix)
{
	wchar_t szTemp[TEMPSTRLEN];

	_itow_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 unsigned long 锣传Θ﹃
std::string ntos(IN unsigned long x, IN int radix)
{
	char szTemp[TEMPSTRLEN];

	_ultoa_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 unsigned long 锣传Θ﹃, 糴じセ
std::wstring ntow(IN unsigned long x, IN int radix)
{
	wchar_t szTemp[TEMPSTRLEN];

	_ultow_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 int 锣传Θ﹃
std::string ntos(IN int x, IN int radix)
{
	char szTemp[TEMPSTRLEN];

	_itoa_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 int 锣传Θ﹃, 糴じセ
std::wstring ntow(IN int x, IN int radix)
{
	wchar_t szTemp[TEMPSTRLEN];

	_itow_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 unsigned int 锣传Θ﹃
std::string ntos(IN unsigned int x, IN int radix)
{
	char szTemp[TEMPSTRLEN];

	_i64toa_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 unsigned int 锣传Θ﹃, 糴じセ
std::wstring ntow(IN unsigned int x, IN int radix)
{
	wchar_t szTemp[TEMPSTRLEN];

	_i64tow_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 __int64 锣传Θ﹃
std::string ntos(IN __int64 x, IN int radix)
{
	char szTemp[TEMPSTRLEN];

	_i64toa_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 __int64 锣传Θ﹃, 糴じセ
std::wstring ntow(IN __int64 x, IN int radix)
{
	wchar_t szTemp[TEMPSTRLEN];

	_i64tow_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 unsigned __int64 锣传Θ﹃
std::string ntos(IN unsigned __int64 x, IN int radix)
{
	char szTemp[TEMPSTRLEN];

	_ui64toa_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 unsigned __int64 锣传Θ﹃, 糴じセ
std::wstring ntow(IN unsigned __int64 x, IN int radix)
{
	wchar_t szTemp[TEMPSTRLEN];

	_ui64tow_s(x, szTemp, _countof(szTemp), radix);

	return szTemp;
}
//-----------------------------------------------------------------------------
// 盢 float 锣传Θ﹃
std::string ntos(IN float x, IN int count)
{
	std::string szFloat;
	char szTemp[_CVTBUFSIZE];
	int dec = 0, sign = 0;

	_fcvt_s(szTemp, sizeof(szTemp), x, count, &dec, &sign);
	szFloat = szTemp;
	szFloat.insert(dec, ".");
 
	if(sign)
		szFloat.insert(0, "-");

	return szFloat;
}
//-----------------------------------------------------------------------------
// 盢 float 锣传Θ﹃, 糴じセ
std::wstring ntow(IN float x, IN int count)
{
	return nsconv(ntos(x, count));
}
//-----------------------------------------------------------------------------
// 盢 float 锣传Θ﹃
std::string ntos(IN float x)
{
	char szTemp[TEMPSTRLEN];

	_snprintf_s(szTemp, _countof(szTemp), _TRUNCATE, "%g", x);

	return std::string(szTemp);
}
//-----------------------------------------------------------------------------
// 盢 float 锣传Θ﹃, 糴じセ
std::wstring ntow(IN float x)
{
	wchar_t szTemp[TEMPSTRLEN];

	_snwprintf_s(szTemp, _countof(szTemp), _TRUNCATE, L"%g", x);

	return std::wstring(szTemp);
}
//-----------------------------------------------------------------------------
// 盢 double 锣传Θ﹃
std::string ntos(IN double x, IN int count)
{
	std::string szResult;
	char szTemp[_CVTBUFSIZE];
	int dec = 0, sign = 0;

	_fcvt_s(szTemp, sizeof(szTemp), x, count, &dec, &sign);
	szResult = szTemp;

	szResult.insert(dec, ".");

	if(sign)
		szResult.insert(0, "-");

	return szResult;
}
//-----------------------------------------------------------------------------
// 盢 double 锣传Θ﹃, 糴じセ
std::wstring ntow(IN double x, IN int count)
{
	return nsconv(ntos(x, count));
}
//-----------------------------------------------------------------------------
// 盢 double 锣传Θ﹃
std::string ntos(IN double x)
{
	char szTemp[TEMPSTRLEN];

	_snprintf_s(szTemp, _countof(szTemp), _TRUNCATE, "%g", x);

	return std::string(szTemp);
}
//-----------------------------------------------------------------------------
// 盢 double 锣传Θ﹃, 糴じセ
std::wstring ntow(IN double x)
{
	wchar_t szTemp[TEMPSTRLEN];

	_snwprintf_s(szTemp, _countof(szTemp), _TRUNCATE, L"%g", x);

	return std::wstring(szTemp);
}
//-----------------------------------------------------------------------------
// 眔じ﹃
std::string ntobs(IN unsigned int bytes)
{
	char szTemp[TEMPSTRLEN];

	_snprintf_s(szTemp, _countof(szTemp), _TRUNCATE, "%u.%u", bytes / 1024, static_cast<unsigned int>((bytes % 1024) / 1024.0f * 10));

	return std::string(szTemp);
}
//-----------------------------------------------------------------------------
// 眔じ﹃
std::wstring ntobw(IN unsigned int bytes)
{
	wchar_t szTemp[TEMPSTRLEN];

	_snwprintf_s(szTemp, _countof(szTemp), _TRUNCATE, L"%u.%u", bytes / 1024, static_cast<unsigned int>((bytes % 1024) / 1024.0f * 10));

	return std::wstring(szTemp);
}
//-----------------------------------------------------------------------------
// 眔じ﹃
std::string ntobs(IN unsigned __int64 bytes)
{
	char szTemp[TEMPSTRLEN];

	_snprintf_s(szTemp, _countof(szTemp), _TRUNCATE, "%I64u.%I64u", bytes / 1024, static_cast<unsigned __int64>((bytes % 1024) / 1024.0f * 10));

	return std::string(szTemp);
}
//-----------------------------------------------------------------------------
// 眔じ﹃
std::wstring ntobw(IN unsigned __int64 bytes)
{
	wchar_t szTemp[TEMPSTRLEN];

	_snwprintf_s(szTemp, _countof(szTemp), _TRUNCATE, L"%I64u.%I64u", bytes / 1024, static_cast<unsigned __int64>((bytes % 1024) / 1024.0f * 10));

	return std::wstring(szTemp);
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------