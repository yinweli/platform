//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xserver.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 伺服器IOCP執行
void C_XServer::ServerIOCP(IN S_XOverlapped *pOverlapped, IN unsigned long ulBytes, IN bool bResult)
{
	if(pOverlapped == nullptr)
		return;

	m_ccKernal.BenchmarkIOCPStart();

	switch(pOverlapped->emType)
	{
	case ENUM_XOverlapped_Accept:
		AcceptFinish(*pOverlapped, ulBytes, bResult);
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
// 伺服器處理執行
void C_XServer::ServerProc()
{
	m_ccKernal.BenchmarkProcStart();

	// 核心處理
	m_ccKernal.Process();

	// 新增連線處理
	for(unsigned long ulCount = m_ccListUnit.Size(), ulMax = m_ccKernal.SocketTotal(); ulCount < ulMax; ++ulCount)
		AcceptStart();

	// 開始接收/傳送處理
	for(const std::set<SOCKET>::value_type &Itor : m_ccListUnit.SocketProcess())
	{
		RecvStart(Itor);
		SendStart(Itor);
		NoticeStart(Itor);
	}//for

	// 開始斷線處理
	for(const std::set<SOCKET>::value_type &Itor : m_ccListUnit.SocketDisconnect())
		m_ccAPI.ReleaseSocket(Itor);

	m_ccKernal.BenchmarkProcEnd();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------