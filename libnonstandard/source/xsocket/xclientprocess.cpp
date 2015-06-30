//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xclient.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 客戶端IOCP執行
void C_XClient::ClientIOCP(IN S_XOverlapped *pOverlapped, IN unsigned long ulBytes, IN bool bResult)
{
	if(pOverlapped == nullptr)
		return;

	m_ccKernal.BenchmarkIOCPStart();

	switch(pOverlapped->emType)
	{
	case ENUM_XOverlapped_Connect:
		ConnectFinish(*pOverlapped, ulBytes, bResult);
		break;

	case ENUM_XOverlapped_Recv:
		RecvFinish(*pOverlapped, ulBytes, bResult);
		break;

	case ENUM_XOverlapped_Send:
		SendFinish(*pOverlapped, ulBytes, bResult);
		break;

	default:
		C_NOutput::Instance().Error(ERRORNSTD, __T("unknow overlapped type"));
		break;
	}//switch

	m_ccKernal.BenchmarkIOCPEnd();
}
//-----------------------------------------------------------------------------
// 客戶端處理執行
void C_XClient::ClientProc()
{
	m_ccKernal.BenchmarkProcStart();

	// 核心處理
	m_ccKernal.Process();

	// 連線處理
	if(m_ccKernal.ConnectCheck())
		ConnectStart(m_ccListConnect.IPData(INVALID_SOCKET));

	// 開始接收/傳送處理
	for(const std::set<SOCKET>::value_type &Itor : m_ccListUnit.SocketProcess())
	{
		RecvStart(Itor);
		SendStart(Itor);
		NoticeStart(Itor);
	}//for

	m_ccKernal.BenchmarkProcEnd();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------