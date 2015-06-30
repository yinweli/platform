//-----------------------------------------------------------------------------
#include "_nstring.h"
#include "nscase.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// 取得大小寫反轉的字元
char reverse(IN char c)
{
	if(islower(c))
		return static_cast<char>(toupper(c));

	if(isupper(c))
		return static_cast<char>(tolower(c));

	return c;
}
//-----------------------------------------------------------------------------
// 取得大小寫反轉的字元, 寬字元版本
wchar_t wreverse(IN wchar_t c)
{
	if(iswlower(c))
		return static_cast<wchar_t>(toupper(c));

	if(iswupper(c))
		return static_cast<wchar_t>(tolower(c));

	return c;
}
//-----------------------------------------------------------------------------
// 將字串內所有的字元轉換為小寫
std::string nslower(IN const std::string &szInput)
{
	std::string szReszult = szInput;

	std::transform(szReszult.begin(), szReszult.end(), szReszult.begin(), tolower);

	return szReszult;
}
//-----------------------------------------------------------------------------
// 將字串內所有的字元轉換為小寫, 寬字元版本
std::wstring nslower(IN const std::wstring &szInput)
{
	std::wstring szReszult = szInput;

	std::transform(szReszult.begin(), szReszult.end(), szReszult.begin(), tolower);

	return szReszult;
}
//-----------------------------------------------------------------------------
// 將字串內所有的字元轉換為大寫
std::string nsupper(IN const std::string &szInput)
{
	std::string szReszult = szInput;

	std::transform(szReszult.begin(), szReszult.end(), szReszult.begin(), toupper);

	return szReszult;
}
//-----------------------------------------------------------------------------
// 將字串內所有的字元轉換為大寫, 寬字元版本
std::wstring nsupper(IN const std::wstring &szInput)
{
	std::wstring szReszult = szInput;

	std::transform(szReszult.begin(), szReszult.end(), szReszult.begin(), toupper);

	return szReszult;
}
//-----------------------------------------------------------------------------
// 將字串內所有的字元大小寫反轉
std::string nseverse(IN const std::string &szInput)
{
	std::string szReszult = szInput;

	std::transform(szReszult.begin(), szReszult.end(), szReszult.begin(), reverse);

	return szReszult;
}
//-----------------------------------------------------------------------------
// 將字串內所有的字元大小寫反轉, 寬字元版本
std::wstring nseverse(IN const std::wstring &szInput)
{
	std::wstring szReszult = szInput;

	std::transform(szReszult.begin(), szReszult.end(), szReszult.begin(), wreverse);

	return szReszult;
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------