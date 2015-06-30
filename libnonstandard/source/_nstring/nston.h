/**
 * @file nston.h
 * @note �r���ഫ�ƭ�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _NSTON
#define _NSTON
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#ifndef UNICODE
#undef nton
#define nton ston ///< �N�r���ഫ��..., �bunicode�sĶ��, nton�۷��wton, �_�h�N�Oston @ingroup nston
#else
#undef nton
#define nton wton ///< �N�r���ഫ��..., �bunicode�sĶ��, nton�۷��wton, �_�h�N�Oston @ingroup nston
#endif
//-----------------------------------------------------------------------------
/**
 * @brief �N�r���ഫ�� bool
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT bool &r);
/**
 * @brief �N�r���ഫ�� bool, �e�r������
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT bool &r);
/**
 * @brief �N�r���ഫ�� char
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT char &r);
/**
 * @brief �N�r���ഫ�� char, �e�r������
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT char &r);
/**
 * @brief �N�r���ഫ�� unsigned char
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT unsigned char &r);
/**
 * @brief �N�r���ഫ�� unsigned char, �e�r������
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT unsigned char &r);
/**
 * @brief �N�r���ഫ�� short
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT short &r);
/**
 * @brief �N�r���ഫ�� short, �e�r������
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT short &r);
/**
 * @brief �N�r���ഫ�� unsigned short
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT unsigned short &r);
/**
 * @brief �N�r���ഫ�� unsigned short, �e�r������
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT unsigned short &r);
/**
 * @brief �N�r���ഫ�� long
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT long &r);
/**
 * @brief �N�r���ഫ�� long, �e�r������
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT long &r);
/**
 * @brief �N�r���ഫ�� unsigned long
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT unsigned long &r);
/**
 * @brief �N�r���ഫ�� unsigned long, �e�r������
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT unsigned long &r);
/**
 * @brief �N�r���ഫ�� int
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT int &r);
/**
 * @brief �N�r���ഫ�� int, �e�r������
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT int &r);
/**
 * @brief �N�r���ഫ�� unsigned int
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT unsigned int &r);
/**
 * @brief �N�r���ഫ�� unsigned long, �e�r������
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT unsigned int &r);
/**
 * @brief �N�r���ഫ�� __int64
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT __int64 &r);
/**
 * @brief �N�r���ഫ�� __int64, �e�r������
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT __int64 &r);
/**
 * @brief �N�r���ഫ�� unsigned __int64
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT unsigned __int64 &r);
/**
 * @brief �N�r���ഫ�� unsigned long, �e�r������
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT unsigned __int64 &r);
/**
 * @brief �N�r���ഫ�� float
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT float &r);
/**
 * @brief �N�r���ഫ�� float, �e�r������
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT float &r);
/**
 * @brief �N�r���ഫ�� double
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void ston(IN const std::string &s, OUT double &r);
/**
 * @brief �N�r���ഫ�� double, �e�r������
 * @param s �r��
 * @param r �ഫ���G
 * @ingroup nston
 */
void wton(IN const std::wstring &s, OUT double &r);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------