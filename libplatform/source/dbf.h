/**
 * @file dbf.h
 * @note dbf組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _DBF
#define _DBF
//-----------------------------------------------------------------------------
/**
 * @brief dbf紀錄結構
 */
struct S_RecordDBF
{
	cstring szFilePath; ///< dbf檔名路徑
	int iSize; ///< dbf資料數量

	S_RecordDBF();
	S_RecordDBF(IN const cstring &filepath, IN int size);
};
//-----------------------------------------------------------------------------
/**
 * @brief dbf類別
 */
class C_DBF
{
private:
	//-------------------------------------
	gcroot<LibCSNStandard::DBFData ^> m_Data; ///< dbf資料
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_DBF();
	virtual ~C_DBF();
	//-------------------------------------
	/**
	 * @brief 新增dbf
	 * @param szName dbf名稱
	 * @param szClass 類別名稱(包括命名空間與類別名稱, 用 . 分隔)
	 * @param szComponent 組件名稱
	 * @param szFilePath 檔名路徑
	 * @return true表示成功, false則否
	 */
	bool Add(IN const cstring &szName, IN const cstring &szClass, IN const cstring &szComponent, IN const cstring &szFilePath);
	/**
	 * @brief 重新讀取dbf
	 * @return true表示成功, false則否
	 */
	bool Reload();
	/**
	 * @brief 重新讀取dbf
	 * @param szName dbf名稱
	 * @return true表示成功, false則否
	 */
	bool Reload(IN const cstring &szName);
	/**
	 * @brief 取得dbf
	 * @param szName dbf名稱
	 * @param ccGUID 索引物件
	 * @return dbf物件
	 */
	LibCSNStandard::DBF ^Get(IN const cstring &szName, IN const C_Argu &ccGUID);
	/**
	 * @brief 取得dbf迭代器
	 * @param szName dbf名稱
	 * @return dbf迭代器
	 */
	LibCSNStandard::DBFItor ^Get(IN const cstring &szName);
	/**
	 * @brief 取得紀錄列表
	 * @return 紀錄列表
	 */
	std::map<cstring, S_RecordDBF> Record() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------