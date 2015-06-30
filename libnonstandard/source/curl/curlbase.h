/**
 * @file curlbase.h
 * @note curl��¦���O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CURLBASE
#define _CURLBASE
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ��l��curl
 * @ingroup curl
 */
void CURLInitialize();
/**
 * @brief ����curl
 * @ingroup curl
 */
void CURLRelease();
//-----------------------------------------------------------------------------
/**
 * @brief curl���~���O
 * @ingroup curl
 */
class C_ErrorCURL : public C_ErrorBase
{
private:
	//-------------------------------------
	nstring m_szError; ///< ���~�r��
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorCURL(IN CURLcode code);
	C_ErrorCURL(IN CURLMcode code);
	C_ErrorCURL(IN CURLFORMcode code);
	virtual ~C_ErrorCURL();
	//-------------------------------------
	operator bool () const;
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief curl��¦���O
 * @ingroup curl
 */
class C_CURLBase
{
private:
	//-------------------------------------
	CURL *m_pCURL; ///< curl handle
	//-------------------------------------

public:
	//-------------------------------------
	C_CURLBase();
	virtual ~C_CURLBase();
	//-------------------------------------
	operator CURL * () const;
	//-------------------------------------
	/**
	 * @brief �]�wcurl
	 * @param emOption �ﶵ�C�|
	 * @param ulValue �ﶵ���e
	 * @return true��ܦ��\, false�h�_
	 */
	bool Option(IN CURLoption emOption, IN unsigned long ulValue);
	/**
	 * @brief �]�wcurl
	 * @param emOption �ﶵ�C�|
	 * @param szValue �ﶵ���e
	 * @return true��ܦ��\, false�h�_
	 */
	bool Option(IN CURLoption emOption, IN const nstring &szValue);
	/**
	 * @brief ����curl
	 * @return true��ܦ��\, false�h�_
	 */
	bool Perform();
	/**
	 * @brief ���o��J�r�ꪺURL�s�X�r��
	 * @param szInput ��J�r��
	 * @return URL�s�X�r��
	 */
	nstring URLEncode(IN const nstring &szInput);
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------