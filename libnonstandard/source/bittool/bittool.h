/**
 * @file bittool.h
 * @note �줸�ާ@�t�C�禡
 * @author yinweli
 */
/**
 * @page �p��ϥ�bittool
 * bittool�����禡�Ω�줸�ާ@\n\n
 * bittool�����禡, ��J�ȳ��O1��byte�j�p\n
 * �o��ܦp�G�Q�n��W�L1��byte�j�p����Ƨ@�줸�ާ@, �N�n�ƥ����D�Q�n�ާ@���줸�O�b���Ӧ줸�դ�, �M��u��J���Ӧ줸�ժ���ƨӾާ@\n
 * �t�~�N�O�u�n�A�έק�줸�ո�ƪ��ާ@, �禡���u���ѧ���ܫ᪺���G�@���Ǧ^��, ���O�èS���h�ק�ϥΪ̿�J�����\n
 * �ҥH�ϥΤW�ݭn���H�U���\n\n
 * char x = 0;\n\n
 * x = bitval(x, 0, 1); // �� x ���Ĥ@�Ӧ줸�]��true, �M��⵲�G�]�^ x\n\n
 * --------------------------------------------------\n
 * Header           : bittool.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref bittool
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
 * @brief ���o�ƭȻݭn���X�мƶq
 * @param iValue �ƭ�
 * @return �X�мƶq
 * @ingroup bittool
 */
unsigned int bitsize(IN int iValue);
/**
 * @brief ���oc���줸��mpos����
 * @param c ��J���
 * @param pos ��m
 * @return ��
 * @ingroup bittool
 */
bool bitget(IN char c, IN unsigned char pos);
/**
 * @brief ���oc���q�줸0��줸pos���O�_��true
 * @param c ��J���
 * @param pos ��m
 * @return true��ܿ�J��Ƥ���true, false�h�_
 * @ingroup bittool
 */
bool bitany(IN char c, IN unsigned char pos);
/**
 * @brief ���oc���q�줸0��줸pos���O�_��false
 * @param c ��J���
 * @param pos ��m
 * @return true��ܿ�J��Ƥ���false, false�h�_
 * @ingroup bittool
 */
bool bitanf(IN char c, IN unsigned char pos);
/**
 * @brief ���oc���q�줸0��줸pos���_����false
 * @param c ��J���
 * @param pos ��m
 * @return true��ܿ�J��ƥ���false, false�h�_
 * @ingroup bittool
 */
bool bitnon(IN char c, IN unsigned char pos);
/**
 * @brief �Ǧ^��c���줸��mpos���]�ȵ��G, ���|�ק�c�����e
 * @param c ��J���
 * @param pos ��m
 * @param b �s��
 * @return ���G
 * @ingroup bittool
 */
char bitval(IN char c, IN unsigned char pos, IN bool b);
/**
 * @brief �Ǧ^��c���줸��mpos���줸�ϦV���G, ���|�ק�c�����e
 * @param c ��J���
 * @param pos ��m
 * @return ���G
 * @ingroup bittool
 */
char bitval(IN char c, IN unsigned char pos);
/**
 * @brief �Ǧ^��c���q�줸0��줸pos���Ҧ��줸�]�ȵ��G, ���|�ק�c�����e
 * @param c ��J���
 * @param pos ��m
 * @param b �s��
 * @return ���G
 * @ingroup bittool
 */
char bitfil(IN char c, IN unsigned char pos, IN bool b);
/**
 * @brief �Ǧ^��c���q�줸0��줸pos���Ҧ��줸�ϦV���G, ���|�ק�c�����e
 * @param c ��J���
 * @param pos ��m
 * @return ���G
 * @ingroup bittool
 */
char bitnot(IN char c, IN unsigned char pos);
/**
 * @brief ���oc���q�줸0��줸pos���Otrue���ƶq
 * @param c ��J���
 * @param pos ��m
 * @return �줸��true���ƶq
 * @ingroup bittool
 */
unsigned char bittcount(IN char c, IN unsigned char pos);
/**
 * @brief ���oc���q�줸0��줸pos���Ofalse���ƶq
 * @param c ��J���
 * @param pos ��m
 * @return �줸��false���ƶq
 * @ingroup bittool
 */
unsigned char bitfcount(IN char c, IN unsigned char pos);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------