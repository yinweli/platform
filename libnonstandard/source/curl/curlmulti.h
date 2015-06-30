/**
 * @file curlmulti.h
 * @note curl多元類別
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CURLMULTI
#define _CURLMULTI
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief curl多元類別
 * @ingroup curl
 */
class C_CURLMulti
{
private:
	//-------------------------------------
	CURLM *m_pCURLM; ///< multi-curl handle
	std::map<CURL *, bool> m_Status; ///< 處理狀態列表 <curl指標, 處理狀態>
	//-------------------------------------

public:
	//-------------------------------------
	C_CURLMulti();
	virtual ~C_CURLMulti();
	//-------------------------------------
	/**
	 * @brief 定時處理
	 */
	void Process();
	/**
	 * @brief 執行curl
	 * @param ccCURLMeta curl單元物件
	 * @return true表示成功, false則否
	 */
	bool Perform(IN const C_CURLMeta &ccCURLMeta);
	/**
	 * @brief 取得curl是否存在
	 * @param ccCURLMeta curl單元物件
	 * @return true表示存在, false則否
	 */
	bool IsExist(IN const C_CURLMeta &ccCURLMeta) const;
	/**
	 * @brief 取得curl是否完成
	 * @param ccCURLMeta curl單元物件
	 * @return true表示完成, false則否(或是不存在)
	 */
	bool IsComplete(IN const C_CURLMeta &ccCURLMeta) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------