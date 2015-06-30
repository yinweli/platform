/**
 * @file objdbf.h
 * @note dbf組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJDBF
#define _OBJDBF
//-----------------------------------------------------------------------------
/**
 * @brief dbf類別
 */
class C_ObjDBF : public C_Object
{
public:
	//-------------------------------------
	C_ObjDBF(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief 新增dbf
	 * @param szName dbf名稱
	 * @param szClass 類別名稱(包括命名空間與類別名稱, 用 . 分隔)
	 * @param szComponent 組件名稱
	 * @param szFilePath 檔名路徑
	 * @return true表示成功, false則否
	 */
	bool Add(IN const cstring &szName, IN const cstring &szClass, IN const cstring &szComponent, IN const cstring &szFilePath)
	{
		_G_();

		return C_Platform::Instance().GetDBF().Add(szName, szClass, szComponent, szFilePath);
	};
	/**
	 * @brief 重新讀取dbf
	 * @return true表示成功, false則否
	 */
	bool Reload()
	{
		_G_();

		return C_Platform::Instance().GetDBF().Reload();
	};
	/**
	 * @brief 重新讀取dbf
	 * @param szName dbf名稱
	 * @return true表示成功, false則否
	 */
	bool Reload(IN const cstring &szName)
	{
		_G_();

		return C_Platform::Instance().GetDBF().Reload(szName);
	};
	/**
	 * @brief 取得dbf
	 * @param szName dbf名稱
	 * @param ccGUID 索引物件
	 * @return dbf物件
	 */
	LibCSNStandard::DBF ^Get(IN const cstring &szName, IN const C_Argu &ccGUID)
	{
		_G_();

		return C_Platform::Instance().GetDBF().Get(szName, ccGUID);
	};
	/**
	 * @brief 取得dbf迭代器
	 * @param szName dbf名稱
	 * @return dbf迭代器
	 */
	LibCSNStandard::DBFItor ^Get(IN const cstring &szName)
	{
		_G_();

		return C_Platform::Instance().GetDBF().Get(szName);
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------