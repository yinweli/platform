/**
 * @file component.h
 * @note ����ե�
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
 * @brief ���󪫥����O
 */
class C_ComponentObj
{
private:
	//-------------------------------------
	cstring m_szServer; ///< ���A���W��
	cstring m_szType; ///< ���A�W��
	//-------------------------------------

public:
	//-------------------------------------
	C_ComponentObj(IN const cstring &server, IN const cstring &type);
	virtual ~C_ComponentObj();
	//-------------------------------------
	/**
	 * @brief ���o���A���W��
	 * @return ���A���W��
	 */
	cstring Server() const;
	/**
	 * @brief ���o���A�W��
	 * @return ���A�W��
	 */
	cstring Type() const;
	//-------------------------------------
	/**
	 * @brief ���o�į�����ե�
	 * @return �į�����ե�
	 */
	C_ObjBenchmark ObjBenchmark() const;
	/**
	 * @brief ���o�R�O�ե�
	 * @return �R�O�ե�
	 */
	C_ObjCommand ObjCommand() const;
	/**
	 * @brief ���o����ե�
	 * @return ����ե�
	 */
	C_ObjComponent ObjComponent() const;
	/**
	 * @brief ���o��Ʈw�ե�
	 * @return ��Ʈw�ե�
	 */
	C_ObjDatabase ObjDatabase() const;
	/**
	 * @brief ���odbf�ե�
	 * @return dbf�ե�
	 */
	C_ObjDBF ObjDBF() const;
	/**
	 * @brief ���o�ƥ�ե�
	 * @return �ƥ�ե�
	 */
	C_ObjEvent ObjEvent() const;
	/**
	 * @brief ���o�w�ɳB�z�ե�
	 * @return �w�ɳB�z�ե�
	 */
	C_ObjHandle ObjHandle() const;
	/**
	 * @brief ���o�����ե�
	 * @return �����ե�
	 */
	C_ObjNetwork ObjNetwork() const;
	/**
	 * @brief ���o��X�ե�
	 * @return ��X�ե�
	 */
	C_ObjOutput ObjOutput() const;
	/**
	 * @brief ���o�ʥ]�B�z�ե�
	 * @return �ʥ]�B�z�ե�
	 */
	C_ObjPacket ObjPacket() const;
	//-------------------------------------
	/**
	 * @brief ��l��
	 * @return true��ܦ��\, false�h�_
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
 * @brief ����������O
 */
class C_ComponentKey
{
private:
	//-------------------------------------
	cstring m_szServer; ///< ���A���W��
	cstring m_szName; ///< �ѧO�W��
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
 * @brief ���󤶭����O
 */
class C_ComponentInterface
{
public:
	//-------------------------------------
	C_ComponentInterface() {};
	virtual ~C_ComponentInterface() {};
	//-------------------------------------
	/**
	 * @brief �إߪ������
	 * @param ccKey ���ު���
	 * @return �������
	 */
	virtual C_ComponentObj *Create(IN const C_ComponentKey &ccKey) const = 0;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �x���������O
 */
template<typename T> class C_ComponentTemplate : public C_ComponentInterface
{
public:
	//-------------------------------------
	C_ComponentTemplate() {};
	virtual ~C_ComponentTemplate() {};
	//-------------------------------------
	/**
	 * @brief �إߪ������
	 * @param ccKey ���ު���
	 * @return �������
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
 * @brief �������O
 */
class C_Component
{
private:
	//-------------------------------------
	std::map<cstring, C_ComponentInterface *> m_Data; ///< �ո˦C�� <�ո˦W��, �ո˫���>
	std::map<C_ComponentKey, C_ComponentObj *> m_Object; ///< ����C�� <���ު���, �������>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_Component();
	virtual ~C_Component();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W�ո�
	 * @return true��ܦ��\, false�h�_
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
	 * @brief ���o����
	 * @param ccKey ���ު���
	 * @return �������
	 */
	C_ComponentObj *Get(IN const C_ComponentKey &ccKey);
	/**
	 * @brief ���o�����C��
	 * @param szServer ���A���W��
	 * @return �����C��
	 */
	std::set<cstring> Record(IN const cstring &szServer) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------