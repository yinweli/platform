/**
 * @file objcomponent.h
 * @note 元件組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJCOMPONENT
#define _OBJCOMPONENT
//-----------------------------------------------------------------------------
/**
 * @brief 元件類別
 */
class C_ObjComponent : public C_Object
{
public:
	//-------------------------------------
	C_ObjComponent(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief 新增元件
	 * @return true表示成功, false則否
	 */
	template<typename T> bool Add()
	{
		_G_();

		return C_Platform::Instance().GetComponent().Add<T>();
	};
	/**
	 * @brief 取得元件
	 * @return 物件指標
	 */
	template<typename T> T *Get()
	{
		_G_();

		return reinterpret_cast<T *>(C_Platform::Instance().GetComponent().Get(C_ComponentKey(m_szServer, type_name(T))));
	};
	/**
	 * @brief 取得元件
	 * @param szType 型態名稱
	 * @return 物件指標
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