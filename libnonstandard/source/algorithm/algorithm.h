/**
 * @file algorithm.h
 * @note 演算法系列函式
 * @author yinweli
 */
/**
 * @page 如何使用algorithm
 * algorithm內含一些演算法的集合\n\n
 * --------------------------------------------------\n
 * Header           : algorithm.h\n
 * Library(debug)   : \n
 * Library(release) : \n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref algorithm
 */
/** @defgroup algorithm */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _ALGORITHM
#define _ALGORITHM
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
// map演算法
/**
 * @brief 新增資料到std::map中, 如果已有資料, 就回傳 end
 * @param r 要操作的std::map物件
 * @param k 索引值
 * @param v 資料值
 * @return 新增的迭代器
 * @ingroup algorithm
 */
template<typename K, typename V> typename std::map<K, V>::iterator insertmap(OUT std::map<K, V> &r, IN const K k, IN const V v)
{
	std::map<K, V>::iterator Itor = r.lower_bound(k);

	if(Itor != r.end() && r.key_comp()(k, Itor->first) == false)
		return r.end();
	else
		return r.insert(Itor, std::map<K, V>::value_type(k, v));
}
/**
 * @brief 新增或更新資料到std::map中
 * @param r 要操作的std::map物件
 * @param k 索引值
 * @param v 資料值
 * @return 新增或更新的迭代器
 * @ingroup algorithm
 */
template<typename K, typename V> typename std::map<K, V>::iterator updatemap(OUT std::map<K, V> &r, IN const K k, IN const V v)
{
	std::map<K, V>::iterator Itor = r.lower_bound(k);

	if(Itor != r.end() && r.key_comp()(k, Itor->first) == false)
		Itor->second = v;
	else
		Itor = r.insert(Itor, std::map<K, V>::value_type(k, v));

	return Itor;
}
/**
 * @brief 從std::map中刪除元素, 並傳回指向下一個元素的迭代器
 * @note 標準版的STL中, 關聯容器的erase函式不會傳回指向下一個元素的迭代器, 但是VC6.0版本的會. 而事實上這樣寫我覺得比較簡潔, 所以這個函式就是用來給舊用法的
 * @param r 要操作的std::map物件
 * @param k 索引值
 * @return 下一個元素的迭代器
 * @ingroup algorithm
 */
template<typename K, typename V> typename std::map<K, V>::iterator erasemap(OUT std::map<K, V> &r, IN const K k)
{
	std::map<K, V>::iterator Itor = r.find(k);

	r.erase(Itor++);

	return Itor;
}
/**
 * @brief 從std::map中依照條件判斷刪除元素
 * @param r 要操作的std::map物件
 * @param p 條件判斷物件
 * @ingroup algorithm
 */
template<typename K, typename V, typename P> void removeifmap(std::map<K, V> &r, P p)
{
	std::map<K, V>::iterator Itor = r.begin();

	while((Itor = std::find_if(Itor, r.end(), p)) != r.end())
		r.erase(Itor++);
}
//-----------------------------------------------------------------------------
// multimap演算法
/**
 * @brief 新增資料到std::multimap中, 如果已有資料, 就回傳 end
 * @param r 要操作的std::multimap物件
 * @param k 索引值
 * @param v 資料值
 * @return 新增的迭代器
 * @ingroup algorithm
 */
template<typename K, typename V> typename std::multimap<K, V>::iterator insertmultimap(OUT std::multimap<K, V> &r, IN const K k, IN const V v)
{
	std::multimap<K, V>::iterator Itor = r.lower_bound(k);

	if(Itor != r.end() && r.key_comp()(k, Itor->first) == false)
		return r.end();
	else
		return r.insert(Itor, std::multimap<K, V>::value_type(k, v));
}
/**
 * @brief 新增或更新資料到std::multimap中
 * @param r 要操作的std::multimap物件
 * @param k 索引值
 * @param v 資料值
 * @return 新增或更新的迭代器
 * @ingroup algorithm
 */
template<typename K, typename V> typename std::multimap<K, V>::iterator updatemultimap(OUT std::multimap<K, V> &r, IN const K k, IN const V v)
{
	std::multimap<K, V>::iterator Itor = r.lower_bound(k);

	if(Itor != r.end() && r.key_comp()(k, Itor->first) == false)
		Itor->second = v;
	else
		Itor = r.insert(Itor, std::multimap<K, V>::value_type(k, v));

	return Itor;
}
/**
 * @brief 從std::multimap中刪除元素, 並傳回指向下一個元素的迭代器
 * @note 標準版的STL中, 關聯容器的erase函式不會傳回指向下一個元素的迭代器, 但是VC6.0版本的會. 而事實上這樣寫我覺得比較簡潔, 所以這個函式就是用來給舊用法的
 * @param r 要操作的std::multimap物件
 * @param k 索引值
 * @return 下一個元素的迭代器
 * @ingroup algorithm
 */
template<typename K, typename V> typename std::multimap<K, V>::iterator erasemultimap(OUT std::multimap<K, V> &r, IN const K k)
{
	std::multimap<K, V>::iterator Itor = r.find(k);

	r.erase(Itor++);

	return Itor;
}
/**
 * @brief 從std::multimap中依照條件判斷刪除元素
 * @param r 要操作的std::multimap物件
 * @param p 條件判斷物件
 * @ingroup algorithm
 */
template<typename K, typename V, typename P> void removeifmultimap(std::multimap<K, V> &r, P p)
{
	std::multimap<K, V>::iterator Itor = r.begin();

	while((Itor = std::find_if(Itor, r.end(), p)) != r.end())
		r.erase(Itor++);
}
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------