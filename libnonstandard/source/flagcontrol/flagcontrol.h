/**
 * @file flagcontrol.h
 * @note 旗標控制類別
 * @author yinweli
 */
/**
 * @page 如何使用flagcontrol
 * flagcontrol用於以位元為單位操作記憶體\n\n
 * 首先建立一個實體使用 C_FlagCtrl 宣告如下\n\n
 * C_FlagCtrl ccFlag;\n\n
 * 然後準備一塊記憶體來給旗標控制使用\n\n
 * char cFlag[1024]; // 在此使用了char陣列, 但實際上只要能取到指標, 什麼型態都可以\n\n
 * 接著呼叫 C_FlagCtrl.Initialize() 函式初始化旗標控制類別\n\n
 * ccFlag.Initialize((void *)cFlag, 1024 * 8); // 因為1byte = 8bit, 所以可控制的旗標總數為 1024 * 8\n\n
 * 完成後就可以呼叫旗標操作函式來對此記憶體做旗標控制了\n\n
 * --------------------------------------------------\n
 * Header           : flagcontrol.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref flagcontrol
 */
/** @defgroup flagcontrol */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _FLAGCONTROL
#define _FLAGCONTROL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\bittool\bittool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
class C_FlagCtrlRef;
//-----------------------------------------------------------------------------
/**
 * @brief 旗標控制類別
 * @note 這個類別本身並不含儲存旗標的記憶體, 它只是把使用者想要拿來做旗標的記憶體指標跟旗標數量記錄下來, 然後提供一系列函式來對此指標指向的記憶體做旗標操作\n
 *       類別中的操作函式用到的旗標數量/旗標位置, 單位都是bit\n
 *       例如 旗標數量 = 8, 就是8bit, 也就是1Byte\n\n
 * @ingroup flagcontrol
 */
class C_FlagCtrl
{
private:
	//-------------------------------------
	void *m_pData; ///< 旗標陣列指標
	unsigned long m_ulSize; ///< 旗標數量
	//-------------------------------------

public:
	//-------------------------------------
	C_FlagCtrl(IN void *pData = nullptr, IN unsigned long ulSize = 0);
	virtual ~C_FlagCtrl();
	//-------------------------------------
	/**
	 * @brief 初始化
	 * @param pData 用於旗標控制的記憶體指標, 如果為nullptr, 就會使此類別的操作函式沒有效果(但是不會造成程式錯誤)
	 * @param ulSize 旗標數量, 如果超過了記憶體本身的實際大小, 可能會造成誤寫, 單位是bit
	 */
	void Initialize(IN void *pData, IN unsigned long ulSize);
	/**
	 * @brief 設定旗標
	 * @param ulPos 旗標位置, 單位是bit
	 * @param b 值
	 * @return true表示設定成功, false則否
	 */
	bool Flag(IN unsigned long ulPos, IN bool b);
	/**
	 * @brief 將所有旗標反向
	 * @return true表示設定成功, false則否
	 */
	bool Flip();
	/**
	 * @brief 將指定旗標反向
	 * @param ulPos 旗標位置, 單位是bit
	 * @return true表示設定成功, false則否
	 */
	bool Flip(IN unsigned long ulPos);
	/**
	 * @brief 將所有旗標設為true
	 * @return true表示設定成功, false則否
	 */
	bool Set();
	/**
	 * @brief 將指定旗標設為true
	 * @param ulPos 旗標位置, 單位是bit
	 * @return true表示設定成功, false則否
	 */
	bool Set(IN unsigned long ulPos);
	/**
	 * @brief 將所有旗標設為false
	 * @return true表示設定成功, false則否
	 */
	bool Reset();
	/**
	 * @brief 將指定旗標設為false
	 * @param ulPos 旗標位置, 單位是bit
	 * @return true表示設定成功, false則否
	 */
	bool Reset(IN unsigned long ulPos);
	/**
	 * @brief 取得指定旗標值
	 * @param ulPos 旗標位置, 單位是bit
	 * @return 旗標值
	 */
	bool Test(IN unsigned long ulPos) const;
	/**
	 * @brief 檢查所有旗標中是否有設為true的
	 * @return true表示旗標中有true的旗標, false則否
	 */
	bool Any() const;
	/**
	 * @brief 檢查所有旗標中是否有設為false的
	 * @return true表示旗標中有false的旗標, false則否
	 */
	bool Anyf() const;
	/**
	 * @brief 檢查所有旗標中是否全為false
	 * @return true表示旗標全為false, false則否
	 */
	bool None() const;
	/**
	 * @brief 將數值寫入旗標
	 * @param ulPos 旗標位置, 單位是bit
	 * @param ulSize 使用的旗標數量
	 * @param iValue 數值
	 * @return true表示寫入成功, false則否
	 */
	bool SetValue(IN unsigned long ulPos, IN unsigned long ulSize, IN int iValue);
	/**
	 * @brief 從旗標讀取數值
	 * @param ulPos 旗標位置, 單位是bit
	 * @param ulSize 使用的旗標數量
	 * @return 數值
	 */
	int GetValue(IN unsigned long ulPos, IN unsigned long ulSize) const;
	/**
	 * @brief 取得設為true的旗標數量
	 * @return 設為true的旗標數量
	 */
	unsigned long Count() const;
	/**
	 * @brief 取得旗標數量
	 * @return 旗標數量
	 */
	unsigned long Size() const;
	// [] 運算子
	bool operator [] (IN unsigned long ulPos) const;
	// [] 運算子
	C_FlagCtrlRef operator [] (IN unsigned long ulPos);
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 旗標設置類別
 * @note 這是用於 C_FlagCtrl 的 [] 運算子 的傳回值類別, 使用者不會需要宣告此類別
 * @ingroup flagcontrol
 */
class C_FlagCtrlRef
{
private:
	//-------------------------------------
	C_FlagCtrl *pFlag; ///< 旗標控制類別
	unsigned long ulPos; ///< 旗標位置
	//-------------------------------------

public:
	//-------------------------------------
	C_FlagCtrlRef(IN C_FlagCtrl *p = nullptr, IN unsigned long s = 0);
	virtual ~C_FlagCtrlRef();
	//-------------------------------------
	/**
	 * @brief 將旗標反向
	 * @return true表示設定成功, false則否
	 */
	bool Flip();
	/**
	 * @brief 將旗標設為true
	 * @return true表示設定成功, false則否
	 */
	bool Set();
	/**
	 * @brief 將旗標設為false
	 * @return true表示設定成功, false則否
	 */
	bool Reset();
	/**
	 * @brief 取得旗標值
	 * @return 旗標值
	 */
	bool Test() const;
	// =  運算子
	C_FlagCtrlRef &operator = (IN bool b);
	// =  運算子
	C_FlagCtrlRef &operator = (IN const C_FlagCtrlRef &r);
	// bool轉型運算子
	operator bool () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------