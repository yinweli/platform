//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xserver.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// �}�laccept
void C_XServer::AcceptStart()
{
	if(m_ccKernal.IOCP() == INVALID_HANDLE_VALUE)
		return;

	if(m_ccKernal.Socket() == INVALID_SOCKET)
		return;

	if(m_ccThreadMgr.Size() <= 0)
		return;

	SOCKET Socket = INVALID_SOCKET;

	// �إ߷s��Socket
	if(m_ccAPI.CreateSocket(m_ccKernal.Addr(), Socket) == false)
		return;

	// �إ߶ǿ�椸
	if(m_ccListUnit.Add(Socket) == false)
	{
		m_ccAPI.ReleaseSocket(Socket);

		return;
	}//if

	// ��w�ǿ�椸
	C_XUnitLock ccUnit = m_ccListUnit.Lock(Socket);

	if(ccUnit == false)
	{
		m_ccAPI.ReleaseSocket(Socket);

		return;
	}//if

	// �إ߭��|����
	S_XOverlapped *pOverlapped = m_ccListOverlapped.Add(ENUM_XOverlapped_Accept, Socket);

	if(pOverlapped == nullptr)
	{
		m_ccAPI.ReleaseSocket(Socket);
		m_ccListUnit.Del(Socket);

		return;
	}//if

	// �Ұ�accept
	if(m_ccAPI.Accept(m_ccKernal.Socket(), pOverlapped->Socket, reinterpret_cast<void *>(pOverlapped->cBuffer), *pOverlapped) == false)
	{
		C_NOutput::Instance().Error(ERRORNSTD, __T("start failed"));
		m_ccAPI.ReleaseSocket(Socket);
		m_ccListUnit.Del(Socket);
		m_ccListOverlapped.Del(pOverlapped->emType, pOverlapped->Socket);

		return;
	}//if

	m_ccAPI.AssociateIOCompletionPort(m_ccKernal.IOCP(), Socket, 0);
}
//-----------------------------------------------------------------------------
// ����accept
void C_XServer::AcceptFinish(IN S_XOverlapped &sOverlapped, IN unsigned long ulBytes, IN bool bResult)
{
	SOCKET SocketServer = m_ccKernal.Socket();
	sockaddr sAddrServer; // ���A����}���c
	sockaddr sAddrClient; // �Ȥ�ݦ�}���c

	if(bResult == false)
	{
		m_ccListUnit.Del(sOverlapped.Socket);
		m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);

		return;
	}//if

	// ���o�s�u��}
	if(m_ccAPI.GetAcceptSockAddr(reinterpret_cast<void *>(sOverlapped.cBuffer), sAddrServer, sAddrClient) == false)
	{
		m_ccListUnit.Del(sOverlapped.Socket);
		m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);

		return;
	}//if

	// ����accept
	if(m_ccAPI.AcceptContext(SocketServer, sOverlapped.Socket) == false)
	{
		m_ccListUnit.Del(sOverlapped.Socket);
		m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);

		return;
	}//if

	// ��w�ǿ�椸
	C_XUnitLock ccUnit = m_ccListUnit.Lock(sOverlapped.Socket);

	if(ccUnit == false)
	{
		m_ccListUnit.Del(sOverlapped.Socket);
		m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);

		return;
	}//if

	ccUnit->Address(sAddrClient);
	ccUnit->Running(true);
	m_ccListNotice.AddConnect(sOverlapped.Socket);
	m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------