/**
 * @file objcomponent.h
 * @note ����ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJCOMPONENT
#define _OBJCOMPONENT
//-----------------------------------------------------------------------------
/**
 * @brief �������O
 */
class C_ObjComponent : public C_Object
{
public:
	//-------------------------------------
	C_ObjComponent(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief �s�W����
	 * @return true��ܦ��\, false�h�_
	 */
	template<typename T> bool Add()
	{
		_G_();

		return C_Platform::Instance().GetComponent().Add<T>();
	};
	/**
	 * @brief ���o����
	 * @return �������
	 */
	template<typename T> T *Get()
	{
		_G_();

		return reinterpret_cast<T *>(C_Platform::Instance().GetComponent().Get(C_ComponentKey(m_szServer, type_name(T))));
	};
	/**
	 * @brief ���o����
	 * @param szType ���A�W��
	 * @return �������
	 */
	template<typename T> T *Get(IN const cstring &szType)
	{
		_G_();

		return reinterpret_cast<T *>(C_Platform::Instance().GetComponent().Get(C_ComponentKey(m_szServer, szType)));
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------