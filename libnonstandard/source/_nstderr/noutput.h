/**
 * @file noutput.h
 * @note 錯誤輸出類別
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _NOUTPUT
#define _NOUTPUT
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#define NOUTPUT_MAX 4096 ///< 錯誤訊息最大數量 @ingroup nstderror
//-----------------------------------------------------------------------------
/**
 * @brief 錯誤輸出類別
 * @ingroup nstderror
 */
class C_NOutput
{
private:
	//-------------------------------------
	std::deque<estring> m_Data; ///< 錯誤訊息列表
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_NOutput();
	virtual ~C_NOutput();
	//-------------------------------------
	/**
	 * @brief 取得錯誤輸出物件
	 * @return 錯誤輸出物件
	 */
	static C_NOutput &Instance();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 錯誤輸出
	 * @param szError 錯誤字串
	 * @return 只會傳回false
	 */
	bool Error(IN const estring &szError);
	/**
	 * @brief 錯誤輸出
	 * @param ccError 錯誤訊息物件
	 * @param szError 錯誤字串
	 * @return 只會傳回false
	 */
	bool Error(IN const C_ErrorNSTD &ccError, IN const estring &szError);
	/**
	 * @brief 錯誤輸出
	 * @param ccError 錯誤訊息物件
	 * @param ccErrorExt 額外錯誤物件
	 * @return 只會傳回false
	 */
	bool Error(IN const C_ErrorNSTD &ccError, IN const C_ErrorBase &ccErrorExt);
	/**
	 * @brief 錯誤輸出
	 * @param ccError 錯誤訊息物件
	 * @param ccErrorExt 額外錯誤物件
	 * @param szError 錯誤字串
	 * @return 只會傳回false
	 */
	bool Error(IN const C_ErrorNSTD &ccError, IN const C_ErrorBase &ccErrorExt, IN const estring &szError);
	/**
	 * @brief 取得錯誤訊息
	 * @return 錯誤訊息
	 */
	estring Get();
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