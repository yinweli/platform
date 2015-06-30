/**
 * @file winlist.h
 * @note ������T�C�����O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _WINLIST
#define _WINLIST
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ������T���c
 * @ingroup winlist
 */
struct S_Windows
{
	HWND hWnd; ///< ��������N�X
	nstring szName; ///< �����W��

	S_Windows(IN HWND h, IN const nstring &name);
};
//-----------------------------------------------------------------------------
/**
 * @brief ������T�C�����O
 * @ingroup winlist
 */
class C_WinList
{
private:
	//-------------------------------------
	std::vector<S_Windows> m_Windows; ///< ������T�C��
	//-------------------------------------

public:
	//-------------------------------------
	typedef std::vector<S_Windows>::const_iterator const_iterator; ///< ������T�C���N�����O
	//-------------------------------------

public:
	//-------------------------------------
	C_WinList();
	virtual ~C_WinList();
	//-------------------------------------
	/**
	 * @brief ��l��
	 * @return true��ܰ��榨�\, false�h�_
	 */
	bool Initialize();
	/**
	 * @brief ���o�C��}�Y���N��
	 * @return ���N��
	 */
	C_WinList::const_iterator Begin() const;
	/**
	 * @brief ���o�C�������N��
	 * @return ���N��
	 */
	C_WinList::const_iterator End() const;
	/**
	 * @brief ���o�ƶq
	 * @return �ƶq
	 */
	unsigned long Size() const;
	/**
	 * @brief �ˬd�O�_����
	 * @return true��ܬ���, false�h�_
	 */
	bool Empty() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------