/**
 * @file dbsqlite.h
 * @note SQLite��Ʈw
 * @author yinweli
 */
/**
 * @page �p��ϥ�dbsqlite
 * dbsqlite�O�ӥΩ�Q�ΰO����إ߸�Ʈw�\�઺����\n\n
 * �n�إ�dbsqlite�����H C_DBSQLite �إ߹���\n\n
 * C_DBSQLite ccDB;\n\n
 * �M��I�s C_DBSQLite.Open() �禡�ӱҰʸ�Ʈw\n
 * �Ұʮɥi�H��ܵ�����Ʈw�@���ɦW���|, dbsqlite�|���Ʈw���e�O���쨺���ɮ׸�, �U���b�H���ɮ׶}�Ҹ�Ʈw, �|Ū���ɮפ�����ƭ��ظ�Ʈw\n
 * �Y�O�������W��, �h����Ʈw�u�|�s�b�O���餤\n
 * �ϥΧ�����i�H�I�s C_DBSQLite.Close() ������Ʈw\n
 * �n����SQL�y�y, �u�n�I�s C_DBSQLite.Execute() �禡����R�O�è��o���G\n\n
 * --------------------------------------------------\n
 * Header           : dbsqlite.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref dbsqlite\n
 */
/** @defgroup dbsqlite */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _DBSQLITE
#define _DBSQLITE
//-----------------------------------------------------------------------------
#ifdef _DEBUG
#pragma comment(lib, "..\\libthirdparty\\sqlite 3.8.7.4\\vc2013_lib_debug\\sqlite_debug.lib")
#else
#pragma comment(lib, "..\\libthirdparty\\sqlite 3.8.7.4\\vc2013_lib_release\\sqlite_release.lib")
#endif
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\benchmark\benchmark.h"
#include "..\dbase\dbase.h"
#include "..\dbstore\dbstore.h"
#include "..\..\..\libthirdparty\sqlite 3.8.7.4\include\sqlite3.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief SQLite���~���O
 * @ingroup dbsqlite
 */
class C_ErrorSQLite : public C_ErrorBase
{
private:
	//-------------------------------------
	estring m_szError; ///< ���~�r��
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorSQLite(IN sqlite3 *sqlite);
	virtual ~C_ErrorSQLite();
	//-------------------------------------
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief DBSQLite���O
 * @ingroup dbsqlite
 */
class C_DBSQLite : public C_DBase
{
public:
	//-------------------------------------
	static const nstring m_szType; ///< ��Ʈw���A�r��
	//-------------------------------------

private:
	//-------------------------------------
	sqlite3 *m_pDBObj; ///< ��Ʈw�������
	//-------------------------------------
	nstring m_szDBAddr; ///< ��Ʈw��}
	nstring m_szDBName; ///< ��Ʈw�W��
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
	C_DBSQLite();
	virtual ~C_DBSQLite();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------