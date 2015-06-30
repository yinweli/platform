/**
 * @file objoutput.h
 * @note ��X�ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJOUTPUT
#define _OBJOUTPUT
//-----------------------------------------------------------------------------
/**
 * @brief ��X���O
 */
class C_ObjOutput : public C_Object
{
public:
	//-------------------------------------
	C_ObjOutput(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief �s�W��X
	 * @param szOutput ��X�r��
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