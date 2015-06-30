/**
 * @file network.h
 * @note 網路組件
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
 * @brief 網路結構
 */
struct S_Network
{
	std::string szData; ///< 資料字串
	unsigned long ulSize; ///< 資料長度

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
 * @brief 網路索引類別
 */
class C_NetworkKey
{
private:
	//-------------------------------------
	cstring m_szServer; ///< 伺服器名稱
	cstring m_szName; ///< 識別名稱
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
	 * @brief 取得索引字串
	 * @return 索引字串
	 */
	cstring Key() const
	{
		return m_szServer + __T(":") + m_szName;
	};
	/**
	 * @brief 取得伺服器名稱
	 * @return 伺服器名稱
	 */
	cstring Server() const
	{
		_G_();

		return m_szServer;
	};
	/**
	 * @brief 取得識別名稱
	 * @return 識別名稱
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
 * @brief 網路類別
 */
class C_Network
{
private:
	//-------------------------------------
	std::map<C_NetworkKey, C_XClient *> m_Client; ///< 客戶端網路列表 <索引物件, 網路指標>
	std::map<C_NetworkKey, C_XServer *> m_Server; ///< 伺服器網路列表 <索引物件, 網路指標>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_Network();
	virtual ~C_Network();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 新增客戶端網路物件
	 * @param ccKey 索引物件
	 * @param ccIPData 位址物件
	 * @return true表示成功, false則否
	 */
	bool AddClient(IN const C_NetworkKey &ccKey, IN const C_IPData &ccIPData);
	/**
	 * @brief 新增伺服器網路物件
	 * @param ccKey 索引物件
	 * @param ccIPData 位址物件
	 * @param iConnect 連線數
	 * @return true表示成功, false則否
	 */
	bool AddServer(IN const C_NetworkKey &ccKey, IN const C_IPData &ccIPData, IN int iConnect);
	/**
	 * @brief 傳送封包到伺服器
	 * @param ccKey 索引物件
	 * @param Packet 封包物件
	 * @param ccEvent 事件處理物件
	 * @param ccRecord 封包網路物件
	 */
	void SendToServer(IN const C_NetworkKey &ccKey, IN LibCSNStandard::Packet ^Packet, IN C_Event &ccEvent, IN C_Record &ccRecord);
	/**
	 * @brief 傳送封包到客戶端
	 * @param ccKey 索引物件
	 * @param Packet 封包物件
	 * @param ccEvent 事件處理物件
	 * @param ccRecord 封包網路物件
	 */
	void SendToClient(IN const C_NetworkKey &ccKey, IN LibCSNStandard::Packet ^Packet, IN C_Event &ccEvent, IN C_Record &ccRecord);
	/**
	 * @brief 傳送封包到客戶端
	 * @param ccKey 索引物件
	 * @param Socket SocketID
	 * @param Packet 封包物件
	 * @param ccEvent 事件處理物件
	 * @param ccRecord 封包網路物件
	 */
	void SendToClient(IN const C_NetworkKey &ccKey, IN SOCKET Socket, IN LibCSNStandard::Packet ^Packet, IN C_Event &ccEvent, IN C_Record &ccRecord);
	/**
	 * @brief 中斷客戶端連線
	 * @param ccKey 索引物件
	 * @param Socket SocketID
	 */
	void CloseClient(IN const C_NetworkKey &ccKey, IN SOCKET Socket);
	/**
	 * @brief 執行定時處理
	 * @param szServer 伺服器名稱
	 * @param ccEvent 事件處理物件
	 * @param ccPacket 封包處理物件
	 * @param ccRecord 封包網路物件
	 */
	void Execute(IN const cstring &szServer, IN C_Event &ccEvent, IN C_Packet &ccPacket, IN C_Record &ccRecord);
	/**
	 * @brief 檢查網路是否存在
	 * @param ccKey 索引物件
	 * @return true表示存在, false則否
	 */
	bool IsExist(IN const C_NetworkKey &ccKey) const;
	/**
	 * @brief 取得客戶端網路紀錄列表
	 * @param szServer 伺服器名稱
	 * @return 客戶端網路紀錄列表
	 */
	std::map<cstring, S_XClient> RecordClient(IN const cstring &szServer) const;
	/**
	 * @brief 取得伺服器網路紀錄列表
	 * @param szServer 伺服器名稱
	 * @return 伺服器網路紀錄列表
	 */
	std::map<cstring, S_XServer> RecordServer(IN const cstring &szServer) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------