/**
 * @file objcommand.h
 * @note �R�O�ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJCOMMAND
#define _OBJCOMMAND
//-----------------------------------------------------------------------------
/**
 * @brief �R�O���O
 */
class C_ObjCommand : public C_Object
{
public:
	//-------------------------------------
	C_ObjCommand(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief �s�W�R�O(�R�A�禡����)
	 * @param szName �R�O�W��
	 * @param szHelp �����r��
	 * @param pfCommand �R�O�禡����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Add(IN const cstring &szName, IN const cstring &szHelp, IN C_CommandGeneral::LPFN_Command pfCommand)
	{
		_G_();

		return C_Platform::Instance().GetCommand().Add(C_CommandKey(m_szServer, szName), szHelp, pfCommand);
	};
	/**
	 * @brief �s�W�R�O(�����禡����)
	 * @param szName �R�O�W��
	 * @param szHelp �����r��
	 * @param pfCommand �R�O�禡����
	 * @param Object �B�z����
	 * @return true��ܦ��\, false�h�_
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