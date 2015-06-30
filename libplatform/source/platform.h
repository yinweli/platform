/**
 * @file platform.h
 * @note 平台組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _PLATFORM
#define _PLATFORM
//-----------------------------------------------------------------------------
const cstring TYPE_FILE = __T("file"); ///< 設定型態 - 檔案
const cstring TYPE_JSON = __T("json"); ///< 設定型態 - json字串
const cstring FILE_LOGERROR = __T("error"); ///< 檔名 - 錯誤紀錄
const cstring FILE_LOGOUTPUT = __T("output"); ///< 檔名 - 訊息紀錄
const cstring DIR_CRASHREPORT = __T("crashreport"); ///< 資料夾 - 崩潰紀錄
const cstring DIR_DBF = __T("dbf"); ///< 資料夾 - dbf
const cstring DIR_LOG = __T("log"); ///< 資料夾 - 紀錄
const cstring EXT_DBF = __T("dbf"); ///< 副檔名 - dbf
const cstring EXT_LOG = __T("log"); ///< 副檔名 - 紀錄
//-----------------------------------------------------------------------------
unsigned int __stdcall ThreadOutput(IN void *pParam);
//-----------------------------------------------------------------------------
/**
 * @brief 平台類別
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
	gcroot<Setup::Setup ^> m_Setup; ///< 設定物件
	//-------------------------------------
	C_BMData m_ccBMData; ///< 效能物件
	C_Command m_ccCommand; ///< 命令物件
	C_Component m_ccComponent; ///< 元件物件
	C_Control m_ccControl; ///< 控制物件
	C_Database m_ccDatabase; ///< 資料庫物件
	C_DBF m_ccDBF; ///< dbf物件
	C_Event m_ccEvent; ///< 事件物件
	C_Handle m_ccHandle; ///< 定時處理物件
	C_Network m_ccNetwork; ///< 網路物件
	C_Output m_ccOutput; ///< 輸出物件
	C_Packet m_ccPacket; ///< 封包處理物件
	C_Record m_ccRecord; ///< 封包紀錄物件
	C_Server m_ccServer; ///< 伺服器物件
	C_ThreadMgr m_ccThread; ///< 執行緒物件
	//-------------------------------------

private:
	//-------------------------------------
	/**
	 * @brief 取得設定物件
	 * @retrun 設定物件
	 */
	Setup::Setup ^GetSetup();
	/**
	 * @brief 取得效能物件
	 * @return 效能物件
	 */
	C_BMData &GetBMData();
	/**
	 * @brief 取得命令物件
	 * @return 命令物件
	 */
	C_Command &GetCommand();
	/**
	 * @brief 取得元件物件
	 * @return 元件物件
	 */
	C_Component &GetComponent();
	/**
	 * @brief 取得控制物件
	 * @return 控制物件
	 */
	C_Control &GetControl();
	/**
	 * @brief 取得資料庫物件
	 * @return 資料庫物件
	 */
	C_Database &GetDatabase();
	/**
	 * @brief 取得dbf物件
	 * @return dbf物件
	 */
	C_DBF &GetDBF();
	/**
	 * @brief 取得事件物件
	 * @return 事件物件
	 */
	C_Event &GetEvent();
	/**
	 * @brief 取得定時處理物件
	 * @return 定時處理物件
	 */
	C_Handle &GetHandle();
	/**
	 * @brief 取得網路物件
	 * @return 網路物件
	 */
	C_Network &GetNetwork();
	/**
	 * @brief 取得輸出物件
	 * @return 輸出物件
	 */
	C_Output &GetOutput();
	/**
	 * @brief 取得封包處理物件
	 * @return 封包處理物件
	 */
	C_Packet &GetPacket();
	/**
	 * @brief 取得封包紀錄物件
	 * @return 封包紀錄物件
	 */
	C_Record &GetRecord();
	/**
	 * @brief 取得伺服器物件
	 * @return 伺服器物件
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
	 * @brief 初始化
	 * @param argc 參數數量
	 * @param argv 參數列表
	 * @return true表示成功, false則否
	 */
	bool Initialize(IN int argc, IN char *argv[]);
	/**
	 * @brief 釋放
	 */
	void Release();
	/**
	 * @brief 定時處理
	 * @return true表示繼續執行, false則否
	 */
	bool Process();
	/**
	 * @brief 取得平台名稱
	 * @return 平台名稱
	 */
	cstring GetName();
	/**
	 * @brief 取得版本字串
	 * @return 版本字串
	 */
	cstring GetVersion();
	//-------------------------------------
	/**
	 * @brief 新增組裝
	 * @return true表示成功, false則否
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