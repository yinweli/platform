/**
 * @file objevent.h
 * @note �ƥ�B�z�ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJEVENT
#define _OBJEVENT
//-----------------------------------------------------------------------------
/**
 * @brief �ƥ�B�z���O
 */
class C_ObjEvent : public C_Object
{
public:
	//-------------------------------------
	C_ObjEvent(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief �s�W�ƥ�B�z(�R�A�禡����)
	 * @param szName �����W��
	 * @param emEvent �ƥ�B�z�C�|
	 * @param pfEvent �B�z�禡����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Add(IN const cstring &szName, IN ENUM_Event emEvent, IN C_EventGeneral::LPFN_Event pfEvent)
	{
		_G_();

		return C_Platform::Instance().GetEvent().Add(C_EventKey(m_szServer, szName, emEvent), pfEvent);
	};
	/**
	 * @brief �s�W�ƥ�B�z(�����禡����)
	 * @param szName �����W��
	 * @param emEvent �ƥ�B�z�C�|
	 * @param pfEvent �B�z�禡����
	 * @param Object �B�z����
	 * @return true��ܦ��\, false�h�_
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