/**
 * @file objpacket.h
 * @note �ʥ]�B�z�ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJPACKET
#define _OBJPACKET
//-----------------------------------------------------------------------------
/**
 * @brief �ʥ]�B�z���O
 */
class C_ObjPacket : public C_Object
{
public:
	//-------------------------------------
	C_ObjPacket(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief �s�W�ʥ]�B�z(�R�A�禡����)
	 * @param szName �����W��
	 * @param pfPacket �B�z�禡����
	 * @param Packet �ʥ]����
	 * @return true��ܦ��\, false�h�_
	 */
	template<typename T> bool Add(IN const cstring &szName, IN typename C_PacketGeneral<T>::LPFN_Packet pfPacket, IN T ^Packet)
	{
		_G_();

		return C_Platform::Instance().GetPacket().Add<T>(C_PacketKey(m_szServer, szName, Packet), pfPacket);
	};
	/**
	 * @brief �s�W�ʥ]�B�z(�����禡����)
	 * @param szName �����W��
	 * @param pfPacket �B�z�禡����
	 * @param Packet �ʥ]����
	 * @param Object �B�z����
	 * @return true��ܦ��\, false�h�_
	 */
	template<typename T, typename O> bool Add(IN const cstring &szName, IN typename C_PacketTemplate<T, O>::LPFN_Packet pfPacket, IN T ^Packet, IN O &Object)
	{
		_G_();

		return C_Platform::Instance().GetPacket().Add<T, O>(C_PacketKey(m_szServer, szName, Packet), pfPacket, Object);
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------