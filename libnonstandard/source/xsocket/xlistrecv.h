/**
 * @file xlistrecv.h
 * @note �����C�����O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XLISTRECV
#define _XLISTRECV
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ����������O
 * @ingroup xlist
 */
class C_XRecv
{
private:
	//-------------------------------------
	void *m_pData; ///< ��ƫ���
	unsigned long m_ulSize; ///< ��ƪ���
	unsigned long m_ulRecv; ///< ��������
	//-------------------------------------

public:
	//-------------------------------------
	C_XRecv();
	virtual ~C_XRecv();
	//-------------------------------------
	operator C_XComplete () const;
	//-------------------------------------
	/**
	 * @brief ��l��
	 * @param ulSize ��ƪ���
	 * @return true��ܦ��\, false�h�_
	 */
	bool Initialize(IN unsigned long ulSize);
	/**
	 * @brief ����
	 */
	void Release();
	/**
	 * @brief �s�W���
	 * @param ccPoint ���о�����
	 */
	void Add(IN C_XPoint &ccPoint);
	/**
	 * @brief �ˬd�O�_����
	 * @return true��ܬ���, false�h�_
	 */
	bool Empty() const;
	/**
	 * @brief �ˬd�O�_����
	 * @return true��ܧ���, false�h�_
	 */
	bool IsComplete() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �����C�����O
 * @ingroup xlist
 */
class C_XListRecv
{
private:
	//-------------------------------------
	std::deque<C_XRecv> m_Recv; ///< ������ƦC��
	//-------------------------------------

public:
	//-------------------------------------
	C_XListRecv();
	virtual ~C_XListRecv();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W�������
	 * @param pData ��ƫ���
	 * @param ulSize ��ƪ���
	 * @return true��ܦ��\, false�h�_
	 */
	bool Add(IN const void *pData, IN unsigned long ulSize);
	/**
	 * @brief ���o������ƪ���
	 * @return ������ƪ���
	 */
	C_XRecv Get();
	/**
	 * @brief ���o������Ƽƶq
	 * @return ������Ƽƶq
	 */
	unsigned long Size() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------