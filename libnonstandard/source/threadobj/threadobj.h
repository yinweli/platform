/**
 * @file threadobj.h
 * @note ��������O
 * @author yinweli
 */
/**
 * @page �p��ϥ�threadobj
 * threadobj�Ω���������������\n\n
 * �b�إ߰�����e, ���إ� C_ThreadMgr ����, �M��I�s C_ThreadMgr.Create() �禡�ӫإ߰����\n
 * ���ۦb������禡���̫e���H�ǤJ������Ѽƫإ� C_ThreadObj ����\n
 * �������������i�H�I�s C_ThreadObj.IsShutdown() �ӽT�w�O�_���q���n���������\n
 * ��L�����(�άO�D�����)�i�H�I�s C_ThreadMgr.Shutdown() �������o�Ӻ޲z�����U�������\n
 * �����������ɭP C_ThreadObj ����Ѻc�ɷ|�q�� C_ThreadMgr ���Ӱ�����w�g����\n
 * ���O�n�`�N, �p�G�޲z�����޲z�������٭n���Q�Ѻc, �N�|�y���{�����~\n\n
 * --------------------------------------------------\n
 * Header           : thread.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref threadobj\n
 */
/** @defgroup threadobj */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _THREADOBJ
#define _THREADOBJ
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\argument\argument.h"
#include "..\threadlock\threadlock.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
class C_ThreadMgr;
//-----------------------------------------------------------------------------
/**
 * @brief ��������O
 * @ingroup threadobj
 */
class C_ThreadObj
{
private:
	//-------------------------------------
	C_ThreadMgr *m_pThreadMgr; ///< ������޲z������
	unsigned long m_ulThreadID; ///< ������s��
	//-------------------------------------

public:
	//-------------------------------------
	C_ThreadObj(IN void *param);
	virtual ~C_ThreadObj();
	//-------------------------------------
	operator bool () const;
	//-------------------------------------
	/**
	 * @brief �M���Ѽ�
	 */
	void ClrParam();
	/**
	 * @brief �]�w�Ѽ�
	 * @param szName �ѼƦW��
	 * @param ccParam �Ѽƭ�
	 */
	void SetParam(IN const nstring &szName, IN const C_Argu &ccParam);
	/**
	 * @brief �R���Ѽ�
	 * @param szName �ѼƦW��
	 */
	void DelParam(IN const nstring &szName);
	/**
	 * @brief ���o�Ѽ�
	 * @param szName �ѼƦW��
	 * @param ccParam �Ѽƭ�
	 * @return true��ܦ��\, false�h�_
	 */
	bool GetParam(IN const nstring &szName, OUT C_Argu &ccParam) const;
	/**
	 * @brief �O�_�n���������
	 * @return true��ܭn���������, false�h�_
	 */
	bool IsShutdown() const;
	/**
	 * @brief ���o������s��
	 * @return ������s��
	 */
	unsigned long ThreadID() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �޲z�����O
 * @ingroup threadobj
 */
class C_ThreadMgr
{
	//-------------------------------------
	friend class C_ThreadObj;
	//-------------------------------------

private:
	//-------------------------------------
	std::map<unsigned long, bool> m_Thread; ///< ������s���C�� <������s��, �����X��>
	std::map<nstring, C_Argu> m_Param; ///< �ѼƦC��
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

private:
	//-------------------------------------
	/**
	 * @brief �s�W������s��
	 * @param ulThreadID ������s��
	 */
	void AddThreadID(IN unsigned long ulThreadID);
	/**
	 * @brief �R��������s��
	 * @param ulThreadID ������s��
	 */
	void DelThreadID(IN unsigned long ulThreadID);
	/**
	 * @brief ���o����X��
	 * @param ulThreadID ������s��
	 * @return true����~�����, false�h�_
	 */
	bool IsShutdown(IN unsigned long ulThreadID) const;
	//-------------------------------------

public:
	//-------------------------------------
	typedef unsigned (__stdcall *LPFN_Thread) (void *); ///< ������禡���ЧκA
	//-------------------------------------

public:
	//-------------------------------------
	C_ThreadMgr();
	virtual ~C_ThreadMgr();
	//-------------------------------------
	/**
	 * @brief �إ߰����
	 * @param pfThread ������禡����
	 * @return true��ܫإߦ��\, false�h�_
	 */
	bool Create(IN LPFN_Thread pfThread);
	/**
	 * @brief ���������
	 */
	void Shutdown();
	/**
	 * @brief ���������
	 * @param ulThreadID ������s��
	 */
	void Shutdown(IN unsigned long ulThreadID);
	/**
	 * @brief �M���Ѽ�
	 */
	void ClrParam();
	/**
	 * @brief �]�w�Ѽ�
	 * @param szName �ѼƦW��
	 * @param ccParam �Ѽƭ�
	 */
	void SetParam(IN const nstring &szName, IN const C_Argu &ccParam);
	/**
	 * @brief �R���Ѽ�
	 * @param szName �ѼƦW��
	 */
	void DelParam(IN const nstring &szName);
	/**
	 * @brief ���o�Ѽ�
	 * @param szName �ѼƦW��
	 * @param ccParam �Ѽƭ�
	 * @return true��ܦ��\, false�h�_
	 */
	bool GetParam(IN const nstring &szName, OUT C_Argu &ccParam) const;
	/**
	 * @brief ���o������C��
	 * @return ������C��
	 */
	std::set<unsigned long> List() const;
	/**
	 * @brief ���o������ƶq
	 * @return ������ƶq
	 */
	unsigned long Size() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------