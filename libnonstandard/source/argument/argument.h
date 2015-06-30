/**
 * @file argument.h
 * @note �Ѽ����O
 * @author yinweli
 */
/**
 * @page �p��ϥ�argument
 * argument�]�t�T�����O :\n
 * C_Argu ���O�Ω�̰�¦���Ѽ��ഫ, �i�H�ഫ���U�ؼƭȩάO�r��, �ϥΪ̥i�H�����ߤ@�Ӧh�\��ƭ�/�r���ഫ��\n
 * C_Argp ���O�Ω��x�s �W��:��� �Ҧ������, �W�٥����O�r��, ��ƫh����ƭ�/�r��, �I�s C_Argp.Set() �禡�i�H��J���, �I�s C_Argp.Get() �禡�i�H���o���\n
 * C_Argv ���O�Ω��x�s��ƦC��, ���P�� C_Argp ���O�Φr�갵������, C_Argv ���O�μƭȧ@������, �I�s C_Argp.Set() �禡�i�H��J���, �I�s C_Argp.Get() �禡�i�H���o���, �t�~�惡���O�ϥ� << �B��l�]�i�H��J���(�۰ʰl�[�b�̧���)\n\n
 * --------------------------------------------------\n
 * Header           : argument.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref argument
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
 * @brief �Ѽư�¦���O
 * @ingroup argument
 */
class C_Argu
{
private:
	//-------------------------------------
	nstring m_szValue; ///< �ѼƸ��
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
	// �]�ȹB��l
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
	// �૬�B��l
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
	 * @brief ���o����
	 * @return ����
	 */
	unsigned long size() const;
	/**
	 * @brief �ˬd�O�_����
	 * @return true��ܬ���, false�h�_
	 */
	bool empty() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �M�說�Ѽ����O
 * @ingroup argp
 */
class C_Argp
{
private:
	//-------------------------------------
	std::map<nstring, C_Argu> m_Argument; ///< �ѼƦC�� <�ѼƦW��, �ѼƸ��>
	//-------------------------------------

public:
	//-------------------------------------
	typedef std::map<nstring, C_Argu>::iterator iterator; ///< �ѼƦC���N�����O
	typedef std::map<nstring, C_Argu>::const_iterator const_iterator; ///< �ѼƦC���N�����O
	//-------------------------------------

public:
	//-------------------------------------
	C_Argp();
	C_Argp(IN const C_Argp &argp);
	virtual ~C_Argp();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void clear();
	/**
	 * @brief �]�w�Ѽ�
	 * @param szName �ѼƦW��
	 * @param value �Ѽƭ�
	 */
	void set(IN const nstring &szName, IN const C_Argu &value);
	/**
	 * @brief �]�w�Ѽ�
	 * @param value �Ѽƭ�
	 */
	void set(IN const C_Argp &value);
	/**
	 * @brief ���o�Ѽ�
	 * @param szName �ѼƦW��
	 * @return �ѼƸ��
	 */
	C_Argu get(IN const nstring &szName) const;
	/**
	 * @brief ���o�ѼƦC��
	 * @return �ѼƦC��
	 */
	std::map<nstring, C_Argu> get() const;
	/**
	 * @brief ���o�ѼƦC��}�Y���N��
	 * @return �ѼƦC���N��
	 */
	C_Argp::iterator begin();
	/**
	 * @brief ���o�ѼƦC�������N��
	 * @return �ѼƦC���N��
	 */
	C_Argp::iterator end();
	/**
	 * @brief ���o�ѼƦC��}�Y���N��
	 * @return �ѼƦC���N��
	 */
	C_Argp::const_iterator begin() const;
	/**
	 * @brief ���o�ѼƦC�������N��
	 * @return �ѼƦC���N��
	 */
	C_Argp::const_iterator end() const;
	/**
	 * @brief ���o�ѼƼƶq
	 * @return �ѼƼƶq
	 */
	unsigned long size() const;
	/**
	 * @brief ���o�O�_����
	 * @return true��ܬ���, false�h�_
	 */
	bool empty() const;
	/**
	 * @brief ���o�ѼƬO�_�s�b
	 * @param szName �ѼƦW��
	 * @return true��ܦs�b, false�h�_
	 */
	bool exist(IN const nstring &szName) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �ǦC���Ѽ����O
 * @ingroup argv
 */
class C_Argv
{
private:
	//-------------------------------------
	std::vector<C_Argu> m_Argument; ///< �ѼƦC��
	//-------------------------------------

public:
	//-------------------------------------
	typedef std::vector<C_Argu>::iterator iterator; ///< �ѼƦC���N�����O
	typedef std::vector<C_Argu>::const_iterator const_iterator; ///< �ѼƦC���N�����O
	//-------------------------------------

public:
	//-------------------------------------
	C_Argv();
	C_Argv(IN const C_Argv &argv);
	virtual ~C_Argv();
	//-------------------------------------
	// << �B��l
	C_Argv &operator << (IN const C_Argu &value);
	C_Argv &operator << (IN const C_Argv &value);
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void clear();
	/**
	 * @brief �]�w�Ѽ�
	 * @param value �Ѽƭ�
	 */
	void set(IN const C_Argv &value);
	/**
	 * @brief �]�w�Ѽ�
	 * @param ulPos �ѼƦ�m
	 * @param value �Ѽƭ�
	 */
	void set(IN unsigned long ulPos, IN const C_Argu &value);
	/**
	 * @brief ���o�Ѽ�
	 * @param ulPos �ѼƦ�m
	 * @return �ѼƸ��
	 */
	C_Argu get(IN unsigned long ulPos) const;
	/**
	 * @brief ���o�����Ѽ�
	 * @return �����ѼƦC��
	 */
	std::vector<C_Argu> get() const;
	/**
	 * @brief ���o�ѼƦC��}�Y���N��
	 * @return �ѼƦC���N��
	 */
	C_Argv::iterator begin();
	/**
	 * @brief ���o�ѼƦC�������N��
	 * @return �ѼƦC���N��
	 */
	C_Argv::iterator end();
	/**
	 * @brief ���o�ѼƦC��}�Y���N��
	 * @return �ѼƦC���N��
	 */
	C_Argv::const_iterator begin() const;
	/**
	 * @brief ���o�ѼƦC�������N��
	 * @return �ѼƦC���N��
	 */
	C_Argv::const_iterator end() const;
	/**
	 * @brief ���o�ѼƼƶq
	 * @return �ѼƼƶq
	 */
	unsigned long size() const;
	/**
	 * @brief ���o�O�_����
	 * @return true��ܬ���, false�h�_
	 */
	bool empty() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief ���o�ǦC���Ѽƪ���
 * @param Data �ӷ����
 * @return �ǦC���Ѽƪ���
 */
template<typename T> C_Argv toargv(IN const std::vector<T> &Data)
{
	C_Argv ccArgv;

	std::for_each(Data.begin(), Data.end(), [&ccArgv] (const std::vector<T>::value_type &Itor) { ccArgv << Itor; });

	return ccArgv;
};
/**
 * @brief ���o�ǦC���Ѽƪ���
 * @param Data �ӷ����
 * @param Ofs �첾��m
 * @return �ǦC���Ѽƪ���
 */
template<typename T> C_Argv toargv(IN const std::vector<T> &Data, IN typename std::vector<T>::size_type Ofs)
{
	C_Argv ccArgv;

	std::for_each(Data.begin() + Ofs, Data.end(), [&ccArgv] (const std::vector<T>::value_type &Itor) { ccArgv << Itor; });

	return ccArgv;
};
/**
 * @brief ���o�ǦC���Ѽƪ���
 * @param Data �ӷ����
 * @param Ofs �첾��m
 * @param Count �ѼƼƶq
 * @return �ǦC���Ѽƪ���
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