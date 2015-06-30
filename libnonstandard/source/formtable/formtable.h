/**
 * @file formtable.h
 * @note 格式化表格類別
 * @author yinweli
 */
/**
 * @page 如何使用formtable
 * formtable用於建立表格字串\n\n
 * 首先建立一個實體使用 C_FormTable 宣告如下\n\n
 * C_FormTable ccFormTable;\n\n
 * 然後呼叫 C_FormTable.SetContent() 函式來設定表格內容\n
 * 內容設定完畢後呼叫 C_FormTable.Export() 函式輸出表格到容器中\n\n
 * --------------------------------------------------\n
 * Header           : formtable.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref formtable
 */
/** @defgroup formtable */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _FORMTABLE
#define _FORMTABLE
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\_nstroutf\_nstroutf.h"
#include "..\algorithm\algorithm.h"
#include "..\argument\argument.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 格式化表格類別
 * @ingroup formtable
 */
class C_FormTable
{
private:
	//-------------------------------------
	std::map<nstring, nstring> m_Data; ///< 表格列表 <座標字串, 內容字串>
	int m_iSizeX; ///< x軸長度
	int m_iSizeY; ///< y軸長度
	//-------------------------------------

public:
	//-------------------------------------
	TCHAR Vertical; ///< 直線字元
	TCHAR Horizontal; ///< 橫線字元
	TCHAR Cross; ///< 交錯字元
	//-------------------------------------

private:
	//-------------------------------------
	/**
	 * @brief 取得長度列表
	 * @return 長度列表
	 */
	std::vector<int> Length() const;
	/**
	 * @brief 取得座標字串
	 * @param iX x軸座標
	 * @param iY y軸座標
	 * @return 座標字串
	 */
	nstring StringCoor(IN int iX, IN int iY) const;
	/**
	 * @brief 建立格線字串
	 * @param Len 長度列表
	 * @return 格線字串
	 */
	nstring StringLine(IN const std::vector<int> &Len) const;
	/**
	 * @brief 建立內容字串
	 * @param Len 長度列表
	 * @param Data 資料列表
	 * @param bAlign 對齊旗標
	 * @return 內容字串
	 */
	nstring StringData(IN const std::vector<int> &Len, IN const std::vector<nstring> &Data, IN bool bAlign) const;
	//-------------------------------------

public:
	//-------------------------------------
	C_FormTable();
	virtual ~C_FormTable();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 設定內容
	 * @param iX x軸座標
	 * @param iY y軸座標
	 * @param ccData 資料物件
	 */
	void Set(IN int iX, IN int iY, IN const C_Argu &ccData);
	/**
	 * @brief 新增內容
	 * @param Data 資料列表
	 */
	void Add(IN const std::vector<nstring> &Data);
	/**
	 * @brief 新增內容
	 * @param ccData 資料列表
	 */
	void Add(IN const C_Argv &ccData);
	/**
	 * @brief 輸出表格
	 * @return 結果列表
	 */
	std::vector<nstring> ExportList() const;
	/**
	 * @brief 輸出表格
	 * @return 結果字串
	 */
	nstring ExportString() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------