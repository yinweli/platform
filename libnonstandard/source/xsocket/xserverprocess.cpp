//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xserver.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// ���A��IOCP����
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
// ���A���B�z����
void C_XServer::ServerProc()
{
	m_ccKernal.BenchmarkProcStart();

	// �֤߳B�z
	m_ccKernal.Process();

	// �s�W�s�u�B�z
	for(unsigned long ulCount = m_ccListUnit.Size(), ulMax = m_ccKernal.SocketTotal(); ulCount < ulMax; ++ulCount)
		AcceptStart();

	// �}�l����/�ǰe�B�z
	for(const std::set<SOCKET>::value_type &Itor : m_ccListUnit.SocketProcess())
	{
		RecvStart(Itor);
		SendStart(Itor);
		NoticeStart(Itor);
	}//for

	// �}�l�_�u�B�z
	for(const std::set<SOCKET>::value_type &Itor : m_ccListUnit.SocketDisconnect())
		m_ccAPI.ReleaseSocket(Itor);

	m_ccKernal.BenchmarkProcEnd();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------