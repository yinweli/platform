/**
 * @file formtable.h
 * @note �榡�ƪ�����O
 * @author yinweli
 */
/**
 * @page �p��ϥ�formtable
 * formtable�Ω�إߪ��r��\n\n
 * �����إߤ@�ӹ���ϥ� C_FormTable �ŧi�p�U\n\n
 * C_FormTable ccFormTable;\n\n
 * �M��I�s C_FormTable.SetContent() �禡�ӳ]�w��椺�e\n
 * ���e�]�w������I�s C_FormTable.Export() �禡��X����e����\n\n
 * --------------------------------------------------\n
 * Header           : formtable.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref formtable
 */
/** @defgroup formtable */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _FORMTABLE
#define _FORMTABLE
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\_nstroutf\_nstroutf.h"
#include "..\algorithm\algorithm.h"
#include "..\argument\argument.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �榡�ƪ�����O
 * @ingroup formtable
 */
class C_FormTable
{
private:
	//-------------------------------------
	std::map<nstring, nstring> m_Data; ///< ���C�� <�y�Цr��, ���e�r��>
	int m_iSizeX; ///< x�b����
	int m_iSizeY; ///< y�b����
	//-------------------------------------

public:
	//-------------------------------------
	TCHAR Vertical; ///< ���u�r��
	TCHAR Horizontal; ///< ��u�r��
	TCHAR Cross; ///< ����r��
	//-------------------------------------

private:
	//-------------------------------------
	/**
	 * @brief ���o���צC��
	 * @return ���צC��
	 */
	std::vector<int> Length() const;
	/**
	 * @brief ���o�y�Цr��
	 * @param iX x�b�y��
	 * @param iY y�b�y��
	 * @return �y�Цr��
	 */
	nstring StringCoor(IN int iX, IN int iY) const;
	/**
	 * @brief �إ߮�u�r��
	 * @param Len ���צC��
	 * @return ��u�r��
	 */
	nstring StringLine(IN const std::vector<int> &Len) const;
	/**
	 * @brief �إߤ��e�r��
	 * @param Len ���צC��
	 * @param Data ��ƦC��
	 * @param bAlign ����X��
	 * @return ���e�r��
	 */
	nstring StringData(IN const std::vector<int> &Len, IN const std::vector<nstring> &Data, IN bool bAlign) const;
	//-------------------------------------

public:
	//-------------------------------------
	C_FormTable();
	virtual ~C_FormTable();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �]�w���e
	 * @param iX x�b�y��
	 * @param iY y�b�y��
	 * @param ccData ��ƪ���
	 */
	void Set(IN int iX, IN int iY, IN const C_Argu &ccData);
	/**
	 * @brief �s�W���e
	 * @param Data ��ƦC��
	 */
	void Add(IN const std::vector<nstring> &Data);
	/**
	 * @brief �s�W���e
	 * @param ccData ��ƦC��
	 */
	void Add(IN const C_Argv &ccData);
	/**
	 * @brief ��X���
	 * @return ���G�C��
	 */
	std::vector<nstring> ExportList() const;
	/**
	 * @brief ��X���
	 * @return ���G�r��
	 */
	nstring ExportString() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------