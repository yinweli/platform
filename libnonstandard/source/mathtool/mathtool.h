/**
 * @file mathtool.h
 * @note �ƾǨt�C�禡
 * @author yinweli
 */
/**
 * @page �p��ϥ�mathtool
 * mathtool�����禡�Ω�ƾǭp��\n\n
 * --------------------------------------------------\n
 * Header           : mathtool.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref mathtool
 */
/** @defgroup mathtool */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _MATHTOOL
#define _MATHTOOL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �ե�float�ഫ��int���A�ɷ|��1���~�t
 * @note �u���b VC++6.0 �����U�~�ݭn���禡�ե��ഫ�~�t
 * @param f �B�I��
 * @return �ե��᪺���
 * @ingroup mathtool
 */
int float2int(IN float f);
/**
 * @brief ���o�������H���ƦC�C��
 * @note �|�� iMin ~ iMax �������Ҧ��Ʀr�����H���ƦC
 * @param iMin �üƳ̤p��
 * @param iMax �üƳ̤j��
 * @return RandList ���G�C��
 * @ingroup mathtool
 */
std::vector<int> uniquerandlist(IN int iMin, IN int iMax);
/**
 * @brief ���o���w�d�򤺪��ü�(�d��q 0 ~ RAND_MAX)
 * @param iMin �üƳ̤p��
 * @param iMax �üƳ̤j��
 * @return �üƭ�
 * @ingroup mathtool
 */
int rangerand(IN int iMin, IN int iMax);
/**
 * @brief �]�w�üƺؤl64�줸����
 * @param ui64Seed �üƺؤl
 * @ingroup mathtool
 */
void srand64(unsigned __int64 ui64Seed);
/**
 * @brief ���o�ü�64�줸����
 * @note �̤j�Ȭ� RAND_MAX64
 * @return �üƭ�
 * @ingroup mathtool
 */
unsigned __int64 rand64();
/**
 * @brief ���o__int64���A�����
 * @param i ��
 * @return �����
 * @ingroup mathtool
 */
unsigned __int64 abs64(IN __int64 i);
/**
 * @brief ���o�H2�����ƪ�log���G
 * @param f �ƭ�
 * @return ���G
 * @ingroup mathtool
 */
double log2(double f);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------