/**
 * @file inifile.h
 * @note ini�ɮ�Ū�����O
 * @author yinweli
 */
/**
 * @page �p��ϥ�inifile
 * inifile�Ω�ini�ɮ׾ާ@\n\n
 * �����إߤ@�ӹ���ϥ� C_IniFile �ŧi�p�U\n\n
 * C_IniFile ccIni;\n\n
 * ���۩I�s C_IniFile.Initialize() �禡��Q�nŪ����ini�ɮץ[�J���O��\n
 * �M��N�i�H�I�s C_IniFile.Get() �禡�Ө��oini�����]�w��\n\n
 * --------------------------------------------------\n
 * Header           : inifile.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref inifile
 */
/** @defgroup inifile */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _INIFILE
#define _INIFILE
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\argument\argument.h"
#include "..\filetool\filetool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ini���s�b���~���O
 * @ingroup inifile
 */
class C_ErrorIniNotExist : public C_ErrorBase
{
private:
	//-------------------------------------
	estring m_szError; ///< ���~�r��
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorIniNotExist(IN const nstring &filepath);
	virtual ~C_ErrorIniNotExist();
	//-------------------------------------
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief iniŪ�����~���O
 * @ingroup inifile
 */
class C_ErrorIniNotFound : public C_ErrorBase
{
private:
	//-------------------------------------
	estring m_szError; ///< ���~�r��
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorIniNotFound(IN const nstring &filepath, IN const nstring &section, IN const estring &key);
	virtual ~C_ErrorIniNotFound();
	//-------------------------------------
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief ���o�]�w��
 * @param szFilePath �ɦW���|
 * @param szSection �Ϭq�W��
 * @param szKey ���ަW��
 * @param ccValue �]�w��
 * @return true��ܦ��\, false�h�_
 */
bool GetIniValue(IN const nstring &szFilePath, IN const nstring &szSection, IN const nstring &szKey, OUT C_Argu &ccValue);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------