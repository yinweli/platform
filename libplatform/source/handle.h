/**
 * @file handle.h
 * @note �w�ɳB�z�ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _HANDLE
#define _HANDLE
//-----------------------------------------------------------------------------
/**
 * @brief �w�ɳB�z�������O
 */
class C_HandleKey
{
private:
	//-------------------------------------
	cstring m_szServer; ///< ���A���W��
	cstring m_szName; ///< �ѧO�W��
	//-------------------------------------

public:
	//-------------------------------------
	C_HandleKey() {};
	C_HandleKey(IN const cstring &server, IN const cstring &name) : m_szServer(server), m_szName(name) {};
	//-------------------------------------
	bool operator < (IN const C_HandleKey &rhs) const
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
 * @brief �w�ɳB�z�������O
 */
class C_HandleInterface
{
protected:
	//-------------------------------------
	unsigned long m_ulInterval; ///< ���j�ɶ�
	unsigned long m_ulTimeLast; ///< �W���ɶ�
	//-------------------------------------

public:
	//-------------------------------------
	C_HandleInterface(IN unsigned long interval) : m_ulInterval(interval), m_ulTimeLast(0) {};
	virtual ~C_HandleInterface() {};
	//-------------------------------------
	/**
	 * @brief �ˬd�O�_����
	 * @return true��ܰ���, false�h�_
	 */
	bool Check()
	{
		_G_();

		unsigned long ulTimeNow = timeGetTime();

		if(m_ulTimeLast + m_ulInterval > ulTimeNow)
			return false;

		m_ulTimeLast = ulTimeNow;

		return true;
	};
	/**
	 * @brief �]�w���j�ɶ�
	 * @param ulInterval ���j�ɶ�
	 */
	void Set(IN unsigned long ulInterval)
	{
		_G_();

		m_ulInterval = ulInterval;
	};
	/**
	 * @brief ���o���j�ɶ�
	 * @return ���j�ɶ�
	 */
	unsigned long Get() const
	{
		_G_();

		return m_ulInterval;
	};
	//-------------------------------------
	/**
	 * @brief ����w�ɳB�z
	 * @return true��ܦ��\, false�h�_
	 */
	virtual bool Execute() = 0;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �@��w�ɳB�z���O
 */
class C_HandleGeneral : public C_HandleInterface
{
public:
	//-------------------------------------
	typedef void (*LPFN_Handle) (); ///< �B�z�禡����
	//-------------------------------------

private:
	//-------------------------------------
	LPFN_Handle m_pfHandle; ///< �B�z�禡����
	//-------------------------------------

public:
	//-------------------------------------
	C_HandleGeneral(IN unsigned long interval, IN LPFN_Handle handle) : C_HandleInterface(interval), m_pfHandle(handle) {};
	virtual ~C_HandleGeneral() {};
	//-------------------------------------
	/**
	 * @brief ����w�ɳB�z
	 * @return true��ܦ��\, false�h�_
	 */
	bool Execute()
	{
		_G_();

		if(m_pfHandle == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("handle null"));

		m_pfHandle();

		return true;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �x�Ωw�ɳB�z���O
 */
template<typename O> class C_HandleTemplate : public C_HandleInterface
{
public:
	//-------------------------------------
	typedef void (O::*LPFN_Handle) (); ///< �B�z�禡����
	//-------------------------------------

private:
	//-------------------------------------
	LPFN_Handle m_pfHandle; ///< �B�z�禡����
	O *m_pObject; ///< �B�z�������
	//-------------------------------------

public:
	//-------------------------------------
	C_HandleTemplate(IN unsigned long interval, IN LPFN_Handle handle, IN O &object) : C_HandleInterface(interval), m_pfHandle(handle), m_pObject(&object) {};
	virtual ~C_HandleTemplate() {};
	//-------------------------------------
	/**
	 * @brief ����w�ɳB�z
	 * @return true��ܦ��\, false�h�_
	 */
	bool Execute()
	{
		_G_();

		if(m_pfHandle == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("handle null"));

		if(m_pObject == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("object null"));

		(m_pObject->*m_pfHandle)();

		return true;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �w�ɳB�z���O
 */
class C_Handle
{
private:
	//-------------------------------------
	std::map<C_HandleKey, C_HandleInterface *> m_Data; ///< �w�ɳB�z�C�� <���ު���, �w�ɳB�z����>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_Handle();
	virtual ~C_Handle();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W�w�ɳB�z(�R�A�禡����)
	 * @param ccKey ���ު���
	 * @param ulInterval �B�z���j�ɶ�
	 * @param pfHandle �B�z�禡����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Add(IN const C_HandleKey &ccKey, IN unsigned long ulInterval, IN C_HandleGeneral::LPFN_Handle pfHandle)
	{
		_G_();

		if(ccKey == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

		if(pfHandle == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("handle null(") + ccKey.Key() + __T(")"));

		C_ThreadLock ccLock(&m_csCommon);

		if(m_Data.find(ccKey) != m_Data.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + ccKey.Key() + __T(")"));

		C_HandleInterface *pHandle = nstdnew C_HandleGeneral(ulInterval, pfHandle);

		if(pHandle == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create handle failed(") + ccKey.Key() + __T(")"));

		m_Data[ccKey] = pHandle;

		return true;
	};
	/**
	 * @brief �s�W�w�ɳB�z(�����禡����)
	 * @param ccKey ���ު���
	 * @param ulInterval �B�z���j�ɶ�
	 * @param pfHandle �B�z�禡����
	 * @param Object �B�z����
	 * @return true��ܦ��\, false�h�_
	 */
	template<typename O> bool Add(IN const C_HandleKey &ccKey, IN unsigned long ulInterval, IN typename C_HandleTemplate<O>::LPFN_Handle pfHandle, IN O &Object)
	{
		_G_();

		if(ccKey == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

		if(pfHandle == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("handle null(") + ccKey.Key() + __T(")"));

		C_ThreadLock ccLock(&m_csCommon);

		if(m_Data.find(ccKey) != m_Data.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + ccKey.Key() + __T(")"));

		C_HandleInterface *pHandle = nstdnew C_HandleTemplate<O>(ulInterval, pfHandle, Object);

		if(pHandle == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create handle failed(") + ccKey.Key() + __T(")"));

		m_Data[ccKey] = pHandle;

		return true;
	};
	/**
	 * @brief ����w�ɳB�z
	 * @param szServer ���A���W��
	 */
	void Execute(IN const cstring &szServer);
	/**
	 * @brief ���o�����C��
	 * @param szServer ���A���W��
	 * @return �����C��
	 */
	std::map<cstring, unsigned long> Record(IN const cstring &szServer) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------