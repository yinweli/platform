/**
 * @file objhandle.h
 * @note 定時處理組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJHANDLE
#define _OBJHANDLE
//-----------------------------------------------------------------------------
#define HANDLE_NAME(type, func) (cstring(type_name(type)) + __T(":") + _var(func)) ///< 取得定時處理名稱
//-----------------------------------------------------------------------------
/**
 * @brief 定時處理類別
 */
class C_ObjHandle : public C_Object
{
public:
	//-------------------------------------
	C_ObjHandle(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief 新增定時處理(靜態函式版本)
	 * @param szName 定時處理名稱
	 * @param ulInterval 處理間隔時間
	 * @param pfHandle 處理函式指標
	 * @return true表示成功, false則否
	 */
	bool Add(IN const cstring &szName, IN unsigned long ulInterval, IN C_HandleGeneral::LPFN_Handle pfHandle)
	{
		_G_();

		return C_Platform::Instance().GetHandle().Add(C_HandleKey(m_szServer, szName), ulInterval, pfHandle);
	};
	/**
	 * @brief 新增定時處理(成員函式版本)
	 * @param szName 定時處理名稱
	 * @param ulInterval 處理間隔時間
	 * @param pfHandle 處理函式指標
	 * @param Object 處理物件
	 * @return true表示成功, false則否
	 */
	template<typename O> bool Add(IN const cstring &szName, IN unsigned long ulInterval, IN typename C_HandleTemplate<O>::LPFN_Handle pfHandle, IN O &Object)
	{
		_G_();

		return C_Platform::Instance().GetHandle().Add(C_HandleKey(m_szServer, szName), ulInterval, pfHandle, Object);
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------