/**
 * @file nstrlen.h
 * @note �r��r��, ���׭p��
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _NSTRLEN
#define _NSTRLEN
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �p��r��r��
 * @param szInput ��J�r��
 * @return �r��r��
 * @ingroup nslen
 */
unsigned long nscount(IN const std::string &szInput);
/**
 * @brief �p��r��r��, �e�r������
 * @param szInput ��J�r��
 * @return �r��r��
 * @ingroup nslen
 */
unsigned long nscount(IN const std::wstring &szInput);
/**
 * @brief �p��r��줸��
 * @param szInput ��J�r��
 * @return �r��줸��
 * @ingroup nslen
 */
unsigned long nsbytes(IN const std::string &szInput);
/**
 * @brief �p��r��줸��, �e�r������
 * @param szInput ��J�r��
 * @return �r��줸��
 * @ingroup nslen
 */
unsigned long nsbytes(IN const std::wstring &szInput);
/**
 * @brief �Hmulti-byte�覡�p��r��줸��
 * @param szInput ��J�r��
 * @return �r��줸��
 * @ingroup nslen
 */
unsigned long mbbytes(IN const std::string &szInput);
/**
 * @brief �Hmulti-byte�覡�p��r��줸��, �e�r������
 * @param szInput ��J�r��
 * @return �r��줸��
 * @ingroup nslen
 */
unsigned long mbbytes(IN const std::wstring &szInput);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------