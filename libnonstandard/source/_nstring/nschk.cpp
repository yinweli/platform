//-----------------------------------------------------------------------------
#include "_nstring.h"
#include "nschk.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// �ˬd�Ҧ����r���O�_���O�^��
bool alphachk(IN const std::string &szInput)
{
	return std::find_if(szInput.begin(), szInput.end(), std::not1(std::ptr_fun(isalpha))) == szInput.end();
}
//-----------------------------------------------------------------------------
// �ˬd�Ҧ����r���O�_���O�^��, �e�r������
bool alphachk(IN const std::wstring &szInput)
{
	return std::find_if(szInput.begin(), szInput.end(), std::not1(std::ptr_fun(iswalpha))) == szInput.end();
}
//-----------------------------------------------------------------------------
// �ˬd�Ҧ����r���O�_���O�Ʀr
bool digitchk(IN const std::string &szInput)
{
	return std::find_if(szInput.begin(), szInput.end(), std::not1(std::ptr_fun(isdigit))) == szInput.end();
}
//-----------------------------------------------------------------------------
// �ˬd�Ҧ����r���O�_���O�Ʀr, �e�r������
bool digitchk(IN const std::wstring &szInput)
{
	return std::find_if(szInput.begin(), szInput.end(), std::not1(std::ptr_fun(iswdigit))) == szInput.end();
}
//-----------------------------------------------------------------------------
// �ˬd�Ҧ����r���O�_���O�^��P�Ʀr
bool alphadigitchk(IN const std::string &szInput)
{
	return std::find_if(szInput.begin(), szInput.end(), std::not1(std::ptr_fun(isalnum))) == szInput.end();
}
//-----------------------------------------------------------------------------
// �ˬd�Ҧ����r���O�_���O�^��P�Ʀr, �e�r������
bool alphadigitchk(IN const std::wstring &szInput)
{
	return std::find_if(szInput.begin(), szInput.end(), std::not1(std::ptr_fun(iswalnum))) == szInput.end();
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------