/**
 * @file xlistoverlapped.h
 * @note ���|�C�����O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XLISTOVERLAPPED
#define _XLISTOVERLAPPED
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief ���|�����C�|
 * @ingroup xlist
 */
enum ENUM_XOverlapped
{
	ENUM_XOverlapped_NULL = 0, ///< �L��
	ENUM_XOverlapped_Accept, ///< �����s�u
	ENUM_XOverlapped_Connect, ///< ���ݳs�u
	ENUM_XOverlapped_Recv, ///< ����
	ENUM_XOverlapped_Send, ///< �ǰe

	ENUM_XOverlapped_FORCE_DWORD = ENUM_FORCE_DWORD, 
};
//-----------------------------------------------------------------------------
/**
 * @brief ���|���c
 * @ingroup xlist
 */
struct S_XOverlapped
{
	OVERLAPPED sOverlapped; ///< ���|���c
	char cBuffer[XSOCKET_BUFFERSIZE]; ///< �ǿ�w�İ�
	ENUM_XOverlapped emType; ///< ���|����
	SOCKET Socket; ///< SocketID

	S_XOverlapped();
	S_XOverlapped(IN ENUM_XOverlapped type, IN SOCKET socket);
	operator OVERLAPPED & ();
	operator OVERLAPPED * ();
	bool operator < (IN const S_XOverlapped &rhs) const;
};
//-----------------------------------------------------------------------------
/**
 * @brief ���|�C�����O
 * @ingroup xlist
 */
class C_XListOverlapped
{
private:
	//-------------------------------------
	std::set<S_XOverlapped> m_Overlapped; ///< ���|�C��
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_XListOverlapped();
	virtual ~C_XListOverlapped();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �s�W���|����
	 * @param emType ���|����
	 * @param Socket SocketID
	 * @return ���|����
	 */
	S_XOverlapped *Add(IN ENUM_XOverlapped emType, IN SOCKET Socket);
	/**
	 * @brief �R�����|����
	 * @param emType ���|����
	 * @param Socket SocketID
	 */
	void Del(IN ENUM_XOverlapped emType, IN SOCKET Socket);
	/**
	 * @brief ���o���|����ƶq
	 * @return ���|����ƶq
	 */
	unsigned long Size() const;
	/**
	 * @brief ���o���w���|��������ƶq
	 * @param emType ���|����
	 * @return ���|����ƶq
	 */
	unsigned long Size(IN ENUM_XOverlapped emType) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------