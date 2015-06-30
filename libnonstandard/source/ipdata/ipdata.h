/**
 * @file ipdata.h
 * @note 位址類別
 * @author yinweli
 */
/**
 * @page 如何使用ipdata
 * ipdata用於儲存位址與埠號資料\n
 * 使用時建立 C_IPData 物件, 填寫位址字串與埠號就可以了\n
 * C_IPData.Import() 與 C_IPData.Export() 函式可以讓物件內部資料轉換為字串, 或是把字串輸入到物件內\n\n
 * --------------------------------------------------\n
 * Header           : ipdata.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref ipdata
 */
/** @defgroup ipdata */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _IPDATA
#define _IPDATA
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 位址類別
 * @ingroup ipdata
 */
class C_IPData
{
private:
	//-------------------------------------
	nstring m_szIP; ///< 位址字串
	unsigned long m_ulPort; ///< 埠號
	//-------------------------------------

private:
	//-------------------------------------
	/**
	 * @brief 取得校正位址字串
	 * @return 校正位址字串
	 */
	nstring CorrectIP() const;
	//-------------------------------------

public:
	//-------------------------------------
	C_IPData();
	C_IPData(IN const nstring &data);
	C_IPData(IN const nstring &ip, IN unsigned long port);
	virtual ~C_IPData();
	//-------------------------------------
	bool operator < (IN const C_IPData &rhs) const;
	bool operator > (IN const C_IPData &rhs) const;
	bool operator <= (IN const C_IPData &rhs) const;
	bool operator >= (IN const C_IPData &rhs) const;
	bool operator == (IN const C_IPData &rhs) const;
	bool operator != (IN const C_IPData &rhs) const;
	//-------------------------------------
	/**
	 * @brief 匯入字串
	 * @param szData 資料字串
	 * @return true表示成功, false則否
	 */
	bool Import(IN const nstring &szData);
	/**
	 * @brief 匯入資料
	 * @param szIP 位址字串
	 * @param ulPort 埠號
	 * @return true表示成功, false則否
	 */
	bool Import(IN const nstring &szIP, IN unsigned long ulPort);
	/**
	 * @brief 匯出字串
	 * @return 資料字串
	 */
	nstring Export() const;
	/**
	 * @brief 取得位址字串
	 * @return 位址字串
	 */
	nstring IP() const;
	/**
	 * @brief 取得埠號
	 * @return 埠號
	 */
	unsigned long Port() const;
	/**
	 * @brief 取得是否為空
	 * @return true表示為空, false則否
	 */
	bool Empty() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------