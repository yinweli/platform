/**
 * @file event.h
 * @note 事件處理組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _EVENT
#define _EVENT
//-----------------------------------------------------------------------------
/**
 * @brief 事件處理列舉
 */
public enum class ENUM_Event
{
	Connect, ///< 連線事件
	Disconnect, ///< 斷線事件
	PacketRecv, ///< 接收封包事件
	PacketSend, ///< 傳送封包事件
};
//-----------------------------------------------------------------------------
/**
 * @brief 索引物件類別
 */
class C_EventKey
{
private:
	//-------------------------------------
	cstring m_szServer; ///< 伺服器名稱
	cstring m_szName; ///< 識別名稱
	ENUM_Event m_emEvent; ///< 事件處理列舉
	//-------------------------------------

public:
	//-------------------------------------
	C_EventKey() {};
	C_EventKey(IN const cstring &server, IN const cstring &name, IN ENUM_Event event) : m_szServer(server), m_szName(name), m_emEvent(event) {};
	//-------------------------------------
	bool operator < (IN const C_EventKey &rhs) const
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
		return m_szServer + __T(":") + m_szName + __T(":") + cstring(m_emEvent);
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
	 * @brief 取得事件處理列舉
	 * @return 事件處理列舉
	 */
	ENUM_Event Event() const
	{
		_G_();

		return m_emEvent;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 事件處理介面類別
 */
class C_EventInterface
{
public:
	//-------------------------------------
	C_EventInterface() {};
	virtual ~C_EventInterface() {};
	//-------------------------------------
	/**
	 * @brief 執行事件處理
	 * @param Socket SocketID
	 * @return true表示成功, false則否
	 */
	virtual bool Execute(IN SOCKET Socket) = 0;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 一般事件處理類別
 */
class C_EventGeneral : public C_EventInterface
{
public:
	//-------------------------------------
	typedef void (*LPFN_Event) (IN SOCKET Socket); ///< 處理函式指標
	//-------------------------------------

private:
	//-------------------------------------
	LPFN_Event m_pfEvent; ///< 處理函式指標
	//-------------------------------------

public:
	//-------------------------------------
	C_EventGeneral(IN LPFN_Event event) : m_pfEvent(event) {};
	virtual ~C_EventGeneral() {};
	//-------------------------------------
	/**
	 * @brief 執行事件處理
	 * @param Socket SocketID
	 * @return true表示成功, false則否
	 */
	bool Execute(IN SOCKET Socket)
	{
		_G_();

		if(m_pfEvent == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("event null"));

		m_pfEvent(Socket);

		return true;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 泛形事件處理類別
 */
template<typename O> class C_EventTemplate : public C_EventInterface
{
public:
	//-------------------------------------
	typedef void (O::*LPFN_Event) (IN SOCKET Socket); ///< 處理函式指標
	//-------------------------------------

private:
	//-------------------------------------
	LPFN_Event m_pfEvent; ///< 處理函式指標
	O *m_pObject; ///< 處理物件指標
	//-------------------------------------

public:
	//-------------------------------------
	C_EventTemplate(IN LPFN_Event event, IN O &object) : m_pfEvent(event), m_pObject(&object) {};
	virtual ~C_EventTemplate() {};
	//-------------------------------------
	/**
	 * @brief 執行事件處理
	 * @param Socket SocketID
	 * @return true表示成功, false則否
	 */
	bool Execute(IN SOCKET Socket)
	{
		_G_();

		if(m_pfEvent == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("event null"));

		if(m_pObject == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("object null"));

		(m_pObject->*m_pfEvent)(Socket);

		return true;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 事件處理列表類別
 */
class C_EventList
{
private:
	//-------------------------------------
	std::vector<C_EventInterface *> m_Data; ///< 事件處理指標列表
	//-------------------------------------

public:
	//-------------------------------------
	C_EventList() {};
	virtual ~C_EventList() { Clear(); };
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear()
	{
		_G_();

		std::for_each(m_Data.begin(), m_Data.end(), [] (std::vector<C_EventInterface *>::value_type &Itor) { if(Itor) delete Itor; });
		m_Data.clear();
	};
	/**
	 * @brief 新增事件處理指標
	 * @param pEvent 事件處理指標
	 */
	void Add(IN C_EventInterface *pEvent)
	{
		_G_();

		if(pEvent)
			m_Data.push_back(pEvent);
	};
	/**
	 * @brief 執行事件處理
	 * @param Socket SocketID
	 */
	void Execute(IN SOCKET Socket)
	{
		_G_();

		std::for_each(m_Data.begin(), m_Data.end(), [Socket] (std::vector<C_EventInterface *>::value_type &Itor) { if(Itor) Itor->Execute(Socket); });
	};
	/**
	 * @brief 取得事件處理指標數量
	 * @return 事件處理指標數量
	 */
	int Size() const
	{
		_G_();

		return m_Data.size();
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 事件處理類別
 */
class C_Event
{
private:
	//-------------------------------------
	std::map<C_EventKey, C_EventList> m_Data; ///< 事件處理列表 <索引物件, 列表物件>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_Event();
	virtual ~C_Event();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 新增事件處理(靜態函式版本)
	 * @param ccKey 索引物件
	 * @param pfEvent 處理函式指標
	 * @return true表示成功, false則否
	 */
	bool Add(IN const C_EventKey &ccKey, IN C_EventGeneral::LPFN_Event pfEvent)
	{
		_G_();

		if(ccKey == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

		if(pfEvent == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("event null(") + ccKey.Key() + __T(")"));

		C_ThreadLock ccLock(&m_csCommon);
		std::map<C_EventKey, C_EventList>::iterator Itor = m_Data.find(ccKey);

		if(Itor == m_Data.end())
			Itor = insertmap(m_Data, ccKey, C_EventList());

		if(Itor == m_Data.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create list failed(") + ccKey.Key() + __T(")"));

		C_EventInterface *pEvent = nstdnew C_EventGeneral(pfEvent);

		if(pEvent == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create event failed(") + ccKey.Key() + __T(")"));

		Itor->second.Add(pEvent);

		return true;
	};
	/**
	 * @brief 新增事件處理(成員函式版本)
	 * @param ccKey 索引物件
	 * @param pfEvent 處理函式指標
	 * @param Object 處理物件
	 * @return true表示成功, false則否
	 */
	template<typename O> bool Add(IN const C_EventKey &ccKey, IN typename C_EventTemplate<O>::LPFN_Event pfEvent, IN O &Object)
	{
		_G_();

		if(ccKey == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

		if(pfEvent == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("event null(") + ccKey.Key() + __T(")"));

		C_ThreadLock ccLock(&m_csCommon);
		std::map<C_EventKey, C_EventList>::iterator Itor = m_Data.find(ccKey);

		if(Itor == m_Data.end())
			Itor = insertmap(m_Data, ccKey, C_EventList());

		if(Itor == m_Data.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create list failed(") + ccKey.Key() + __T(")"));

		C_EventInterface *pEvent = nstdnew C_EventTemplate<O>(pfEvent, Object);

		if(pEvent == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create event failed(") + ccKey.Key() + __T(")"));

		Itor->second.Add(pEvent);

		return true;
	};
	/**
	 * @brief 執行事件處理
	 * @param ccKey 索引物件
	 * @param Socket SocketID
	 */
	void Execute(IN const C_EventKey &ccKey, IN SOCKET Socket);
	/**
	 * @brief 取得紀錄列表
	 * @param szServer 伺服器名稱
	 * @return 紀錄列表
	 */
	std::map<cstring, int> Record(IN const cstring &szServer) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------