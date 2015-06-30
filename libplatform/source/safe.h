/**
 * @file safe.h
 * @note �w���B�z�ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _SAFE
#define _SAFE
//-----------------------------------------------------------------------------
#undef max // �קK�X�{C4003���~
#undef min // �קK�X�{C4003���~
//-----------------------------------------------------------------------------
/**
 * @brief �w���ˬd
 * @param value �ˬd��
 * @param rmin ���G�̤p��
 * @param rmax ���G�̤j��
 * @return true��ܦ��\, false�h�_
 */
template<typename T> bool SafeChk(IN T value, IN T rmin, IN T rmax)
{
	return value >= rmin && value <= rmax;
};
/**
 * @brief �w���]��
 * @param result �⦡���G
 * @param value �]�m��
 * @param rmin ���G�̤p��
 * @param rmax ���G�̤j��
 * @return true��ܦ��\, false�h�_
 */
template<typename T> bool SafeSet(OUT T &result, IN T value, IN T rmin, IN T rmax)
{
	if(SafeChk(value, rmin, rmax) == false)
		return false;

	result = value;

	return true;
};
/**
 * @brief �w���]��
 * @param result �⦡���G
 * @param value �]�m��
 * @return true��ܦ��\, false�h�_
 */
template<typename T> bool SafeSet(OUT T &result, IN T value)
{
	if(SafeChk(value, std::numeric_limits<T>::min(), std::numeric_limits<T>::max()) == false)
		return false;

	result = value;

	return true;
};
/**
 * @brief �w���[�k
 * @param result �⦡���G
 * @param lhs �⦡����
 * @param rhs �⦡�k��
 * @param rmin ���G�̤p��
 * @param rmax ���G�̤j��
 * @return true��ܦ��\, false�h�_
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
 * @brief �w���[�k
 * @param result �⦡���G
 * @param lhs �⦡����
 * @param rhs �⦡�k��
 * @return true��ܦ��\, false�h�_
 */
template<typename T> bool SafeAdd(OUT T &result, IN T lhs, IN T rhs)
{
	return SafeAdd(result, lhs, rhs, std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
};
/**
 * @brief �w�����k
 * @param result �⦡���G
 * @param lhs �⦡����
 * @param rhs �⦡�k��
 * @param rmin ���G�̤p��
 * @param rmax ���G�̤j��
 * @return true��ܦ��\, false�h�_
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
 * @brief �w�����k
 * @param result �⦡���G
 * @param lhs �⦡����
 * @param rhs �⦡�k��
 * @return true��ܦ��\, false�h�_
 */
template<typename T> bool SafeMulti(OUT T &result, IN T lhs, IN T rhs)
{
	return SafeMulti(result, lhs, rhs, std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------