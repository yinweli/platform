/**
 * @file objevent.h
 * @note 事件處理組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJEVENT
#define _OBJEVENT
//-----------------------------------------------------------------------------
/**
 * @brief 事件處理類別
 */
class C_ObjEvent : public C_Object
{
public:
	//-------------------------------------
	C_ObjEvent(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief 新增事件處理(靜態函式版本)
	 * @param szName 網路名稱
	 * @param emEvent 事件處理列舉
	 * @param pfEvent 處理函式指標
	 * @return true表示成功, false則否
	 */
	bool Add(IN const cstring &szName, IN ENUM_Event emEvent, IN C_EventGeneral::LPFN_Event pfEvent)
	{
		_G_();

		return C_Platform::Instance().GetEvent().Add(C_EventKey(m_szServer, szName, emEvent), pfEvent);
	};
	/**
	 * @brief 新增事件處理(成員函式版本)
	 * @param szName 網路名稱
	 * @param emEvent 事件處理列舉
	 * @param pfEvent 處理函式指標
	 * @param Object 處理物件
	 * @return true表示成功, false則否
	 */
	template<typename O> bool Add(IN const cstring &szName, IN ENUM_Event emEvent, IN typename C_EventTemplate<O>::LPFN_Event pfEvent, IN O &Object)
	{
		_G_();

		return C_Platform::Instance().GetEvent().Add(C_EventKey(m_szServer, szName, emEvent), pfEvent, Object);
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------