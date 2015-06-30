/**
 * @file dbf.h
 * @note dbf�ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _DBF
#define _DBF
//-----------------------------------------------------------------------------
/**
 * @brief dbf�������c
 */
struct S_RecordDBF
{
	cstring szFilePath; ///< dbf�ɦW���|
	int iSize; ///< dbf��Ƽƶq

	S_RecordDBF();
	S_RecordDBF(IN const cstring &filepath, IN int size);
};
//-----------------------------------------------------------------------------
/**
 * @brief dbf���O
 */
class C_DBF
{
private:
	//-------------------------------------
	gcroot<LibCSNStandard::DBFData ^> m_Data; ///< dbf���
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_DBF();
	virtual ~C_DBF();
	//-------------------------------------
	/**
	 * @brief �s�Wdbf
	 * @param szName dbf�W��
	 * @param szClass ���O�W��(�]�A�R�W�Ŷ��P���O�W��, �� . ���j)
	 * @param szComponent �ե�W��
	 * @param szFilePath �ɦW���|
	 * @return true��ܦ��\, false�h�_
	 */
	bool Add(IN const cstring &szName, IN const cstring &szClass, IN const cstring &szComponent, IN const cstring &szFilePath);
	/**
	 * @brief ���sŪ��dbf
	 * @return true��ܦ��\, false�h�_
	 */
	bool Reload();
	/**
	 * @brief ���sŪ��dbf
	 * @param szName dbf�W��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Reload(IN const cstring &szName);
	/**
	 * @brief ���odbf
	 * @param szName dbf�W��
	 * @param ccGUID ���ު���
	 * @return dbf����
	 */
	LibCSNStandard::DBF ^Get(IN const cstring &szName, IN const C_Argu &ccGUID);
	/**
	 * @brief ���odbf���N��
	 * @param szName dbf�W��
	 * @return dbf���N��
	 */
	LibCSNStandard::DBFItor ^Get(IN const cstring &szName);
	/**
	 * @brief ���o�����C��
	 * @return �����C��
	 */
	std::map<cstring, S_RecordDBF> Record() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------