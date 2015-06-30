//-----------------------------------------------------------------------------
#include "curl.h"
#include "curlmulti.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
C_CURLMulti::C_CURLMulti() : m_pCURLM(curl_multi_init()) {}
//-----------------------------------------------------------------------------
C_CURLMulti::~C_CURLMulti()
{
	if(m_pCURLM)
		curl_multi_cleanup(m_pCURLM);
}
//-----------------------------------------------------------------------------
// 定時處理
void C_CURLMulti::Process()
{
	if(m_pCURLM == nullptr)
		return;

	// 檢查是否有活動中的curl
	{
		int iCURLCount = 0;
		C_ErrorCURL ccResult = curl_multi_perform(m_pCURLM, &iCURLCount);

		if(ccResult == false)
		{
			C_NOutput::Instance().Error(ERRORNSTD, ccResult, __T("perform failed"));
			return;
		}//if

		if(iCURLCount <= 0)
			return;
	}

	// 執行curl multi
	{
		struct timeval sTime;
		fd_set sRead, sWrite, sExcept;
		int iMaxFD = -1;

		sTime.tv_sec = 0;
		sTime.tv_usec = 100;
		FD_ZERO(&sRead);
		FD_ZERO(&sWrite);
		FD_ZERO(&sExcept);

		C_ErrorCURL ccResult = curl_multi_fdset(m_pCURLM, &sRead, &sWrite, &sExcept, &iMaxFD);

		if(ccResult == false)
		{
			C_NOutput::Instance().Error(ERRORNSTD, ccResult, __T("fdset failed"));
			return;
		}//if

		if(select(iMaxFD + 1, &sRead, &sWrite, &sExcept, &sTime) == -1)
		{
			C_NOutput::Instance().Error(ERRORNSTD, __T("select failed"));
			return;
		}//if
	}

	// 檢查結果
	{
		int iMsgCount = 0;
		CURLMsg *pMsg = curl_multi_info_read(m_pCURLM, &iMsgCount);

		while(pMsg)
		{
			if(pMsg->msg == CURLMSG_DONE)
			{
				C_ErrorCURL ccResult(pMsg->data.result);

				m_Status[pMsg->easy_handle] = ccResult;

				if(ccResult == false)
					C_NOutput::Instance().Error(ERRORNSTD, ccResult, __T("transfer failed"));
			}//if

			pMsg = curl_multi_info_read(m_pCURLM, &iMsgCount);
		}//while
	}
}
//-----------------------------------------------------------------------------
// 執行curl
bool C_CURLMulti::Perform(IN const C_CURLMeta &ccCURLMeta)
{
	if(m_pCURLM == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("curlm null"));

	C_ErrorCURL ccResult = curl_multi_add_handle(m_pCURLM, ccCURLMeta);

	if(ccResult == false)
		return C_NOutput::Instance().Error(ERRORNSTD, ccResult, __T("perform failed"));

	m_Status[ccCURLMeta] = false;

	return true;
}
//-----------------------------------------------------------------------------
// 取得curl是否存在
bool C_CURLMulti::IsExist(IN const C_CURLMeta &ccCURLMeta) const
{
	return m_Status.find(ccCURLMeta) != m_Status.end();
}
//-----------------------------------------------------------------------------
// 取得curl是否完成
bool C_CURLMulti::IsComplete(IN const C_CURLMeta &ccCURLMeta) const
{
	std::map<CURL *, bool>::const_iterator Itor = m_Status.find(ccCURLMeta);

	return Itor != m_Status.end() && Itor->second;
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------