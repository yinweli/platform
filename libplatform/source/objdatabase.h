/**
 * @file objdatabase.h
 * @note 資料庫組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJDATABASE
#define _OBJDATABASE
//-----------------------------------------------------------------------------
/**
 * @brief 資料庫類別
 */
class C_ObjDatabase : public C_Object
{
public:
	//-------------------------------------
	C_ObjDatabase(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief 執行命令
	 * @param szName 資料庫名稱
	 * @param szCommand SQL語句
	 * @return true表示執行成功, false則否
	 */
	bool Execute(IN const cstring &szName, IN const cstring &szCommand)
	{
		_G_();

		C_DBase *pDBase = C_Platform::Instance().GetDatabase().Get(szName);

		return pDBase ? pDBase->Execute(szCommand) : false;
	};
	/**
	 * @brief 執行命令
	 * @param szName 資料庫名稱
	 * @param szCommand SQL語句
	 * @param ccStore 執行結果
	 * @return true表示執行成功, false則否
	 */
	bool Execute(IN const cstring &szName, IN const cstring &szCommand, OUT C_DBStore &ccStore)
	{
		_G_();

		C_DBase *pDBase = C_Platform::Instance().GetDatabase().Get(szName);

		return pDBase ? pDBase->Execute(szCommand, ccStore) : false;
	};
	/**
	 * @brief 與資料庫是否連線中
	 * @param szName 資料庫名稱
	 * @return true表示連線中, false則否
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