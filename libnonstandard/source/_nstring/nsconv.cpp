//-----------------------------------------------------------------------------
#include "_nstring.h"
#include "nsconv.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// �ഫstd::string��std::wstring
std::wstring nsconv(IN const std::string &szInput)
{
	return std::wstring(static_cast<const wchar_t *>(_bstr_t(szInput.c_str())));
}
//-----------------------------------------------------------------------------
// �ഫstd::wstring��std::string
std::string nsconv(IN const std::wstring &szInput)
{
	return std::string(static_cast<const char *>(_bstr_t(szInput.c_str())));
}
//-----------------------------------------------------------------------------
// �ഫSystem::String��std::string
std::string nsconvna(IN System::String ^szInput)
{
	std::string szResult;
	const char *pTemp = static_cast<const char *>((System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(szInput)).ToPointer());

	if(pTemp)
		szResult = pTemp;

	System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void *)pTemp));

	return szResult;
}
//-----------------------------------------------------------------------------
// �ഫSystem::String��std::wstring
std::wstring nsconvaw(IN System::String ^szInput)
{
	std::wstring szResult;
	const wchar_t *pTemp = static_cast<const wchar_t *>((System::Runtime::InteropServices::Marshal::StringToHGlobalUni(szInput)).ToPointer());
	
	if(pTemp)
		szResult = pTemp;

	System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void *)pTemp));

	return szResult;
}
//-----------------------------------------------------------------------------
// �ഫstd::string��System::String
System::String ^nsconvc(IN const std::string &szInput)
{
	return gcnew System::String(szInput.c_str());
}
//-----------------------------------------------------------------------------
// �ഫstd::wstring��System::String
System::String ^nsconvc(IN const std::wstring &szInput)
{
	return gcnew System::String(szInput.c_str());
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------