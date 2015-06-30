/**
 * @file safe.h
 * @note 安全處理組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _SAFE
#define _SAFE
//-----------------------------------------------------------------------------
#undef max // 避免出現C4003錯誤
#undef min // 避免出現C4003錯誤
//-----------------------------------------------------------------------------
/**
 * @brief 安全檢查
 * @param value 檢查值
 * @param rmin 結果最小值
 * @param rmax 結果最大值
 * @return true表示成功, false則否
 */
template<typename T> bool SafeChk(IN T value, IN T rmin, IN T rmax)
{
	return value >= rmin && value <= rmax;
};
/**
 * @brief 安全設值
 * @param result 算式結果
 * @param value 設置值
 * @param rmin 結果最小值
 * @param rmax 結果最大值
 * @return true表示成功, false則否
 */
template<typename T> bool SafeSet(OUT T &result, IN T value, IN T rmin, IN T rmax)
{
	if(SafeChk(value, rmin, rmax) == false)
		return false;

	result = value;

	return true;
};
/**
 * @brief 安全設值
 * @param result 算式結果
 * @param value 設置值
 * @return true表示成功, false則否
 */
template<typename T> bool SafeSet(OUT T &result, IN T value)
{
	if(SafeChk(value, std::numeric_limits<T>::min(), std::numeric_limits<T>::max()) == false)
		return false;

	result = value;

	return true;
};
/**
 * @brief 安全加法
 * @param result 算式結果
 * @param lhs 算式左值
 * @param rhs 算式右值
 * @param rmin 結果最小值
 * @param rmax 結果最大值
 * @return true表示成功, false則否
 */
template<typename T> bool SafeAdd(OUT T &result, IN T lhs, IN T rhs, IN T rmin, IN T rmax)
{
	T temp = lhs + rhs;

	if(SafeChk(temp, rmin, rmax) == false)
		return false;

	result = temp;

	return true;
};
/**
 * @brief 安全加法
 * @param result 算式結果
 * @param lhs 算式左值
 * @param rhs 算式右值
 * @return true表示成功, false則否
 */
template<typename T> bool SafeAdd(OUT T &result, IN T lhs, IN T rhs)
{
	return SafeAdd(result, lhs, rhs, std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
};
/**
 * @brief 安全乘法
 * @param result 算式結果
 * @param lhs 算式左值
 * @param rhs 算式右值
 * @param rmin 結果最小值
 * @param rmax 結果最大值
 * @return true表示成功, false則否
 */
template<typename T> bool SafeMulti(OUT T &result, IN T lhs, IN T rhs, IN T rmin, IN T rmax)
{
	T temp = lhs * rhs;

	if(SafeChk(temp, rmin, rmax) == false)
		return false;

	result = temp;

	return true;
};
/**
 * @brief 安全乘法
 * @param result 算式結果
 * @param lhs 算式左值
 * @param rhs 算式右值
 * @return true表示成功, false則否
 */
template<typename T> bool SafeMulti(OUT T &result, IN T lhs, IN T rhs)
{
	return SafeMulti(result, lhs, rhs, std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------