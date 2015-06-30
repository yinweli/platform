/**
 * @file curlmeta.h
 * @note curl�椸���O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CURLMETA
#define _CURLMETA
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief curl�H�����O
 * @ingroup curl
 */
class C_CURLChip
{
private:
	//-------------------------------------
	void *m_pData; ///< ��ƫ���
	unsigned long m_ulSize; ///< ��ƪ���
	//-------------------------------------

public:
	//-------------------------------------
	C_CURLChip();
	C_CURLChip(IN void *data, IN unsigned long size);
	virtual ~C_CURLChip();
	//-------------------------------------
	operator bool () const;
	operator void * () const;
	operator unsigned long () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief curl���G���O
 * @ingroup curl
 */
class C_CURLResult
{
private:
	//-------------------------------------
	void *m_pData; ///< ��ƫ���
	unsigned long m_ulSize; ///< ��ƪ���
	//-------------------------------------

public:
	//-------------------------------------
	C_CURLResult();
	C_CURLResult(IN const std::vector<C_CURLChip> &chip);
	virtual ~C_CURLResult();
	//-------------------------------------
	operator bool () const;
	operator void * () const;
	operator unsigned long () const;
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief curl�椸���O
 * @ingroup curl
 */
class C_CURLMeta : public C_CURLBase
{
	//-------------------------------------
	/**
	 * @brief �g�J���G�禡
	 * @param pResult ���G����
	 * @param count ���G�ƶq
	 * @param size ���G����
	 * @param pData �۩w�q����
	 * @return ��o�����G����
	 * @ingroup curl
	 */
	static size_t WriteResult(void *pResult, size_t count, size_t size, void *pData);
	//-------------------------------------

private:
	//-------------------------------------
	std::vector<C_CURLChip> m_Chip; ///< �H���C��
	//-------------------------------------

public:
	//-------------------------------------
	C_CURLMeta();
	virtual ~C_CURLMeta();
	//-------------------------------------
	/**
	 * @brief ����curl
	 * @return true��ܦ��\, false�h�_
	 */
	bool Perform();
	/**
	 * @brief ���o���G����
	 * @return ���G����
	 */
	C_CURLResult Result() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------