/**
 * @file xlistsend.h
 * @note �ǰe�C�����O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XLISTSEND
#define _XLISTSEND
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �ǰe������O
 * @ingroup xlist
 */
class C_XSend
{
private:
	//-------------------------------------
	void *m_pData; ///< ��ƫ���
	unsigned long m_ulSize; ///< ��ƪ���
	//-------------------------------------

public:
	//-------------------------------------
	C_XSend();
	virtual ~C_XSend();
	//-------------------------------------
	operator WSABUF () const;
	//-------------------------------------
	/**
	 * @brief ��l��
	 * @param pData ��ƫ���
	 * @param ulSize ��ƪ���
	 * @return true��ܦ��\, false�h�_
	 */
	bool Initialize(IN const void *pData, IN unsigned long ulSize);
	/**
	 * @brief ����
	 */
	void Release();
	/**
	 * @brief �ˬd�O�_����
	 * @return true��ܬ���, false�h�_
	 */
	bool Empty() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �ǰe�C�����O
 * @ingroup xlist
 */
class C_XListSend
{
private:
	//-------------------------------------
	std::deque<C_XSend> m_Send; ///< �ǰe��ƦC��
	//-------------------------------------

public:
	//-------------------------------------
	C_XListSend();
	virtual ~C_XListSend();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W�ǰe���
	 * @param pData ��ƫ���
	 * @param ulSize ��ƪ���
	 * @return true��ܦ��\, false�h�_
	 */
	bool Add(IN const void *pData, IN unsigned long ulSize);
	/**
	 * @brief ���o�ǰe��ƪ���
	 * @return �ǰe��ƪ���
	 */
	C_XSend Get();
	/**
	 * @brief ���o�ǰe��Ƽƶq
	 * @return �ǰe��Ƽƶq
	 */
	unsigned long Size() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------