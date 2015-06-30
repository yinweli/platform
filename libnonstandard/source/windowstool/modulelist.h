/**
 * @file modulelist.h
 * @note �ҲզC�����O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _MODULELIST
#define _MODULELIST
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �Ҳո�T���c
 * @ingroup modulelist
 */
struct S_Module
{
	unsigned long ulHandle; ///< �Ҳժ�����N�X
	unsigned long ulProcessID; ///< ���Ҳթ��ݳB�z�{�Ǳ���N�X
	unsigned long ulAddress; ///< �Ҳժ��}�l��}
	unsigned long ulSize; ///< �Ҳժ��j�p, ���:bytes
	nstring szModuleName; ///< �ҲզW��
	nstring szModulePath; ///< �Ҳո��|

	S_Module(IN MODULEENTRY32 &r);
};
//-----------------------------------------------------------------------------
/**
 * @brief �ҲզC�����O
 * @ingroup modulelist
 */
class C_ModuleList
{
private:
	//-------------------------------------
	std::vector<S_Module> m_Module; ///< �Ҳո�T�C��
	//-------------------------------------

public:
	//-------------------------------------
	typedef std::vector<S_Module>::const_iterator const_iterator; ///< �Ҳո�T�C���N�����O
	//-------------------------------------

public:
	//-------------------------------------
	C_ModuleList();
	virtual ~C_ModuleList();
	//-------------------------------------
	/**
	 * @brief ��l��
	 * @param ulProcessID �B�z�{�Ǳ���N�X
	 * @return true��ܰ��榨�\, false�h�_
	 */
	bool Initialize(IN unsigned long ulProcessID = GetCurrentProcessId());
	/**
	 * @brief ���o�C��}�Y���N��
	 * @return ���N��
	 */
	C_ModuleList::const_iterator Begin() const;
	/**
	 * @brief ���o�C�������N��
	 * @return ���N��
	 */
	C_ModuleList::const_iterator End() const;
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