/**
 * @file dbmysql.h
 * @note MySQL��Ʈw
 * @author yinweli
 */
/**
 * @page �p��ϥ�dbmysql
 * dbmysql�O�ӥΩ�PMySQL��Ʈw�s�u������\n\n
 * �n�إ�dbmysql�����H C_DBMySQL �إ߹���\n\n
 * C_DBMySQL ccDB;\n\n
 * �M��I�s C_DBMySQL.Connect() ���Ʈw�s�u\n
 * �s�u���\�ᥲ�����_�I�s C_DBMySQL.Process() �禡���������B�@\n
 * �ϥΧ�����i�H�I�s C_DBMySQL.Disconnect() ���Ʈw�_�u\n\n
 * �n����SQL�y�y, �u�n�I�s C_DBMySQL.Execute() �禡����R�O�è��o���G\n\n
 * --------------------------------------------------\n
 * Header           : dbmysql.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref dbmysql\n
 */
/** @defgroup dbmysql */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _DBMYSQL
#define _DBMYSQL
//-----------------------------------------------------------------------------
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "..\\libthirdparty\\mysql-connector-c-6.1.5-win32\\lib\\libmysql.lib")
//-----------------------------------------------------------------------------
#define _WINSOCK2_ ///< �w�q�ϥ� winsock2.h �Ӥ��ϥ� windows.h
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\benchmark\benchmark.h"
#include "..\dbase\dbase.h"
#include "..\dbstore\dbstore.h"
#include "..\..\..\libthirdparty\mysql-connector-c-6.1.5-win32\include\mysql.h" ///< �]�����ݭnwinsock, �ҥH��b_nstd.h���ޤJ�ɤ���
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief MySQL���~���O
 * @ingroup dbmysql
 */
class C_ErrorMySQL : public C_ErrorBase
{
private:
	//-------------------------------------
	estring m_szError; ///< ���~�r��
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorMySQL(IN MYSQL *mysql);
	virtual ~C_ErrorMySQL();
	//-------------------------------------
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief MySQL��Ʈw���O, �ϥ�OLEDB
 * @ingroup dbmysql
 */
class C_DBMySQL : public C_DBase
{
public:
	//-------------------------------------
	static const nstring m_szType; ///< ��Ʈw���A�r��
	//-------------------------------------

private:
	//-------------------------------------
	MYSQL *m_pMySQL; ///< MySQL�������
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
	C_DBMySQL();
	virtual ~C_DBMySQL();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------