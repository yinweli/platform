/**
 * @file console.h
 * @note 控制台類別
 * @author yinweli
 */
/**
 * @page 如何使用console
 * console用於處理控制台模式下的命令式鍵盤輸入與顯示\n\n
 * 使用時只要宣告 C_Console 的物件, 視情況重載 C_Console.Show() 函式, 然後定時呼叫 C_Console.Process() 函式即可\n
 * 如果想要取得使用者輸入的指令與參數, 呼叫 C_Console.GetCommand() 函式會取得一個字串, 這個字串是使用者按下enter後紀錄的字串, 分析這個字串就可以了\n\n
 * --------------------------------------------------\n
 * Header           : console.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref console
 */
/** @defgroup console */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef __CONSOLE
#define __CONSOLE
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\actualkeycodes\actualkeycodes.h"
#include "..\algorithm\algorithm.h"
#include "..\consoletool\consoletool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 指令儲存列表類別
 * @ingroup console
 */
class C_ConsoleQueue
{
private:
	//-------------------------------------
	std::queue<nstring> m_Data; ///< 指令儲存列表
	//-------------------------------------

public:
	//-------------------------------------
	C_ConsoleQueue();
	virtual ~C_ConsoleQueue();
	//-------------------------------------
	/**
	 * @brief 新增資料
	 * @param szData 資料字串
	 */
	void Add(IN const nstring &szData);
	/**
	 * @brief 取得資料
	 * @return 資料字串
	 */
	nstring Data();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 指令歷史列表類別
 * @ingroup console
 */
class C_ConsoleHistory
{
private:
	//-------------------------------------
	std::vector<nstring> m_Data; ///< 指令歷史列表
	unsigned long m_ulPos; ///< 游標位置
	//-------------------------------------

public:
	//-------------------------------------
	C_ConsoleHistory();
	virtual ~C_ConsoleHistory();
	//-------------------------------------
	/**
	 * @brief 新增資料
	 * @param szData 資料字串
	 */
	void Add(IN const nstring &szData);
	/**
	 * @brief 游標向前一步
	 */
	void Prev();
	/**
	 * @brief 游標向後一步
	 */
	void Next();
	/**
	 * @brief 取得游標所指資料字串
	 * @return 資料字串
	 */
	nstring Data() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 指令字串管理類別
 * @ingroup console
 */
class C_ConsoleKBStr
{
private:
	//-------------------------------------
	nstring m_szTitle; ///< 標題字串
	nstring m_szToken; ///< 分隔字串
	nstring m_szData; ///< 資料字串
	short m_wPos; ///< 游標位置
	bool m_bInsert; ///< 替代旗標
	//-------------------------------------

public:
	//-------------------------------------
	C_ConsoleKBStr();
	virtual ~C_ConsoleKBStr();
	//-------------------------------------
	/**
	 * @brief 設定標題字串
	 * @param szTitle 資料字串
	 */
	void SetTitle(IN const nstring &szTitle);
	/**
	 * @brief 設定分隔字串
	 * @param szToken 分隔字串
	 */
	void SetToken(IN const nstring &szToken);
	/**
	 * @brief 清除資料字串
	 */
	void ClrData();
	/**
	 * @brief 設定資料字串
	 * @param szData 資料字串
	 */
	void SetData(IN const nstring &szData);
	/**
	 * @brief 插入資料字元
	 * @param emKey 字元列舉
	 * @param ulMaxChar 最大字元數量
	 */
	void InsData(IN ENUM_AKCodes emKey, IN unsigned long ulMaxChar);
	/**
	 * @brief 向前刪除字元
	 */
	void DelPrev();
	/**
	 * @brief 向後刪除字元
	 */
	void DelNext();
	/**
	 * @brief 游標移動到最前
	 */
	void MoveFront();
	/**
	 * @brief 游標移動到最尾
	 */
	void MoveBack();
	/**
	 * @brief 游標向前一步
	 */
	void MovePrev();
	/**
	 * @brief 游標向後一步
	 */
	void MoveNext();
	/**
	 * @brief 開關替代旗標
	 */
	void Insert();
	/**
	 * @brief 檢查是否為空
	 * @return true表示為空, false則否
	 */
	bool Empty() const;
	/**
	 * @brief 取得標題字串
	 * @return 標題字串
	 */
	nstring Title() const;
	/**
	 * @brief 取得分隔字串
	 * @return 分隔字串
	 */
	nstring Token() const;
	/**
	 * @brief 取得資料字串
	 * @return 資料字串
	 */
	nstring Data() const;
	/**
	 * @brief 取得組合字串
	 * @return 組合字串
	 */
	nstring Combination() const;
	/**
	 * @brief 取得資料字串長度
	 * @return 資料字串長度
	 */
	unsigned long Size() const;
	/**
	 * @brief 取得游標位置
	 */
	short GetPos() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 控制台類別
 * @ingroup console
 */
class C_Console
{
private:
	//-------------------------------------
	C_ConsoleQueue m_Command; ///< 指令列表
	C_ConsoleHistory m_ccHistory; ///< 指令歷史列表
	C_ConsoleKBStr m_ccKBStr; ///< 指令字串管理
	//-------------------------------------

public:
	//-------------------------------------
	C_Console();
	virtual ~C_Console();
	//-------------------------------------
	/**
	 * @brief 定時處理
	 */
	void Process();
	/**
	 * @brief 設定標題字串
	 * @param szTitle 資料字串
	 */
	void SetTitle(IN const nstring &szTitle);
	/**
	 * @brief 設定分隔字串
	 * @param szToken 分隔字串
	 */
	void SetToken(IN const nstring &szToken);
	/**
	 * @brief 取得標題字串
	 * @return 標題字串
	 */
	nstring GetTitle() const;
	/**
	 * @brief 取得分隔字串
	 * @return 分隔字串
	 */
	nstring GetToken() const;
	/**
	 * @brief 取得指令字串
	 * @return 指令字串
	 */
	nstring GetCommand();
	//-------------------------------------
	/**
	 * @brief 顯示指令
	 * @param szString 顯示字串
	 * @param ulCursor 游標位置
	 * @param bReplace 取代旗標
	 */
	virtual void Show(IN const nstring &szString, IN unsigned long ulCursor, IN bool bReplace);
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------