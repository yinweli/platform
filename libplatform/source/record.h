/**
 * @file record.h
 * @note �ʥ]�����ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _RECORD
#define _RECORD
//-----------------------------------------------------------------------------
/**
 * @brief �ʥ]�����������O
 */
class C_RecordKey
{
private:
	//-------------------------------------
	cstring m_szPacket; ///< �ʥ]�W��
	cstring m_szSource; ///< �ӷ���}
	cstring m_szTarget; ///< �ؼЦ�}
	//-------------------------------------

public:
	//-------------------------------------
	C_RecordKey() {};
	C_RecordKey(IN const cstring &packet, IN const cstring &source, IN const cstring &target) : m_szPacket(packet), m_szSource(source), m_szTarget(target) {};
	//-------------------------------------
	bool operator < (IN const C_RecordKey &rhs) const
	{
		return Key() < rhs.Key();
	};
	//-------------------------------------
	/**
	 * @brief ���o���ަr��
	 * @return ���ަr��
	 */
	cstring Key() const
	{
		return m_szPacket + __T(":") + m_szSource + __T(":") + m_szTarget;
	};
	/**
	 * @brief ���o�ʥ]�W��
	 * @return �ʥ]�W��
	 */
	cstring Packet() const
	{
		_G_();

		return m_szPacket;
	};
	/**
	 * @brief ���o�ӷ���}
	 * @return �ӷ���}
	 */
	cstring Source() const
	{
		_G_();

		return m_szSource;
	};
	/**
	 * @brief ���o�ؼЦ�}
	 * @return �ؼЦ�}
	 */
	cstring Target() const
	{
		_G_();

		return m_szTarget;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �ʥ]����������O
 */
class C_RecordData
{
private:
	//-------------------------------------
	unsigned __int64 m_ui64Size; ///< �ʥ]�j�p(bytes)
	unsigned __int64 m_ui64Count; ///< �ʥ]�ƶq
	//-------------------------------------

public:
	//-------------------------------------
	C_RecordData() : m_ui64Size(0), m_ui64Count(0) {};
	//-------------------------------------
	/**
	 * @brief �ʥ]����
	 */
	void Add(IN unsigned long ulSize)
	{
		_G_();

		m_ui64Size += ulSize;
		m_ui64Count++;
	};
	/**
	 * @brief ���o�ʥ]�j�p
	 * @return �ʥ]�j�p
	 */
	unsigned __int64 Size() const
	{
		_G_();

		return m_ui64Size;
	};
	/**
	 * @brief ���o�ʥ]�ƶq
	 * @return �ʥ]�ƶq
	 */
	unsigned __int64 Count() const
	{
		_G_();

		return m_ui64Count;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief �ʥ]�������O
 */
class C_Record
{
private:
	//-------------------------------------
	std::map<C_RecordKey, C_RecordData> m_Data; ///< �����C�� <���ު���, ��ƪ���>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	typedef std::map<C_RecordKey, C_RecordData>::const_iterator const_iterator; ///< ���N�����A
	//-------------------------------------

public:
	//-------------------------------------
	C_Record();
	virtual ~C_Record();
	//-------------------------------------
	/**
	 * @brief �M������
	 */
	void Clear();
	/**
	 * @brief ��������
	 * @param Packet �ʥ]����
	 * @param szSource �ӷ���}
	 * @param szTatget �ؼЦ�}
	 * @param ulSize �ʥ]�j�p
	 */
	void Record(IN LibCSNStandard::Packet ^Packet, IN const cstring &szSource, IN const cstring &szTatget, IN unsigned long ulSize);
	/**
	 * @brief ���o�����C��
	 * @return �����C��
	 */
	std::map<C_RecordKey, C_RecordData> Record() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------