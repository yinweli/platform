//-----------------------------------------------------------------------------
#include "_nstring.h"
#include "nscase.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// ���o�j�p�g���઺�r��
char reverse(IN char c)
{
	if(islower(c))
		return static_cast<char>(toupper(c));

	if(isupper(c))
		return static_cast<char>(tolower(c));

	return c;
}
//-----------------------------------------------------------------------------
// ���o�j�p�g���઺�r��, �e�r������
wchar_t wreverse(IN wchar_t c)
{
	if(iswlower(c))
		return static_cast<wchar_t>(toupper(c));

	if(iswupper(c))
		return static_cast<wchar_t>(tolower(c));

	return c;
}
//-----------------------------------------------------------------------------
// �N�r�ꤺ�Ҧ����r���ഫ���p�g
std::string nslower(IN const std::string &szInput)
{
	std::string szReszult = szInput;

	std::transform(szReszult.begin(), szReszult.end(), szReszult.begin(), tolower);

	return szReszult;
}
//-----------------------------------------------------------------------------
// �N�r�ꤺ�Ҧ����r���ഫ���p�g, �e�r������
std::wstring nslower(IN const std::wstring &szInput)
{
	std::wstring szReszult = szInput;

	std::transform(szReszult.begin(), szReszult.end(), szReszult.begin(), tolower);

	return szReszult;
}
//-----------------------------------------------------------------------------
// �N�r�ꤺ�Ҧ����r���ഫ���j�g
std::string nsupper(IN const std::string &szInput)
{
	std::string szReszult = szInput;

	std::transform(szReszult.begin(), szReszult.end(), szReszult.begin(), toupper);

	return szReszult;
}
//-----------------------------------------------------------------------------
// �N�r�ꤺ�Ҧ����r���ഫ���j�g, �e�r������
std::wstring nsupper(IN const std::wstring &szInput)
{
	std::wstring szReszult = szInput;

	std::transform(szReszult.begin(), szReszult.end(), szReszult.begin(), toupper);

	return szReszult;
}
//-----------------------------------------------------------------------------
// �N�r�ꤺ�Ҧ����r���j�p�g����
std::string nseverse(IN const std::string &szInput)
{
	std::string szReszult = szInput;

	std::transform(szReszult.begin(), szReszult.end(), szReszult.begin(), reverse);

	return szReszult;
}
//-----------------------------------------------------------------------------
// �N�r�ꤺ�Ҧ����r���j�p�g����, �e�r������
std::wstring nseverse(IN const std::wstring &szInput)
{
	std::wstring szReszult = szInput;

	std::transform(szReszult.begin(), szReszult.end(), szReszult.begin(), wreverse);

	return szReszult;
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------