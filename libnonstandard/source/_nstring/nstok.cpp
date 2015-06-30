//-----------------------------------------------------------------------------
#include "_nstring.h"
#include "nstok.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// 取得字串切割結果
std::vector<std::string> nstok(IN const std::string &szInput, IN const std::string &szTok)
{
	std::vector<std::string> Result;

	if(szInput.empty() == false && szTok.empty() == false)
	{
		std::string szTemp;

		for(const std::string::value_type &Itor : szInput)
		{
			if(szTok.find(Itor) == std::string::npos)
				szTemp.push_back(Itor);
			else
			{
				Result.push_back(szTemp);
				szTemp.clear();
			}//if
		}//for

		if(szTemp.empty() == false)
			Result.push_back(szTemp);
	}//if

	return Result;
}
//-----------------------------------------------------------------------------
// 取得字串切割結果, 寬字元版本
std::vector<std::wstring> nstok(IN const std::wstring &szInput, IN const std::wstring &szTok)
{
	std::vector<std::wstring> Result;

	if(szInput.empty() == false && szTok.empty() == false)
	{
		std::wstring szTemp;

		for(const std::wstring::value_type &Itor : szInput)
		{
			if(szTok.find(Itor) == std::wstring::npos)
				szTemp.push_back(Itor);
			else
			{
				Result.push_back(szTemp);
				szTemp.clear();
			}//if
		}//for

		if(szTemp.empty() == false)
			Result.push_back(szTemp);
	}//if

	return Result;
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------