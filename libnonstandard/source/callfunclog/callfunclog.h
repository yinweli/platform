/**
 * @file callfunclog.h
 * @note �禡�l�ܨt�C�禡
 * @author yinweli
 */
/**
 * @page �p��ϥ�callfunclog
 * callfunclog�����禡�Ω�禡�l�ܻP�l�ܵ��G��X\n\n
 * �b�{�������Ҧ��禡(�άO�A�Q�n�l�ܪ��禡)�̲K�[�@��O������\n
 * �N�|�b���������I�s�L���禡�O���U��, ���O�O���ƶq����b MAX_LOGCOUNT �o�Ӥj�p, �W�L���ܷ|���ª��O���R���H�e�Ƿs���O��\n\n
 * �n���o�禡�O���C���ܥi�H�I�s C_CallFuncLog.Get() �禡\n\n
 * --------------------------------------------------\n
 * Header           : callfunclog.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref callfunclog
 */
/** @defgroup callfunclog */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CALLFUNCLOG
#define _CALLFUNCLOG
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\_ntime\_ntime.h"
#include "..\filetool\filetool.h"
#include "..\threadlock\threadlock.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#define MAX_LOGCOUNT 256 ///< �̤j�O���ƶq @ingroup callfunclog
#define _G_() { nstd::C_CallFuncLog::Instance().Add(__FUNCTIONX__, __FILEX__, __LINE__); } ///< �O������ @ingroup callfunclog
//-----------------------------------------------------------------------------
/**
 * @brief �O���I�s�禡���c
 * @ingroup callfunclog
 */
struct S_CallFuncLog
{
	nstring szFunc; ///< �Q�I�s���禡�W��
	nstring szFile; ///< �禡�Q�I�s�ɪ��{���X�ɮצW��
	unsigned long ulLine; ///< �禡�Q�I�s�ɪ��渹

	S_CallFuncLog();
	S_CallFuncLog(IN const nstring &func, IN const nstring &file, IN unsigned long line);
};
//-----------------------------------------------------------------------------
/**
 * @brief �O���I�s�禡���O
 * @ingroup callfunclog
 */
class C_CallFuncLog
{
private:
	//-------------------------------------
	std::list<S_CallFuncLog> m_CallList; ///< �����I�s�C��
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_CallFuncLog();
	virtual ~C_CallFuncLog();
	//-------------------------------------
	/**
	 * @brief ���o�O���I�s�禡����
	 * @return �O���I�s�禡����
	 */
	static C_CallFuncLog &Instance();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W����
	 * @param szFuncName �Q�I�s���禡�W��
	 * @param szFileName �禡�Q�I�s�ɪ��{���X�ɮצW��
	 * @param ulLine �禡�Q�I�s�ɪ��渹
	 */
	void Add(IN const nstring &szFuncName, IN const nstring &szFileName, IN unsigned long ulLine);
	/**
	 * @brief ���o����, ��X��C��
	 * @param CallList �O����X�즹�C��
	 */
	void Get(OUT std::list<S_CallFuncLog> &CallList) const;
	/**
	 * @brief ���o����, ��X���ɮ�
	 * @param szFilePath �O���ɮ׸��|
	 */
	void Get(IN const nstring &szFilePath) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------