/**
 * @file taskinterval.h
 * @note ���j�������O
 * @author yinweli
 */
/**
 * @page �p��ϥ�taskinterval
 * taskinterval�ΨӺ޲z����ݭn�C�j�h�[�N����B�z���禡\n\n
 * �ϥήɥ��إ� C_TaskIntervalList ���O������, �M��w�ɩI�s C_TaskIntervalList.Process() �禡��������B�@\n
 * �n�s�W���j���Ȯ�, ���ǳƦn�n���檺�禡, �o�Ө禡���쫬�w�q�b C_TaskIntervalGeneral::LPFN_Process �H�� C_TaskIntervalTemplate::LPFN_Process ��, �ƹ�W�o��өw�q�O�@�˪�\n
 * �@�ӥ��T���禡�N�|�������o��\n\n
 * void �禡�W��()\n\n
 * �o�Ө禡�O����禡, ���O�����禡, ���O�����R�A�禡���i�H\n\n
 * �I�s C_TaskIntervalList.Add() �禡�ӷs�W���j����\n
 * �I�s C_TaskIntervalList.Del() �禡�ӧR�����j����\n
 * �I�s C_TaskIntervalList.Set() �禡�ӳ]�w���j���Ȫ����j�ɶ�\n\n
 * --------------------------------------------------\n
 * Header           : taskinterval.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref taskinterval
 */
/** @defgroup taskinterval */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _TASKINTERVAL
#define _TASKINTERVAL
//-----------------------------------------------------------------------------
#pragma comment(lib, "winmm.lib")
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ��¦���j�������O
 * @ingroup taskinterval
 */
class C_TaskInterval
{
protected:
	//-------------------------------------
	unsigned long m_ulInterval; ///< ���j�ɶ�
	unsigned long m_ulTimeNext; ///< �U���ɶ�
	//-------------------------------------

public:
	//-------------------------------------
	C_TaskInterval(IN unsigned long interval);
	virtual ~C_TaskInterval();
	//-------------------------------------
	/**
	 * @brief �]�w���j�ɶ�
	 * @param ulInterval ���j�ɶ�
	 */
	void Set(IN unsigned long ulInterval);
	/**
	 * @brief �ˬd�O�_����
	 * @return true��ܰ���, false�h�_
	 */
	bool Check();
	/**
	 * @brief ���o���j�ɶ�
	 * @return ���j�ɶ�
	 */
	unsigned long Interval() const;
	//-------------------------------------
	/**
	 * @brief �w�ɳB�z
	 */
	virtual void Process() = 0;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �@�붡�j�������O
 * @ingroup taskinterval
 */
class C_TaskIntervalGeneral : public C_TaskInterval
{
public:
	//-------------------------------------
	typedef void (*LPFN_Process) (); ///< �B�z�禡����
	//-------------------------------------

private:
	//-------------------------------------
	LPFN_Process m_pfProcess; ///< �B�z�禡����
	//-------------------------------------

public:
	//-------------------------------------
	C_TaskIntervalGeneral(IN unsigned long interval, IN LPFN_Process process) : C_TaskInterval(interval), m_pfProcess(process) {};
	virtual ~C_TaskIntervalGeneral() {}
	//-------------------------------------
	/**
	 * @brief �w�ɳB�z
	 */
	void Process()
	{
		if(m_pfProcess == nullptr)
			return;

		if(Check() == false)
			return;

		m_pfProcess();
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �x�ζ��j�������O
 * @ingroup taskinterval
 */
template<typename _Obj> class C_TaskIntervalTemplate : public C_TaskInterval
{
public:
	//-------------------------------------
	typedef void (_Obj::*LPFN_Process) (); ///< �B�z�禡����
	//-------------------------------------

private:
	//-------------------------------------
	_Obj *m_pObject; ///< �B�z�������
	LPFN_Process m_pfProcess; ///< �B�z�禡����
	//-------------------------------------

public:
	//-------------------------------------
	C_TaskIntervalTemplate(IN unsigned long interval, IN _Obj &object, IN LPFN_Process process) : C_TaskInterval(interval), m_pObject(&object), m_pfProcess(process) {};
	virtual ~C_TaskIntervalTemplate() {};
	//-------------------------------------
	/**
	 * @brief �w�ɳB�z
	 */
	void Process()
	{
		if(m_pObject == nullptr)
			return;

		if(m_pfProcess == nullptr)
			return;

		if(Check() == false)
			return;

		(m_pObject->*m_pfProcess)();
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief ���j���ȦC�����O
 * @ingroup taskinterval
 */
class C_TaskIntervalList
{
private:
	//-------------------------------------
	std::map<nstring, C_TaskInterval *> m_Task; ///< ���j���ȦC�� <���j���ȦW��, ���j���ȫ���>
	//-------------------------------------

public:
	//-------------------------------------
	C_TaskIntervalList();
	virtual ~C_TaskIntervalList();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �w�ɳB�z
	 */
	void Process();
	/**
	 * @brief �s�W���j����(�R�A�禡����)
	 * @param szName ���j���ȦW��
	 * @param ulInterval ���j�ɶ�, ���O�@��
	 * @param pfProcess �B�z�禡����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Add(IN const nstring &szName, IN unsigned long ulInterval, IN C_TaskIntervalGeneral::LPFN_Process pfProcess)
	{
		if(szName.empty())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

		if(pfProcess == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("process null(") + szName + __T(")"));

		if(m_Task.find(szName) != m_Task.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + szName + __T(")"));

		C_TaskInterval *pProcess = nstdnew C_TaskIntervalGeneral(ulInterval, pfProcess);

		if(pProcess == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create task failed(") + szName + __T(")"));

		m_Task[szName] = pProcess;

		return true;
	};
	/**
	 * @brief �s�W���j����(�����禡����)
	 * @param szName ���j���ȦW��
	 * @param ulInterval ���j�ɶ�, ���O�@��
	 * @param Object �B�z����
	 * @param pfProcess �B�z�禡����
	 * @return true��ܦ��\, false�h�_
	 */
	template<typename _Obj> bool Add(IN const nstring &szName, IN unsigned long ulInterval, IN _Obj &Object, IN typename C_TaskIntervalTemplate<_Obj>::LPFN_Process pfProcess)
	{
		if(szName.empty())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

		if(pfProcess == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("process null(") + szName + __T(")"));

		if(m_Task.find(szName) != m_Task.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + szName + __T(")"));

		C_TaskInterval *pProcess = nstdnew C_TaskIntervalTemplate<_Obj>(ulInterval, Object, pfProcess);

		if(pProcess == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create task failed(") + szName + __T(")"));

		m_Task[szName] = pProcess;

		return true;
	};
	/**
	 * @brief �R�����j����
	 * @param szName ���j���ȦW��
	 */
	void Del(IN const nstring &szName);
	/**
	 * @brief �]�w���j�ɶ�
	 * @param szName ���j���ȦW��
	 * @param ulInterval ���j�ɶ�, ���O�@��
	 */
	void Set(IN const nstring &szName, IN unsigned long ulInterval);
	/**
	 * @brief ���o���j�ɶ�
	 * @param szName ���j���ȦW��
	 * @return ���j�ɶ�
	 */
	unsigned long Get(IN const nstring &szName) const;
	/**
	 * @brief ���o���j���ȦC��
	 * @return ���j���ȦC��
	 */
	std::set<nstring> List() const;
	/**
	 * @brief ���o�ƶq
	 * @return �ƶq
	 */
	unsigned long Size() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------