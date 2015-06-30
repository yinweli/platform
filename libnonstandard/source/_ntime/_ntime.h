/**
 * @file _ntime.h
 * @note �D�зǮɶ����O
 * @author yinweli
 */
/**
 * @page �p��ϥ�_ntime
 * _ntime�O�ӥΩ�ɶ��B�z�����O\n\n
 * --------------------------------------------------\n
 * Header           : _ntime.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref ntime\n
 */
/** @defgroup ntime */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef __NTIME
#define __NTIME
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\_nstroutf\_nstroutf.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �D�зǮɶ��C�|
 * @ingroup ntime
 */
enum ENUM_NTime
{
	ENUM_NTime_NULL = 0, ///< �L��
	ENUM_NTime_GMT, ///< ��L�ªv�ɶ�
	ENUM_NTime_Local, ///< ���a�ɶ�

	ENUM_NTime_FORCE_DWORD = ENUM_FORCE_DWORD, 
};
//-----------------------------------------------------------------------------
/**
 * @brief �D�зǮɶ����O
 * @ingroup ntime
 */
class C_NTime
{
private:
	//-------------------------------------
	short m_wYear; ///< �~
	short m_wMon; ///< ��
	short m_wDay; ///< ��
	short m_wHour; ///< ��
	short m_wMin; ///< ��
	short m_wSec; ///< ��
	//-------------------------------------

public:
	//-------------------------------------
	C_NTime();
	C_NTime(IN ENUM_NTime emNTime);
	C_NTime(IN __int64 second);
	C_NTime(IN const struct tm &time);
	C_NTime(IN const SYSTEMTIME &time);
	C_NTime(IN const nstring &time);
	C_NTime(IN const nstring &time, IN const nstring &tok);
	C_NTime(IN short year, IN short mon, IN short day, IN short hour, IN short min, IN short sec);
	virtual ~C_NTime();
	//-------------------------------------
	// = �B��l
	C_NTime &operator = (IN const C_NTime &time);
	C_NTime &operator = (IN __int64 second);
	C_NTime &operator = (IN const struct tm &time);
	C_NTime &operator = (IN const SYSTEMTIME &time);
	// + �B��l
	const C_NTime operator + (IN __int64 second) const;
	// - �B��l
	const C_NTime operator - (IN __int64 second) const;
	// += �B��l
	C_NTime &operator += (IN __int64 second);
	// -= �B��l
	C_NTime &operator -= (IN __int64 second);
	// == �B��l
	bool operator == (IN const C_NTime &time) const;
	bool operator == (IN __int64 second) const;
	bool operator == (IN const struct tm &time) const;
	bool operator == (IN const SYSTEMTIME &time) const;
	// != �B��l
	bool operator != (IN const C_NTime &time) const;
	bool operator != (IN __int64 second) const;
	bool operator != (IN const struct tm &time) const;
	bool operator != (IN const SYSTEMTIME &time) const;
	// < �B��l
	bool operator < (IN const C_NTime &time) const;
	bool operator < (IN __int64 second) const;
	bool operator < (IN const struct tm &time) const;
	bool operator < (IN const SYSTEMTIME &time) const;
	// > �B��l
	bool operator > (IN const C_NTime &time) const;
	bool operator > (IN __int64 second) const;
	bool operator > (IN const struct tm &time) const;
	bool operator > (IN const SYSTEMTIME &time) const;
	// <= �B��l
	bool operator <= (IN const C_NTime &time) const;
	bool operator <= (IN __int64 second) const;
	bool operator <= (IN const struct tm &time) const;
	bool operator <= (IN const SYSTEMTIME &time) const;
	// >= �B��l
	bool operator >= (IN const C_NTime &time) const;
	bool operator >= (IN __int64 second) const;
	bool operator >= (IN const struct tm &time) const;
	bool operator >= (IN const SYSTEMTIME &time) const;
	// �૬�B��l
	operator __int64 () const;
	operator struct tm () const;
	operator SYSTEMTIME () const;
	operator nstring () const;
	/**
	 * @brief ���o�ɶ��r��
	 * @param szTokDate ������j�Ÿ�
	 * @param szTokTime �ɶ����j�Ÿ�
	 * @return �ɶ��r��
	 */
	nstring Time(IN const nstring &szTokDate, IN const nstring &szTokTime) const;
	/**
	 * @brief �]�w�~
	 * @param wYear �~
	 */
	void Year(IN short wYear);
	/**
	 * @brief �]�w��
	 * @param wMon ��
	 */
	void Mon(IN short wMon);
	/**
	 * @brief �]�w��
	 * @param wDay ��
	 */
	void Day(IN short wDay);
	/**
	 * @brief �]�w��
	 * @param wHour ��
	 */
	void Hour(IN short wHour);
	/**
	 * @brief �]�w��
	 * @param wMin ��
	 */
	void Min(IN short wMin);
	/**
	 * @brief �]�w��
	 * @param wSec ��
	 */
	void Sec(IN short wSec);
	/**
	 * @brief ���o�~
	 * @return �~
	 */
	short Year() const;
	/**
	 * @brief ���o��
	 * @return ��
	 */
	short Mon() const;
	/**
	 * @brief ���o��
	 * @return ��
	 */
	short Day() const;
	/**
	 * @brief ���o�P��, �p�G�Ǧ^-1��ܿ��~
	 * @return �P��
	 */
	short Week() const;
	/**
	 * @brief ���o��
	 * @return ��
	 */
	short Hour() const;
	/**
	 * @brief ���o��
	 * @return ��
	 */
	short Min() const;
	/**
	 * @brief ���o��
	 * @return ��
	 */
	short Sec() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief ���o��L�ªv�ɶ��r��
 * @return ��L�ªv�ɶ��r��
 * @ingroup ntime
 */
nstring TimeStringGTM();
/**
 * @brief ���o��L�ªv�ɶ��r��
 * @param szTokDate ������j�Ÿ�
 * @param szTokTime �ɶ����j�Ÿ�
 * @return ��L�ªv�ɶ��r��
 * @ingroup ntime
 */
nstring TimeStringGTM(IN const nstring &szTokDate, IN const nstring &szTokTime);
/**
 * @brief ���o���a�ɶ��r��
 * @return ���a�ɶ��r��
 * @ingroup ntime
 */
nstring TimeStringLocal();
/**
 * @brief ���o���a�ɶ��r��
 * @param szTokDate ������j�Ÿ�
 * @param szTokTime �ɶ����j�Ÿ�
 * @return ���a�ɶ��r��
 * @ingroup ntime
 */
nstring TimeStringLocal(IN const nstring &szTokDate, IN const nstring &szTokTime);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------