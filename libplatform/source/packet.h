/**
 * @file packet.h
 * @note �ʥ]�B�z�ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _PACKET
#define _PACKET
//-----------------------------------------------------------------------------
/**
 * @brief �ʥ]�B�z�������O
 */
class C_PacketKey
{
private:
	//-------------------------------------
	cstring m_szServer; ///< ���A���W��
	cstring m_szName; ///< �ѧO�W��
	int m_iPacketID; ///< �ʥ]�s��
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
	 * @brief ���o���ަr��
	 * @return ���ަr��
	 */
	cstring Key() const
	{
		return m_szServer + __T(":") + m_szName + __T(":") + ntox(m_iPacketID);
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
	 * @brief ���o�ʥ]�s��
	 * @return �ʥ]�s��
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
 * @brief �ʥ]�B�z�������O
 */
class C_PacketInterface
{
public:
	//-------------------------------------
	C_PacketInterface() {};
	virtual ~C_PacketInterface() {};
	//-------------------------------------
	/**
	 * @brief ����ʥ]�B�z
	 * @param Socket SocketID
	 * @param szJson Json�r��
	 * @return true��ܦ��\, false�h�_
	 */
	virtual bool Execute(IN SOCKET Socket, IN const cstring &szJson) = 0;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �@��ʥ]�B�z���O
 */
template<typename T> class C_PacketGeneral : public C_PacketInterface
{
public:
	//-------------------------------------
	typedef void (*LPFN_Packet) (IN SOCKET Socket, IN T ^Packet); ///< �@��ʥ]�B�z�禡����
	//-------------------------------------

private:
	//-------------------------------------
	LPFN_Packet m_pfPacket; ///< �B�z�禡����
	//-------------------------------------

public:
	//-------------------------------------
	C_PacketGeneral(IN LPFN_Packet packet) : m_pfPacket(packet) {};
	virtual ~C_PacketGeneral() {};
	//-------------------------------------
	/**
	 * @brief ����ʥ]�B�z
	 * @param Socket SocketID
	 * @param Packet �ʥ]����
	 * @return true��ܦ��\, false�h�_
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
 * @brief �x�Ϋʥ]�B�z���O
 */
template<typename T, typename O> class C_PacketTemplate : public C_PacketInterface
{
public:
	//-------------------------------------
	typedef void (O::*LPFN_Packet) (IN SOCKET Socket, IN T ^Packet); ///< �x�Ϋʥ]�B�z�禡����
	//-------------------------------------

private:
	//-------------------------------------
	LPFN_Packet m_pfPacket; ///< �B�z�禡����
	O *m_pObject; ///< �B�z�������
	//-------------------------------------

public:
	//-------------------------------------
	C_PacketTemplate(IN LPFN_Packet packet, IN O &object) : m_pfPacket(packet), m_pObject(&object) {};
	virtual ~C_PacketTemplate() {};
	//-------------------------------------
	/**
	 * @brief ����ʥ]�B�z
	 * @param Socket SocketID
	 * @param szJson Json�r��
	 * @return true��ܦ��\, false�h�_
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
 * @brief �ʥ]�B�z���O
 */
class C_Packet
{
private:
	//-------------------------------------
	std::map<C_PacketKey, C_PacketInterface *> m_Data; ///< �ʥ]�B�z�C�� <���ު���, �ʥ]�B�z����>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_Packet();
	virtual ~C_Packet();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W�ʥ]�B�z(�R�A�禡����)
	 * @param ccKey ���ު���
	 * @param pfPacket �B�z�禡����
	 * @return true��ܦ��\, false�h�_
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
	 * @brief �s�W�ʥ]�B�z(�����禡����)
	 * @param ccKey ���ު���
	 * @param pfPacket �B�z�禡����
	 * @param Object �B�z����
	 * @return true��ܦ��\, false�h�_
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
	 * @brief ����ʥ]�B�z
	 * @param szServer ���A���W��
	 * @param szName �ѧO�W��
	 * @param Socket SocketID
	 * @param szJson Json�r��
	 * @param Packet �ʥ]����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Execute(IN const cstring &szServer, IN const cstring &szName, IN SOCKET Socket, IN const cstring &szJson, OUT LibCSNStandard::Packet ^Packet);
	/**
	 * @brief ���o�����C��
	 * @param szServer ���A���W��
	 * @return �����C��
	 */
	std::set<C_PacketKey> Record(IN const cstring &szServer) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------