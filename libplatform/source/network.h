/**
 * @file network.h
 * @note �����ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _NETWORK
#define _NETWORK
//-----------------------------------------------------------------------------
class C_Event;
class C_Packet;
class C_Record;
//-----------------------------------------------------------------------------
/**
 * @brief �������c
 */
struct S_Network
{
	std::string szData; ///< ��Ʀr��
	unsigned long ulSize; ///< ��ƪ���

	S_Network(IN LibCSNStandard::Packet ^Packet)
	{
		szData = ConvertAnsi(LibCSNStandard::Json::ToString(Packet));
		ulSize = nsbytes(szData) + 1;
	};
	operator const void * () const { return static_cast<const void *>(szData.c_str()); };
	operator unsigned long () const { return ulSize; };
};
//-----------------------------------------------------------------------------
/**
 * @brief �����������O
 */
class C_NetworkKey
{
private:
	//-------------------------------------
	cstring m_szServer; ///< ���A���W��
	cstring m_szName; ///< �ѧO�W��
	//-------------------------------------

public:
	//-------------------------------------
	C_NetworkKey() {};
	C_NetworkKey(IN const cstring &server, IN const cstring &name) : m_szServer(server), m_szName(name) {};
	//-------------------------------------
	bool operator < (IN const C_NetworkKey &rhs) const
	{
		return Key() < rhs.Key();
	};
	operator bool () const
	{
		return Key().empty() == false;
	};
	//-------------------------------------
	/**
	 * @brief ���o���ަr��
	 * @return ���ަr��
	 */
	cstring Key() const
	{
		return m_szServer + __T(":") + m_szName;
	};
	/**
	 * @brief ���o���A���W��
	 * @return ���A���W��
	 */
	cstring Server() const
	{
		_G_();

		return m_szServer;
	};
	/**
	 * @brief ���o�ѧO�W��
	 * @return �ѧO�W��
	 */
	cstring Name() const
	{
		_G_();

		return m_szName;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �������O
 */
class C_Network
{
private:
	//-------------------------------------
	std::map<C_NetworkKey, C_XClient *> m_Client; ///< �Ȥ�ݺ����C�� <���ު���, ��������>
	std::map<C_NetworkKey, C_XServer *> m_Server; ///< ���A�������C�� <���ު���, ��������>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_Network();
	virtual ~C_Network();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W�Ȥ�ݺ�������
	 * @param ccKey ���ު���
	 * @param ccIPData ��}����
	 * @return true��ܦ��\, false�h�_
	 */
	bool AddClient(IN const C_NetworkKey &ccKey, IN const C_IPData &ccIPData);
	/**
	 * @brief �s�W���A����������
	 * @param ccKey ���ު���
	 * @param ccIPData ��}����
	 * @param iConnect �s�u��
	 * @return true��ܦ��\, false�h�_
	 */
	bool AddServer(IN const C_NetworkKey &ccKey, IN const C_IPData &ccIPData, IN int iConnect);
	/**
	 * @brief �ǰe�ʥ]����A��
	 * @param ccKey ���ު���
	 * @param Packet �ʥ]����
	 * @param ccEvent �ƥ�B�z����
	 * @param ccRecord �ʥ]��������
	 */
	void SendToServer(IN const C_NetworkKey &ccKey, IN LibCSNStandard::Packet ^Packet, IN C_Event &ccEvent, IN C_Record &ccRecord);
	/**
	 * @brief �ǰe�ʥ]��Ȥ��
	 * @param ccKey ���ު���
	 * @param Packet �ʥ]����
	 * @param ccEvent �ƥ�B�z����
	 * @param ccRecord �ʥ]��������
	 */
	void SendToClient(IN const C_NetworkKey &ccKey, IN LibCSNStandard::Packet ^Packet, IN C_Event &ccEvent, IN C_Record &ccRecord);
	/**
	 * @brief �ǰe�ʥ]��Ȥ��
	 * @param ccKey ���ު���
	 * @param Socket SocketID
	 * @param Packet �ʥ]����
	 * @param ccEvent �ƥ�B�z����
	 * @param ccRecord �ʥ]��������
	 */
	void SendToClient(IN const C_NetworkKey &ccKey, IN SOCKET Socket, IN LibCSNStandard::Packet ^Packet, IN C_Event &ccEvent, IN C_Record &ccRecord);
	/**
	 * @brief ���_�Ȥ�ݳs�u
	 * @param ccKey ���ު���
	 * @param Socket SocketID
	 */
	void CloseClient(IN const C_NetworkKey &ccKey, IN SOCKET Socket);
	/**
	 * @brief ����w�ɳB�z
	 * @param szServer ���A���W��
	 * @param ccEvent �ƥ�B�z����
	 * @param ccPacket �ʥ]�B�z����
	 * @param ccRecord �ʥ]��������
	 */
	void Execute(IN const cstring &szServer, IN C_Event &ccEvent, IN C_Packet &ccPacket, IN C_Record &ccRecord);
	/**
	 * @brief �ˬd�����O�_�s�b
	 * @param ccKey ���ު���
	 * @return true��ܦs�b, false�h�_
	 */
	bool IsExist(IN const C_NetworkKey &ccKey) const;
	/**
	 * @brief ���o�Ȥ�ݺ��������C��
	 * @param szServer ���A���W��
	 * @return �Ȥ�ݺ��������C��
	 */
	std::map<cstring, S_XClient> RecordClient(IN const cstring &szServer) const;
	/**
	 * @brief ���o���A�����������C��
	 * @param szServer ���A���W��
	 * @return ���A�����������C��
	 */
	std::map<cstring, S_XServer> RecordServer(IN const cstring &szServer) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------