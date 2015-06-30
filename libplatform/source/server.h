/**
 * @file server.h
 * @note 伺服器組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _SERVER
#define _SERVER
//-----------------------------------------------------------------------------
/**
 * @brief 伺服器物件類別
 */
class C_ServerObj
{
private:
	//-------------------------------------
	cstring m_szServer; ///< 伺服器名稱
	//-------------------------------------
	C_ThreadMgr m_ccThread; ///< 執行緒物件
	//-------------------------------------

private:
	//-------------------------------------
	/**
	 * @brief 顯示效能資訊
	 * @param ccArgv 命令參數
	 * @return 結果字串
	 */
	cstring Cmd_Benchmark(IN const C_Argv &ccArgv);
	/**
	 * @brief 變更命令目標
	 * @param ccArgv 命令參數
	 * @return 結果字串
	 */
	cstring Cmd_Change(IN const C_Argv &ccArgv);
	/**
	 * @brief 顯示元件資訊
	 * @param ccArgv 命令參數
	 * @return 結果字串
	 */
	cstring Cmd_Component(IN const C_Argv &ccArgv);
	/**
	 * @brief 顯示資料庫資訊
	 * @param ccArgv 命令參數
	 * @return 結果字串
	 */
	cstring Cmd_Database(IN const C_Argv &ccArgv);
	/**
	 * @brief 顯示dbf資訊
	 * @param ccArgv 命令參數
	 * @return 結果字串
	 */
	cstring Cmd_DBF(IN const C_Argv &ccArgv);
	/**
	 * @brief 顯示事件資訊
	 * @param ccArgv 命令參數
	 * @return 結果字串
	 */
	cstring Cmd_Event(IN const C_Argv &ccArgv);
	/**
	 * @brief 顯示定時處理資訊
	 * @param ccArgv 命令參數
	 * @return 結果字串
	 */
	cstring Cmd_Handle(IN const C_Argv &ccArgv);
	/**
	 * @brief 顯示命令說明
	 * @param ccArgv 命令參數
	 * @return 結果字串
	 */
	cstring Cmd_Help(IN const C_Argv &ccArgv);
	/**
	 * @brief 顯示命令目標
	 * @param ccArgv 命令參數
	 * @return 結果字串
	 */
	cstring Cmd_List(IN const C_Argv &ccArgv);
	/**
	 * @brief 顯示客戶端網路資訊
	 * @param ccArgv 命令參數
	 * @return 結果字串
	 */
	cstring Cmd_NetClient(IN const C_Argv &ccArgv);
	/**
	 * @brief 顯示伺服器網路資訊
	 * @param ccArgv 命令參數
	 * @return 結果字串
	 */
	cstring Cmd_NetServer(IN const C_Argv &ccArgv);
	/**
	 * @brief 顯示封包處理資訊
	 * @param ccArgv 命令參數
	 * @return 結果字串
	 */
	cstring Cmd_Packet(IN const C_Argv &ccArgv);
	/**
	 * @brief 顯示封包紀錄資訊
	 * @param ccArgv 命令參數
	 * @return 結果字串
	 */
	cstring Cmd_Record(IN const C_Argv &ccArgv);
	//-------------------------------------

public:
	//-------------------------------------
	C_ServerObj(IN const cstring &server);
	virtual ~C_ServerObj();
	//-------------------------------------
	/**
	 * @brief 初始化
	 * @param Setup 設定物件
	 * @return true表示成功, false則否
	 */
	bool Initialize(IN Setup::SServer ^Setup);
	/**
	 * @brief 釋放
	 */
	void Release();
	/**
	 * @brief 定時處理
	 * @return true表示繼續執行, false則否
	 */
	bool Process();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 伺服器類別
 */
class C_Server
{
private:
	//-------------------------------------
	std::map<cstring, C_ServerObj *> m_Data; ///< 伺服器列表 <伺服器名稱, 伺服器指標>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_Server();
	virtual ~C_Server();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 新增伺服器
	 * @param Setup 設定物件
	 * @return true表示成功, false則否
	 */
	bool Add(IN Setup::SServer ^Setup);
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------