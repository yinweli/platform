/**
 * @file objpacket.h
 * @note 封包處理組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJPACKET
#define _OBJPACKET
//-----------------------------------------------------------------------------
/**
 * @brief 封包處理類別
 */
class C_ObjPacket : public C_Object
{
public:
	//-------------------------------------
	C_ObjPacket(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief 新增封包處理(靜態函式版本)
	 * @param szName 網路名稱
	 * @param pfPacket 處理函式指標
	 * @param Packet 封包物件
	 * @return true表示成功, false則否
	 */
	template<typename T> bool Add(IN const cstring &szName, IN typename C_PacketGeneral<T>::LPFN_Packet pfPacket, IN T ^Packet)
	{
		_G_();

		return C_Platform::Instance().GetPacket().Add<T>(C_PacketKey(m_szServer, szName, Packet), pfPacket);
	};
	/**
	 * @brief 新增封包處理(成員函式版本)
	 * @param szName 網路名稱
	 * @param pfPacket 處理函式指標
	 * @param Packet 封包物件
	 * @param Object 處理物件
	 * @return true表示成功, false則否
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