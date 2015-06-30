/**
 * @file curlmulti.h
 * @note curl�h�����O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CURLMULTI
#define _CURLMULTI
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief curl�h�����O
 * @ingroup curl
 */
class C_CURLMulti
{
private:
	//-------------------------------------
	CURLM *m_pCURLM; ///< multi-curl handle
	std::map<CURL *, bool> m_Status; ///< �B�z���A�C�� <curl����, �B�z���A>
	//-------------------------------------

public:
	//-------------------------------------
	C_CURLMulti();
	virtual ~C_CURLMulti();
	//-------------------------------------
	/**
	 * @brief �w�ɳB�z
	 */
	void Process();
	/**
	 * @brief ����curl
	 * @param ccCURLMeta curl�椸����
	 * @return true��ܦ��\, false�h�_
	 */
	bool Perform(IN const C_CURLMeta &ccCURLMeta);
	/**
	 * @brief ���ocurl�O�_�s�b
	 * @param ccCURLMeta curl�椸����
	 * @return true��ܦs�b, false�h�_
	 */
	bool IsExist(IN const C_CURLMeta &ccCURLMeta) const;
	/**
	 * @brief ���ocurl�O�_����
	 * @param ccCURLMeta curl�椸����
	 * @return true��ܧ���, false�h�_(�άO���s�b)
	 */
	bool IsComplete(IN const C_CURLMeta &ccCURLMeta) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------