//-----------------------------------------------------------------------------
#include "_nstring.h"
#include "nstrlen.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// 璸衡﹃计
unsigned long nscount(IN const std::string &szInput)
{
	unsigned long ulResult = 0;

	for(std::string::const_iterator Itor = szInput.begin(); Itor != szInput.end(); std::advance(Itor, static_cast<unsigned char>(*Itor) < 128 ? 1 : 2))
		++ulResult;

	return ulResult;
}
//-----------------------------------------------------------------------------
// 璸衡﹃计
unsigned long nscount(IN const std::wstring &szInput)
{
	return szInput.size();
}
//-----------------------------------------------------------------------------
// 璸衡﹃じ计
unsigned long nsbytes(IN const std::string &szInput)
{
	return szInput.size();
}
//-----------------------------------------------------------------------------
// 璸衡﹃じ计
unsigned long nsbytes(IN const std::wstring &szInput)
{
	return nscount(szInput) * sizeof(std::wstring::value_type);
}
//-----------------------------------------------------------------------------
// multi-byteよΑ璸衡﹃じ计
unsigned long mbbytes(IN const std::string &szInput)
{
	return szInput.size();
}
//-----------------------------------------------------------------------------
// multi-byteよΑ璸衡﹃じ计, 糴じセ
unsigned long mbbytes(IN const std::wstring &szInput)
{
	unsigned long ulResult = 0;

	std::for_each(szInput.begin(), szInput.end(), [&ulResult] (const std::wstring::value_type &Itor) { ulResult += Itor < 128 ? 1 : 2; });

	return ulResult;
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------