/**
 * @file bittool.h
 * @note 位元操作系列函式
 * @author yinweli
 */
/**
 * @page 如何使用bittool
 * bittool內的函式用於位元操作\n\n
 * bittool內的函式, 輸入值都是1個byte大小\n
 * 這表示如果想要對超過1個byte大小的資料作位元操作, 就要事先知道想要操作的位元是在哪個位元組中, 然後只輸入那個位元組的資料來操作\n
 * 另外就是只要涉及修改位元組資料的操作, 函式都只提供把改變後的結果作為傳回值, 但是並沒有去修改使用者輸入的資料\n
 * 所以使用上需要像以下顯示\n\n
 * char x = 0;\n\n
 * x = bitval(x, 0, 1); // 把 x 中第一個位元設為true, 然後把結果設回 x\n\n
 * --------------------------------------------------\n
 * Header           : bittool.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref bittool
 */
/** @defgroup bittool */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _BITTOOL
#define _BITTOOL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\mathtool\mathtool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 取得數值需要的旗標數量
 * @param iValue 數值
 * @return 旗標數量
 * @ingroup bittool
 */
unsigned int bitsize(IN int iValue);
/**
 * @brief 取得c內位元位置pos的值
 * @param c 輸入資料
 * @param pos 位置
 * @return 值
 * @ingroup bittool
 */
bool bitget(IN char c, IN unsigned char pos);
/**
 * @brief 取得c內從位元0到位元pos中是否有true
 * @param c 輸入資料
 * @param pos 位置
 * @return true表示輸入資料中有true, false則否
 * @ingroup bittool
 */
bool bitany(IN char c, IN unsigned char pos);
/**
 * @brief 取得c內從位元0到位元pos中是否有false
 * @param c 輸入資料
 * @param pos 位置
 * @return true表示輸入資料中有false, false則否
 * @ingroup bittool
 */
bool bitanf(IN char c, IN unsigned char pos);
/**
 * @brief 取得c內從位元0到位元pos中否全為false
 * @param c 輸入資料
 * @param pos 位置
 * @return true表示輸入資料全為false, false則否
 * @ingroup bittool
 */
bool bitnon(IN char c, IN unsigned char pos);
/**
 * @brief 傳回對c內位元位置pos的設值結果, 不會修改c的內容
 * @param c 輸入資料
 * @param pos 位置
 * @param b 新值
 * @return 結果
 * @ingroup bittool
 */
char bitval(IN char c, IN unsigned char pos, IN bool b);
/**
 * @brief 傳回對c內位元位置pos的位元反向結果, 不會修改c的內容
 * @param c 輸入資料
 * @param pos 位置
 * @return 結果
 * @ingroup bittool
 */
char bitval(IN char c, IN unsigned char pos);
/**
 * @brief 傳回對c內從位元0到位元pos的所有位元設值結果, 不會修改c的內容
 * @param c 輸入資料
 * @param pos 位置
 * @param b 新值
 * @return 結果
 * @ingroup bittool
 */
char bitfil(IN char c, IN unsigned char pos, IN bool b);
/**
 * @brief 傳回對c內從位元0到位元pos的所有位元反向結果, 不會修改c的內容
 * @param c 輸入資料
 * @param pos 位置
 * @return 結果
 * @ingroup bittool
 */
char bitnot(IN char c, IN unsigned char pos);
/**
 * @brief 取得c內從位元0到位元pos中是true的數量
 * @param c 輸入資料
 * @param pos 位置
 * @return 位元為true的數量
 * @ingroup bittool
 */
unsigned char bittcount(IN char c, IN unsigned char pos);
/**
 * @brief 取得c內從位元0到位元pos中是false的數量
 * @param c 輸入資料
 * @param pos 位置
 * @return 位元為false的數量
 * @ingroup bittool
 */
unsigned char bitfcount(IN char c, IN unsigned char pos);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------