/**
 * @file objdbf.h
 * @note dbf�ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJDBF
#define _OBJDBF
//-----------------------------------------------------------------------------
/**
 * @brief dbf���O
 */
class C_ObjDBF : public C_Object
{
public:
	//-------------------------------------
	C_ObjDBF(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief �s�Wdbf
	 * @param szName dbf�W��
	 * @param szClass ���O�W��(�]�A�R�W�Ŷ��P���O�W��, �� . ���j)
	 * @param szComponent �ե�W��
	 * @param szFilePath �ɦW���|
	 * @return true��ܦ��\, false�h�_
	 */
	bool Add(IN const cstring &szName, IN const cstring &szClass, IN const cstring &szComponent, IN const cstring &szFilePath)
	{
		_G_();

		return C_Platform::Instance().GetDBF().Add(szName, szClass, szComponent, szFilePath);
	};
	/**
	 * @brief ���sŪ��dbf
	 * @return true��ܦ��\, false�h�_
	 */
	bool Reload()
	{
		_G_();

		return C_Platform::Instance().GetDBF().Reload();
	};
	/**
	 * @brief ���sŪ��dbf
	 * @param szName dbf�W��
	 * @return true��ܦ��\, false�h�_
	 */
	bool Reload(IN const cstring &szName)
	{
		_G_();

		return C_Platform::Instance().GetDBF().Reload(szName);
	};
	/**
	 * @brief ���odbf
	 * @param szName dbf�W��
	 * @param ccGUID ���ު���
	 * @return dbf����
	 */
	LibCSNStandard::DBF ^Get(IN const cstring &szName, IN const C_Argu &ccGUID)
	{
		_G_();

		return C_Platform::Instance().GetDBF().Get(szName, ccGUID);
	};
	/**
	 * @brief ���odbf���N��
	 * @param szName dbf�W��
	 * @return dbf���N��
	 */
	LibCSNStandard::DBFItor ^Get(IN const cstring &szName)
	{
		_G_();

		return C_Platform::Instance().GetDBF().Get(szName);
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------