/**
 * @file objnetwork.h
 * @note 網路組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJNETWORK
#define _OBJNETWORK
//-----------------------------------------------------------------------------
/**
 * @brief 網路類別
 */
class C_ObjNetwork : public C_Object
{
public:
	//-------------------------------------
	C_ObjNetwork(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief 傳送封包到伺服器
	 * @param szName 網路名稱
	 * @param Packet 封包物件
	 */
	void SendToServer(IN const cstring &szName, IN LibCSNStandard::Packet ^Packet)
	{
		_G_();

		return C_Platform::Instance().GetNetwork().SendToServer(C_NetworkKey(m_szServer, szName), Packet, C_Platform::Instance().GetEvent(), C_Platform::Instance().GetRecord());
	};
	/**
	 * @brief 傳送封包到客戶端
	 * @param szName 網路名稱
	 * @param Packet 封包物件
	 */
	void SendToClient(IN const cstring &szName, IN LibCSNStandard::Packet ^Packet)
	{
		_G_();

		return C_Platform::Instance().GetNetwork().SendToClient(C_NetworkKey(m_szServer, szName), Packet, C_Platform::Instance().GetEvent(), C_Platform::Instance().GetRecord());
	};
	/**
	 * @brief 傳送封包到客戶端
	 * @param szName 網路名稱
	 * @param Socket SocketID
	 * @param Packet 封包物件
	 */
	void SendToClient(IN const cstring &szName, IN SOCKET Socket, IN LibCSNStandard::Packet ^Packet)
	{
		_G_();

		return C_Platform::Instance().GetNetwork().SendToClient(C_NetworkKey(m_szServer, szName), Socket, Packet, C_Platform::Instance().GetEvent(), C_Platform::Instance().GetRecord());
	};
	/**
	 * @brief 中斷客戶端連線
	 * @param szName 網路名稱
	 * @param Socket SocketID
	 */
	void CloseClient(IN const cstring &szName, IN SOCKET Socket)
	{
		_G_();

		C_Platform::Instance().GetNetwork().CloseClient(C_NetworkKey(m_szServer, szName), Socket);
	};
	/**
	 * @brief 檢查網路是否存在
	 * @param szName 網路名稱
	 * @return true表示存在, false則否
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