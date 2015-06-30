//-----------------------------------------------------------------------------
#include "_nstderr.h"
#include "errorwin.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_ErrorWin::C_ErrorWin() : m_iWinError(GetLastError()) {}
//-----------------------------------------------------------------------------
C_ErrorWin::C_ErrorWin(IN int error) : m_iWinError(error) {}
//-----------------------------------------------------------------------------
C_ErrorWin::~C_ErrorWin() {}
//-----------------------------------------------------------------------------
C_ErrorWin::operator bool () const
{
	return m_iWinError == ERROR_SUCCESS;
}
//-----------------------------------------------------------------------------
C_ErrorWin::operator int () const
{
	return m_iWinError;
}
//-----------------------------------------------------------------------------
C_ErrorWin::operator estring () const
{
	estring szWinError;
	TCHAR *szTemp = nullptr;
	unsigned long ulFlag = FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER;
	unsigned long ulLang = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);

	if(FormatMessage(ulFlag, nullptr, m_iWinError, ulLang, szTemp, 0, nullptr) == TRUE)
	{
		szWinError = szTemp;
		LocalFree(szTemp);
	}
	else
		szWinError = __T("unknow error");

	TCHAR szErrorID[64];

	_itot_s(m_iWinError, szErrorID, _countof(szErrorID), 10);

	return szWinError + __T(" (") + szErrorID + __T(")");
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------