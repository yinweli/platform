/**
 * @file filetool.h
 * @note �ɮפu��t�C�禡
 * @author yinweli
 */
/**
 * @page �p��ϥ�filetool
 * filetool�����禡�Ω��ɮ׾ާ@\n\n
 * --------------------------------------------------\n
 * Header           : filetool.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref filetool
 */
/** @defgroup filetool */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _FILETOOL
#define _FILETOOL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �M���ɮ׵��c, �Ω� FindFileInDir �禡
 * @ingroup filetool
 */
struct S_FindFile
{
	nstring szPath; ///< �ؿ��r��
	nstring szName; ///< �ɮצW��
};
//-----------------------------------------------------------------------------
/**
 * @brief �ˬd�ɮ׬O�_�s�b
 * @param szFilePath �n�ˬd���ɦW(�]�t���|�P�ɦW)
 * @return true����ɮצs�b, false�h�_
 * @ingroup filetool
 */
bool fexist(IN const nstring &szFilePath);
/**
 * @brief ���o�ɮת���
 * @param f �H fopen �禡�}�Ҫ��ɮ׫���
 * @return �ɮת���(byte)
 * @ingroup filetool
 */
long fsize(IN FILE *f);
/**
 * @brief ���o�ɮת���
 * @param szFilePath �n���o���ת��ɦW(�]�t���|�P�ɦW)
 * @return �ɮת���(byte)
 * @ingroup filetool
 */
long fsize(IN const nstring &szFilePath);
/**
 * @brief Ū����ƨ�r�ꤤ
 * @param szFilePath �nŪ�����ɦW(�]�t���|�P�ɦW)
 * @param szData ��Ʀr��
 * @return true���Ū�����\, false�h�_
 * @ingroup filetool
 */
bool freadstr(IN const nstring &szFilePath, OUT nstring &szData);
/**
 * @brief �g�J��ƨ��ɮפ�
 * @param szFilePath �n�g�J���ɦW(�]�t���|�P�ɦW)
 * @param bAppend true��ܲK�[���ɮ׫�, false�h�_
 * @param pData ��ƫ���
 * @param ulSize ��ƪ���
 * @return true��ܼg�J���\, false�h�_
 * @ingroup filetool
 */
bool fwritedata(IN const nstring &szFilePath, IN bool bAppend, IN const void *pData, IN unsigned long ulSize);
/**
 * @brief �g�J�r����ɮפ�
 * @param szFilePath �n�g�J���ɦW(�]�t���|�P�ɦW)
 * @param bAppend true��ܲK�[���ɮ׫�, false�h�_
 * @param szData ��Ʀr��
 * @return true��ܼg�J���\, false�h�_
 * @ingroup filetool
 */
bool fwritestr(IN const nstring &szFilePath, IN bool bAppend, IN const std::string &szData);
/**
 * @brief �g�J�r����ɮפ�
 * @param szFilePath �n�g�J���ɦW(�]�t���|�P�ɦW)
 * @param bAppend true��ܲK�[���ɮ׫�, false�h�_
 * @param szData ��Ʀr��
 * @return true��ܼg�J���\, false�h�_
 * @ingroup filetool
 */
bool fwritestr(IN const nstring &szFilePath, IN bool bAppend, IN const std::wstring &szData);
/**
 * @brief ���o�{���Ҧb���ؿ�
 * @return �{���Ҧb���ؿ��r��
 * @ingroup filetool
 */
nstring GetCurrentDirectoryEx();
/**
 * @brief ���o���|�r�ꤺ�]�t���ؿ��W�٦C��
 * @param szPath ���|�r��
 * @param bFull �p�G��true, �h��X���r��|�]�t�����|
 * @param bSkip �p�G��true, ���|��X�̫�@�����|
 * @return ���G�C��
 * @ingroup filetool
 */
std::vector<nstring> GetPathList(IN const nstring &szPath, IN bool bFull = true, IN bool bSkip = true);
/**
 * @brief �M��ؿ����U�Ҧ��ɮ�
 * @param szPath ���|�r��
 * @return ���G�C��
 * @ingroup filetool
 */
std::vector<S_FindFile> GetFileList(IN const nstring &szPath);
/**
 * @brief ���o�H������榡�����|�P�ɦW�r��
 * @note �榡�p�U\n
 *       ���|\\�~\\��\\��\\yyyy-mm-dd hh-mm-ss �ɦW
 * @param szPath ���|
 * @param szFile �ɦW
 * @param bDirYear ���|�O�_�n�]�t �~ ��Ƨ�
 * @param bDirMonth ���|�O�_�n�]�t �� ��Ƨ�
 * @param bDirDay ���|�O�_�n�]�t �� ��Ƨ�
 * @param bFNDate �ɦW�O�_�n�]�t yyyy-mm-dd �r��
 * @param bFNTime �ɦW�O�_�n�]�t hh-mm-ss �r��
 * @return ���|�P�ɦW�r��
 * @ingroup filetool
 */
nstring GetDateFormatPath(IN const nstring &szPath, IN const nstring &szFile, IN bool bDirYear = true, IN bool bDirMonth = true, IN bool bDirDay = true, IN bool bFNDate = true, IN bool bFNTime = true);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------