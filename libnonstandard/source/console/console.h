/**
 * @file console.h
 * @note ����x���O
 * @author yinweli
 */
/**
 * @page �p��ϥ�console
 * console�Ω�B�z����x�Ҧ��U���R�O����L��J�P���\n\n
 * �ϥήɥu�n�ŧi C_Console ������, �����p���� C_Console.Show() �禡, �M��w�ɩI�s C_Console.Process() �禡�Y�i\n
 * �p�G�Q�n���o�ϥΪ̿�J�����O�P�Ѽ�, �I�s C_Console.GetCommand() �禡�|���o�@�Ӧr��, �o�Ӧr��O�ϥΪ̫��Uenter��������r��, ���R�o�Ӧr��N�i�H�F\n\n
 * --------------------------------------------------\n
 * Header           : console.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref console
 */
/** @defgroup console */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef __CONSOLE
#define __CONSOLE
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\actualkeycodes\actualkeycodes.h"
#include "..\algorithm\algorithm.h"
#include "..\consoletool\consoletool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ���O�x�s�C�����O
 * @ingroup console
 */
class C_ConsoleQueue
{
private:
	//-------------------------------------
	std::queue<nstring> m_Data; ///< ���O�x�s�C��
	//-------------------------------------

public:
	//-------------------------------------
	C_ConsoleQueue();
	virtual ~C_ConsoleQueue();
	//-------------------------------------
	/**
	 * @brief �s�W���
	 * @param szData ��Ʀr��
	 */
	void Add(IN const nstring &szData);
	/**
	 * @brief ���o���
	 * @return ��Ʀr��
	 */
	nstring Data();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief ���O���v�C�����O
 * @ingroup console
 */
class C_ConsoleHistory
{
private:
	//-------------------------------------
	std::vector<nstring> m_Data; ///< ���O���v�C��
	unsigned long m_ulPos; ///< ��Ц�m
	//-------------------------------------

public:
	//-------------------------------------
	C_ConsoleHistory();
	virtual ~C_ConsoleHistory();
	//-------------------------------------
	/**
	 * @brief �s�W���
	 * @param szData ��Ʀr��
	 */
	void Add(IN const nstring &szData);
	/**
	 * @brief ��ЦV�e�@�B
	 */
	void Prev();
	/**
	 * @brief ��ЦV��@�B
	 */
	void Next();
	/**
	 * @brief ���o��Щҫ���Ʀr��
	 * @return ��Ʀr��
	 */
	nstring Data() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief ���O�r��޲z���O
 * @ingroup console
 */
class C_ConsoleKBStr
{
private:
	//-------------------------------------
	nstring m_szTitle; ///< ���D�r��
	nstring m_szToken; ///< ���j�r��
	nstring m_szData; ///< ��Ʀr��
	short m_wPos; ///< ��Ц�m
	bool m_bInsert; ///< ���N�X��
	//-------------------------------------

public:
	//-------------------------------------
	C_ConsoleKBStr();
	virtual ~C_ConsoleKBStr();
	//-------------------------------------
	/**
	 * @brief �]�w���D�r��
	 * @param szTitle ��Ʀr��
	 */
	void SetTitle(IN const nstring &szTitle);
	/**
	 * @brief �]�w���j�r��
	 * @param szToken ���j�r��
	 */
	void SetToken(IN const nstring &szToken);
	/**
	 * @brief �M����Ʀr��
	 */
	void ClrData();
	/**
	 * @brief �]�w��Ʀr��
	 * @param szData ��Ʀr��
	 */
	void SetData(IN const nstring &szData);
	/**
	 * @brief ���J��Ʀr��
	 * @param emKey �r���C�|
	 * @param ulMaxChar �̤j�r���ƶq
	 */
	void InsData(IN ENUM_AKCodes emKey, IN unsigned long ulMaxChar);
	/**
	 * @brief �V�e�R���r��
	 */
	void DelPrev();
	/**
	 * @brief �V��R���r��
	 */
	void DelNext();
	/**
	 * @brief ��в��ʨ�̫e
	 */
	void MoveFront();
	/**
	 * @brief ��в��ʨ�̧�
	 */
	void MoveBack();
	/**
	 * @brief ��ЦV�e�@�B
	 */
	void MovePrev();
	/**
	 * @brief ��ЦV��@�B
	 */
	void MoveNext();
	/**
	 * @brief �}�����N�X��
	 */
	void Insert();
	/**
	 * @brief �ˬd�O�_����
	 * @return true��ܬ���, false�h�_
	 */
	bool Empty() const;
	/**
	 * @brief ���o���D�r��
	 * @return ���D�r��
	 */
	nstring Title() const;
	/**
	 * @brief ���o���j�r��
	 * @return ���j�r��
	 */
	nstring Token() const;
	/**
	 * @brief ���o��Ʀr��
	 * @return ��Ʀr��
	 */
	nstring Data() const;
	/**
	 * @brief ���o�զX�r��
	 * @return �զX�r��
	 */
	nstring Combination() const;
	/**
	 * @brief ���o��Ʀr�����
	 * @return ��Ʀr�����
	 */
	unsigned long Size() const;
	/**
	 * @brief ���o��Ц�m
	 */
	short GetPos() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief ����x���O
 * @ingroup console
 */
class C_Console
{
private:
	//-------------------------------------
	C_ConsoleQueue m_Command; ///< ���O�C��
	C_ConsoleHistory m_ccHistory; ///< ���O���v�C��
	C_ConsoleKBStr m_ccKBStr; ///< ���O�r��޲z
	//-------------------------------------

public:
	//-------------------------------------
	C_Console();
	virtual ~C_Console();
	//-------------------------------------
	/**
	 * @brief �w�ɳB�z
	 */
	void Process();
	/**
	 * @brief �]�w���D�r��
	 * @param szTitle ��Ʀr��
	 */
	void SetTitle(IN const nstring &szTitle);
	/**
	 * @brief �]�w���j�r��
	 * @param szToken ���j�r��
	 */
	void SetToken(IN const nstring &szToken);
	/**
	 * @brief ���o���D�r��
	 * @return ���D�r��
	 */
	nstring GetTitle() const;
	/**
	 * @brief ���o���j�r��
	 * @return ���j�r��
	 */
	nstring GetToken() const;
	/**
	 * @brief ���o���O�r��
	 * @return ���O�r��
	 */
	nstring GetCommand();
	//-------------------------------------
	/**
	 * @brief ��ܫ��O
	 * @param szString ��ܦr��
	 * @param ulCursor ��Ц�m
	 * @param bReplace ���N�X��
	 */
	virtual void Show(IN const nstring &szString, IN unsigned long ulCursor, IN bool bReplace);
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------