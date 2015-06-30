/**
 * @file ipdata.h
 * @note ��}���O
 * @author yinweli
 */
/**
 * @page �p��ϥ�ipdata
 * ipdata�Ω��x�s��}�P�𸹸��\n
 * �ϥήɫإ� C_IPData ����, ��g��}�r��P�𸹴N�i�H�F\n
 * C_IPData.Import() �P C_IPData.Export() �禡�i�H�����󤺳�����ഫ���r��, �άO��r���J�쪫��\n\n
 * --------------------------------------------------\n
 * Header           : ipdata.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref ipdata
 */
/** @defgroup ipdata */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _IPDATA
#define _IPDATA
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ��}���O
 * @ingroup ipdata
 */
class C_IPData
{
private:
	//-------------------------------------
	nstring m_szIP; ///< ��}�r��
	unsigned long m_ulPort; ///< ��
	//-------------------------------------

private:
	//-------------------------------------
	/**
	 * @brief ���o�ե���}�r��
	 * @return �ե���}�r��
	 */
	nstring CorrectIP() const;
	//-------------------------------------

public:
	//-------------------------------------
	C_IPData();
	C_IPData(IN const nstring &data);
	C_IPData(IN const nstring &ip, IN unsigned long port);
	virtual ~C_IPData();
	//-------------------------------------
	bool operator < (IN const C_IPData &rhs) const;
	bool operator > (IN const C_IPData &rhs) const;
	bool operator <= (IN const C_IPData &rhs) const;
	bool operator >= (IN const C_IPData &rhs) const;
	bool operator == (IN const C_IPData &rhs) const;
	bool operator != (IN const C_IPData &rhs) const;
	//-------------------------------------
	/**
	 * @brief �פJ�r��
	 * @param szData ��Ʀr��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Import(IN const nstring &szData);
	/**
	 * @brief �פJ���
	 * @param szIP ��}�r��
	 * @param ulPort ��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Import(IN const nstring &szIP, IN unsigned long ulPort);
	/**
	 * @brief �ץX�r��
	 * @return ��Ʀr��
	 */
	nstring Export() const;
	/**
	 * @brief ���o��}�r��
	 * @return ��}�r��
	 */
	nstring IP() const;
	/**
	 * @brief ���o��
	 * @return ��
	 */
	unsigned long Port() const;
	/**
	 * @brief ���o�O�_����
	 * @return true��ܬ���, false�h�_
	 */
	bool Empty() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------