/**
 * @file dbstore.h
 * @note ��Ʈw���G���O
 * @author yinweli
 */
/**
 * @page �p��ϥ�dbstore
 * dbstore�O�ӥΩ��x�s��Ʈw�d�ߵ��G�����O\n\n
 * --------------------------------------------------\n
 * Header           : dbstore.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref dbstore\n
 */
/** @defgroup dbstore */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _DBSTORE
#define _DBSTORE
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\argument\argument.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ��Ʈw���G���~���O
 * @ingroup dbstore
 */
class C_ErrorDBStore : public C_ErrorBase
{
private:
	//-------------------------------------
	estring m_szError; ///< ���~�r��
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorDBStore(IN unsigned long line);
	C_ErrorDBStore(IN unsigned long line, IN const estring &column);
	virtual ~C_ErrorDBStore();
	//-------------------------------------
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief ��Ʈw���G���O
 * @ingroup dbstore
 */
class C_DBStore
{
private:
	//-------------------------------------
	std::map<nstring, C_Argu> m_Store; ///< ��Ʈw���G�C�� <���ަr��, ��ƪ���>
	unsigned long m_ulSize; ///< ���G����
	//-------------------------------------

public:
	//-------------------------------------
	C_DBStore();
	virtual ~C_DBStore();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W���
	 * @param ulLine ��Ʀ渹
	 * @param szColumn ���W��
	 * @param szData ��Ʀr��
	 */
	void Add(IN unsigned long ulLine, IN const nstring &szColumn, IN const std::string &szData);
	/**
	 * @brief �s�W���
	 * @param ulLine ��Ʀ渹
	 * @param szColumn ���W��
	 * @param szData ��Ʀr��
	 */
	void Add(IN unsigned long ulLine, IN const nstring &szColumn, IN const std::wstring &szData);
	/**
	 * @brief ���o���
	 * @param ulLine �渹
	 * @param szColumn ���W��
	 * @param r ���
	 * @return true��ܨ��o���\, false�h�_
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT bool &r) const;
	/**
	 * @brief ���o���
	 * @param ulLine �渹
	 * @param szColumn ���W��
	 * @param r ���
	 * @return true��ܨ��o���\, false�h�_
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT char &r) const;
	/**
	 * @brief ���o���
	 * @param ulLine �渹
	 * @param szColumn ���W��
	 * @param r ���
	 * @return true��ܨ��o���\, false�h�_
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT short &r) const;
	/**
	 * @brief ���o���
	 * @param ulLine �渹
	 * @param szColumn ���W��
	 * @param r ���
	 * @return true��ܨ��o���\, false�h�_
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT unsigned short &r) const;
	/**
	 * @brief ���o���
	 * @param ulLine �渹
	 * @param szColumn ���W��
	 * @param r ���
	 * @return true��ܨ��o���\, false�h�_
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT long &r) const;
	/**
	 * @brief ���o���
	 * @param ulLine �渹
	 * @param szColumn ���W��
	 * @param r ���
	 * @return true��ܨ��o���\, false�h�_
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT unsigned long &r) const;
	/**
	 * @brief ���o���
	 * @param ulLine �渹
	 * @param szColumn ���W��
	 * @param r ���
	 * @return true��ܨ��o���\, false�h�_
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT int &r) const;
	/**
	 * @brief ���o���
	 * @param ulLine �渹
	 * @param szColumn ���W��
	 * @param r ���
	 * @return true��ܨ��o���\, false�h�_
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT unsigned int &r) const;
	/**
	 * @brief ���o���
	 * @param ulLine �渹
	 * @param szColumn ���W��
	 * @param r ���
	 * @return true��ܨ��o���\, false�h�_
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT float &r) const;
	/**
	 * @brief ���o���
	 * @param ulLine �渹
	 * @param szColumn ���W��
	 * @param r ���
	 * @return true��ܨ��o���\, false�h�_
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT double &r) const;
	/**
	 * @brief ���o���
	 * @param ulLine �渹
	 * @param szColumn ���W��
	 * @param r ���
	 * @return true��ܨ��o���G���\, false�h�_
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT std::string &r) const;
	/**
	 * @brief ���o���
	 * @param ulLine �渹
	 * @param szColumn ���W��
	 * @param r ���
	 * @return true��ܨ��o���G���\, false�h�_
	 */
	bool Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT std::wstring &r) const;
	/**
	 * @brief ���o�O�_����
	 * @return true��ܬ���, false�h�_
	 */
	bool Empty() const;
	/**
	 * @brief ���o���G����
	 * @return ���G����
	 */
	unsigned long Size() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------