/**
 * @file objhandle.h
 * @note �w�ɳB�z�ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJHANDLE
#define _OBJHANDLE
//-----------------------------------------------------------------------------
#define HANDLE_NAME(type, func) (cstring(type_name(type)) + __T(":") + _var(func)) ///< ���o�w�ɳB�z�W��
//-----------------------------------------------------------------------------
/**
 * @brief �w�ɳB�z���O
 */
class C_ObjHandle : public C_Object
{
public:
	//-------------------------------------
	C_ObjHandle(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief �s�W�w�ɳB�z(�R�A�禡����)
	 * @param szName �w�ɳB�z�W��
	 * @param ulInterval �B�z���j�ɶ�
	 * @param pfHandle �B�z�禡����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Add(IN const cstring &szName, IN unsigned long ulInterval, IN C_HandleGeneral::LPFN_Handle pfHandle)
	{
		_G_();

		return C_Platform::Instance().GetHandle().Add(C_HandleKey(m_szServer, szName), ulInterval, pfHandle);
	};
	/**
	 * @brief �s�W�w�ɳB�z(�����禡����)
	 * @param szName �w�ɳB�z�W��
	 * @param ulInterval �B�z���j�ɶ�
	 * @param pfHandle �B�z�禡����
	 * @param Object �B�z����
	 * @return true��ܦ��\, false�h�_
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