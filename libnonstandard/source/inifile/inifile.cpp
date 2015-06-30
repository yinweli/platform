//-----------------------------------------------------------------------------
#include "inifile.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_ErrorIniNotExist::C_ErrorIniNotExist(IN const nstring &filepath) : m_szError(__T("file not exist(") + filepath + __T(")")) {}
//-----------------------------------------------------------------------------
C_ErrorIniNotExist::~C_ErrorIniNotExist() {}
//-----------------------------------------------------------------------------
C_ErrorIniNotExist::operator estring () const
{
	return m_szError;
}
//-----------------------------------------------------------------------------
C_ErrorIniNotFound::C_ErrorIniNotFound(IN const nstring &filepath, IN const nstring &section, IN const nstring &key) : m_szError(__T("value not found(") + filepath + __T(":") + section + __T(":") + key + __T(")")) {}
//-----------------------------------------------------------------------------
C_ErrorIniNotFound::~C_ErrorIniNotFound() {}
//-----------------------------------------------------------------------------
C_ErrorIniNotFound::operator estring () const
{
	return m_szError;
}
//-----------------------------------------------------------------------------
// 取得設定值
bool GetIniValue(IN const nstring &szFilePath, IN const nstring &szSection, IN const nstring &szKey, OUT C_Argu &ccValue)
{
	if(fexist(szFilePath) == false)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorIniNotExist(szFilePath));

	TCHAR szTemp[4096] = {0};

	if(GetPrivateProfileString(szSection.c_str(), szKey.c_str(), nullptr, szTemp, _countof(szTemp), szFilePath.c_str()) <= 0)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorIniNotFound(szFilePath, szSection, szKey));

	ccValue = trimtailspace(nstruncate(szTemp, __T(';')));

	return true;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------