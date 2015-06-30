//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xclient.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// �}�lsend
void C_XClient::SendStart(IN SOCKET Socket)
{
	if(m_ccKernal.IOCP() == INVALID_HANDLE_VALUE)
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

	// �ˬd�ǰe�X��, ����������
	if(ccUnit->Send())
		return;

	// �إ߭��|����
	S_XOverlapped *pOverlapped = m_ccListOverlapped.Add(ENUM_XOverlapped_Send, Socket);

	if(pOverlapped == nullptr)
		return;

	// ���o�ǰe����
	C_XSend ccSend = ccUnit->GetSend();

	if(ccSend.Empty())
	{
		m_ccListOverlapped.Del(pOverlapped->emType, pOverlapped->Socket); // �R�����|����

		return;
	}//if

	WSABUF sWSABuf = ccSend;

	// �Ұ�send
	if(m_ccAPI.Send(Socket, sWSABuf, *pOverlapped) == false)
	{
		C_NOutput::Instance().Error(ERRORNSTD, __T("start failed"));
		m_ccAPI.ReleaseSocket(Socket);
		m_ccListUnit.Del(Socket);
		m_ccListOverlapped.Del(pOverlapped->emType, pOverlapped->Socket);
		ccSend.Release(); // ����ǰe����

		return;
	}//if

	ccUnit->Send(true); // �}�Ҷǰe�X��, ���� SendFinish �Q�I�s�ɤ~�|�����ǰe�X��
	ccSend.Release();
}
//-----------------------------------------------------------------------------
// ����send
void C_XClient::SendFinish(IN S_XOverlapped &sOverlapped, IN unsigned long ulBytes, IN bool bResult)
{
	// �B�z���ѩάO�Ȥ���_�u
	if(bResult == false || ulBytes <= 0)
	{
		m_ccListUnit.Del(sOverlapped.Socket);
		m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);

		return;
	}//if

	// ��w�ǿ�椸
	C_XUnitLock ccUnit = m_ccListUnit.Lock(sOverlapped.Socket);

	if(ccUnit)
	{
		m_ccKernal.RecordSend(ulBytes);
		ccUnit->Send(false); // �����ǰe�X��, SendStart �}�ҺX��, ����o������
	}//if

	m_ccListOverlapped.Del(sOverlapped.emType, sOverlapped.Socket);
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------