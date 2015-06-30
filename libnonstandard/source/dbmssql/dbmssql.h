/**
 * @file dbmssql.h
 * @note MSSQL��Ʈw
 * @author yinweli
 */
/**
 * @page �p��ϥ�dbmssql
 * dbmssql�O�ӥΩ�PMSSQL��Ʈw�s�u������\n
 * �t�Υ����n�w��sqlncli10.0, �i�b�����}��� http://go.microsoft.com/fwlink/?LinkId=123717&clcid=0x404 \n\n
 * �n�إ�dbmssql�����n�I�sCOM����l�禡 CoInitialize() ��l��COM����\n
 * �åB�n�O�o�b�{�������ɩI�s CoUninitialize() ��COM��������\n
 * �M��H C_DBMSSQL �إ߹���\n\n
 * C_DBMSSQL ccDB;\n\n
 * �M��I�s C_DBMSSQL.Connect() ���Ʈw�s�u\n
 * �s�u���\�ᥲ�����_�I�s C_DBMSSQL.Process() �禡���������B�@\n
 * �ϥΧ�����i�H�I�s C_DBMSSQL.Disconnect() ���Ʈw�_�u\n\n
 * �n����SQL�y�y, �u�n�I�s C_DBMSSQL.Execute() �禡����R�O�è��o���G\n\n
 * --------------------------------------------------\n
 * Header           : dbmssql.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref dbmssql\n
 */
/** @defgroup dbmssql */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _DBMSSQL
#define _DBMSSQL
//-----------------------------------------------------------------------------
#pragma comment(lib, "winmm.lib")
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\algorithm\algorithm.h"
#include "..\benchmark\benchmark.h"
#include "..\comtool\comtool.h"
#include "..\dbase\dbase.h"
#include "..\dbstore\dbstore.h"
#include "..\debugtool\debugtool.h"
#include "..\memorytool\memorytool.h"
#include "..\..\..\libthirdparty\msda 2.8\include\msdasc.h"
#include "..\..\..\libthirdparty\msda 2.8\include\oledb.h"
#include "..\..\..\libthirdparty\msda 2.8\include\oledberr.h"
#include "..\..\..\libthirdparty\sqlncli 2008\include\sqlncli.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#define DBINITCONSTANTS ///< OLEDB���n�w�q @ingroup dbmssql
#define INITGUID ///< �w�qGUID @ingroup dbmssql
#define OLEDBVER 0x0270 ///< �w�qOLEDB���� @ingroup dbmssql
#define _SQLNCLI_OLEDB_ ///< �w�qsqlncli @ingroup dbmssql
//-----------------------------------------------------------------------------
/**
 * @brief MSSQL���~���O
 * @ingroup dbmssql
 */
class C_ErrorMSSQL : public C_ErrorBase
{
private:
	//-------------------------------------
	estring m_szError; ///< ���~�r��
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorMSSQL(IN IUnknown *object, IN REFIID refiid);
	virtual ~C_ErrorMSSQL();
	//-------------------------------------
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �j�w������O
 * @ingroup dbmssql
 */
class C_DBMSSQLBind
{
private:
	//-------------------------------------
	std::vector<C_NString> m_ColumnName; ///< ���W�٦C��
	DBBINDING *m_pBindData; ///< �j�w���C����
	unsigned long m_ulColumns; ///< �j�w���ƶq
	unsigned long m_ulRowSize; ///< �@��O���һݪ��j�p
	//-------------------------------------

public:
	//-------------------------------------
	C_DBMSSQLBind();
	virtual ~C_DBMSSQLBind();
	//-------------------------------------
	/**
	 * @brief �إ߸j�w�����
	 * @return true��ܫإߦ��\, false�h�_
	 */
	bool Create(IN C_ICom<IColumnsInfo> &ccIColumnsInfo);
	/**
	 * @brief ���o�j�w���C�����
	 * @return �j�w���C�����
	 */
	const DBBINDING *GetColumnData() const;
	/**
	 * @brief ���o�j�w��쪺�W��
	 * @param ulColumnID ���s��
	 * @return ���W��
	 */
	nstring GetColumnName(IN unsigned long ulColumnID) const;
	/**
	 * @brief ���o�j�w��쪺��Ʀ첾��
	 * @param ulColumnID ���s��
	 * @return ��Ʀ첾��
	 */
	unsigned long GetValueOfs(IN unsigned long ulColumnID) const;
	/**
	 * @brief ���o�j�w���ƶq
	 * @return �j�w���ƶq
	 */
	unsigned long GetColumns() const;
	/**
	 * @brief ���o�@��O���һݪ��j�p
	 * @return �@��O���һݪ��j�p
	 */
	unsigned long GetRowSize() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief MSSQL��Ʈw���O, �ϥ�OLEDB
 * @ingroup dbmssql
 */
class C_DBMSSQL : public C_DBase
{
public:
	//-------------------------------------
	static const nstring m_szType; ///< ��Ʈw���A�r��
	//-------------------------------------

private:
	//-------------------------------------
	C_ICom<ICommandText> m_ccCommand; ///< ����R�O����
	//-------------------------------------
	nstring m_szDBAddr; ///< ��Ʈw��}
	nstring m_szDBName; ///< ��Ʈw�W��
	nstring m_szUserID; ///< �ϥΪ̱b��
	nstring m_szPassword; ///< ��Ʈw�K�X
	bool m_bReconnect; ///< ���s�X��
	unsigned long m_ulUpdateTime; ///< ��s�ɶ�
	//-------------------------------------

private:
	//-------------------------------------
	/**
	 * @brief ���Ʈw�s�u
	 * @param szDBAddr ��Ʈw��}
	 * @param szDBName ��Ʈw�W��
	 * @param szUserID ��Ʈw�b��
	 * @param szPassword ��Ʈw�K�X
	 * @param bReConnect �۰ʭ��s�X��
	 * @return true��ܳs�u���\, false�h�_
	 */
	bool DBConnect(IN const nstring &szDBAddr, IN const nstring &szDBName, IN const nstring &szUserID, IN const nstring &szPassword, IN bool bReConnect);
	/**
	 * @brief ���Ʈw�_�u
	 * @return true��ܰ��榨�\, false�h�_
	 */
	bool DBDisconnect();
	/**
	 * @brief �w�ɳB�z
	 * @return true��ܰ��榨�\, false�h�_
	 */
	bool DBProcess();
	/**
	 * @brief �P��Ʈw�O�_�s�u��
	 * @return true��ܰ���s�u��, false�h�_
	 */
	bool DBIsConnect();
	/**
	 * @brief ����R�O
	 * @param szCommand SQL�y�y
	 * @param pStore ���浲�G����
	 * @return true��ܰ��榨�\, false�h�_
	 */
	bool DBExecute(IN const nstring &szCommand, OUT C_DBStore *pStore = nullptr);
	/**
	 * @brief ���o��Ʈw��}
	 * @return ��Ʈw��}
	 */
	nstring DBAddr() const;
	/**
	 * @brief ���o��Ʈw�W��
	 * @return ��Ʈw�W��
	 */
	nstring DBName() const;
	//-------------------------------------

public:
	//-------------------------------------
	C_DBMSSQL();
	virtual ~C_DBMSSQL();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------