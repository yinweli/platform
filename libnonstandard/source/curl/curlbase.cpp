//-----------------------------------------------------------------------------
#include "curl.h"
#include "curlbase.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// 初始化curl
void CURLInitialize()
{
	curl_global_init(CURL_GLOBAL_ALL);
}
//-----------------------------------------------------------------------------
// 釋放curl
void CURLRelease()
{
	curl_global_cleanup();
}
//-----------------------------------------------------------------------------
C_ErrorCURL::C_ErrorCURL(IN CURLcode code) : m_szError(code == CURLE_OK ? __T("") : C_NString(curl_easy_strerror(code))) {}
//-----------------------------------------------------------------------------
C_ErrorCURL::C_ErrorCURL(IN CURLMcode code) : m_szError(code == CURLM_OK || code == CURLM_CALL_MULTI_PERFORM ? __T("") : C_NString(curl_multi_strerror(code))) {}
//-----------------------------------------------------------------------------
C_ErrorCURL::C_ErrorCURL(IN CURLFORMcode code)
{
	switch(code)
	{
	case CURL_FORMADD_MEMORY: m_szError = __T("out of memory"); break;
	case CURL_FORMADD_OPTION_TWICE: m_szError = __T("option twice"); break;
	case CURL_FORMADD_NULL: m_szError = __T("pointer null"); break;
	case CURL_FORMADD_UNKNOWN_OPTION: m_szError = __T("unknow option"); break;
	case CURL_FORMADD_INCOMPLETE: m_szError = __T("incomplete"); break;
	case CURL_FORMADD_ILLEGAL_ARRAY: m_szError = __T("illegal array"); break;
	case CURL_FORMADD_DISABLED: m_szError = __T("disabled"); break;
	default: break;
	}//switch
}
//-----------------------------------------------------------------------------
C_ErrorCURL::~C_ErrorCURL() {}
//-----------------------------------------------------------------------------
C_ErrorCURL::operator bool () const
{
	return m_szError.empty();
}
//-----------------------------------------------------------------------------
C_ErrorCURL::operator estring () const
{
	return m_szError;
}
//-----------------------------------------------------------------------------
C_CURLBase::C_CURLBase() : m_pCURL(curl_easy_init()) {}
//-----------------------------------------------------------------------------
C_CURLBase::~C_CURLBase()
{
	if(m_pCURL)
		curl_easy_cleanup(m_pCURL);
}
//-----------------------------------------------------------------------------
C_CURLBase::operator CURL * () const
{
	return m_pCURL;
}
//-----------------------------------------------------------------------------
// 設定curl
bool C_CURLBase::Option(IN CURLoption emOption, IN unsigned long ulValue)
{
	if(m_pCURL == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("curl null"));

	C_ErrorCURL ccResult = curl_easy_setopt(m_pCURL, emOption, ulValue);

	if(ccResult == false)
		return C_NOutput::Instance().Error(ERRORNSTD, ccResult, __T("option(") + ntox(emOption) + __T(") failed"));

	return true;
}
//-----------------------------------------------------------------------------
// 設定curl
bool C_CURLBase::Option(IN CURLoption emOption, IN const nstring &szValue)
{
	if(m_pCURL == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("curl null"));

	C_ErrorCURL ccResult = curl_easy_setopt(m_pCURL, emOption, C_NString(szValue).c_str());

	if(ccResult == false)
		return C_NOutput::Instance().Error(ERRORNSTD, ccResult, __T("option(") + ntox(emOption) + __T(") failed"));

	return true;
}
//-----------------------------------------------------------------------------
// 執行curl
bool C_CURLBase::Perform()
{
	if(m_pCURL == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("curl null"));

	C_ErrorCURL ccResult = curl_easy_perform(m_pCURL);

	if(ccResult == false)
		return C_NOutput::Instance().Error(ERRORNSTD, ccResult, __T("perform failed"));

	return true;
}
//-----------------------------------------------------------------------------
// 取得輸入字串的URL編碼字串
nstring C_CURLBase::URLEncode(IN const nstring &szInput)
{
	if(m_pCURL == nullptr)
		return __T("");

	std::string szInputTemp = C_NString(szInput);
	char *pTemp = curl_easy_escape(m_pCURL, szInputTemp.c_str(), szInputTemp.size());

	if(pTemp == nullptr)
		return __T("");

	nstring szResult = C_NString(pTemp);

	curl_free(pTemp);

	return szResult;
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------