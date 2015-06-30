//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xclient.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// �Ȥ��IOCP����
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
// �Ȥ�ݳB�z����
void C_XClient::ClientProc()
{
	m_ccKernal.BenchmarkProcStart();

	// �֤߳B�z
	m_ccKernal.Process();

	// �s�u�B�z
	if(m_ccKernal.ConnectCheck())
		ConnectStart(m_ccListConnect.IPData(INVALID_SOCKET));

	// �}�l����/�ǰe�B�z
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