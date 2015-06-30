//-----------------------------------------------------------------------------
#include "_nstring.h"
#include "nsedit.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// ���o�r��, �p�G��J�r���Y�����O���w�r��, �N���J���w�r����Y��
std::string insthand(IN const std::string &szInput, IN const std::string &szKey)
{
	std::string szResult = szInput;

	if(szKey.empty() == false && szResult.find(szKey) != 0)
		szResult.insert(0, szKey);

	return szResult;
}
//-----------------------------------------------------------------------------
// ���o�r��, �p�G��J�r���Y�����O���w�r��, �N���J���w�r����Y��, �e�r������
std::wstring insthand(IN const std::wstring &szInput, IN const std::wstring &szKey)
{
	std::wstring szResult = szInput;

	if(szKey.empty() == false && szResult.find(szKey) != 0)
		szResult.insert(0, szKey);

	return szResult;
}
//-----------------------------------------------------------------------------
// ���o�r��, �p�G�r��������O���w�r��, �N���J���w�r������
std::string insttail(IN const std::string &szInput, IN const std::string &szKey)
{
	std::string szResult = szInput;

	if(szKey.empty() == false && szResult.rfind(szKey) != (szResult.size() - szKey.size()))
		szResult.append(szKey);

	return szResult;
}
//-----------------------------------------------------------------------------
// ���o�r��, �p�G�r��������O���w�r��, �N���J���w�r������, �e�r������
std::wstring insttail(IN const std::wstring &szInput, IN const std::wstring &szKey)
{
	std::wstring szResult = szInput;

	if(szKey.empty() == false && szResult.rfind(szKey) != (szResult.size() - szKey.size()))
		szResult.append(szKey);

	return szResult;
}
//-----------------------------------------------------------------------------
// ���o�r��, �p�G�r���Y�����O���w�r��, �N���J���w�r����Y��
std::string insthandtail(IN const std::string &szInput, IN const std::string &szKey)
{
	return insthand(insttail(szInput, szKey), szKey);
}
//-----------------------------------------------------------------------------
// ���o�r��, �p�G�r���Y�����O���w�r��, �N���J���w�r����Y��, �e�r������
std::wstring insthandtail(IN const std::wstring &szInput, IN const std::wstring &szKey)
{
	return insthand(insttail(szInput, szKey), szKey);
}
//-----------------------------------------------------------------------------
// ���o�r��, �p�G�r���Y���O���w�r��, �N�q�Y���h�����w�r��
std::string trimhand(IN const std::string &szInput, IN const std::string &szKey)
{
	std::string szResult = szInput;

	if(szKey.empty() == false && szResult.find(szKey) == 0)
		szResult.erase(0, szKey.size());

	return szResult;
}
//-----------------------------------------------------------------------------
// ���o�r��, �p�G�r���Y���O���w�r��, �N�q�Y���h�����w�r��, �e�r������
std::wstring trimhand(IN const std::wstring &szInput, IN const std::wstring &szKey)
{
	std::wstring szResult = szInput;

	if(szKey.empty() == false && szResult.find(szKey) == 0)
		szResult.erase(0, szKey.size());

	return szResult;
}
//-----------------------------------------------------------------------------
// ���o�r��, �p�G�r������O���w�r��, �N�q�����h�����w�r��
std::string trimtail(IN const std::string &szInput, IN const std::string &szKey)
{
	std::string szResult = szInput;
	std::string::size_type Len = szKey.size();
	std::string::size_type Pos = szResult.size() - Len;

	if(szKey.empty() == false && szResult.rfind(szKey) == Pos)
		szResult.erase(Pos, Len);

	return szResult;
}
//-----------------------------------------------------------------------------
// ���o�r��, �p�G�r������O���w�r��, �N�q�����h�����w�r��, �e�r������
std::wstring trimtail(IN const std::wstring &szInput, IN const std::wstring &szKey)
{
	std::wstring szResult = szInput;
	std::wstring::size_type Len = szKey.size();
	std::wstring::size_type Pos = szResult.size() - Len;

	if(szKey.empty() == false && szResult.rfind(szKey) == Pos)
		szResult.erase(Pos, Len);

	return szResult;
}
//-----------------------------------------------------------------------------
// ���o�r��, �p�G�r���Y���O���w�r��, �N�q�Y���h�����w�r��
std::string trimhandtail(IN const std::string &szInput, IN const std::string &szKey)
{
	return trimhand(trimtail(szInput, szKey), szKey);
}
//-----------------------------------------------------------------------------
// ���o�r��, �p�G�r���Y���O���w�r��, �N�q�Y���h�����w�r��, �e�r������
std::wstring trimhandtail(IN const std::wstring &szInput, IN const std::wstring &szKey)
{
	return trimhand(trimtail(szInput, szKey), szKey);
}
//-----------------------------------------------------------------------------
// ���o�h���r���Y���ťի᪺�r��
std::string trimhandspace(IN const std::string &szInput)
{
	std::string szResult = szInput;

	szResult.erase(szResult.begin(), std::find_if(szResult.begin(), szResult.end(), std::not1(std::ptr_fun(isspace))));

	return szResult;
}
//-----------------------------------------------------------------------------
// ���o�h���r���Y���ťի᪺�r��, �e�r������
std::wstring trimhandspace(IN const std::wstring &szInput)
{
	std::wstring szResult = szInput;

	szResult.erase(szResult.begin(), std::find_if(szResult.begin(), szResult.end(), std::not1(std::ptr_fun(isspace))));

	return szResult;
}
//-----------------------------------------------------------------------------
// ���o�h���r������ťի᪺�r��
std::string trimtailspace(IN const std::string &szInput)
{
	std::string szResult = szInput;
	std::string::reverse_iterator Itor = std::find_if(szResult.rbegin(), szResult.rend(), std::not1(std::ptr_fun(isspace)));

	szResult.erase(Itor.base(), szResult.end());

	return szResult;
}
//-----------------------------------------------------------------------------
// ���o�h���r������ťի᪺�r��, �e�r������
std::wstring trimtailspace(IN const std::wstring &szInput)
{
	std::wstring szResult = szInput;
	std::wstring::reverse_iterator Itor = std::find_if(szResult.rbegin(), szResult.rend(), std::not1(std::ptr_fun(isspace)));

	szResult.erase(Itor.base(), szResult.end());

	return szResult;
}
//-----------------------------------------------------------------------------
// ���o�h���r���Y���ťի᪺�r��
std::string trimhandtailspace(IN const std::string &szInput)
{
	return trimhandspace(trimtailspace(szInput));
}
//-----------------------------------------------------------------------------
// ���o�h���r���Y���ťի᪺�r��, �e�r������
std::wstring trimhandtailspace(IN const std::wstring &szInput)
{
	return trimhandspace(trimtailspace(szInput));
}
//-----------------------------------------------------------------------------
// ���o�I�h���w�r���᪺�r��
std::string nstruncate(IN const std::string &szInput, IN std::string::value_type Key)
{
	std::string szResult = szInput;
	std::string::size_type Pos = szResult.find_first_of(Key);
	std::string::size_type Len = szResult.size() - Pos;

	if(Pos != std::string::npos && Len > 0)
		szResult.erase(Pos, Len);

	return szResult;
}
//-----------------------------------------------------------------------------
// ���o�I�h���w�r���᪺�r��, �e�r������
std::wstring nstruncate(IN const std::wstring &szInput, IN std::wstring::value_type Key)
{
	std::wstring szResult = szInput;
	std::wstring::size_type Pos = szResult.find_first_of(Key);
	std::wstring::size_type Len = szResult.size() - Pos;

	if(Pos != std::wstring::npos && Len > 0)
		szResult.erase(Pos, Len);

	return szResult;
}
//-----------------------------------------------------------------------------
// ���o���N�᪺�r��
std::string nsreplace(IN const std::string &szInput, IN const std::string &szKey, IN const std::string &szReplace)
{
	std::string szResult = szInput;

	if(szKey != szReplace)
	{
		std::string::size_type Pos = szResult.find(szKey);

		while(Pos != std::string::npos)
		{
			szResult = szResult.replace(Pos, szKey.size(), szReplace);
			Pos = szResult.find(szKey);
		}//while
	}//if

	return szResult;
}
//-----------------------------------------------------------------------------
// ���o���N�᪺�r��, �e�r������
std::wstring nsreplace(IN const std::wstring &szInput, IN const std::wstring &szKey, IN const std::wstring &szReplace)
{
	std::wstring szResult = szInput;

	if(szKey != szReplace)
	{
		std::wstring::size_type Pos = szResult.find(szKey);

		while(Pos != std::wstring::npos)
		{
			szResult = szResult.replace(Pos, szKey.size(), szReplace);
			Pos = szResult.find(szKey);
		}//while
	}//if

	return szResult;
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------