/**
 * @file obj.h
 * @note 物件組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJ
#define _OBJ
//-----------------------------------------------------------------------------
/**
 * @brief 物件類別
 */
class C_Object
{
protected:
	//-------------------------------------
	cstring m_szServer; /// 伺服器名稱
	//-------------------------------------

public:
	//-------------------------------------
	C_Object(IN const cstring &server) : m_szServer(server) {};
	virtual ~C_Object() {};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------