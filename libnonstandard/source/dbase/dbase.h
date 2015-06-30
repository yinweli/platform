/**
 * @file dbase.h
 * @note ��Ʈw��¦����
 * @author yinweli
 */
/**
 * @page �p��ϥ�dbase
 * dbase�O�ӥΩ�����Ʈw�R�O���������O\n\n
 * --------------------------------------------------\n
 * Header           : dbase.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref dbase\n
 */
/** @defgroup dbase */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _DBASE
#define _DBASE
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\argument\argument.h"
#include "..\consoletool\consoletool.h"
#include "..\dbstore\dbstore.h"
#include "..\threadlock\threadlock.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ��Ʈw�����¦���O
 * @ingroup dbase
 */
class C_DBase
{
private:
	//-------------------------------------
	nstring m_szType; ///< ��Ʈw���A
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

protected:
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
	virtual bool DBConnect(IN const nstring &szDBAddr, IN const nstring &szDBName, IN const nstring &szUserID, IN const nstring &szPassword, IN bool bReConnect) = 0;
	/**
	 * @brief ���Ʈw�_�u
	 * @return true��ܰ��榨�\, false�h�_
	 */
	virtual bool DBDisconnect() = 0;
	/**
	 * @brief �w�ɳB�z
	 * @return true��ܰ��榨�\, false�h�_
	 */
	virtual bool DBProcess() = 0;
	/**
	 * @brief �P��Ʈw�O�_�s�u��
	 * @return true��ܰ���s�u��, false�h�_
	 */
	virtual bool DBIsConnect() = 0;
	/**
	 * @brief ����R�O
	 * @param szCommand SQL�y�y
	 * @param pStore ���浲�G����
	 * @return true��ܰ��榨�\, false�h�_
	 */
	virtual bool DBExecute(IN const nstring &szCommand, OUT C_DBStore *pStore = nullptr) = 0;
	/**
	 * @brief ���o��Ʈw��}
	 * @return ��Ʈw��}
	 */
	virtual nstring DBAddr() const = 0;
	/**
	 * @brief ���o��Ʈw�W��
	 * @return ��Ʈw�W��
	 */
	virtual nstring DBName() const = 0;
	//-------------------------------------

public:
	//-------------------------------------
	C_DBase(IN const nstring &type);
	virtual ~C_DBase();
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
	bool Connect(IN const nstring &szDBAddr, IN const nstring &szDBName, IN const nstring &szUserID, IN const nstring &szPassword, IN bool bReConnect);
	/**
	 * @brief ���Ʈw�_�u
	 */
	void Disconnect();
	/**
	 * @brief �w�ɳB�z
	 */
	void Process();
	/**
	 * @brief �P��Ʈw�O�_�s�u��
	 * @return true��ܳs�u��, false�h�_
	 */
	bool IsConnect();
	/**
	 * @brief ����R�O
	 * @param szCommand SQL�y�y
	 * @return true��ܰ��榨�\, false�h�_
	 */
	bool Execute(IN const nstring &szCommand);
	/**
	 * @brief ����R�O
	 * @param szCommand SQL�y�y
	 * @param ccStore ���浲�G
	 * @return true��ܰ��榨�\, false�h�_
	 */
	bool Execute(IN const nstring &szCommand, OUT C_DBStore &ccStore);
	/**
	 * @brief ���o��Ʈw��}
	 * @return ��Ʈw��}
	 */
	nstring Addr() const;
	/**
	 * @brief ���o��Ʈw�W��
	 * @return ��Ʈw�W��
	 */
	nstring Name() const;
	/**
	 * @brief ���o��Ʈw���A�r��
	 * @return ��Ʈw���A�r��
	 */
	nstring Type() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------