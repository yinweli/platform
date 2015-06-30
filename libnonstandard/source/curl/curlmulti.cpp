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
// �w�ɳB�z
void C_CURLMulti::Process()
{
	if(m_pCURLM == nullptr)
		return;

	// �ˬd�O�_�����ʤ���curl
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

	// ����curl multi
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

	// �ˬd���G
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
// ����curl
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
// ���ocurl�O�_�s�b
bool C_CURLMulti::IsExist(IN const C_CURLMeta &ccCURLMeta) const
{
	return m_Status.find(ccCURLMeta) != m_Status.end();
}
//-----------------------------------------------------------------------------
// ���ocurl�O�_����
bool C_CURLMulti::IsComplete(IN const C_CURLMeta &ccCURLMeta) const
{
	std::map<CURL *, bool>::const_iterator Itor = m_Status.find(ccCURLMeta);

	return Itor != m_Status.end() && Itor->second;
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------