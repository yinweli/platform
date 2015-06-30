/**
 * @file argument.h
 * @note 把计摸
 * @author yinweli
 */
/**
 * @page ㄏノargument
 * argument摸 :\n
 * C_Argu 摸ノ程膀娄把计锣传, 锣传Θ贺计┪琌﹃, ㄏノ跌ぇ斑计/﹃锣传竟\n
 * C_Argp 摸ノ纗 嘿:戈 家Α戈, 嘿ゲ斗琌﹃, 戈玥计/﹃, ㊣ C_Argp.Set() ㄧΑ块戈, ㊣ C_Argp.Get() ㄧΑ眔戈\n
 * C_Argv 摸ノ纗戈, ぃ C_Argp 摸ノ﹃暗ま, C_Argv 摸ノ计ま, ㊣ C_Argp.Set() ㄧΑ块戈, ㊣ C_Argp.Get() ㄧΑ眔戈, 癸摸ㄏノ << 笲衡块戈(笆發程Ю狠)\n\n
 * --------------------------------------------------\n
 * Header           : argument.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 冈灿弧叫把酚 @ref argument
 */
/** @defgroup argument */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _ARGUMENT
#define _ARGUMENT
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 把计膀娄摸
 * @ingroup argument
 */
class C_Argu
{
private:
	//-------------------------------------
	nstring m_szValue; ///< 把计戈
	//-------------------------------------

public:
	//-------------------------------------
	C_Argu();
	C_Argu(IN bool value);
	C_Argu(IN char value);
	C_Argu(IN unsigned char value);
	C_Argu(IN short value);
	C_Argu(IN unsigned short value);
	C_Argu(IN long value);
	C_Argu(IN unsigned long value);
	C_Argu(IN int value);
	C_Argu(IN unsigned int value);
	C_Argu(IN __int64 value);
	C_Argu(IN unsigned __int64 value);
	C_Argu(IN float value);
	C_Argu(IN double value);
	C_Argu(IN const char *value);
	C_Argu(IN const wchar_t *value);
	C_Argu(IN const std::string &value);
	C_Argu(IN const std::wstring &value);
	C_Argu(IN void *value);
	C_Argu(IN const C_Argu &argu);
	virtual ~C_Argu();
	//-------------------------------------
	// 砞笲衡
	C_Argu &operator = (IN bool value);
	C_Argu &operator = (IN char value);
	C_Argu &operator = (IN unsigned char value);
	C_Argu &operator = (IN short value);
	C_Argu &operator = (IN unsigned short value);
	C_Argu &operator = (IN long value);
	C_Argu &operator = (IN unsigned long value);
	C_Argu &operator = (IN int value);
	C_Argu &operator = (IN unsigned int value);
	C_Argu &operator = (IN __int64 value);
	C_Argu &operator = (IN unsigned __int64 value);
	C_Argu &operator = (IN float value);
	C_Argu &operator = (IN double value);
	C_Argu &operator = (IN const char *value);
	C_Argu &operator = (IN const wchar_t *value);
	C_Argu &operator = (IN const std::string &value);
	C_Argu &operator = (IN const std::wstring &value);
	C_Argu &operator = (IN void *value);
	C_Argu &operator = (IN const C_Argu &argu);
	//-------------------------------------
	// 锣笲衡
	operator bool () const;
	operator char () const;
	operator unsigned char () const;
	operator short () const;
	operator unsigned short () const;
	operator long () const;
	operator unsigned long () const;
	operator int () const;
	operator unsigned int () const;
	operator __int64 () const;
	operator unsigned __int64 () const;
	operator float () const;
	operator double () const;
	operator std::string () const;
	operator std::wstring () const;
	operator void * () const;
	//-------------------------------------
	/**
	 * @brief 眔
	 * @return 
	 */
	unsigned long size() const;
	/**
	 * @brief 浪琩琌
	 * @return trueボ, false玥
	 */
	bool empty() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 琈癸Α把计摸
 * @ingroup argp
 */
class C_Argp
{
private:
	//-------------------------------------
	std::map<nstring, C_Argu> m_Argument; ///< 把计 <把计嘿, 把计戈>
	//-------------------------------------

public:
	//-------------------------------------
	typedef std::map<nstring, C_Argu>::iterator iterator; ///< 把计竟
	typedef std::map<nstring, C_Argu>::const_iterator const_iterator; ///< 把计竟
	//-------------------------------------

public:
	//-------------------------------------
	C_Argp();
	C_Argp(IN const C_Argp &argp);
	virtual ~C_Argp();
	//-------------------------------------
	/**
	 * @brief 睲埃场
	 */
	void clear();
	/**
	 * @brief 砞﹚把计
	 * @param szName 把计嘿
	 * @param value 把计
	 */
	void set(IN const nstring &szName, IN const C_Argu &value);
	/**
	 * @brief 砞﹚把计
	 * @param value 把计
	 */
	void set(IN const C_Argp &value);
	/**
	 * @brief 眔把计
	 * @param szName 把计嘿
	 * @return 把计戈
	 */
	C_Argu get(IN const nstring &szName) const;
	/**
	 * @brief 眔把计
	 * @return 把计
	 */
	std::map<nstring, C_Argu> get() const;
	/**
	 * @brief 眔把计秨繷竟
	 * @return 把计竟
	 */
	C_Argp::iterator begin();
	/**
	 * @brief 眔把计挡Ю竟
	 * @return 把计竟
	 */
	C_Argp::iterator end();
	/**
	 * @brief 眔把计秨繷竟
	 * @return 把计竟
	 */
	C_Argp::const_iterator begin() const;
	/**
	 * @brief 眔把计挡Ю竟
	 * @return 把计竟
	 */
	C_Argp::const_iterator end() const;
	/**
	 * @brief 眔把计计秖
	 * @return 把计计秖
	 */
	unsigned long size() const;
	/**
	 * @brief 眔琌
	 * @return trueボ, false玥
	 */
	bool empty() const;
	/**
	 * @brief 眔把计琌
	 * @param szName 把计嘿
	 * @return trueボ, false玥
	 */
	bool exist(IN const nstring &szName) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief Α把计摸
 * @ingroup argv
 */
class C_Argv
{
private:
	//-------------------------------------
	std::vector<C_Argu> m_Argument; ///< 把计
	//-------------------------------------

public:
	//-------------------------------------
	typedef std::vector<C_Argu>::iterator iterator; ///< 把计竟
	typedef std::vector<C_Argu>::const_iterator const_iterator; ///< 把计竟
	//-------------------------------------

public:
	//-------------------------------------
	C_Argv();
	C_Argv(IN const C_Argv &argv);
	virtual ~C_Argv();
	//-------------------------------------
	// << 笲衡
	C_Argv &operator << (IN const C_Argu &value);
	C_Argv &operator << (IN const C_Argv &value);
	//-------------------------------------
	/**
	 * @brief 睲埃场
	 */
	void clear();
	/**
	 * @brief 砞﹚把计
	 * @param value 把计
	 */
	void set(IN const C_Argv &value);
	/**
	 * @brief 砞﹚把计
	 * @param ulPos 把计竚
	 * @param value 把计
	 */
	void set(IN unsigned long ulPos, IN const C_Argu &value);
	/**
	 * @brief 眔把计
	 * @param ulPos 把计竚
	 * @return 把计戈
	 */
	C_Argu get(IN unsigned long ulPos) const;
	/**
	 * @brief 眔场把计
	 * @return 场把计
	 */
	std::vector<C_Argu> get() const;
	/**
	 * @brief 眔把计秨繷竟
	 * @return 把计竟
	 */
	C_Argv::iterator begin();
	/**
	 * @brief 眔把计挡Ю竟
	 * @return 把计竟
	 */
	C_Argv::iterator end();
	/**
	 * @brief 眔把计秨繷竟
	 * @return 把计竟
	 */
	C_Argv::const_iterator begin() const;
	/**
	 * @brief 眔把计挡Ю竟
	 * @return 把计竟
	 */
	C_Argv::const_iterator end() const;
	/**
	 * @brief 眔把计计秖
	 * @return 把计计秖
	 */
	unsigned long size() const;
	/**
	 * @brief 眔琌
	 * @return trueボ, false玥
	 */
	bool empty() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 眔Α把计ン
 * @param Data ㄓ方戈
 * @return Α把计ン
 */
template<typename T> C_Argv toargv(IN const std::vector<T> &Data)
{
	C_Argv ccArgv;

	std::for_each(Data.begin(), Data.end(), [&ccArgv] (const std::vector<T>::value_type &Itor) { ccArgv << Itor; });

	return ccArgv;
};
/**
 * @brief 眔Α把计ン
 * @param Data ㄓ方戈
 * @param Ofs 簿竚
 * @return Α把计ン
 */
template<typename T> C_Argv toargv(IN const std::vector<T> &Data, IN typename std::vector<T>::size_type Ofs)
{
	C_Argv ccArgv;

	std::for_each(Data.begin() + Ofs, Data.end(), [&ccArgv] (const std::vector<T>::value_type &Itor) { ccArgv << Itor; });

	return ccArgv;
};
/**
 * @brief 眔Α把计ン
 * @param Data ㄓ方戈
 * @param Ofs 簿竚
 * @param Count 把计计秖
 * @return Α把计ン
 */
template<typename T> C_Argv toargv(IN const std::vector<T> &Data, IN typename std::vector<T>::size_type Ofs, IN typename std::vector<T>::size_type Count)
{
	C_Argv ccArgv;

	std::for_each(Data.begin() + Ofs, Data.begin() + Ofs + Count, [&ccArgv] (const std::vector<T>::value_type &Itor) { ccArgv << Itor; });

	return ccArgv;
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------