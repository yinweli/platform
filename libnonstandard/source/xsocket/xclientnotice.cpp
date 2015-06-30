//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xclient.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// �}�l�q��
void C_XClient::NoticeStart(IN SOCKET Socket)
{
	// ��w�ǿ�椸
	C_XUnitLock ccUnit = m_ccListUnit.Lock(Socket);

	if(ccUnit == false)
		return;

	C_XRecv ccRecv;

	// ���o XSOCKET_NOTICESIZE ������������, �άO����Ū���������N�|����
	for(unsigned long ulCount = 0; ulCount < XSOCKET_NOTICESIZE; ++ulCount)
	{
		ccRecv = ccUnit->GetRecv();

		if(ccRecv.Empty() == false)
			m_ccListNotice.AddReceive(Socket, ccRecv);
	}//for
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------