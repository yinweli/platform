/**
 * @file taskschedule.h
 * @note �Ƶ{�������O
 * @author yinweli
 */
/**
 * @page �p��ϥ�taskschedule
 * taskschedule�ΨӺ޲z����ݭn�w�ɰ���B�z���禡\n\n
 * �ϥήɥ��إ� C_TaskScheduleList ���O������, �M��w�ɩI�s C_TaskScheduleList.Process() �禡��������B�@\n
 * �n�s�W�Ƶ{���Ȯ�, ���ǳƦn�n���檺�禡, �o�Ө禡���쫬�w�q�b C_TaskScheduleGeneral::LPFN_Process �H�� C_TaskScheduleTemplate::LPFN_Process ��, �ƹ�W�o��өw�q�O�@�˪�\n
 * �@�ӥ��T���禡�N�|�������o��\n\n
 * void �禡�W��()\n\n
 * �o�Ө禡�O����禡, ���O�����禡, ���O�����R�A�禡���i�H\n\n
 * �I�s C_TaskScheduleList.Add() �禡�ӷs�W�Ƶ{����\n
 * �I�s C_TaskScheduleList.Del() �禡�ӧR���Ƶ{����\n
 * �I�s C_TaskScheduleList.Set() �禡�ӳ]�w�Ƶ{���Ȫ��Ƶ{�ɶ�\n\n
 * --------------------------------------------------\n
 * Header           : taskschedule.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref taskschedule
 */
/** @defgroup taskschedule */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _TASKSCHEDULE
#define _TASKSCHEDULE
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
 * @brief �s�y�ɶ��r��
 * @param lYear �~, -1��ܨC�~����
 * @param lMonth ��(1 ~ 12), -1��ܨC�����
 * @param lMDay ��(1 ~ 31), -1��ܨC�����
 * @param lWDay �P(0 ~ 6, 0��ܬO�g��, 1��ܬO�g�@, �̦�����), �P�u���b�鬰-1���ɭԤ~�i�H�ϥ�, -1��ܨC�P�X����
 * @param lHour ��(0 ~ 23), -1��ܨC�ɰ���
 * @param lMin ��(0 ~ 59), -1��ܨC������
 * @param lSec ��(0 ~ 59), -1��ܨC�����
 * @return �ɶ��r��
 * @ingroup taskschedule
 */
nstring MakeSchedule(IN long lYear, IN long lMonth, IN long lMDay, IN long lWDay, IN long lHour, IN long lMin, IN long lSec);
/**
 * @brief �s�y�ɶ��r��, �榡�|�P�L�o�r��@�P
 * @param lYear �~, -1��ܨC�~����
 * @param lMonth ��(1 ~ 12), -1��ܨC�����
 * @param lMDay ��(1 ~ 31), -1��ܨC�����
 * @param lWDay �P(0 ~ 6, 0��ܬO�g��, 1��ܬO�g�@, �̦�����), �P�u���b�鬰-1���ɭԤ~�i�H�ϥ�, -1��ܨC�P�X����
 * @param lHour ��(0 ~ 23), -1��ܨC�ɰ���
 * @param lMin ��(0 ~ 59), -1��ܨC������
 * @param lSec ��(0 ~ 59), -1��ܨC�����
 * @param szFilter �L�o�r��
 * @return �ɶ��r��
 * @ingroup taskschedule
 */
nstring MakeSchedule(IN long lYear, IN long lMonth, IN long lMDay, IN long lWDay, IN long lHour, IN long lMin, IN long lSec, IN const nstring &szFilter);
//-----------------------------------------------------------------------------
/**
 * @brief ��¦�Ƶ{�������O
 * @ingroup taskschedule
 */
class C_TaskSchedule
{
protected:
	//-------------------------------------
	nstring m_szSchedule; ///< �Ƶ{�ɶ��r��, �ɶ��榡 year/month/mday/wday/hour/min/sec
	bool m_bBlock; ///< ���׺X��
	//-------------------------------------

public:
	//-------------------------------------
	C_TaskSchedule(IN const nstring &schedule);
	virtual ~C_TaskSchedule();
	//-------------------------------------
	/**
	 * @brief �]�w�Ƶ{�ɶ�
	 * @param szSchedule �Ƶ{�ɶ��r��
	 */
	void Set(IN const nstring &szSchedule);
	/**
	 * @brief �ˬd�O�_����
	 * @return true��ܰ���, false�h�_
	 */
	bool Check();
	/**
	 * @brief ���o�Ƶ{�ɶ�
	 * @return �Ƶ{�ɶ��r��
	 */
	nstring Schedule() const;
	//-------------------------------------
	/**
	 * @brief �w�ɳB�z
	 */
	virtual void Process() = 0;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �@��Ƶ{�������O
 * @ingroup taskschedule
 */
class C_TaskScheduleGeneral : public C_TaskSchedule
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
	C_TaskScheduleGeneral(IN const nstring &schedule, IN LPFN_Process process) : C_TaskSchedule(schedule), m_pfProcess(process) {};
	virtual ~C_TaskScheduleGeneral() {};
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
 * @brief �x�αƵ{�������O
 * @ingroup taskschedule
 */
template<typename _Obj> class C_TaskScheduleTemplate : public C_TaskSchedule
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
	C_TaskScheduleTemplate(IN const nstring &schedule, IN _Obj &object, IN LPFN_Process process) : C_TaskSchedule(schedule), m_pObject(&object), m_pfProcess(process) {};
	virtual ~C_TaskScheduleTemplate() {};
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
 * @brief �Ƶ{���ȦC�����O
 * @ingroup taskschedule
 */
class C_TaskScheduleList
{
private:
	//-------------------------------------
	std::map<nstring, C_TaskSchedule *> m_Task; ///< �Ƶ{���ȦC�� <�Ƶ{���ȦW��, �Ƶ{���ȫ���>
	//-------------------------------------

public:
	//-------------------------------------
	C_TaskScheduleList();
	virtual ~C_TaskScheduleList();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W�Ƶ{����(�R�A�禡����)
	 * @param szName �Ƶ{���ȦW��
	 * @param lYear �~, -1��ܨC�~����
	 * @param lMonth ��(1 ~ 12), -1��ܨC�����
	 * @param lMDay ��(1 ~ 31), -1��ܨC�����
	 * @param lWDay �P(0 ~ 6, 0��ܬO�g��, 1��ܬO�g�@, �̦�����), �P�u���b�鬰-1���ɭԤ~�i�H�ϥ�, -1��ܨC�P�X����
	 * @param lHour ��(0 ~ 23), -1��ܨC�ɰ���
	 * @param lMin ��(0 ~ 59), -1��ܨC������
	 * @param lSec ��(0 ~ 59), -1��ܨC�����
	 * @param pfProcess �B�z�禡����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Add(IN const nstring &szName, IN long lYear, IN long lMonth, IN long lMDay, IN long lWDay, IN long lHour, IN long lMin, IN long lSec, IN C_TaskScheduleGeneral::LPFN_Process pfProcess)
	{
		if(szName.empty())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

		if(pfProcess == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("process null(") + szName + __T(")"));

		if(m_Task.find(szName) != m_Task.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + szName + __T(")"));

		C_TaskSchedule *pProcess = nstdnew C_TaskScheduleGeneral(MakeSchedule(lYear, lMonth, lMDay, lWDay, lHour, lMin, lSec), pfProcess);

		if(pProcess == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create task failed(") + szName + __T(")"));

		m_Task[szName] = pProcess;

		return true;
	};
	/**
	 * @brief �s�W�Ƶ{����(�����禡����)
	 * @param szName �Ƶ{���ȦW��
	 * @param lYear �~, -1��ܨC�~����
	 * @param lMonth ��(1 ~ 12), -1��ܨC�����
	 * @param lMDay ��(1 ~ 31), -1��ܨC�����
	 * @param lWDay �P(0 ~ 6, 0��ܬO�g��, 1��ܬO�g�@, �̦�����), �P�u���b�鬰-1���ɭԤ~�i�H�ϥ�, -1��ܨC�P�X����
	 * @param lHour ��(0 ~ 23), -1��ܨC�ɰ���
	 * @param lMin ��(0 ~ 59), -1��ܨC������
	 * @param lSec ��(0 ~ 59), -1��ܨC�����
	 * @param Object �B�z����
	 * @param pfProcess �B�z�禡����
	 * @return true��ܦ��\, false�h�_
	 */
	template<typename _Obj> bool Add(IN const nstring &szName, IN long lYear, IN long lMonth, IN long lMDay, IN long lWDay, IN long lHour, IN long lMin, IN long lSec, IN _Obj &Object, IN typename C_TaskScheduleTemplate<_Obj>::LPFN_Process pfProcess)
	{
		if(szName.empty())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("name empty"));

		if(pfProcess == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("process null(") + szName + __T(")"));

		if(m_Task.find(szName) != m_Task.end())
			return C_NOutput::Instance().Error(ERRORNSTD, __T("already exist(") + szName + __T(")"));

		C_TaskSchedule *pProcess = nstdnew C_TaskScheduleTemplate<_Obj>(MakeSchedule(lYear, lMonth, lMDay, lWDay, lHour, lMin, lSec), Object, pfProcess);

		if(pProcess == nullptr)
			return C_NOutput::Instance().Error(ERRORNSTD, __T("create task failed(") + szName + __T(")"));

		m_Task[szName] = pProcess;

		return true;
	};
	/**
	 * @brief �R���Ƶ{����
	 * @param szName �Ƶ{���ȦW��
	 */
	void Del(IN const nstring &szName);
	/**
	 * @brief �]�w�Ƶ{�ɶ�
	 * @param szName �Ƶ{���ȦW��
	 * @param lYear �~, -1��ܨC�~����
	 * @param lMonth ��(1 ~ 12), -1��ܨC�����
	 * @param lMDay ��(1 ~ 31), -1��ܨC�����
	 * @param lWDay �P(0 ~ 6, 0��ܬO�g��, 1��ܬO�g�@, �̦�����), �P�u���b�鬰-1���ɭԤ~�i�H�ϥ�, -1��ܨC�P�X����
	 * @param lHour ��(0 ~ 23), -1��ܨC�ɰ���
	 * @param lMin ��(0 ~ 59), -1��ܨC������
	 * @param lSec ��(0 ~ 59), -1��ܨC�����
	 */
	void Set(IN const nstring &szName, IN long lYear, IN long lMonth, IN long lMDay, IN long lWDay, IN long lHour, IN long lMin, IN long lSec);
	/**
	 * @brief �w�ɳB�z
	 */
	void Process();
	/**
	 * @brief ���o�Ƶ{���ȦC��
	 * @return �Ƶ{���ȦC��
	 */
	std::map<nstring, nstring> List() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------