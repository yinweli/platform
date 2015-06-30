/**
 * @file comtool.h
 * @note COM介面類別
 * @author yinweli
 */
/**
 * @page 如何使用comtool
 * comtool使用在對COM介面的操作上\n\n
 * 首先建立一個實體使用 C_ICom 宣告如下\n\n
 * C_ICom<IDataInitialize> ccInterFace;\n\n
 * 然後在使用COM方法取得介面時, 用 C_ICom.PPointer() 去接系統給予的介面\n
 * 這裡要注意, 在取得介面的時候, 必須要把指標轉換成 void ** 型態\n\n
 * CoCreateInstance(CLSID_MSDAINITIALIZE, nullptr, CLSCTX_INPROC_SERVER, IID_IDataInitialize, (void **)ccInterFace.PPointer());\n\n
 * 之後如果要使用介面的方法, 需要透過 C_ICom.Pointer() 來使用\n\n
 * ccInterFace.Pointer()->GetDataSource(...);\n\n
 * 介面的釋放則會在此實體被刪除時自動被釋放\n
 * 如果想要自己提前釋放的話, 可以呼叫 C_ICom.DelData() 來釋放\n\n
 * --------------------------------------------------\n
 * Header           : comtool.h\n
 * Library(debug)   : \n
 * Library(release) : \n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref comtool
 */
/** @defgroup comtool */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _COMTOOL
#define _COMTOOL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief COM介面類別, 解構時會自動釋放介面
 * @ingroup comtool
 */
template<class T> class C_ICom
{
protected:
	//-------------------------------------
	T *m_pData; ///< COM介面指標
	//-------------------------------------

public:
	//-------------------------------------
	C_ICom() : m_pData(nullptr) {};
	virtual ~C_ICom() { DelData(); };
	//-------------------------------------
	// == 運算子
	bool operator == (IN T *p) { return m_pData == p; };
	// != 運算子
	bool operator != (IN T *p) { return m_pData != p; };
	//-------------------------------------
	/**
	 * @brief 設定介面
	 * @param p 介面
	 */
	inline void SetData(IN T *p) { m_pData = p; };
	/**
	 * @brief 釋放介面
	 * @note 釋放介面之後, 不可以呼叫 Pointer() 或是 PPointer(),  否則會出現不可預期的錯誤
	 */
	inline void DelData() { if(m_pData){ m_pData->Release(); m_pData = nullptr; } };
	/**
	 * @brief 取得介面
	 * @note 取得介面之後, 使用者必須去檢查介面是否有效(不可為 nullptr)
	 * @return 介面
	 */
	inline T *Pointer() { return m_pData; };
	/**
	 * @brief 取得介面的指標
	 * @return 介面的指標
	 */
	inline T **PPointer() { return &m_pData; };
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------