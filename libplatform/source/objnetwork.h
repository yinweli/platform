/**
 * @file objnetwork.h
 * @note �����ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJNETWORK
#define _OBJNETWORK
//-----------------------------------------------------------------------------
/**
 * @brief �������O
 */
class C_ObjNetwork : public C_Object
{
public:
	//-------------------------------------
	C_ObjNetwork(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief �ǰe�ʥ]����A��
	 * @param szName �����W��
	 * @param Packet �ʥ]����
	 */
	void SendToServer(IN const cstring &szName, IN LibCSNStandard::Packet ^Packet)
	{
		_G_();

		return C_Platform::Instance().GetNetwork().SendToServer(C_NetworkKey(m_szServer, szName), Packet, C_Platform::Instance().GetEvent(), C_Platform::Instance().GetRecord());
	};
	/**
	 * @brief �ǰe�ʥ]��Ȥ��
	 * @param szName �����W��
	 * @param Packet �ʥ]����
	 */
	void SendToClient(IN const cstring &szName, IN LibCSNStandard::Packet ^Packet)
	{
		_G_();

		return C_Platform::Instance().GetNetwork().SendToClient(C_NetworkKey(m_szServer, szName), Packet, C_Platform::Instance().GetEvent(), C_Platform::Instance().GetRecord());
	};
	/**
	 * @brief �ǰe�ʥ]��Ȥ��
	 * @param szName �����W��
	 * @param Socket SocketID
	 * @param Packet �ʥ]����
	 */
	void SendToClient(IN const cstring &szName, IN SOCKET Socket, IN LibCSNStandard::Packet ^Packet)
	{
		_G_();

		return C_Platform::Instance().GetNetwork().SendToClient(C_NetworkKey(m_szServer, szName), Socket, Packet, C_Platform::Instance().GetEvent(), C_Platform::Instance().GetRecord());
	};
	/**
	 * @brief ���_�Ȥ�ݳs�u
	 * @param szName �����W��
	 * @param Socket SocketID
	 */
	void CloseClient(IN const cstring &szName, IN SOCKET Socket)
	{
		_G_();

		C_Platform::Instance().GetNetwork().CloseClient(C_NetworkKey(m_szServer, szName), Socket);
	};
	/**
	 * @brief �ˬd�����O�_�s�b
	 * @param szName �����W��
	 * @return true��ܦs�b, false�h�_
	 */
	bool IsExist(IN const cstring &szName) const
	{
		_G_();

		C_Platform::Instance().GetNetwork().IsExist(C_NetworkKey(m_szServer, szName));
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------