//-----------------------------------------------------------------------------
#include "_include.h"
#include "platform.h"
//-----------------------------------------------------------------------------
// 取得dbf檔名路徑
cstring FilePathDBF(IN const cstring &szName)
{
	_G_();

	return DIR_DBF + __T("\\") + szName + __T(".") + EXT_DBF;
}
//-----------------------------------------------------------------------------
// 取得紀錄檔名路徑
cstring FilePathLog(IN const cstring &szName)
{
	_G_();

	return GetDateFormatPath(DIR_LOG, szName + __T(".") + EXT_LOG, true, true, false, true, false);
}
//-----------------------------------------------------------------------------
// 取得crash report錯誤字串
cstring GetCrashReportError()
{
	TCHAR szError[512];

	crGetLastErrorMsg(szError, 512);

	return szError;
}
//-----------------------------------------------------------------------------
// crash report function
int CALLBACK CrashReport(CR_CRASH_CALLBACK_INFO *pInfo)
{
	C_CallFuncLog::Instance().Get(DIR_CRASHREPORT);

	return CR_CB_DODEFAULT;
}
//-----------------------------------------------------------------------------
// 訊息輸出執行緒
unsigned int __stdcall ThreadOutput(IN void *pParam)
{
	_G_();

	// 建立執行緒物件
	C_ThreadObj ccThread(pParam);

	if(ccThread == false)
		return 0;

	while(ccThread.IsShutdown() == false)
	{
		// libnonstandard錯誤輸出
		{
			estring szTemp = C_NOutput::Instance().Get();

			if(szTemp.empty() == false)
			{
				szTemp += __T("\n");
				fwritestr(FilePathLog(FILE_LOGERROR), true, szTemp);
				printfex(FOREGROUND_INTENSITY | FOREGROUND_RED, szTemp);
			}//if
		}

		// libcsnstandard錯誤輸出
		{
			cstring szTemp = LibCSNStandard::Output::Get();

			if(szTemp.empty() == false)
			{
				szTemp += __T("\n");
				fwritestr(FilePathLog(FILE_LOGERROR), true, szTemp);
				printfex(FOREGROUND_INTENSITY | FOREGROUND_RED, szTemp);
			}//if
		}

		// 訊息輸出
		{
			cstring szTemp = C_Platform::Instance().GetOutput().Get();

			if(szTemp.empty() == false)
			{
				szTemp += __T("\n");
				fwritestr(FilePathLog(FILE_LOGOUTPUT), true, szTemp);
				printfex(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, szTemp);
			}//if
		}

		Sleep(10); // 這裡的睡眠是為了把控制權交還給作業系統, 避免造成作業系統停止回應
	}//while

	return 0;
}
//-----------------------------------------------------------------------------
C_Platform &C_Platform::Instance()
{
	_G_();

	static C_Platform ccPlatform;

	return ccPlatform;
}
//-----------------------------------------------------------------------------
C_Platform::C_Platform() : m_Setup(nullptr) {}
//-----------------------------------------------------------------------------
// 初始化
bool C_Platform::Initialize(IN int argc, IN char *argv[])
{
	_G_();

	CoInitialize(nullptr); // 初始化COM
	InitMemDbg(DIR_LOG); // 設定檢查記憶體洩漏
	XSocketInitialize(nullptr); // 初始化Winsock

	// 建立訊息輸出執行緒
	if(m_ccThread.Create(ThreadOutput) == false)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create output thread failed"));

	C_ConsoleArgv ccConsoleArgv(argc, argv);

	if(ccConsoleArgv.size() < 3)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("argument failed [type(") + TYPE_FILE + __T("/") + TYPE_JSON + __T("), data(filepath/json string)]"));

	// 建立設定物件
	{
		cstring szType = ccConsoleArgv.get(1);
		cstring szSetup;

		if(szType == TYPE_FILE && freadstr(ccConsoleArgv.get(2), szSetup.toref()) == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("read setup file failed"));

		if(szType == TYPE_JSON)
			szSetup = ccConsoleArgv.get(2);

		if(szSetup.empty() == false)
			m_Setup = LibCSNStandard::Json::ToObject<Setup::Setup ^>(szSetup.tostring());

		if((Setup::Setup ^)m_Setup == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("setup failed"));

		m_ccOutput.Add(__T("platform name [") + GetName() + __T("]"));
		m_ccOutput.Add(__T("platform version [") + GetVersion() + __T("]"));
	}

	m_ccOutput.Add(__T("platform [") + GetName() + __T("] initialize"));

	// 安裝crash report
	{
		cstring szName = GetName();
		cstring szVersion = GetVersion();
		CR_INSTALL_INFO sInfo;

		memset(&sInfo, 0, sizeof(CR_INSTALL_INFO));

		sInfo.cb = sizeof(CR_INSTALL_INFO);
		sInfo.pszAppName = szName.c_str();
		sInfo.pszAppVersion = szVersion.c_str();
		sInfo.pszErrorReportSaveDir = DIR_CRASHREPORT.c_str();
		sInfo.pszRestartCmdLine = nullptr;
		sInfo.dwFlags = CR_INST_ALL_POSSIBLE_HANDLERS | CR_INST_NO_GUI | CR_INST_DONT_SEND_REPORT | CR_INST_APP_RESTART | CR_INST_AUTO_THREAD_HANDLERS;

		if(crInstall(&sInfo) != 0)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("install crash report failed(") + GetCrashReportError() + __T(")"));

		if(crSetCrashCallback(CrashReport, nullptr) != 0)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("set crash report callback failed(") + GetCrashReportError() + __T(")"));

		m_ccOutput.Add(__T("install crash report"));
	}

	// 建立dbf
	{
		for(int iPos = 0, iMax = m_Setup->DBF->Length; iPos < iMax; ++iPos)
		{
			cstring szName = m_Setup->DBF[iPos]->Name;
			cstring szClass = m_Setup->DBF[iPos]->Class;
			cstring szComponent = m_Setup->DBF[iPos]->Component;

			if(m_ccDBF.Add(szName, szClass, szComponent, FilePathDBF(szName)))
				m_ccOutput.Add(__T("add dbf [") + szName + __T("]"));
			else
				return C_NOutput::Instance().Error(ERRORNSTD, __T("add dbf failed(") + szName + __T(")"));
		}//for
	}

	// 建立資料庫
	{
		for(int iPos = 0, iMax = m_Setup->Database->Length; iPos < iMax; ++iPos)
		{
			cstring szName = m_Setup->Database[iPos]->Name;
			cstring szType = m_Setup->Database[iPos]->Type;
			cstring szDBAddr = m_Setup->Database[iPos]->DBAddr;
			cstring szDBName = m_Setup->Database[iPos]->DBName;
			cstring szUserID = m_Setup->Database[iPos]->UserID;
			cstring szPassword = m_Setup->Database[iPos]->Password;

			if(m_ccDatabase.Add(szName, szType, szDBAddr, szDBName, szUserID, szPassword))
				m_ccOutput.Add(__T("add database [") + szName + __T("]"));
			else
				return C_NOutput::Instance().Error(ERRORNSTD, __T("add database failed(") + szName + __T(")"));
		}//for
	}

	// 建立伺服器
	{
		for(int iPos = 0, iMax = m_Setup->Server->Length; iPos < iMax; ++iPos)
		{
			cstring szName = m_Setup->Server[iPos]->Name;

			if(m_ccServer.Add(m_Setup->Server[iPos]))
			{
				m_ccControl.Set(szName);
				m_ccOutput.Add(__T("add server [") + szName + __T("]"));
			}
			else
				return C_NOutput::Instance().Error(ERRORNSTD, __T("add server failed(") + szName + __T(")"));
		}//for
	}

	m_ccOutput.Add(__T("platform [") + GetName() + __T("] initialize success"));
	SetConsoleWindowTile(GetName(), GetVersion(), ccConsoleArgv.ExePath());

	return true;
}
//-----------------------------------------------------------------------------
// 釋放
void C_Platform::Release()
{
	_G_();

	m_ccThread.Shutdown();

	while(m_ccThread.Size() > 0)
		Sleep(100);

	crUninstall();
	XSocketRelease();
	CoUninitialize();
}
//-----------------------------------------------------------------------------
// 定時處理
bool C_Platform::Process()
{
	_G_();

	m_ccBMData.Process();
	m_ccControl.Process();
	m_ccDatabase.Process();

	return true;
}
//-----------------------------------------------------------------------------
// 取得平台名稱
cstring C_Platform::GetName()
{
	_G_();

	return (Setup::Setup ^)m_Setup != nullptr ? m_Setup->Name : __T("");
}
//-----------------------------------------------------------------------------
// 取得版本字串
cstring C_Platform::GetVersion()
{
	_G_();

	return (Setup::Setup ^)m_Setup != nullptr ? m_Setup->Version : __T("");
}
//-----------------------------------------------------------------------------
// 取得設定物件
Setup::Setup ^C_Platform::GetSetup()
{
	_G_();

	return m_Setup;
}
//-----------------------------------------------------------------------------
// 取得效能物件
C_BMData &C_Platform::GetBMData()
{
	_G_();

	return m_ccBMData;
}
//-----------------------------------------------------------------------------
// 取得命令物件
C_Command &C_Platform::GetCommand()
{
	_G_();

	return m_ccCommand;
}
//-----------------------------------------------------------------------------
// 取得元件物件
C_Component &C_Platform::GetComponent()
{
	_G_();

	return m_ccComponent;
}
//-----------------------------------------------------------------------------
// 取得控制物件
C_Control &C_Platform::GetControl()
{
	_G_();

	return m_ccControl;
}
//-----------------------------------------------------------------------------
// 取得資料庫物件
C_Database &C_Platform::GetDatabase()
{
	_G_();

	return m_ccDatabase;
}
//-----------------------------------------------------------------------------
// 取得dbf物件
C_DBF &C_Platform::GetDBF()
{
	_G_();

	return m_ccDBF;
}
//-----------------------------------------------------------------------------
// 取得事件物件
C_Event &C_Platform::GetEvent()
{
	_G_();

	return m_ccEvent;
}
//-----------------------------------------------------------------------------
// 取得定時處理物件
C_Handle &C_Platform::GetHandle()
{
	_G_();

	return m_ccHandle;
}
//-----------------------------------------------------------------------------
// 取得網路物件
C_Network &C_Platform::GetNetwork()
{
	_G_();

	return m_ccNetwork;
}
//-----------------------------------------------------------------------------
// 取得輸出物件
C_Output &C_Platform::GetOutput()
{
	_G_();

	return m_ccOutput;
}
//-----------------------------------------------------------------------------
// 取得封包處理物件
C_Packet &C_Platform::GetPacket()
{
	_G_();

	return m_ccPacket;
}
//-----------------------------------------------------------------------------
// 取得封包紀錄物件
C_Record &C_Platform::GetRecord()
{
	_G_();

	return m_ccRecord;
}
//-----------------------------------------------------------------------------
// 取得伺服器物件
C_Server &C_Platform::GetServer()
{
	_G_();

	return m_ccServer;
}
//-----------------------------------------------------------------------------