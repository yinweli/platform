/**
 * @file server.h
 * @note ���A���ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _SERVER
#define _SERVER
//-----------------------------------------------------------------------------
/**
 * @brief ���A���������O
 */
class C_ServerObj
{
private:
	//-------------------------------------
	cstring m_szServer; ///< ���A���W��
	//-------------------------------------
	C_ThreadMgr m_ccThread; ///< ���������
	//-------------------------------------

private:
	//-------------------------------------
	/**
	 * @brief ��ܮį��T
	 * @param ccArgv �R�O�Ѽ�
	 * @return ���G�r��
	 */
	cstring Cmd_Benchmark(IN const C_Argv &ccArgv);
	/**
	 * @brief �ܧ�R�O�ؼ�
	 * @param ccArgv �R�O�Ѽ�
	 * @return ���G�r��
	 */
	cstring Cmd_Change(IN const C_Argv &ccArgv);
	/**
	 * @brief ��ܤ����T
	 * @param ccArgv �R�O�Ѽ�
	 * @return ���G�r��
	 */
	cstring Cmd_Component(IN const C_Argv &ccArgv);
	/**
	 * @brief ��ܸ�Ʈw��T
	 * @param ccArgv �R�O�Ѽ�
	 * @return ���G�r��
	 */
	cstring Cmd_Database(IN const C_Argv &ccArgv);
	/**
	 * @brief ���dbf��T
	 * @param ccArgv �R�O�Ѽ�
	 * @return ���G�r��
	 */
	cstring Cmd_DBF(IN const C_Argv &ccArgv);
	/**
	 * @brief ��ܨƥ��T
	 * @param ccArgv �R�O�Ѽ�
	 * @return ���G�r��
	 */
	cstring Cmd_Event(IN const C_Argv &ccArgv);
	/**
	 * @brief ��ܩw�ɳB�z��T
	 * @param ccArgv �R�O�Ѽ�
	 * @return ���G�r��
	 */
	cstring Cmd_Handle(IN const C_Argv &ccArgv);
	/**
	 * @brief ��ܩR�O����
	 * @param ccArgv �R�O�Ѽ�
	 * @return ���G�r��
	 */
	cstring Cmd_Help(IN const C_Argv &ccArgv);
	/**
	 * @brief ��ܩR�O�ؼ�
	 * @param ccArgv �R�O�Ѽ�
	 * @return ���G�r��
	 */
	cstring Cmd_List(IN const C_Argv &ccArgv);
	/**
	 * @brief ��ܫȤ�ݺ�����T
	 * @param ccArgv �R�O�Ѽ�
	 * @return ���G�r��
	 */
	cstring Cmd_NetClient(IN const C_Argv &ccArgv);
	/**
	 * @brief ��ܦ��A��������T
	 * @param ccArgv �R�O�Ѽ�
	 * @return ���G�r��
	 */
	cstring Cmd_NetServer(IN const C_Argv &ccArgv);
	/**
	 * @brief ��ܫʥ]�B�z��T
	 * @param ccArgv �R�O�Ѽ�
	 * @return ���G�r��
	 */
	cstring Cmd_Packet(IN const C_Argv &ccArgv);
	/**
	 * @brief ��ܫʥ]������T
	 * @param ccArgv �R�O�Ѽ�
	 * @return ���G�r��
	 */
	cstring Cmd_Record(IN const C_Argv &ccArgv);
	//-------------------------------------

public:
	//-------------------------------------
	C_ServerObj(IN const cstring &server);
	virtual ~C_ServerObj();
	//-------------------------------------
	/**
	 * @brief ��l��
	 * @param Setup �]�w����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Initialize(IN Setup::SServer ^Setup);
	/**
	 * @brief ����
	 */
	void Release();
	/**
	 * @brief �w�ɳB�z
	 * @return true����~�����, false�h�_
	 */
	bool Process();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief ���A�����O
 */
class C_Server
{
private:
	//-------------------------------------
	std::map<cstring, C_ServerObj *> m_Data; ///< ���A���C�� <���A���W��, ���A������>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_Server();
	virtual ~C_Server();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W���A��
	 * @param Setup �]�w����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Add(IN Setup::SServer ^Setup);
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------