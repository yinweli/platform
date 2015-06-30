/**
 * @file packet.h
 * @note 封包處理組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _PACKET
#define _PACKET
//-----------------------------------------------------------------------------
/**
 * @brief 封包處理索引類別
 */
class C_PacketKey
{
private:
	//-------------------------------------
	cstring m_szServer; ///< 伺服器名稱
	cstring m_szName; ///< 識別名稱
	int m_iPacketID; ///< 封包編號
	//-------------------------------------

public:
	//-------------------------------------
	C_PacketKey() {};
	C_PacketKey(IN const cstring &server, IN const cstring &name, IN LibCSNStandard::Packet ^packet) : m_szServer(server), m_szName(name), m_iPacketID(packet->packet) {};
	//-------------------------------------
	bool operator < (IN const C_PacketKey &rhs) const
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
		return m_szServer + __T(":") + m_szName + __T(":") + ntox(m_iPacketID);
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
	/**
	 * @brief 取得封包編號
	 * @return 封包編號
	 */
	int PacketID() const
	{
		_G_();

		return m_iPacketID;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 封包處理介面類別
 */
class C_PacketInterface
{
public:
	//-------------------------------------
	C_PacketInterface() {};
	virtual ~C_PacketInterface() {};
	//-------------------------------------
	/**
	 * @brief 執行封包處理
	 * @param Socket SocketID
	 * @param szJson Json字串
	 * @return true表示成功, false則否
	 */
	virtual bool Execute(IN SOCKET Socket, IN const cstring &szJson) = 0;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 一般封包處理類別
 */
template<typename T> class C_PacketGeneral : public C_PacketInterface
{
public:
	//-------------------------------------
	typedef void (*LPFN_Packet) (IN SOCKET Socket, IN T ^Packet); ///< 一般封包處理函式指標
	//-------------------------------------

private:
	//-------------------------------------
	LPFN_Packet m_pfPacket; ///< 處理函式指標
	//-------------------------------------

public:
	//-------------------------------------
	C_PacketGeneral(IN LPFN_Packet packet) : m_pfPacket(packet) {};
	virtual ~C_PacketGeneral() {};
	//-------------------------------------
	/**
	 * @brief 執行封包處理
	 * @param Socket SocketID
	 * @param Packet 封包物件
	 * @return true表示成功, false則否
	 */
	bool Execute(IN SOCKET Socket, IN const cstring &szJson)
	{
		_G_();

		if(m_pfPacket == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("packet null"));

		m_pfPacket(Socket, LibCSNStandard::Json::ToObject<T ^>(szJson.tostring()));

		return true;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 泛形封包處理類別
 */
template<typename T, typename O> class C_PacketTemplate : public C_PacketInterface
{
public:
	//-------------------------------------
	typedef void (O::*LPFN_Packet) (IN SOCKET Socket, IN T ^Packet); ///< 泛形封包處理函式指標
	//-------------------------------------

private:
	//-------------------------------------
	LPFN_Packet m_pfPacket; ///< 處理函式指標
	O *m_pObject; ///< 處理物件指標
	//-------------------------------------

public:
	//-------------------------------------
	C_PacketTemplate(IN LPFN_Packet packet, IN O &object) : m_pfPacket(packet), m_pObject(&object) {};
	virtual ~C_PacketTemplate() {};
	//-------------------------------------
	/**
	 * @brief 執行封包處理
	 * @param Socket SocketID
	 * @param szJson Json字串
	 * @return true表示成功, false則否
	 */
	bool Execute(IN SOCKET Socket, IN const cstring &szJson)
	{
		_G_();

		if(m_pfPacket == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("packet null"));

		if(m_pObject == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("object null"));

		(m_pObject->*m_pfPacket)(Socket, LibCSNStandard::Json::ToObject<T ^>(szJson.tostring()));

		return true;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 封包處理類別
 */
class C_Packet
{
private:
	//-------------------------------------
	std::map<C_PacketKey, C_PacketInterface *> m_Data; ///< 封包處理列表 <索引物件, 封包處理指標>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_Packet();
	virtual ~C_Packet();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 新增封包處理(靜態函式版本)
	 * @param ccKey 索引物件
	 * @param pfPacket 處理函式指標
	 * @return true表示成功, false則否
	 */
	template<typename T> bool Add(IN const C_PacketKey &ccKey, IN typename C_PacketGeneral<T>::LPFN_Packet pfPacket)
	{
		_G_();

		if(ccKey == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

		if(pfPacket == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("packet null(") + ccKey.Key() + __T(")"));

		C_ThreadLock ccLock(&m_csCommon);

		if(m_Data.find(ccKey) != m_Data.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + ccKey.Key() + __T(")"));

		C_PacketInterface *pData = nstdnew C_PacketGeneral<T>(pfPacket);

		if(pData == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create packet failed(") + ccKey.Key() + __T(")"));

		m_Data[ccKey] = pData;

		return true;
	};
	/**
	 * @brief 新增封包處理(成員函式版本)
	 * @param ccKey 索引物件
	 * @param pfPacket 處理函式指標
	 * @param Object 處理物件
	 * @return true表示成功, false則否
	 */
	template<typename T, typename O> bool Add(IN const C_PacketKey &ccKey, IN typename C_PacketTemplate<T, O>::LPFN_Packet pfPacket, IN O &Object)
	{
		_G_();

		if(ccKey == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

		if(pfPacket == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("packet null(") + ccKey.Key() + __T(")"));

		C_ThreadLock ccLock(&m_csCommon);

		if(m_Data.find(ccKey) != m_Data.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + ccKey.Key() + __T(")"));

		C_PacketInterface *pData = nstdnew C_PacketTemplate<T, O>(pfPacket, Object);

		if(pData == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create packet failed(") + ccKey.Key() + __T(")"));

		m_Data[ccKey] = pData;

		return true;
	};
	/**
	 * @brief 執行封包處理
	 * @param szServer 伺服器名稱
	 * @param szName 識別名稱
	 * @param Socket SocketID
	 * @param szJson Json字串
	 * @param Packet 封包物件
	 * @return true表示成功, false則否
	 */
	bool Execute(IN const cstring &szServer, IN const cstring &szName, IN SOCKET Socket, IN const cstring &szJson, OUT LibCSNStandard::Packet ^Packet);
	/**
	 * @brief 取得紀錄列表
	 * @param szServer 伺服器名稱
	 * @return 紀錄列表
	 */
	std::set<C_PacketKey> Record(IN const cstring &szServer) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------