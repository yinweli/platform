/**
 * @file database.h
 * @note ��Ʈw�ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _DATABASE
#define _DATABASE
//-----------------------------------------------------------------------------
/**
 * @brief ��Ʈw�������c
 */
struct S_RecordDatabase
{
	cstring szType; ///< ��Ʈw���A
	cstring szDBAddr; ///< ��Ʈw��}
	cstring szDBName; ///< ��Ʈw�W��

	S_RecordDatabase();
	S_RecordDatabase(IN C_DBase &dbase);
};
//-----------------------------------------------------------------------------
/**
 * @brief ��Ʈw���O
 */
class C_Database
{
private:
	//-------------------------------------
	std::map<cstring, C_DBase *> m_Data; ///< ��Ʈw��� <�ѧO�W��, ��Ʈw����>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_Database();
	virtual ~C_Database();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief �w�ɳB�z
	 */
	void Process();
	/**
	 * @brief �s�W��Ʈw
	 * @param szName �ѧO�W��
	 * @param szType ��Ʈw���A
	 * @param szDBAddr ��Ʈw��}
	 * @param szDBName ��Ʈw�W��
	 * @param szUserID ��Ʈw�b��
	 * @param szPassword ��Ʈw�K�X
	 * @return true��ܦ��\, false�h�_
	 */
	bool Add(IN const cstring &szName, IN const cstring szType, IN const cstring &szDBAddr, IN const cstring &szDBName, IN const cstring &szUserID, IN const cstring &szPassword);
	/**
	 * @brief ���o��Ʈw����
	 * @param szName �ѧO�W��
	 * @return ��Ʈw����
	 */
	C_DBase *Get(IN const cstring &szName);
	/**
	 * @brief ���o�����C��
	 * @return �����C��
	 */
	std::map<cstring, S_RecordDatabase> Record() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------