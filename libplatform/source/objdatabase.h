/**
 * @file objdatabase.h
 * @note ��Ʈw�ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJDATABASE
#define _OBJDATABASE
//-----------------------------------------------------------------------------
/**
 * @brief ��Ʈw���O
 */
class C_ObjDatabase : public C_Object
{
public:
	//-------------------------------------
	C_ObjDatabase(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief ����R�O
	 * @param szName ��Ʈw�W��
	 * @param szCommand SQL�y�y
	 * @return true��ܰ��榨�\, false�h�_
	 */
	bool Execute(IN const cstring &szName, IN const cstring &szCommand)
	{
		_G_();

		C_DBase *pDBase = C_Platform::Instance().GetDatabase().Get(szName);

		return pDBase ? pDBase->Execute(szCommand) : false;
	};
	/**
	 * @brief ����R�O
	 * @param szName ��Ʈw�W��
	 * @param szCommand SQL�y�y
	 * @param ccStore ���浲�G
	 * @return true��ܰ��榨�\, false�h�_
	 */
	bool Execute(IN const cstring &szName, IN const cstring &szCommand, OUT C_DBStore &ccStore)
	{
		_G_();

		C_DBase *pDBase = C_Platform::Instance().GetDatabase().Get(szName);

		return pDBase ? pDBase->Execute(szCommand, ccStore) : false;
	};
	/**
	 * @brief �P��Ʈw�O�_�s�u��
	 * @param szName ��Ʈw�W��
	 * @return true��ܳs�u��, false�h�_
	 */
	bool IsConnect(IN const cstring &szName) const
	{
		_G_();

		C_DBase *pDBase = C_Platform::Instance().GetDatabase().Get(szName);

		return pDBase && pDBase->IsConnect();
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------