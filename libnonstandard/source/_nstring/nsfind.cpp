//-----------------------------------------------------------------------------
#include "_nstring.h"
#include "nsfind.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// 檢查指定字串是否有出現
bool strfind(IN char *szInput, IN const char *szKey)
{
	return (szInput != NULL && szKey != NULL) ? strstr(szInput, szKey) != NULL : false;
}
//-----------------------------------------------------------------------------
// 檢查指定字串是否有出現, 寬字元版本
bool strfind(IN wchar_t *szInput, IN const wchar_t *szKey)
{
	return (szInput != NULL && szKey != NULL) ? wcsstr(szInput, szKey) != NULL : false;
}
//-----------------------------------------------------------------------------
// 檢查指定字串是否有出現
bool strfind(IN std::string &szInput, IN const char *szKey)
{
	return (szKey != NULL) ? szInput.find(szKey ? szKey : "") != std::string::npos : false;
}
//-----------------------------------------------------------------------------
// 檢查指定字串是否有出現, 寬字元版本
bool strfind(IN std::wstring &szInput, IN const wchar_t *szKey)
{
	return (szKey != NULL) ? szInput.find(szKey ? szKey : L"") != std::wstring::npos : false;
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------