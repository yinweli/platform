/**
 * @file xlistnotice.h
 * @note �q���C�����O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XLISTNOTICE
#define _XLISTNOTICE
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �q���C�|
 * @ingroup xlist
 */
enum ENUM_XNotice
{
	ENUM_XNotice_NULL = 0, ///< �L��
	ENUM_XNotice_Connect, ///< �s�u����
	ENUM_XNotice_Disconnect, ///< �_�u����
	ENUM_XNotice_Receive, ///< �������

	ENUM_XNotice_FORCE_DWORD = ENUM_FORCE_DWORD, 
};
//-----------------------------------------------------------------------------
/**
 * @brief ����������O
 * @ingroup xlist
 */
class C_XComplete
{
private:
	//-------------------------------------
	const void *m_pData; ///< ��ƫ���
	unsigned long m_ulSize; ///< ��ƪ���
	//-------------------------------------

public:
	//-------------------------------------
	C_XComplete();
	C_XComplete(IN const void *data, IN unsigned long size);
	virtual ~C_XComplete();
	//-------------------------------------
	/**
	 * @brief ����
	 */
	void Release();
	/**
	 * @brief ���o��ƫ���
	 * @return ��ƫ���
	 */
	const void *Data() const;
	/**
	 * @brief ���o��ƪ���
	 * @return ��ƪ���
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
/**
 * @brief �q�����O
 * @ingroup xlist
 */
class C_XNotice
{
private:
	//-------------------------------------
	unsigned long m_ulTime; ///< ���ͮɶ�, �HtimeGetTime�禡����
	ENUM_XNotice m_emType; ///< �q���C�|
	SOCKET m_Socket; ///< SocketID
	C_XComplete m_ccComplete; ///< ������ƪ���
	//-------------------------------------

public:
	//-------------------------------------
	C_XNotice();
	C_XNotice(IN ENUM_XNotice type, IN SOCKET s);
	C_XNotice(IN ENUM_XNotice type, IN SOCKET s, IN const C_XComplete &complete);
	virtual ~C_XNotice();
	//-------------------------------------
	/**
	 * @brief ���o���ͮɶ�
	 * @return ���ͮɶ�
	 */
	unsigned long Time() const;
	/**
	 * @brief ���o�q���C�|
	 * @return �q���C�|
	 */
	ENUM_XNotice Type() const;
	/**
	 * @brief ���oSocketID
	 * @return SocketID
	 */
	SOCKET Socket() const;
	/**
	 * @brief ���o������ƪ���
	 * @return ������ƪ���
	 */
	C_XComplete Complete() const;
	/**
	 * @brief �ˬd�O�_����
	 * @return true��ܬ���, false�h�_
	 */
	bool Empty() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �q���C�����O
 * @ingroup xlist
 */
class C_XListNotice
{
private:
	//-------------------------------------
	std::deque<C_XNotice> m_Notice; ///< �q���C��
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_XListNotice();
	virtual ~C_XListNotice();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W�s�u�����q��
	 * @param Socket SocketID
	 */
	void AddConnect(IN SOCKET Socket);
	/**
	 * @brief �s�W�_�u�����q��
	 * @param Socket SocketID
	 */
	void AddDisconnect(IN SOCKET Socket);
	/**
	 * @brief �s�W������Ƴq��
	 * @param Socket SocketID
	 * @param ccComplete ������ƪ���
	 */
	void AddReceive(IN SOCKET Socket, IN const C_XComplete &ccComplete);
	/**
	 * @brief ���o�q������C��
	 * @param ulMax �q������̤j�ƶq
	 * @return �q������C��
	 */
	std::vector<C_XNotice> List(IN unsigned long ulMax);
	/**
	 * @brief ���o�q���ƶq
	 * @return �q���ƶq
	 */
	unsigned long Size() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------