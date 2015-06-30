//-----------------------------------------------------------------------------
#include "debugtool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// ��X�r��찣������
void xOutputDebugString(IN const nstring &szData)
{
	OutputDebugString(szData.c_str());
}
//-----------------------------------------------------------------------------
// �NHRESULT���~�N�X�ഫ���r��
nstring HRESULTtoString(IN HRESULT hr)
{
	nstring szResult;
	LPTSTR pTemp;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&pTemp, 0, nullptr);

	if(pTemp)
	{
		pTemp[_tcslen(pTemp) - 2] = 0;
		szResult = pTemp;

		LocalFree(pTemp);
	}
	else
		szResult = nsoutf(__T("Unknow(0x{x08})")) << hr;

	return szResult;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------