/**
 * @file json.h
 * @note json���O
 * @author yinweli
 */
/**
 * @page �p��ϥ�json
 * �o�O�Өϥ�json(JavaScript Object Notation)�榡���r����R����\n\n
 * �����إߤ@�ӹ���ϥ� C_Json �ŧi�p�U\n\n
 * C_Json ccJson;\n\n
 * �M��I�s C_Json.Import() �פJjson�榡�r��\n
 * �άO�I�s C_Json.Export() �ץXjson�榡�r��\n
 * �Y�n�s�W���, �N�I�s C_Json.Add() �t�C�禡\n
 * �Y�n�R�����, �N�I�s C_Json.Del() �禡\n
 * �Y�n���o���, �N�I�s C_Json.Get() �t�C�禡\n
 * �p�G�c�餤���J�F"�\�\�\�|"���r(�ƹ�W���ܦh�r���|�o��)�N�|�y�����~\n
 * �p�G����json�r�ꪺ�OC#�{��, �h�r�ꤤ�p�G��"\\"�]�|�y�����~\n\n
 * --------------------------------------------------\n
 * Header           : json.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref json
 */
/** @defgroup json */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _JSON
#define _JSON
//-----------------------------------------------------------------------------
#ifdef _DEBUG
#pragma comment(lib, "..\\libthirdparty\\jsoncpp-1.0.0\\vc2013_lib_debug\\lib_json.lib")
#else
#pragma comment(lib, "..\\libthirdparty\\jsoncpp-1.0.0\\vc2013_lib_release\\lib_json.lib")
#endif
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\..\..\libthirdparty\jsoncpp-1.0.0\include\json.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief json���O
 * @ingroup json
 */
class C_Json
{
private:
	//-------------------------------------
	Json::Value m_Value; ///< json��ƪ���
	//-------------------------------------

public:
	//-------------------------------------
	C_Json();
	C_Json(IN const C_Json &data);
	virtual ~C_Json();
	//-------------------------------------
	C_Json &operator = (IN const C_Json &ccJson);
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �פJ�r��
	 * @param szJson �r��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Import(IN const std::string &szJson);
	/**
	 * @brief �ץX�r��
	 * @return json�榡�r��
	 */
	std::string Export() const;
	/**
	 * @brief �ץX�r�� - ����Ʀr��
	 * @return json�榡�r��
	 */
	std::string ExportStyled() const;
	/**
	 * @brief �ץX�r�� - �ֳt�r��
	 * @return json�榡�r��
	 */
	std::string ExportFast() const;
	/**
	 * @brief �s�W����
	 * @param szName �����W��
	 * @param value ��
	 */
	void Add(IN const nstring &szName, IN bool value);
	/**
	 * @brief �s�W����
	 * @param szName �����W��
	 * @param value ��
	 */
	void Add(IN const nstring &szName, IN char value);
	/**
	 * @brief �s�W����
	 * @param szName �����W��
	 * @param value ��
	 */
	void Add(IN const nstring &szName, IN unsigned char value);
	/**
	 * @brief �s�W����
	 * @param szName �����W��
	 * @param value ��
	 */
	void Add(IN const nstring &szName, IN short value);
	/**
	 * @brief �s�W����
	 * @param szName �����W��
	 * @param value ��
	 */
	void Add(IN const nstring &szName, IN unsigned short value);
	/**
	 * @brief �s�W����
	 * @param szName �����W��
	 * @param value ��
	 */
	void Add(IN const nstring &szName, IN long value);
	/**
	 * @brief �s�W����
	 * @param szName �����W��
	 * @param value ��
	 */
	void Add(IN const nstring &szName, IN unsigned long value);
	/**
	 * @brief �s�W����
	 * @param szName �����W��
	 * @param value ��
	 */
	void Add(IN const nstring &szName, IN int value);
	/**
	 * @brief �s�W����
	 * @param szName �����W��
	 * @param value ��
	 */
	void Add(IN const nstring &szName, IN unsigned int value);
	/**
	 * @brief �s�W����
	 * @param szName �����W��
	 * @param value ��
	 */
	void Add(IN const nstring &szName, IN float value);
	/**
	 * @brief �s�W����
	 * @param szName �����W��
	 * @param value ��
	 */
	void Add(IN const nstring &szName, IN double value);
	/**
	 * @brief �s�W����
	 * @param szName �����W��
	 * @param value ��
	 */
	void Add(IN const nstring &szName, IN const std::string &value);
	/**
	 * @brief �s�W����
	 * @param szName �����W��
	 * @param value ��
	 */
	void Add(IN const nstring &szName, IN const std::wstring &value);
	/**
	 * @brief �s�W�}�C����
	 * @param szName �����W��
	 * @param array �Ȱ}�C
	 */
	void Add(IN const nstring &szName, IN const std::vector<bool> &array);
	/**
	 * @brief �s�W�}�C����
	 * @param szName �����W��
	 * @param array �Ȱ}�C
	 */
	void Add(IN const nstring &szName, IN const std::vector<char> &array);
	/**
	 * @brief �s�W�}�C����
	 * @param szName �����W��
	 * @param array �Ȱ}�C
	 */
	void Add(IN const nstring &szName, IN const std::vector<unsigned char> &array);
	/**
	 * @brief �s�W�}�C����
	 * @param szName �����W��
	 * @param array �Ȱ}�C
	 */
	void Add(IN const nstring &szName, IN const std::vector<short> &array);
	/**
	 * @brief �s�W�}�C����
	 * @param szName �����W��
	 * @param array �Ȱ}�C
	 */
	void Add(IN const nstring &szName, IN const std::vector<unsigned short> &array);
	/**
	 * @brief �s�W�}�C����
	 * @param szName �����W��
	 * @param array �Ȱ}�C
	 */
	void Add(IN const nstring &szName, IN const std::vector<long> &array);
	/**
	 * @brief �s�W�}�C����
	 * @param szName �����W��
	 * @param array �Ȱ}�C
	 */
	void Add(IN const nstring &szName, IN const std::vector<unsigned long> &array);
	/**
	 * @brief �s�W�}�C����
	 * @param szName �����W��
	 * @param array �Ȱ}�C
	 */
	void Add(IN const nstring &szName, IN const std::vector<int> &array);
	/**
	 * @brief �s�W�}�C����
	 * @param szName �����W��
	 * @param array �Ȱ}�C
	 */
	void Add(IN const nstring &szName, IN const std::vector<unsigned int> &array);
	/**
	 * @brief �s�W�}�C����
	 * @param szName �����W��
	 * @param array �Ȱ}�C
	 */
	void Add(IN const nstring &szName, IN const std::vector<float> &array);
	/**
	 * @brief �s�W�}�C����
	 * @param szName �����W��
	 * @param array �Ȱ}�C
	 */
	void Add(IN const nstring &szName, IN const std::vector<double> &array);
	/**
	 * @brief �s�W�}�C����
	 * @param szName �����W��
	 * @param array �Ȱ}�C
	 */
	void Add(IN const nstring &szName, IN const std::vector<std::string> &array);
	/**
	 * @brief �s�W�}�C����
	 * @param szName �����W��
	 * @param array �Ȱ}�C
	 */
	void Add(IN const nstring &szName, IN const std::vector<std::wstring> &array);
	/**
	 * @brief �R������
	 * @param szName �����W��
	 */
	void Del(IN const nstring &szName);
	/**
	 * @brief ���o����
	 * @param szName �����W��
	 * @param value ��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT bool &value) const;
	/**
	 * @brief ���o����
	 * @param szName �����W��
	 * @param value ��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT char &value) const;
	/**
	 * @brief ���o����
	 * @param szName �����W��
	 * @param value ��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT unsigned char &value) const;
	/**
	 * @brief ���o����
	 * @param szName �����W��
	 * @param value ��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT short &value) const;
	/**
	 * @brief ���o����
	 * @param szName �����W��
	 * @param value ��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT unsigned short &value) const;
	/**
	 * @brief ���o����
	 * @param szName �����W��
	 * @param value ��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT long &value) const;
	/**
	 * @brief ���o����
	 * @param szName �����W��
	 * @param value ��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT unsigned long &value) const;
	/**
	 * @brief ���o����
	 * @param szName �����W��
	 * @param value ��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT int &value) const;
	/**
	 * @brief ���o����
	 * @param szName �����W��
	 * @param value ��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT unsigned int &value) const;
	/**
	 * @brief ���o����
	 * @param szName �����W��
	 * @param value ��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT float &value) const;
	/**
	 * @brief ���o����
	 * @param szName �����W��
	 * @param value ��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT double &value) const;
	/**
	 * @brief ���o����
	 * @param szName �����W��
	 * @param value ��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT std::string &value) const;
	/**
	 * @brief ���o����
	 * @param szName �����W��
	 * @param value ��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT std::wstring &value) const;
	/**
	 * @brief ���o�}�C����
	 * @param szName �����W��
	 * @param value �Ȱ}�C
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT std::vector<bool> &value) const;
	/**
	 * @brief ���o�}�C����
	 * @param szName �����W��
	 * @param value �Ȱ}�C
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT std::vector<char> &value) const;
	/**
	 * @brief ���o�}�C����
	 * @param szName �����W��
	 * @param value �Ȱ}�C
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT std::vector<unsigned char> &value) const;
	/**
	 * @brief ���o�}�C����
	 * @param szName �����W��
	 * @param value �Ȱ}�C
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT std::vector<short> &value) const;
	/**
	 * @brief ���o�}�C����
	 * @param szName �����W��
	 * @param value �Ȱ}�C
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT std::vector<unsigned short> &value) const;
	/**
	 * @brief ���o�}�C����
	 * @param szName �����W��
	 * @param value �Ȱ}�C
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT std::vector<long> &value) const;
	/**
	 * @brief ���o�}�C����
	 * @param szName �����W��
	 * @param value �Ȱ}�C
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT std::vector<unsigned long> &value) const;
	/**
	 * @brief ���o�}�C����
	 * @param szName �����W��
	 * @param value �Ȱ}�C
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT std::vector<int> &value) const;
	/**
	 * @brief ���o�}�C����
	 * @param szName �����W��
	 * @param value �Ȱ}�C
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT std::vector<unsigned int> &value) const;
	/**
	 * @brief ���o�}�C����
	 * @param szName �����W��
	 * @param value �Ȱ}�C
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT std::vector<float> &value) const;
	/**
	 * @brief ���o�}�C����
	 * @param szName �����W��
	 * @param value �Ȱ}�C
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT std::vector<double> &value) const;
	/**
	 * @brief ���o�}�C����
	 * @param szName �����W��
	 * @param value �Ȱ}�C
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT std::vector<std::string> &value) const;
	/**
	 * @brief ���o�}�C����
	 * @param szName �����W��
	 * @param value �Ȱ}�C
	 * @return true��ܦ��\, false�h�_
	 */
	bool Get(IN const nstring &szName, OUT std::vector<std::wstring> &value) const;
	/**
	 * @brief �H�r�ꫬ�A���o����
	 * @param szName �����W��
	 * @return ���G�r��
	 */
	std::string ToString(IN const nstring &szName) const;
	/**
	 * @brief �H�r�ꫬ�A���o����
	 * @param szName �����W��
	 * @return ���G�r��
	 */
	std::wstring ToWString(IN const nstring &szName) const;
	/**
	 * @brief �H�r�ꫬ�A���o�}�C����
	 * @param szName �����W��
	 * @param ulIndex ���ޭ�
	 * @return ���G�r��
	 */
	std::string ToString(IN const nstring &szName, IN unsigned long ulIndex) const;
	/**
	 * @brief �H�r�ꫬ�A���o�}�C����
	 * @param szName �����W��
	 * @param ulIndex ���ޭ�
	 * @return ���G�r��
	 */
	std::wstring ToWString(IN const nstring &szName, IN unsigned long ulIndex) const;
	/**
	 * @brief ���o�������A
	 * @param szName �����W��
	 */
	Json::ValueType Type(IN const nstring &szName) const;
	/**
	 * @brief �ˬd�����O�_�s�b
	 * @param szName �����W��
	 * @return true��ܦs�b, false�h�_
	 */
	bool IsExist(IN const nstring &szName) const;
	/**
	 * @brief �ˬd�O�_����
	 * @return true��ܬ���, false�h�_
	 */
	bool Empty() const;
	/**
	 * @brief ���ojson��ƪ���W�٦C��
	 * @return �W�٦C��
	 */
	std::vector<nstring> Member() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------