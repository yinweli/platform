/**
 * @file xlistconnect.h
 * @note �s�u�C�����O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XLISTCONNECT
#define _XLISTCONNECT
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief �s�u���c
 * @ingroup xlist
 */
struct S_XConnect
{
	C_IPData ccIPData; ///< ��}����
	SOCKET Socket; ///< SocketID

	S_XConnect();
	S_XConnect(IN const C_IPData &ipdata);
};
//-----------------------------------------------------------------------------
/**
 * @brief �s�u�C�����O
 * @ingroup xlist
 */
class C_XListConnect
{
private:
	//-------------------------------------
	std::vector<S_XConnect> m_Connect; ///< �s�u�C��
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_XListConnect();
	virtual ~C_XListConnect();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W�s�u
	 * @param ccIPData ��}����
	 */
	void Add(IN const C_IPData &ccIPData);
	/**
	 * @brief �]�w�s�u
	 * @param ccIPData ��}����
	 * @param Socket SocketID
	 */
	void Set(IN const C_IPData &ccIPData, IN SOCKET Socket);
	/**
	 * @brief �]�w�s�u
	 * @param SocketOld �ª�SocketID
	 * @param SocketNew �s��SocketID
	 */
	void Set(IN SOCKET SocketOld, IN SOCKET SocketNew);
	/**
	 * @brief �R���s�u
	 * @param Socket SocketID
	 */
	void Del(IN SOCKET Socket);
	/**
	 * @brief ���o��}����
	 * @param Socket SocketID
	 * @return ��}����
	 */
	C_IPData IPData(IN SOCKET Socket) const;
	/**
	 * @brief ���o�s�u�ƶq
	 * @return �s�u�ƶq
	 */
	unsigned long Size() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------