/**
 * @file objoutput.h
 * @note 輸出組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJOUTPUT
#define _OBJOUTPUT
//-----------------------------------------------------------------------------
/**
 * @brief 輸出類別
 */
class C_ObjOutput : public C_Object
{
public:
	//-------------------------------------
	C_ObjOutput(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief 新增輸出
	 * @param szOutput 輸出字串
	 */
	void Add(IN const cstring &szOutput)
	{
		_G_();

		C_Platform::Instance().GetOutput().Add(szOutput);
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------