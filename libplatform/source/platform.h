/**
 * @file platform.h
 * @note ���x�ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _PLATFORM
#define _PLATFORM
//-----------------------------------------------------------------------------
const cstring TYPE_FILE = __T("file"); ///< �]�w���A - �ɮ�
const cstring TYPE_JSON = __T("json"); ///< �]�w���A - json�r��
const cstring FILE_LOGERROR = __T("error"); ///< �ɦW - ���~����
const cstring FILE_LOGOUTPUT = __T("output"); ///< �ɦW - �T������
const cstring DIR_CRASHREPORT = __T("crashreport"); ///< ��Ƨ� - �Y�����
const cstring DIR_DBF = __T("dbf"); ///< ��Ƨ� - dbf
const cstring DIR_LOG = __T("log"); ///< ��Ƨ� - ����
const cstring EXT_DBF = __T("dbf"); ///< ���ɦW - dbf
const cstring EXT_LOG = __T("log"); ///< ���ɦW - ����
//-----------------------------------------------------------------------------
unsigned int __stdcall ThreadOutput(IN void *pParam);
//-----------------------------------------------------------------------------
/**
 * @brief ���x���O
 */
class C_Platform
{
	//-------------------------------------
	friend C_ObjBenchmark;
	friend C_ObjCommand;
	friend C_ObjComponent;
	friend C_ObjDatabase;
	friend C_ObjDBF;
	friend C_ObjEvent;
	friend C_ObjHandle;
	friend C_ObjNetwork;
	friend C_ObjOutput;
	friend C_ObjPacket;
	friend C_ServerObj;
	friend unsigned int __stdcall ThreadOutput(IN void *pParam);
	//-------------------------------------

private:
	//-------------------------------------
	gcroot<Setup::Setup ^> m_Setup; ///< �]�w����
	//-------------------------------------
	C_BMData m_ccBMData; ///< �įફ��
	C_Command m_ccCommand; ///< �R�O����
	C_Component m_ccComponent; ///< ���󪫥�
	C_Control m_ccControl; ///< �����
	C_Database m_ccDatabase; ///< ��Ʈw����
	C_DBF m_ccDBF; ///< dbf����
	C_Event m_ccEvent; ///< �ƥ󪫥�
	C_Handle m_ccHandle; ///< �w�ɳB�z����
	C_Network m_ccNetwork; ///< ��������
	C_Output m_ccOutput; ///< ��X����
	C_Packet m_ccPacket; ///< �ʥ]�B�z����
	C_Record m_ccRecord; ///< �ʥ]��������
	C_Server m_ccServer; ///< ���A������
	C_ThreadMgr m_ccThread; ///< ���������
	//-------------------------------------

private:
	//-------------------------------------
	/**
	 * @brief ���o�]�w����
	 * @retrun �]�w����
	 */
	Setup::Setup ^GetSetup();
	/**
	 * @brief ���o�įફ��
	 * @return �įફ��
	 */
	C_BMData &GetBMData();
	/**
	 * @brief ���o�R�O����
	 * @return �R�O����
	 */
	C_Command &GetCommand();
	/**
	 * @brief ���o���󪫥�
	 * @return ���󪫥�
	 */
	C_Component &GetComponent();
	/**
	 * @brief ���o�����
	 * @return �����
	 */
	C_Control &GetControl();
	/**
	 * @brief ���o��Ʈw����
	 * @return ��Ʈw����
	 */
	C_Database &GetDatabase();
	/**
	 * @brief ���odbf����
	 * @return dbf����
	 */
	C_DBF &GetDBF();
	/**
	 * @brief ���o�ƥ󪫥�
	 * @return �ƥ󪫥�
	 */
	C_Event &GetEvent();
	/**
	 * @brief ���o�w�ɳB�z����
	 * @return �w�ɳB�z����
	 */
	C_Handle &GetHandle();
	/**
	 * @brief ���o��������
	 * @return ��������
	 */
	C_Network &GetNetwork();
	/**
	 * @brief ���o��X����
	 * @return ��X����
	 */
	C_Output &GetOutput();
	/**
	 * @brief ���o�ʥ]�B�z����
	 * @return �ʥ]�B�z����
	 */
	C_Packet &GetPacket();
	/**
	 * @brief ���o�ʥ]��������
	 * @return �ʥ]��������
	 */
	C_Record &GetRecord();
	/**
	 * @brief ���o���A������
	 * @return ���A������
	 */
	C_Server &GetServer();
	//-------------------------------------

public:
	//-------------------------------------
	static C_Platform &Instance();
	//-------------------------------------
	C_Platform();
	//-------------------------------------
	/**
	 * @brief ��l��
	 * @param argc �ѼƼƶq
	 * @param argv �ѼƦC��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Initialize(IN int argc, IN char *argv[]);
	/**
	 * @brief ����
	 */
	void Release();
	/**
	 * @brief �w�ɳB�z
	 * @return true����~�����, false�h�_
	 */
	bool Process();
	/**
	 * @brief ���o���x�W��
	 * @return ���x�W��
	 */
	cstring GetName();
	/**
	 * @brief ���o�����r��
	 * @return �����r��
	 */
	cstring GetVersion();
	//-------------------------------------
	/**
	 * @brief �s�W�ո�
	 * @return true��ܦ��\, false�h�_
	 */
	template<typename T> bool AddComponent()
	{
		_G_();

		return m_ccComponent.Add<T>();
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------