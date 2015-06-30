/**
 * @file component.h
 * @note 元件組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _COMPONENT
#define _COMPONENT
//-----------------------------------------------------------------------------
class C_ObjBenchmark;
class C_ObjCommand;
class C_ObjComponent;
class C_ObjDatabase;
class C_ObjDBF;
class C_ObjEvent;
class C_ObjHandle;
class C_ObjNetwork;
class C_ObjOutput;
class C_ObjPacket;
//-----------------------------------------------------------------------------
/**
 * @brief 元件物件類別
 */
class C_ComponentObj
{
private:
	//-------------------------------------
	cstring m_szServer; ///< 伺服器名稱
	cstring m_szType; ///< 型態名稱
	//-------------------------------------

public:
	//-------------------------------------
	C_ComponentObj(IN const cstring &server, IN const cstring &type);
	virtual ~C_ComponentObj();
	//-------------------------------------
	/**
	 * @brief 取得伺服器名稱
	 * @return 伺服器名稱
	 */
	cstring Server() const;
	/**
	 * @brief 取得型態名稱
	 * @return 型態名稱
	 */
	cstring Type() const;
	//-------------------------------------
	/**
	 * @brief 取得效能紀錄組件
	 * @return 效能紀錄組件
	 */
	C_ObjBenchmark ObjBenchmark() const;
	/**
	 * @brief 取得命令組件
	 * @return 命令組件
	 */
	C_ObjCommand ObjCommand() const;
	/**
	 * @brief 取得元件組件
	 * @return 元件組件
	 */
	C_ObjComponent ObjComponent() const;
	/**
	 * @brief 取得資料庫組件
	 * @return 資料庫組件
	 */
	C_ObjDatabase ObjDatabase() const;
	/**
	 * @brief 取得dbf組件
	 * @return dbf組件
	 */
	C_ObjDBF ObjDBF() const;
	/**
	 * @brief 取得事件組件
	 * @return 事件組件
	 */
	C_ObjEvent ObjEvent() const;
	/**
	 * @brief 取得定時處理組件
	 * @return 定時處理組件
	 */
	C_ObjHandle ObjHandle() const;
	/**
	 * @brief 取得網路組件
	 * @return 網路組件
	 */
	C_ObjNetwork ObjNetwork() const;
	/**
	 * @brief 取得輸出組件
	 * @return 輸出組件
	 */
	C_ObjOutput ObjOutput() const;
	/**
	 * @brief 取得封包處理組件
	 * @return 封包處理組件
	 */
	C_ObjPacket ObjPacket() const;
	//-------------------------------------
	/**
	 * @brief 初始化
	 * @return true表示成功, false則否
	 */
	virtual bool Initialize()
	{
		_G_();

		return true;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 元件索引類別
 */
class C_ComponentKey
{
private:
	//-------------------------------------
	cstring m_szServer; ///< 伺服器名稱
	cstring m_szName; ///< 識別名稱
	//-------------------------------------

public:
	//-------------------------------------
	C_ComponentKey() {};
	C_ComponentKey(IN const cstring &server, IN const cstring &name) : m_szServer(server), m_szName(name) {};
	//-------------------------------------
	bool operator < (IN const C_ComponentKey &rhs) const
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
 * @brief 元件介面類別
 */
class C_ComponentInterface
{
public:
	//-------------------------------------
	C_ComponentInterface() {};
	virtual ~C_ComponentInterface() {};
	//-------------------------------------
	/**
	 * @brief 建立物件指標
	 * @param ccKey 索引物件
	 * @return 物件指標
	 */
	virtual C_ComponentObj *Create(IN const C_ComponentKey &ccKey) const = 0;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 泛型元件類別
 */
template<typename T> class C_ComponentTemplate : public C_ComponentInterface
{
public:
	//-------------------------------------
	C_ComponentTemplate() {};
	virtual ~C_ComponentTemplate() {};
	//-------------------------------------
	/**
	 * @brief 建立物件指標
	 * @param ccKey 索引物件
	 * @return 物件指標
	 */
	C_ComponentObj *Create(IN const C_ComponentKey &ccKey) const
	{
		_G_();

		T *pObject = nstdnew T(ccKey.Server(), ccKey.Name());

		if(pObject == nullptr)
			return nullptr;

		C_ComponentObj *pComponent = reinterpret_cast<C_ComponentObj *>(pObject);

		if(pComponent->Initialize() == false)
		{
			delete pObject;

			return nullptr;
		}//if

		return pComponent;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 元件類別
 */
class C_Component
{
private:
	//-------------------------------------
	std::map<cstring, C_ComponentInterface *> m_Data; ///< 組裝列表 <組裝名稱, 組裝指標>
	std::map<C_ComponentKey, C_ComponentObj *> m_Object; ///< 物件列表 <索引物件, 物件指標>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_Component();
	virtual ~C_Component();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 新增組裝
	 * @return true表示成功, false則否
	 */
	template<typename T> bool Add()
	{
		_G_();

		cstring szType(type_name(T));
		C_ThreadLock ccLock(&m_csCommon);

		if(m_Data.find(szType) != m_Data.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + szType + __T(")"));

		C_ComponentInterface *pComponent = reinterpret_cast<C_ComponentInterface *>(nstdnew C_ComponentTemplate<T>());

		if(pComponent == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create component failed(") + szType + __T(")"));

		m_Data[szType] = pComponent;

		return true;
	};
	/**
	 * @brief 取得元件
	 * @param ccKey 索引物件
	 * @return 元件指標
	 */
	C_ComponentObj *Get(IN const C_ComponentKey &ccKey);
	/**
	 * @brief 取得紀錄列表
	 * @param szServer 伺服器名稱
	 * @return 紀錄列表
	 */
	std::set<cstring> Record(IN const cstring &szServer) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------