/**
 * @file curlmeta.h
 * @note curl單元類別
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CURLMETA
#define _CURLMETA
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief curl碎片類別
 * @ingroup curl
 */
class C_CURLChip
{
private:
	//-------------------------------------
	void *m_pData; ///< 資料指標
	unsigned long m_ulSize; ///< 資料長度
	//-------------------------------------

public:
	//-------------------------------------
	C_CURLChip();
	C_CURLChip(IN void *data, IN unsigned long size);
	virtual ~C_CURLChip();
	//-------------------------------------
	operator bool () const;
	operator void * () const;
	operator unsigned long () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief curl結果類別
 * @ingroup curl
 */
class C_CURLResult
{
private:
	//-------------------------------------
	void *m_pData; ///< 資料指標
	unsigned long m_ulSize; ///< 資料長度
	//-------------------------------------

public:
	//-------------------------------------
	C_CURLResult();
	C_CURLResult(IN const std::vector<C_CURLChip> &chip);
	virtual ~C_CURLResult();
	//-------------------------------------
	operator bool () const;
	operator void * () const;
	operator unsigned long () const;
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief curl單元類別
 * @ingroup curl
 */
class C_CURLMeta : public C_CURLBase
{
	//-------------------------------------
	/**
	 * @brief 寫入結果函式
	 * @param pResult 結果指標
	 * @param count 結果數量
	 * @param size 結果長度
	 * @param pData 自定義指標
	 * @return 獲得的結果長度
	 * @ingroup curl
	 */
	static size_t WriteResult(void *pResult, size_t count, size_t size, void *pData);
	//-------------------------------------

private:
	//-------------------------------------
	std::vector<C_CURLChip> m_Chip; ///< 碎片列表
	//-------------------------------------

public:
	//-------------------------------------
	C_CURLMeta();
	virtual ~C_CURLMeta();
	//-------------------------------------
	/**
	 * @brief 執行curl
	 * @return true表示成功, false則否
	 */
	bool Perform();
	/**
	 * @brief 取得結果物件
	 * @return 結果物件
	 */
	C_CURLResult Result() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------