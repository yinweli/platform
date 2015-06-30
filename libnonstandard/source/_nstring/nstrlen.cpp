//-----------------------------------------------------------------------------
#include "_nstring.h"
#include "nstrlen.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// �p��r��r��
unsigned long nscount(IN const std::string &szInput)
{
	unsigned long ulResult = 0;

	for(std::string::const_iterator Itor = szInput.begin(); Itor != szInput.end(); std::advance(Itor, static_cast<unsigned char>(*Itor) < 128 ? 1 : 2))
		++ulResult;

	return ulResult;
}
//-----------------------------------------------------------------------------
// �p��r��r��
unsigned long nscount(IN const std::wstring &szInput)
{
	return szInput.size();
}
//-----------------------------------------------------------------------------
// �p��r��줸��
unsigned long nsbytes(IN const std::string &szInput)
{
	return szInput.size();
}
//-----------------------------------------------------------------------------
// �p��r��줸��
unsigned long nsbytes(IN const std::wstring &szInput)
{
	return nscount(szInput) * sizeof(std::wstring::value_type);
}
//-----------------------------------------------------------------------------
// �Hmulti-byte�覡�p��r��줸��
unsigned long mbbytes(IN const std::string &szInput)
{
	return szInput.size();
}
//-----------------------------------------------------------------------------
// �Hmulti-byte�覡�p��r��줸��, �e�r������
unsigned long mbbytes(IN const std::wstring &szInput)
{
	unsigned long ulResult = 0;

	std::for_each(szInput.begin(), szInput.end(), [&ulResult] (const std::wstring::value_type &Itor) { ulResult += Itor < 128 ? 1 : 2; });

	return ulResult;
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------