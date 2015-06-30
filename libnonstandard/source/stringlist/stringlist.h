/**
 * @file stringlist.h
 * @note ��r�ɮ�Ū����
 * @author yinweli
 */
/**
 * @page �p��ϥ�stringlist
 * stringlist�D�n�O���ѯ¤�r�ɪ�Ū��, �s�W, �s�ɪ��\��\n\n
 * ���O���O�H�@��@���x�s���, �Ф��n��� C_StringList.GetLine() �禡���쪺�r�갵����ק�\n
 * �o�����O���s�ɻPŪ�ɳ��O�H"��"��r�i��, �ثe���䴩Ū��Unicode�榡�ɮ�\n
 * ��M�A�٬O�i�H�s��L��r�i�h, ���O�Цb C_StringList.AddLine() �ɺ�n�Ӧr�ꪺ����\n
 * �s�ɻPŪ�ɮɽп�J���㪺���|�P�ɦW, ���ɦW\n\n
 * --------------------------------------------------\n
 * Header           : stringlist.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref stringlist
 */
/** @defgroup stringlist */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _STRINGLIST
#define _STRINGLIST
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\filetool\filetool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ��r�ɮ�Ū�������O
 * @ingroup stringlist
 */
class C_StringList
{
private:
	//-----------------------------------
	bool m_bLoadFile; ///< Ū���ɮ׺X��
	std::list<nstring> m_StringList; ///< �r��C��
	//-----------------------------------

public:
	//-----------------------------------
	typedef std::list<nstring>::const_iterator const_iterator; ///< �r��C���N�����O
	//-----------------------------------

public:
	//-----------------------------------
	C_StringList();
	virtual ~C_StringList();
	//-----------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief ���oŪ���ɮ׺X��
	 */
	bool IsLoad() const;
	//-----------------------------------
	/**
	 * @brief �[�J�@��
	 * @param szInput �n�[�J���r��
	 * @param ulPos �n�[�J����m
	 */
	void AddLine(IN const TCHAR *szInput, IN unsigned long ulPos = ULONG_MAX);
	/**
	 * @brief �[�J�@����󪺳̩���
	 * @param szInput �n�[�J���榡�Ʀr��, �P printf ���榡�@�P
	 * @param ... �ѼƦC��
	 */
	void AddLineEx(IN const TCHAR *szInput, ...);
	/**
	 * @brief �R���@��
	 * @param ulPos �n�R������m
	 */
	void DelLine(IN unsigned long ulPos);
	/**
	 * @brief ���o�@��
	 * @param ulPos �n���o����m
	 * @return �r��
	 */
	const TCHAR *GetLine(IN unsigned long ulPos) const;
	/**
	 * @brief ���o�@��
	 * @param ulPos �n���o����m
	 * @return �r��
	 */
	nstring GetLineStr(IN unsigned long ulPos) const;
	/**
	 * @brief ���o�@�檺�r��
	 * @param ulPos �n���o����m
	 * @return �r��
	 */
	unsigned long GetLineLen(IN unsigned long ulPos) const;
	/**
	 * @brief ���o���
	 * @return �`���
	 */
	unsigned long GetLineCount() const;
	/**
	 * @brief ���o�r��C��}�Y���N��
	 * @return �r��C���N��
	 */
	C_StringList::const_iterator Begin() const;
	/**
	 * @brief ���o�r��C�������N��
	 * @return �r��C���N��
	 */
	C_StringList::const_iterator End() const;
	//-----------------------------------
	/**
	 * @brief �s��
	 * @param szFilePath �n�s�ɪ��ɦW���|
	 * @param bAppend �O�_�O�K�[�Ҧ�, true��ܦs�ɮɷ|�⤺�e�K�[���ɮפ���, false�h�_
	 * @param bAutoWrap �O�_�۰ʴ���
	 * @param ulPos �s�ɪ��}�l��m
	 * @param ulLines �s�ɪ����
	 * @return true��ܦs�ɦ��\, false�h�_
	 */
	bool Save(IN const nstring &szFilePath, IN bool bAppend, IN bool bAutoWrap, IN unsigned long ulPos, IN unsigned long ulLines);
	/**
	 * @brief �s��
	 * @param szFilePath �n�s�ɪ��ɦW���|
	 * @param bAppend �O�_�O�K�[�Ҧ�, true��ܦs�ɮɷ|�⤺�e�K�[���ɮפ���, false�h�_
	 * @param bAutoWrap �O�_�۰ʴ���
	 * @return true��ܦs�ɦ��\, false�h�_
	 */
	bool Save(IN const nstring &szFilePath, IN bool bAppend, IN bool bAutoWrap);
	/**
	 * @brief Ū��
	 * @param szFilePath �nŪ�ɪ��ɦW���|
	 * @return true���Ū�ɦ��\, false�h�_
	 */
	bool Load(IN const nstring &szFilePath);
	//-----------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------