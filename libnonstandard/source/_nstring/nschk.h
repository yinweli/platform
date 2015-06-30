/**
 * @file nschk.h
 * @note �r���ˬd
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _NSCHK
#define _NSCHK
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �ˬd�Ҧ����r���O�_���O�^��
 * @param szInput �r��
 * @return true��ܳ��O�^��, false�h�_
 * @ingroup nschk
 */
bool alphachk(IN const std::string &szInput);
/**
 * @brief �ˬd�Ҧ����r���O�_���O�^��, �e�r������
 * @param szInput �r��
 * @return true��ܳ��O�^��, false�h�_
 * @ingroup nschk
 */
bool alphachk(IN const std::wstring &szInput);
/**
 * @brief �ˬd�Ҧ����r���O�_���O�Ʀr
 * @param szInput �r��
 * @return true��ܳ��O�Ʀr, false�h�_
 * @ingroup nschk
 */
bool digitchk(IN const std::string &szInput);
/**
 * @brief �ˬd�Ҧ����r���O�_���O�Ʀr, �e�r������
 * @param szInput �r��
 * @return true��ܳ��O�Ʀr, false�h�_
 * @ingroup nschk
 */
bool digitchk(IN const std::wstring &szInput);
/**
 * @brief �ˬd�Ҧ����r���O�_���O�^��P�Ʀr
 * @param szInput �r��
 * @return true��ܳ��O�^��P�Ʀr, false�h�_
 * @ingroup nschk
 */
bool alphadigitchk(IN const std::string &szInput);
/**
 * @brief �ˬd�Ҧ����r���O�_���O�^��P�Ʀr, �e�r������
 * @param szInput �r��
 * @return true��ܳ��O�^��P�Ʀr, false�h�_
 * @ingroup nschk
 */
bool alphadigitchk(IN const std::wstring &szInput);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------