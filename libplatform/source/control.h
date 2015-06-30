/**
 * @file control.h
 * @note 控制組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef __CONTROL
#define __CONTROL
//-----------------------------------------------------------------------------
/**
 * @brief 控制類別
 */
class C_Control
{
private:
	//-------------------------------------
	C_Console m_ccData; ///< 控制台物件
	std::set<cstring> m_Target; ///< 目標列表
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_Control();
	virtual ~C_Control();
	//-------------------------------------
	/**
	 * @brief 定時處理
	 */
	void Process();
	/**
	 * @brief 設定標題字串
	 * @param szTitle 資料字串
	 */
	void Set(IN const cstring &szTitle);
	/**
	 * @brief 取得指令字串
	 * @return 指令字串
	 */
	cstring Get();
	/**
	 * @brief 檢查是否為目前標題字串
	 * @param szTitle 資料字串
	 * @return true表示是, false則否
	 */
	bool Chk(IN const cstring &szTitle) const;
	/**
	 * @brief 取得目標列表
	 * @return 目標列表
	 */
	std::set<cstring> Target() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------