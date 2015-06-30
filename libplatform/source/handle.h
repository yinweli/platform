/**
 * @file handle.h
 * @note 定時處理組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _HANDLE
#define _HANDLE
//-----------------------------------------------------------------------------
/**
 * @brief 定時處理索引類別
 */
class C_HandleKey
{
private:
	//-------------------------------------
	cstring m_szServer; ///< 伺服器名稱
	cstring m_szName; ///< 識別名稱
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
 * @brief 定時處理介面類別
 */
class C_HandleInterface
{
protected:
	//-------------------------------------
	unsigned long m_ulInterval; ///< 間隔時間
	unsigned long m_ulTimeLast; ///< 上次時間
	//-------------------------------------

public:
	//-------------------------------------
	C_HandleInterface(IN unsigned long interval) : m_ulInterval(interval), m_ulTimeLast(0) {};
	virtual ~C_HandleInterface() {};
	//-------------------------------------
	/**
	 * @brief 檢查是否執行
	 * @return true表示執行, false則否
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
	 * @brief 設定間隔時間
	 * @param ulInterval 間隔時間
	 */
	void Set(IN unsigned long ulInterval)
	{
		_G_();

		m_ulInterval = ulInterval;
	};
	/**
	 * @brief 取得間隔時間
	 * @return 間隔時間
	 */
	unsigned long Get() const
	{
		_G_();

		return m_ulInterval;
	};
	//-------------------------------------
	/**
	 * @brief 執行定時處理
	 * @return true表示成功, false則否
	 */
	virtual bool Execute() = 0;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 一般定時處理類別
 */
class C_HandleGeneral : public C_HandleInterface
{
public:
	//-------------------------------------
	typedef void (*LPFN_Handle) (); ///< 處理函式指標
	//-------------------------------------

private:
	//-------------------------------------
	LPFN_Handle m_pfHandle; ///< 處理函式指標
	//-------------------------------------

public:
	//-------------------------------------
	C_HandleGeneral(IN unsigned long interval, IN LPFN_Handle handle) : C_HandleInterface(interval), m_pfHandle(handle) {};
	virtual ~C_HandleGeneral() {};
	//-------------------------------------
	/**
	 * @brief 執行定時處理
	 * @return true表示成功, false則否
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
 * @brief 泛形定時處理類別
 */
template<typename O> class C_HandleTemplate : public C_HandleInterface
{
public:
	//-------------------------------------
	typedef void (O::*LPFN_Handle) (); ///< 處理函式指標
	//-------------------------------------

private:
	//-------------------------------------
	LPFN_Handle m_pfHandle; ///< 處理函式指標
	O *m_pObject; ///< 處理物件指標
	//-------------------------------------

public:
	//-------------------------------------
	C_HandleTemplate(IN unsigned long interval, IN LPFN_Handle handle, IN O &object) : C_HandleInterface(interval), m_pfHandle(handle), m_pObject(&object) {};
	virtual ~C_HandleTemplate() {};
	//-------------------------------------
	/**
	 * @brief 執行定時處理
	 * @return true表示成功, false則否
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
 * @brief 定時處理類別
 */
class C_Handle
{
private:
	//-------------------------------------
	std::map<C_HandleKey, C_HandleInterface *> m_Data; ///< 定時處理列表 <索引物件, 定時處理指標>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_Handle();
	virtual ~C_Handle();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 新增定時處理(靜態函式版本)
	 * @param ccKey 索引物件
	 * @param ulInterval 處理間隔時間
	 * @param pfHandle 處理函式指標
	 * @return true表示成功, false則否
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
	 * @brief 新增定時處理(成員函式版本)
	 * @param ccKey 索引物件
	 * @param ulInterval 處理間隔時間
	 * @param pfHandle 處理函式指標
	 * @param Object 處理物件
	 * @return true表示成功, false則否
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
	 * @brief 執行定時處理
	 * @param szServer 伺服器名稱
	 */
	void Execute(IN const cstring &szServer);
	/**
	 * @brief 取得紀錄列表
	 * @param szServer 伺服器名稱
	 * @return 紀錄列表
	 */
	std::map<cstring, unsigned long> Record(IN const cstring &szServer) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------