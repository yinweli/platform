/**
 * @file comtool.h
 * @note COM�������O
 * @author yinweli
 */
/**
 * @page �p��ϥ�comtool
 * comtool�ϥΦb��COM�������ާ@�W\n\n
 * �����إߤ@�ӹ���ϥ� C_ICom �ŧi�p�U\n\n
 * C_ICom<IDataInitialize> ccInterFace;\n\n
 * �M��b�ϥ�COM��k���o������, �� C_ICom.PPointer() �h���t�ε���������\n
 * �o�̭n�`�N, �b���o�������ɭ�, �����n������ഫ�� void ** ���A\n\n
 * CoCreateInstance(CLSID_MSDAINITIALIZE, nullptr, CLSCTX_INPROC_SERVER, IID_IDataInitialize, (void **)ccInterFace.PPointer());\n\n
 * ����p�G�n�ϥΤ�������k, �ݭn�z�L C_ICom.Pointer() �Өϥ�\n\n
 * ccInterFace.Pointer()->GetDataSource(...);\n\n
 * ����������h�|�b������Q�R���ɦ۰ʳQ����\n
 * �p�G�Q�n�ۤv���e���񪺸�, �i�H�I�s C_ICom.DelData() ������\n\n
 * --------------------------------------------------\n
 * Header           : comtool.h\n
 * Library(debug)   : \n
 * Library(release) : \n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref comtool
 */
/** @defgroup comtool */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _COMTOOL
#define _COMTOOL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief COM�������O, �Ѻc�ɷ|�۰����񤶭�
 * @ingroup comtool
 */
template<class T> class C_ICom
{
protected:
	//-------------------------------------
	T *m_pData; ///< COM��������
	//-------------------------------------

public:
	//-------------------------------------
	C_ICom() : m_pData(nullptr) {};
	virtual ~C_ICom() { DelData(); };
	//-------------------------------------
	// == �B��l
	bool operator == (IN T *p) { return m_pData == p; };
	// != �B��l
	bool operator != (IN T *p) { return m_pData != p; };
	//-------------------------------------
	/**
	 * @brief �]�w����
	 * @param p ����
	 */
	inline void SetData(IN T *p) { m_pData = p; };
	/**
	 * @brief ���񤶭�
	 * @note ���񤶭�����, ���i�H�I�s Pointer() �άO PPointer(),  �_�h�|�X�{���i�w�������~
	 */
	inline void DelData() { if(m_pData){ m_pData->Release(); m_pData = nullptr; } };
	/**
	 * @brief ���o����
	 * @note ���o��������, �ϥΪ̥����h�ˬd�����O�_����(���i�� nullptr)
	 * @return ����
	 */
	inline T *Pointer() { return m_pData; };
	/**
	 * @brief ���o����������
	 * @return ����������
	 */
	inline T **PPointer() { return &m_pData; };
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------