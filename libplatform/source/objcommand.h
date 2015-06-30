/**
 * @file objcommand.h
 * @note 命令組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJCOMMAND
#define _OBJCOMMAND
//-----------------------------------------------------------------------------
/**
 * @brief 命令類別
 */
class C_ObjCommand : public C_Object
{
public:
	//-------------------------------------
	C_ObjCommand(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief 新增命令(靜態函式版本)
	 * @param szName 命令名稱
	 * @param szHelp 說明字串
	 * @param pfCommand 命令函式指標
	 * @return true表示成功, false則否
	 */
	bool Add(IN const cstring &szName, IN const cstring &szHelp, IN C_CommandGeneral::LPFN_Command pfCommand)
	{
		_G_();

		return C_Platform::Instance().GetCommand().Add(C_CommandKey(m_szServer, szName), szHelp, pfCommand);
	};
	/**
	 * @brief 新增命令(成員函式版本)
	 * @param szName 命令名稱
	 * @param szHelp 說明字串
	 * @param pfCommand 命令函式指標
	 * @param Object 處理物件
	 * @return true表示成功, false則否
	 */
	template<typename O> bool Add(IN const cstring &szName, IN const cstring &szHelp, IN typename C_CommandTemplate<O>::LPFN_Command pfCommand, IN O &Object)
	{
		_G_();

		return C_Platform::Instance().GetCommand().Add(C_CommandKey(m_szServer, szName), szHelp, pfCommand, Object);
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------