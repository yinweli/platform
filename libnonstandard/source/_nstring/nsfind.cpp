//-----------------------------------------------------------------------------
#include "_nstring.h"
#include "nsfind.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// �ˬd���w�r��O�_���X�{
bool strfind(IN char *szInput, IN const char *szKey)
{
	return (szInput != NULL && szKey != NULL) ? strstr(szInput, szKey) != NULL : false;
}
//-----------------------------------------------------------------------------
// �ˬd���w�r��O�_���X�{, �e�r������
bool strfind(IN wchar_t *szInput, IN const wchar_t *szKey)
{
	return (szInput != NULL && szKey != NULL) ? wcsstr(szInput, szKey) != NULL : false;
}
//-----------------------------------------------------------------------------
// �ˬd���w�r��O�_���X�{
bool strfind(IN std::string &szInput, IN const char *szKey)
{
	return (szKey != NULL) ? szInput.find(szKey ? szKey : "") != std::string::npos : false;
}
//-----------------------------------------------------------------------------
// �ˬd���w�r��O�_���X�{, �e�r������
bool strfind(IN std::wstring &szInput, IN const wchar_t *szKey)
{
	return (szKey != NULL) ? szInput.find(szKey ? szKey : L"") != std::wstring::npos : false;
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------