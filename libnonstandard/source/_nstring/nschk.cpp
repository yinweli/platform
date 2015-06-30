//-----------------------------------------------------------------------------
#include "_nstring.h"
#include "nschk.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// 浪琩┮Τじ琌常琌璣ゅ
bool alphachk(IN const std::string &szInput)
{
	return std::find_if(szInput.begin(), szInput.end(), std::not1(std::ptr_fun(isalpha))) == szInput.end();
}
//-----------------------------------------------------------------------------
// 浪琩┮Τじ琌常琌璣ゅ, 糴じセ
bool alphachk(IN const std::wstring &szInput)
{
	return std::find_if(szInput.begin(), szInput.end(), std::not1(std::ptr_fun(iswalpha))) == szInput.end();
}
//-----------------------------------------------------------------------------
// 浪琩┮Τじ琌常琌计
bool digitchk(IN const std::string &szInput)
{
	return std::find_if(szInput.begin(), szInput.end(), std::not1(std::ptr_fun(isdigit))) == szInput.end();
}
//-----------------------------------------------------------------------------
// 浪琩┮Τじ琌常琌计, 糴じセ
bool digitchk(IN const std::wstring &szInput)
{
	return std::find_if(szInput.begin(), szInput.end(), std::not1(std::ptr_fun(iswdigit))) == szInput.end();
}
//-----------------------------------------------------------------------------
// 浪琩┮Τじ琌常琌璣ゅ籔计
bool alphadigitchk(IN const std::string &szInput)
{
	return std::find_if(szInput.begin(), szInput.end(), std::not1(std::ptr_fun(isalnum))) == szInput.end();
}
//-----------------------------------------------------------------------------
// 浪琩┮Τじ琌常琌璣ゅ籔计, 糴じセ
bool alphadigitchk(IN const std::wstring &szInput)
{
	return std::find_if(szInput.begin(), szInput.end(), std::not1(std::ptr_fun(iswalnum))) == szInput.end();
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------