/**
 * @file nstox.h
 * @note �ƭ��ഫ�r��
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _NSTOX
#define _NSTOX
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#ifndef UNICODE
#undef ntox
#define ntox ntos ///< �N...�ഫ���r��, �bunicode�sĶ��, ntox�۷��ntow, �_�h�N�Ontos @ingroup nstox
#define ntob ntobs ///< �N�줸���ഫ���줸�r��, �bunicode�sĶ��, ntob�۷��ntobw, �_�h�N�Ontobs @ingroup nstox
#else
#undef ntox
#define ntox ntow ///< �N...�ഫ���r��, �bunicode�sĶ��, ntox�۷��ntow, �_�h�N�Ontos @ingroup nstox
#define ntob ntobw ///< �N�줸���ഫ���줸�r��, �bunicode�sĶ��, ntob�۷��ntobw, �_�h�N�Ontobs @ingroup nstox
#endif
//-----------------------------------------------------------------------------
#define noct(x) ntox(x, 8) ///< �N�ƭ��ഫ��8�i��r��
#define nhex(x) ntox(x, 16) ///< �N�ƭ��ഫ��16�i��r��
//-----------------------------------------------------------------------------
/**
 * @brief �N bool �ഫ���r��
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::string ntos(IN bool x, IN int radix = 10);
/**
 * @brief �N bool �ഫ���r��, �e�r������
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::wstring ntow(IN bool x, IN int radix = 10);
/**
 * @brief �N char �ഫ���r��
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::string ntos(IN char x, IN int radix = 10);
/**
 * @brief �N char �ഫ���r��, �e�r������
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::wstring ntow(IN char x, IN int radix = 10);
/**
 * @brief �N unsigned char �ഫ���r��
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::string ntos(IN unsigned char x, IN int radix = 10);
/**
 * @brief �N unsigned char �ഫ���r��, �e�r������
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::wstring ntow(IN unsigned char x, IN int radix = 10);
/**
 * @brief �N short �ഫ���r��
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::string ntos(IN short x, IN int radix = 10);
/**
 * @brief �N short �ഫ���r��, �e�r������
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::wstring ntow(IN short x, IN int radix = 10);
/**
 * @brief �N unsigned short �ഫ���r��
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::string ntos(IN unsigned short x, IN int radix = 10);
/**
 * @brief �N unsigned short �ഫ���r��, �e�r������
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::wstring ntow(IN unsigned short x, IN int radix = 10);
/**
 * @brief �N long �ഫ���r��
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::string ntos(IN long x, IN int radix = 10);
/**
 * @brief �N long �ഫ���r��, �e�r������
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::wstring ntow(IN long x, IN int radix = 10);
/**
 * @brief �N unsigned long �ഫ���r��
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::string ntos(IN unsigned long x, IN int radix = 10);
/**
 * @brief �N unsigned long �ഫ���r��, �e�r������
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::wstring ntow(IN unsigned long x, IN int radix = 10);
/**
 * @brief �N int �ഫ���r��
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::string ntos(IN int x, IN int radix = 10);
/**
 * @brief �N int �ഫ���r��, �e�r������
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::wstring ntow(IN int x, IN int radix = 10);
/**
 * @brief �N unsigned int �ഫ���r��
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::string ntos(IN unsigned int x, IN int radix = 10);
/**
 * @brief �N unsigned int �ഫ���r��, �e�r������
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::wstring ntow(IN unsigned int x, IN int radix = 10);
/**
 * @brief �N __int64 �ഫ���r��
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::string ntos(IN __int64 x, IN int radix = 10);
/**
 * @brief �N __int64 �ഫ���r��, �e�r������
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::wstring ntow(IN __int64 x, IN int radix = 10);
/**
 * @brief �N unsigned __int64 �ഫ���r��
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::string ntos(IN unsigned __int64 x, IN int radix = 10);
/**
 * @brief �N unsigned __int64 �ഫ���r��, �e�r������
 * @param x �ƭ�
 * @param radix ���(2 ~ 36)
 * @return �r��
 * @ingroup nstox
 */
std::wstring ntow(IN unsigned __int64 x, IN int radix = 10);
/**
 * @brief �N float �ഫ���r��
 * @param x �ƭ�
 * @param count �r��n��ܨ�p�ƥH�U�X��
 * @return �r��
 * @ingroup nstox
 */
std::string ntos(IN float x, IN int count);
/**
 * @brief �N float �ഫ���r��, �e�r������
 * @param x �ƭ�
 * @param count �r��n��ܨ�p�ƥH�U�X��
 * @return �r��
 * @ingroup nstox
 */
std::wstring ntow(IN float x, IN int count);
/**
 * @brief �N float �ഫ���r��
 * @param x �ƭ�
 * @return �r��
 * @ingroup nstox
 */
std::string ntos(IN float x);
/**
 * @brief �N float �ഫ���r��, �e�r������
 * @param x �ƭ�
 * @return �r��
 * @ingroup nstox
 */
std::wstring ntow(IN float x);
/**
 * @brief �N double �ഫ���r��
 * @param x �ƭ�
 * @param count �r��n��ܨ�p�ƥH�U�X��
 * @return �r��
 * @ingroup nstox
 */
std::string ntos(IN double x, IN int count);
/**
 * @brief �N double �ഫ���r��, �e�r������
 * @param x �ƭ�
 * @param count �r��n��ܨ�p�ƥH�U�X��
 * @return �r��
 * @ingroup nstox
 */
std::wstring ntow(IN double x, IN int count);
/**
 * @brief �N double �ഫ���r��
 * @param x �ƭ�
 * @return �r��
 * @ingroup nstox
 */
std::string ntos(IN double x);
/**
 * @brief �N double �ഫ���r��, �e�r������
 * @param x �ƭ�
 * @return �r��
 * @ingroup nstox
 */
std::wstring ntow(IN double x);
/**
 * @brief �N�줸���ഫ���줸�r��
 * @param bytes �줸��
 * @return �줸�r��
 * @ingroup nstox
 */
std::string ntobs(IN unsigned int bytes);
/**
 * @brief �N�줸���ഫ���줸�r��, �e�r������
 * @param bytes �줸��
 * @return �줸�r��
 * @ingroup nstox
 */
std::wstring ntobw(IN unsigned int bytes);
/**
 * @brief �N�줸���ഫ���줸�r��
 * @param bytes �줸��
 * @return �줸�r��
 * @ingroup nstox
 */
std::string ntobs(IN unsigned __int64 bytes);
/**
 * @brief �N�줸���ഫ���줸�r��, �e�r������
 * @param bytes �줸��
 * @return �줸�r��
 * @ingroup nstox
 */
std::wstring ntobw(IN unsigned __int64 bytes);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------