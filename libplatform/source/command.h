/**
 * @file command.h
 * @note 命令組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _COMMAND
#define _COMMAND
//-----------------------------------------------------------------------------
class C_Control;
class C_Output;
//-----------------------------------------------------------------------------
/**
 * @brief 命令索引類別
 */
class C_CommandKey
{
private:
	//-------------------------------------
	cstring m_szServer; ///< 伺服器名稱
	cstring m_szName; ///< 識別名稱
	//-------------------------------------

public:
	//-------------------------------------
	C_CommandKey() {};
	C_CommandKey(IN const cstring &server, IN const cstring &name) : m_szServer(server), m_szName(name) {};
	//-------------------------------------
	bool operator < (IN const C_CommandKey &rhs) const
	{
		return Key() < rhs.Key();
	};
	operator bool () const
	{
		return Key().empty() == false;
	};
	//-------------------------------------
	/**
	 * @brief 取得索引字串
	 * @return 索引字串
	 */
	cstring Key() const
	{
		return m_szServer + __T(":") + m_szName;
	};
	/**
	 * @brief 取得伺服器名稱
	 * @return 伺服器名稱
	 */
	cstring Server() const
	{
		_G_();

		return m_szServer;
	};
	/**
	 * @brief 取得識別名稱
	 * @return 識別名稱
	 */
	cstring Name() const
	{
		_G_();

		return m_szName;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 命令介面類別
 */
class C_CommandInterface
{
public:
	//-------------------------------------
	C_CommandInterface() {};
	virtual ~C_CommandInterface() {};
	//-------------------------------------
	/**
	 * @brief 執行命令處理
	 * @param ccArgv 參數物件
	 * @return 結果字串
	 */
	virtual cstring Execute(IN const C_Argv &ccArgv) = 0;
	/**
	 * @brief 取得說明字串
	 * @return 說明字串
	 */
	virtual cstring Help() const = 0;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 一般命令類別
 */
class C_CommandGeneral : public C_CommandInterface
{
public:
	//-------------------------------------
	typedef cstring (*LPFN_Command) (IN const C_Argv &); ///< 命令函式指標
	//-------------------------------------

private:
	//-------------------------------------
	cstring m_szHelp; ///< 說明字串
	LPFN_Command m_pfCommand; ///< 命令函式指標
	//-------------------------------------

public:
	//-------------------------------------
	C_CommandGeneral(IN const cstring &help, IN LPFN_Command command) : m_szHelp(help), m_pfCommand(command) {};
	virtual ~C_CommandGeneral() {};
	//-------------------------------------
	/**
	 * @brief 執行命令處理
	 * @param ccArgv 參數物件
	 * @return 結果字串
	 */
	cstring Execute(IN const C_Argv &ccArgv)
	{
		_G_();

		return m_pfCommand ? m_pfCommand(ccArgv) : __T("command null");
	};
	/**
	 * @brief 取得說明字串
	 * @return 說明字串
	 */
	cstring Help() const
	{
		_G_();

		return m_szHelp;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 泛形命令類別
 */
template<typename O> class C_CommandTemplate : public C_CommandInterface
{
public:
	//-------------------------------------
	typedef cstring (O::*LPFN_Command) (IN const C_Argv &); ///< 命令函式指標
	//-------------------------------------

private:
	//-------------------------------------
	cstring m_szHelp; ///< 說明字串
	LPFN_Command m_pfCommand; ///< 命令函式指標
	O *m_pObject; ///< 處理物件指標
	//-------------------------------------

public:
	//-------------------------------------
	C_CommandTemplate(IN const cstring &help, IN LPFN_Command command, IN O &object) : m_szHelp(help), m_pfCommand(command), m_pObject(&object) {};
	virtual ~C_CommandTemplate() {};
	//-------------------------------------
	/**
	 * @brief 執行命令處理
	 * @param ccArgv 參數物件
	 * @return 結果字串
	 */
	cstring Execute(IN const C_Argv &ccArgv)
	{
		_G_();

		return m_pObject && m_pfCommand ? (m_pObject->*m_pfCommand)(ccArgv) : __T("command null");
	};
	/**
	 * @brief 取得說明字串
	 * @return 說明字串
	 */
	cstring Help() const
	{
		_G_();

		return m_szHelp;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 命令類別
 */
class C_Command
{
private:
	//-------------------------------------
	std::map<C_CommandKey, C_CommandInterface *> m_Data; ///< 命令列表 <索引物件, 命令指標>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_Command();
	virtual ~C_Command();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 新增命令(靜態函式版本)
	 * @param ccKey 索引物件
	 * @param szHelp 說明字串
	 * @param pfCommand 命令函式指標
	 * @return true表示成功, false則否
	 */
	bool Add(IN const C_CommandKey &ccKey, IN const cstring &szHelp, IN C_CommandGeneral::LPFN_Command pfCommand)
	{
		_G_();

		if(ccKey == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

		if(pfCommand == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("command null(") + ccKey.Key() + __T(")"));

		C_ThreadLock ccLock(&m_csCommon);

		if(m_Data.find(ccKey) != m_Data.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + ccKey.Key() + __T(")"));

		C_CommandInterface *pCommand = nstdnew C_CommandGeneral(szHelp, pfCommand);

		if(pCommand == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create command failed(") + ccKey.Key() + __T(")"));

		m_Data[ccKey] = pCommand;

		return true;
	};
	/**
	 * @brief 新增命令(成員函式版本)
	 * @param ccKey 索引物件
	 * @param szHelp 說明字串
	 * @param pfCommand 命令函式指標
	 * @param Object 處理物件
	 * @return true表示成功, false則否
	 */
	template<typename O> bool Add(IN const C_CommandKey &ccKey, IN const cstring &szHelp, IN typename C_CommandTemplate<O>::LPFN_Command pfCommand, IN O &Object)
	{
		_G_();

		if(ccKey == false)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

		if(pfCommand == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("command null(") + ccKey.Key() + __T(")"));

		C_ThreadLock ccLock(&m_csCommon);

		if(m_Data.find(ccKey) != m_Data.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + ccKey.Key() + __T(")"));

		C_CommandInterface *pCommand = nstdnew C_CommandTemplate<O>(szHelp, pfCommand, Object);

		if(pCommand == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create command failed(") + ccKey.Key() + __T(")"));

		m_Data[ccKey] = pCommand;

		return true;
	};
	/**
	 * @brief 執行命令處理
	 * @param szServer 伺服器名稱
	 * @param ccControl 控制物件
	 * @param ccOutput 輸出物件
	 */
	void Execute(IN const cstring &szServer, IN C_Control &ccControl, IN C_Output &ccOutput);
	/**
	 * @brief 取得紀錄列表
	 * @param szServer 伺服器名稱
	 * @return 紀錄列表
	 */
	std::map<cstring, cstring> Record(IN const cstring &szServer) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------