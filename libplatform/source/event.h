/**
 * @file event.h
 * @note �ƥ�B�z�ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _EVENT
#define _EVENT
//-----------------------------------------------------------------------------
/**
 * @brief �ƥ�B�z�C�|
 */
public enum class ENUM_Event
{
	Connect, ///< �s�u�ƥ�
	Disconnect, ///< �_�u�ƥ�
	PacketRecv, ///< �����ʥ]�ƥ�
	PacketSend, ///< �ǰe�ʥ]�ƥ�
};
//-----------------------------------------------------------------------------
/**
 * @brief ���ު������O
 */
class C_EventKey
{
private:
	//-------------------------------------
	cstring m_szServer; ///< ���A���W��
	cstring m_szName; ///< �ѧO�W��
	ENUM_Event m_emEvent; ///< �ƥ�B�z�C�|
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
	 * @brief ���o���ަr��
	 * @return ���ަr��
	 */
	cstring Key() const
	{
		return m_szServer + __T(":") + m_szName + __T(":") + cstring(m_emEvent);
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
	/**
	 * @brief ���o�ƥ�B�z�C�|
	 * @return �ƥ�B�z�C�|
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
 * @brief �ƥ�B�z�������O
 */
class C_EventInterface
{
public:
	//-------------------------------------
	C_EventInterface() {};
	virtual ~C_EventInterface() {};
	//-------------------------------------
	/**
	 * @brief ����ƥ�B�z
	 * @param Socket SocketID
	 * @return true��ܦ��\, false�h�_
	 */
	virtual bool Execute(IN SOCKET Socket) = 0;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �@��ƥ�B�z���O
 */
class C_EventGeneral : public C_EventInterface
{
public:
	//-------------------------------------
	typedef void (*LPFN_Event) (IN SOCKET Socket); ///< �B�z�禡����
	//-------------------------------------

private:
	//-------------------------------------
	LPFN_Event m_pfEvent; ///< �B�z�禡����
	//-------------------------------------

public:
	//-------------------------------------
	C_EventGeneral(IN LPFN_Event event) : m_pfEvent(event) {};
	virtual ~C_EventGeneral() {};
	//-------------------------------------
	/**
	 * @brief ����ƥ�B�z
	 * @param Socket SocketID
	 * @return true��ܦ��\, false�h�_
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
 * @brief �x�Ψƥ�B�z���O
 */
template<typename O> class C_EventTemplate : public C_EventInterface
{
public:
	//-------------------------------------
	typedef void (O::*LPFN_Event) (IN SOCKET Socket); ///< �B�z�禡����
	//-------------------------------------

private:
	//-------------------------------------
	LPFN_Event m_pfEvent; ///< �B�z�禡����
	O *m_pObject; ///< �B�z�������
	//-------------------------------------

public:
	//-------------------------------------
	C_EventTemplate(IN LPFN_Event event, IN O &object) : m_pfEvent(event), m_pObject(&object) {};
	virtual ~C_EventTemplate() {};
	//-------------------------------------
	/**
	 * @brief ����ƥ�B�z
	 * @param Socket SocketID
	 * @return true��ܦ��\, false�h�_
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
 * @brief �ƥ�B�z�C�����O
 */
class C_EventList
{
private:
	//-------------------------------------
	std::vector<C_EventInterface *> m_Data; ///< �ƥ�B�z���ЦC��
	//-------------------------------------

public:
	//-------------------------------------
	C_EventList() {};
	virtual ~C_EventList() { Clear(); };
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear()
	{
		_G_();

		std::for_each(m_Data.begin(), m_Data.end(), [] (std::vector<C_EventInterface *>::value_type &Itor) { if(Itor) delete Itor; });
		m_Data.clear();
	};
	/**
	 * @brief �s�W�ƥ�B�z����
	 * @param pEvent �ƥ�B�z����
	 */
	void Add(IN C_EventInterface *pEvent)
	{
		_G_();

		if(pEvent)
			m_Data.push_back(pEvent);
	};
	/**
	 * @brief ����ƥ�B�z
	 * @param Socket SocketID
	 */
	void Execute(IN SOCKET Socket)
	{
		_G_();

		std::for_each(m_Data.begin(), m_Data.end(), [Socket] (std::vector<C_EventInterface *>::value_type &Itor) { if(Itor) Itor->Execute(Socket); });
	};
	/**
	 * @brief ���o�ƥ�B�z���мƶq
	 * @return �ƥ�B�z���мƶq
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
 * @brief �ƥ�B�z���O
 */
class C_Event
{
private:
	//-------------------------------------
	std::map<C_EventKey, C_EventList> m_Data; ///< �ƥ�B�z�C�� <���ު���, �C����>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_Event();
	virtual ~C_Event();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W�ƥ�B�z(�R�A�禡����)
	 * @param ccKey ���ު���
	 * @param pfEvent �B�z�禡����
	 * @return true��ܦ��\, false�h�_
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
	 * @brief �s�W�ƥ�B�z(�����禡����)
	 * @param ccKey ���ު���
	 * @param pfEvent �B�z�禡����
	 * @param Object �B�z����
	 * @return true��ܦ��\, false�h�_
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
	 * @brief ����ƥ�B�z
	 * @param ccKey ���ު���
	 * @param Socket SocketID
	 */
	void Execute(IN const C_EventKey &ccKey, IN SOCKET Socket);
	/**
	 * @brief ���o�����C��
	 * @param szServer ���A���W��
	 * @return �����C��
	 */
	std::map<cstring, int> Record(IN const cstring &szServer) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------