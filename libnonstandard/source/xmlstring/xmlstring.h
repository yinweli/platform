/**
 * @file xmlstring.h
 * @note XML�r������O
 * @author yinweli
 */
/**
 * @page �p��ϥ�xmlstring
 * xmlstring����Ū���S�w�榡��XML���, �åB���󤺦s���r��H�s�������ޫO�s���O��\n\n
 * �����إ� C_XMLString\n\n
 * C_XMLString ccXML;\n\n
 * �M��i�H���ƩI�s C_XMLString.Load() ��Ū���h��XML���\n
 * ���۩I�s C_XMLString.Get() �H���ޭȻP�s���Ө��o�O�s���r��\n
 * �p�G�o�Ϳ��~��(�Ҧp�I�s C_XMLString.Load() ����)�i�H�I�s C_XMLString.GetError() ���o���~�T��\n\n
 * XML��󪺮榡�d�Ҧp�U:\n\n
 * <test>\n
 * <str    id = "2">�Ĥ@�Ӧr</str>\n
 * <key001 id = "0">�ĤG�Ӧr</key001>\n
 * <key002 id = "1">�ĤT�Ӧr</key002>\n
 * </test>\n
 * �� C_XMLString ���榡���P���O, str �i�H�令��L�W��\n
 * id �N���Ʀr�N�O�Ӧr�ꪺ���ޭ�\n
 * �r�ꤺ�P�ɤ]�i�H��g�p %%s, %%d �� printf ���榡�Ʀr��\n\n
 * �̫�n�`�N, �ثe�o�Ӥ���u��Ū��ANSI�PUnicode���ɮ�, �p�G�OUTF-8�|�y�����~
 * --------------------------------------------------\n
 * Header           : xmlstring.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref xmlstring
 */
/** @defgroup xmlstring */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XMLSTRING
#define _XMLSTRING
//-----------------------------------------------------------------------------
#ifdef _DEBUG
#pragma comment(lib, "..\\libthirdparty\\tinyxml 2.6.2\\vc2013_lib_debug\\tinyxmld.lib")
#else
#pragma comment(lib, "..\\libthirdparty\\tinyxml 2.6.2\\vc2013_lib_release\\tinyxml.lib")
#endif
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\..\..\libthirdparty\tinyxml 2.6.2\include\tinyxml.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
#define XMLSTRINGID "id" ///< XML�N��r����ޭȪ��W�� @ingroup xmlstring
//-----------------------------------------------------------------------------
/**
 * @brief XML�r�����~���O
 * @ingroup xmlstring
 */
class C_ErrorXMLString : public C_ErrorBase
{
private:
	//-------------------------------------
	estring m_szError; ///< ���~�r��
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorXMLString(IN const TiXmlDocument &xmldoc);
	virtual ~C_ErrorXMLString();
	//-------------------------------------
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief XML�r������O
 * @ingroup xmlstring
 */
class C_XMLString
{
private:
	//-------------------------------------
	std::map<nstring, nstring> m_StringList; ///< �r��C�� <�r��W��, ���e>
	std::map<nstring, nstring>::iterator m_Itor;
	//-------------------------------------

public:
	//-------------------------------------
	C_XMLString();
	virtual ~C_XMLString();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief Ū���r���ɮ�, �i�H���Ƹ��J�h���ɮ�
	 * @param szFile �ɮ׸��|�H���ɦW
	 * @return true��ܦ��\, false�h�_
	 */
	bool Load(IN const nstring &szFile);
	/**
	 * @brief ���o�r��
	 * @note ���禡�����ޭȮ榡, �p�U�d��:\n\n
	 *       <string001>\n
	 *       <type id = "0">�r��1</type>\n
	 *       <string002>\n
	 *       <type id = "1">�r��2</type>\n
	 *       <string003>\n
	 *       <xxxx id = "2">�r��3</xxxx>\n
	 *       </string003>\n
	 *       </string002>\n
	 *       </string001>\n\n
	 *       �n���o "�r��1" ����, ���ޭȥ����O "string001:type:0"\n
	 *       �n���o "�r��2" ����, ���ޭȥ����O "string001:string002:type:1"\n
	 *       �n���o "�r��3" ����, ���ޭȥ����O "string001:string002:string003:type:2"\n
	 * @param szKey ���ޭ�
	 * @param szDefault �p�G�䤣��r��, �Ǧ^���r��
	 * @return �r��
	 */
	nstring Get(IN const nstring &szKey, IN const nstring &szDefault = __T("")) const;
	/**
	 * @brief ���o�r��
	 * @note ���禡�|����ޭȦC��H�νs�������e�զX������ "string001:string002:string003:type:2" ���Ҧ�, ��@���ޭȥh�d�ߦr��
	 * @param KeyList ���ޭȦC��
	 * @param iID �s��
	 * @param szDefault �p�G�䤣��r��, �Ǧ^���r��
	 * @return �r��
	 */
	nstring Get(IN const std::vector<nstring> &KeyList, IN int iID, IN const nstring &szDefault = __T("")) const;
	/**
	 * @brief ���o�r��ƶq
	 * @return �r��ƶq
	 */
	int Size() const;
	/**
	 * @brief ���m���N��
	 */
	void ResetItor();
	/**
	 * @brief �̧Ǩ��o�r��
	 * @param szKey �r�ꪺ���ޭ�
	 * @param szString �r��
	 * @return true��ܳo�������o���\, false�h�_
	 */
	bool GetDataByOrder(OUT nstring &szKey, OUT nstring &szString);
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------