/**
 * @file _ntime.h
 * @note 非標準時間類別
 * @author yinweli
 */
/**
 * @page 如何使用_ntime
 * _ntime是個用於時間處理的類別\n\n
 * --------------------------------------------------\n
 * Header           : _ntime.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref ntime\n
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
 * @brief 非標準時間列舉
 * @ingroup ntime
 */
enum ENUM_NTime
{
	ENUM_NTime_NULL = 0, ///< 無效
	ENUM_NTime_GMT, ///< 格林威治時間
	ENUM_NTime_Local, ///< 本地時間

	ENUM_NTime_FORCE_DWORD = ENUM_FORCE_DWORD, 
};
//-----------------------------------------------------------------------------
/**
 * @brief 非標準時間類別
 * @ingroup ntime
 */
class C_NTime
{
private:
	//-------------------------------------
	short m_wYear; ///< 年
	short m_wMon; ///< 月
	short m_wDay; ///< 日
	short m_wHour; ///< 時
	short m_wMin; ///< 分
	short m_wSec; ///< 秒
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
	// = 運算子
	C_NTime &operator = (IN const C_NTime &time);
	C_NTime &operator = (IN __int64 second);
	C_NTime &operator = (IN const struct tm &time);
	C_NTime &operator = (IN const SYSTEMTIME &time);
	// + 運算子
	const C_NTime operator + (IN __int64 second) const;
	// - 運算子
	const C_NTime operator - (IN __int64 second) const;
	// += 運算子
	C_NTime &operator += (IN __int64 second);
	// -= 運算子
	C_NTime &operator -= (IN __int64 second);
	// == 運算子
	bool operator == (IN const C_NTime &time) const;
	bool operator == (IN __int64 second) const;
	bool operator == (IN const struct tm &time) const;
	bool operator == (IN const SYSTEMTIME &time) const;
	// != 運算子
	bool operator != (IN const C_NTime &time) const;
	bool operator != (IN __int64 second) const;
	bool operator != (IN const struct tm &time) const;
	bool operator != (IN const SYSTEMTIME &time) const;
	// < 運算子
	bool operator < (IN const C_NTime &time) const;
	bool operator < (IN __int64 second) const;
	bool operator < (IN const struct tm &time) const;
	bool operator < (IN const SYSTEMTIME &time) const;
	// > 運算子
	bool operator > (IN const C_NTime &time) const;
	bool operator > (IN __int64 second) const;
	bool operator > (IN const struct tm &time) const;
	bool operator > (IN const SYSTEMTIME &time) const;
	// <= 運算子
	bool operator <= (IN const C_NTime &time) const;
	bool operator <= (IN __int64 second) const;
	bool operator <= (IN const struct tm &time) const;
	bool operator <= (IN const SYSTEMTIME &time) const;
	// >= 運算子
	bool operator >= (IN const C_NTime &time) const;
	bool operator >= (IN __int64 second) const;
	bool operator >= (IN const struct tm &time) const;
	bool operator >= (IN const SYSTEMTIME &time) const;
	// 轉型運算子
	operator __int64 () const;
	operator struct tm () const;
	operator SYSTEMTIME () const;
	operator nstring () const;
	/**
	 * @brief 取得時間字串
	 * @param szTokDate 日期分隔符號
	 * @param szTokTime 時間分隔符號
	 * @return 時間字串
	 */
	nstring Time(IN const nstring &szTokDate, IN const nstring &szTokTime) const;
	/**
	 * @brief 設定年
	 * @param wYear 年
	 */
	void Year(IN short wYear);
	/**
	 * @brief 設定月
	 * @param wMon 月
	 */
	void Mon(IN short wMon);
	/**
	 * @brief 設定日
	 * @param wDay 日
	 */
	void Day(IN short wDay);
	/**
	 * @brief 設定時
	 * @param wHour 時
	 */
	void Hour(IN short wHour);
	/**
	 * @brief 設定分
	 * @param wMin 分
	 */
	void Min(IN short wMin);
	/**
	 * @brief 設定秒
	 * @param wSec 秒
	 */
	void Sec(IN short wSec);
	/**
	 * @brief 取得年
	 * @return 年
	 */
	short Year() const;
	/**
	 * @brief 取得月
	 * @return 月
	 */
	short Mon() const;
	/**
	 * @brief 取得日
	 * @return 日
	 */
	short Day() const;
	/**
	 * @brief 取得星期, 如果傳回-1表示錯誤
	 * @return 星期
	 */
	short Week() const;
	/**
	 * @brief 取得時
	 * @return 時
	 */
	short Hour() const;
	/**
	 * @brief 取得分
	 * @return 分
	 */
	short Min() const;
	/**
	 * @brief 取得秒
	 * @return 秒
	 */
	short Sec() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 取得格林威治時間字串
 * @return 格林威治時間字串
 * @ingroup ntime
 */
nstring TimeStringGTM();
/**
 * @brief 取得格林威治時間字串
 * @param szTokDate 日期分隔符號
 * @param szTokTime 時間分隔符號
 * @return 格林威治時間字串
 * @ingroup ntime
 */
nstring TimeStringGTM(IN const nstring &szTokDate, IN const nstring &szTokTime);
/**
 * @brief 取得本地時間字串
 * @return 本地時間字串
 * @ingroup ntime
 */
nstring TimeStringLocal();
/**
 * @brief 取得本地時間字串
 * @param szTokDate 日期分隔符號
 * @param szTokTime 時間分隔符號
 * @return 本地時間字串
 * @ingroup ntime
 */
nstring TimeStringLocal(IN const nstring &szTokDate, IN const nstring &szTokTime);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------