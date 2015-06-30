/**
 * @file command.h
 * @note �R�O�ե�
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
 * @brief �R�O�������O
 */
class C_CommandKey
{
private:
	//-------------------------------------
	cstring m_szServer; ///< ���A���W��
	cstring m_szName; ///< �ѧO�W��
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
	 * @brief ���o���ަr��
	 * @return ���ަr��
	 */
	cstring Key() const
	{
		return m_szServer + __T(":") + m_szName;
	};
	/**
	 * @brief ���o���A���W��
	 * @return ���A���W��
	 */
	cstring Server() const
	{
		_G_();

		return m_szServer;
	};
	/**
	 * @brief ���o�ѧO�W��
	 * @return �ѧO�W��
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
 * @brief �R�O�������O
 */
class C_CommandInterface
{
public:
	//-------------------------------------
	C_CommandInterface() {};
	virtual ~C_CommandInterface() {};
	//-------------------------------------
	/**
	 * @brief ����R�O�B�z
	 * @param ccArgv �Ѽƪ���
	 * @return ���G�r��
	 */
	virtual cstring Execute(IN const C_Argv &ccArgv) = 0;
	/**
	 * @brief ���o�����r��
	 * @return �����r��
	 */
	virtual cstring Help() const = 0;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �@��R�O���O
 */
class C_CommandGeneral : public C_CommandInterface
{
public:
	//-------------------------------------
	typedef cstring (*LPFN_Command) (IN const C_Argv &); ///< �R�O�禡����
	//-------------------------------------

private:
	//-------------------------------------
	cstring m_szHelp; ///< �����r��
	LPFN_Command m_pfCommand; ///< �R�O�禡����
	//-------------------------------------

public:
	//-------------------------------------
	C_CommandGeneral(IN const cstring &help, IN LPFN_Command command) : m_szHelp(help), m_pfCommand(command) {};
	virtual ~C_CommandGeneral() {};
	//-------------------------------------
	/**
	 * @brief ����R�O�B�z
	 * @param ccArgv �Ѽƪ���
	 * @return ���G�r��
	 */
	cstring Execute(IN const C_Argv &ccArgv)
	{
		_G_();

		return m_pfCommand ? m_pfCommand(ccArgv) : __T("command null");
	};
	/**
	 * @brief ���o�����r��
	 * @return �����r��
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
 * @brief �x�ΩR�O���O
 */
template<typename O> class C_CommandTemplate : public C_CommandInterface
{
public:
	//-------------------------------------
	typedef cstring (O::*LPFN_Command) (IN const C_Argv &); ///< �R�O�禡����
	//-------------------------------------

private:
	//-------------------------------------
	cstring m_szHelp; ///< �����r��
	LPFN_Command m_pfCommand; ///< �R�O�禡����
	O *m_pObject; ///< �B�z�������
	//-------------------------------------

public:
	//-------------------------------------
	C_CommandTemplate(IN const cstring &help, IN LPFN_Command command, IN O &object) : m_szHelp(help), m_pfCommand(command), m_pObject(&object) {};
	virtual ~C_CommandTemplate() {};
	//-------------------------------------
	/**
	 * @brief ����R�O�B�z
	 * @param ccArgv �Ѽƪ���
	 * @return ���G�r��
	 */
	cstring Execute(IN const C_Argv &ccArgv)
	{
		_G_();

		return m_pObject && m_pfCommand ? (m_pObject->*m_pfCommand)(ccArgv) : __T("command null");
	};
	/**
	 * @brief ���o�����r��
	 * @return �����r��
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
 * @brief �R�O���O
 */
class C_Command
{
private:
	//-------------------------------------
	std::map<C_CommandKey, C_CommandInterface *> m_Data; ///< �R�O�C�� <���ު���, �R�O����>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_Command();
	virtual ~C_Command();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W�R�O(�R�A�禡����)
	 * @param ccKey ���ު���
	 * @param szHelp �����r��
	 * @param pfCommand �R�O�禡����
	 * @return true��ܦ��\, false�h�_
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
	 * @brief �s�W�R�O(�����禡����)
	 * @param ccKey ���ު���
	 * @param szHelp �����r��
	 * @param pfCommand �R�O�禡����
	 * @param Object �B�z����
	 * @return true��ܦ��\, false�h�_
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
	 * @brief ����R�O�B�z
	 * @param szServer ���A���W��
	 * @param ccControl �����
	 * @param ccOutput ��X����
	 */
	void Execute(IN const cstring &szServer, IN C_Control &ccControl, IN C_Output &ccOutput);
	/**
	 * @brief ���o�����C��
	 * @param szServer ���A���W��
	 * @return �����C��
	 */
	std::map<cstring, cstring> Record(IN const cstring &szServer) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------