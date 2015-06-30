/**
 * @file winlist.h
 * @note 視窗資訊列表類別
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _WINLIST
#define _WINLIST
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 視窗資訊結構
 * @ingroup winlist
 */
struct S_Windows
{
	HWND hWnd; ///< 視窗控制代碼
	nstring szName; ///< 視窗名稱

	S_Windows(IN HWND h, IN const nstring &name);
};
//-----------------------------------------------------------------------------
/**
 * @brief 視窗資訊列表類別
 * @ingroup winlist
 */
class C_WinList
{
private:
	//-------------------------------------
	std::vector<S_Windows> m_Windows; ///< 視窗資訊列表
	//-------------------------------------

public:
	//-------------------------------------
	typedef std::vector<S_Windows>::const_iterator const_iterator; ///< 視窗資訊列表迭代器型別
	//-------------------------------------

public:
	//-------------------------------------
	C_WinList();
	virtual ~C_WinList();
	//-------------------------------------
	/**
	 * @brief 初始化
	 * @return true表示執行成功, false則否
	 */
	bool Initialize();
	/**
	 * @brief 取得列表開頭迭代器
	 * @return 迭代器
	 */
	C_WinList::const_iterator Begin() const;
	/**
	 * @brief 取得列表結尾迭代器
	 * @return 迭代器
	 */
	C_WinList::const_iterator End() const;
	/**
	 * @brief 取得數量
	 * @return 數量
	 */
	unsigned long Size() const;
	/**
	 * @brief 檢查是否為空
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