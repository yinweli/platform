/**
 * @file xlistunit.h
 * @note �ǿ�椸�C�����O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XLISTUNIT
#define _XLISTUNIT
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
class C_XUnit;
//-----------------------------------------------------------------------------
/**
 * @brief �ǿ�椸��w���O
 * @ingroup xlist
 */
class C_XUnitLock
{
private:
	//-------------------------------------
	C_XUnit *m_pUnit; ///< �ǿ�椸����
	//-------------------------------------
	CRITICAL_SECTION *m_pLock; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_XUnitLock();
	C_XUnitLock(IN const C_XUnit *unit);
	virtual ~C_XUnitLock();
	//-------------------------------------
	operator bool () const;
	//-------------------------------------
	C_XUnit *operator -> ();
	//-------------------------------------
	/**
	 * @brief ����ǿ�椸
	 */
	void UnLock();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �ǿ�椸���O
 * @ingroup xlist
 */
class C_XUnit
{
	//-------------------------------------
	friend C_XUnitLock;
	//-------------------------------------

private:
	//-------------------------------------
	C_XListRecv m_ListRecv; ///< �����C��
	C_XListSend m_ListSend; ///< �ǰe�C��
	sockaddr_in m_sAddress; ///< �s�u��}
	bool m_bRunning; ///< ����X��
	bool m_bRecv; ///< �����X��
	bool m_bSend; ///< �ǰe�X��
	bool m_bDisconnect; ///< �_�u�X��
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_XUnit();
	virtual ~C_XUnit();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W�������
	 * @param pData ��ƫ���
	 * @param ulSize ��ƪ���
	 * @return true��ܦ��\, false�h�_
	 */
	bool AddRecv(IN const void *pData, IN unsigned long ulSize);
	/**
	 * @brief ���o�������
	 * @return �������
	 */
	C_XRecv GetRecv();
	/**
	 * @brief ���o������ƬO�_����
	 * @return true��ܬ���, false�h�_
	 */
	bool RecvEmpty() const;
	/**
	 * @brief �s�W�ǰe���
	 * @param pData ��ƫ���
	 * @param ulSize ��ƪ���
	 * @return true��ܦ��\, false�h�_
	 */
	bool AddSend(IN const void *pData, IN unsigned long ulSize);
	/**
	 * @brief ���o�ǰe���
	 * @return �ǰe���
	 */
	C_XSend GetSend();
	/**
	 * @brief ���o�ǰe��ƬO�_����
	 * @return true��ܬ���, false�h�_
	 */
	bool SendEmpty() const;
	/**
	 * @brief �]�w�s�u��}
	 * @param sAddress �s�u��}
	 */
	void Address(IN const sockaddr &sAddress);
	/**
	 * @brief ���o�s�u��}
	 * @param szIP ip
	 * @param ulPort port
	 */
	void Address(OUT nstring &szIP, OUT unsigned long &ulPort) const;
	/**
	 * @brief �]�w����X��
	 * @param bEnable �X��
	 */
	void Running(IN bool bEnable);
	/**
	 * @brief ���o����X��
	 * @return �����X��
	 */
	bool Running() const;
	/**
	 * @brief �]�w�����X��
	 * @param bEnable �X��
	 */
	void Recv(IN bool bEnable);
	/**
	 * @brief ���o�����X��
	 * @return �����X��
	 */
	bool Recv() const;
	/**
	 * @brief �]�w�ǰe�X��
	 * @param bEnable �X��
	 */
	void Send(IN bool bEnable);
	/**
	 * @brief ���o�ǰe�X��
	 * @return �ǰe�X��
	 */
	bool Send() const;
	/**
	 * @brief �]�w�_�u�X��
	 * @param bEnable �X��
	 */
	void Disconnect(IN bool bEnable);
	/**
	 * @brief ���o�_�u�X��
	 * @return �ǰe�X��
	 */
	bool Disconnect() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �ǿ�椸�C�����O
 * @ingroup xlist
 */
class C_XListUnit
{
private:
	//-------------------------------------
	std::map<SOCKET, C_XUnit *> m_Unit; ///< �ǿ�椸�C�� <SocketID, �ǿ�椸����>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_XListUnit();
	virtual ~C_XListUnit();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W�ǿ�椸
	 * @param Socket SocketID
	 * @return true��ܦ��\, false�h�_
	 */
	bool Add(IN SOCKET Socket);
	/**
	 * @brief �R���ǿ�椸
	 * @param Socket SocketID
	 */
	void Del(IN SOCKET Socket);
	/**
	 * @brief �ˬd�ǿ�椸�O�_�s�b
	 * @param Socket SocketID
	 * @return true��ܦs�b, false�h�_
	 */
	bool IsExist(IN SOCKET Socket) const;
	/**
	 * @brief ��w�ǿ�椸
	 * @param Socket SocketID
	 * @return �ǿ�椸��w����
	 */
	C_XUnitLock Lock(IN SOCKET Socket) const;
	/**
	 * @brief ���o�����ǿ�椸�ƶq
	 * @return �ǿ�椸�ƶq
	 */
	unsigned long Size() const;
	/**
	 * @brief ���o�ԲӶǿ�椸�ƶq
	 * @param bRunning ����X��
	 * @return �ǿ�椸�ƶq
	 */
	unsigned long Size(IN bool bRunning) const;
	/**
	 * @brief ���o����SocketID�C��
	 * @return SocketID�C��
	 */
	std::set<SOCKET> SocketList() const;
	/**
	 * @brief ���o�B�zSocketID�C��
	 * @return SocketID�C��
	 */
	std::set<SOCKET> SocketProcess() const;
	/**
	 * @brief ���o�_�uSocketID�C��
	 * @return SocketID�C��
	 */
	std::set<SOCKET> SocketDisconnect() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------