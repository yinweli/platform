//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xserver.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// �}�lrecv
void C_XServer::RecvStart(IN SOCKET Socket)
{
	if(m_ccKernal.IOCP() == INVALID_HANDLE_VALUE)
		return;

	if(m_ccKernal.Socket() == INVALID_SOCKET)
		return;

	if(m_ccThreadMgr.Size() <= 0)
		return;

	if(Socket == INVALID_SOCKET)
		return;

	// ��w�ǿ�椸
	C_XUnitLock ccUnit = m_ccListUnit.Lock(Socket);

	if(ccUnit == false)
		return;

	// �ˬd�ǿ�椸����X��
	if(ccUnit->Running() == false)
		return;

	// �ˬd�����X��, ����������
	if(ccUnit->Recv())
		return;

	// �إ߭��|����
	S_XOverlapped *pOverlapped = m_ccListOverlapped.Add(ENUM_XOverlapped_Recv, Socket);

	if(pOverlapped == nullptr)
		return;

	WSABUF sWSABuf;

	sWSABuf.buf = pOverlapped->cBuffer;
	sWSABuf.len = sizeof(pOverlapped->cBuffer);

	// �Ұ�recv
	if(m_ccAPI.Recv(Socket, sWSABuf, *pOverlapped) == false)
	{
		m_ccListNotice.AddDisconnect(Socket); // �_�u�q����recv���~�ɵo�X
		m_ccListUnit.Del(Socket);
		m_ccListOverlapped.Del(pOverlapped->emType, pOverlapped->Socket);
		m_ccAPI.ReleaseSocket(Socket);

		return;
	}//if

	ccUnit->Recv(true); // �}�ұ����X��, ���� RecvFinish �Q�I�s�ɤ~�|���������X��
}
//-----------------------------------------------------------------------------
// ����recv
void C_XServer::RecvFinish(IN S_XOverlapped &sOverlapped, IN unsigned long ulBytes, IN bool bResult)
{
	// �B�z���ѩάO�Ȥ���_�u
	if(bResult == false || ulBytes <= 0)
	{
		m_ccListNotice.AddDisconnect(sOverlapped.Socket); // �_�u�q����recv���~�ɵo�X
		m_ccListUnit.Del(sOverlapped.Socket);
		m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);

		return;
	}//if

	// ��w�ǿ�椸
	C_XUnitLock ccUnit = m_ccListUnit.Lock(sOverlapped.Socket);

	if(ccUnit)
	{
		// �N������ƥ[�J�����C��
		if(ccUnit->AddRecv(sOverlapped.cBuffer, ulBytes))
			m_ccKernal.RecordRecv(ulBytes);

		ccUnit->Recv(false); // ���������X��, RecvStart �}�ҺX��, ����o������
	}//if

	m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------