/**
 * @file record.h
 * @note 封包紀錄組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _RECORD
#define _RECORD
//-----------------------------------------------------------------------------
/**
 * @brief 封包紀錄索引類別
 */
class C_RecordKey
{
private:
	//-------------------------------------
	cstring m_szPacket; ///< 封包名稱
	cstring m_szSource; ///< 來源位址
	cstring m_szTarget; ///< 目標位址
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
	 * @brief 取得索引字串
	 * @return 索引字串
	 */
	cstring Key() const
	{
		return m_szPacket + __T(":") + m_szSource + __T(":") + m_szTarget;
	};
	/**
	 * @brief 取得封包名稱
	 * @return 封包名稱
	 */
	cstring Packet() const
	{
		_G_();

		return m_szPacket;
	};
	/**
	 * @brief 取得來源位址
	 * @return 來源位址
	 */
	cstring Source() const
	{
		_G_();

		return m_szSource;
	};
	/**
	 * @brief 取得目標位址
	 * @return 目標位址
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
 * @brief 封包紀錄資料類別
 */
class C_RecordData
{
private:
	//-------------------------------------
	unsigned __int64 m_ui64Size; ///< 封包大小(bytes)
	unsigned __int64 m_ui64Count; ///< 封包數量
	//-------------------------------------

public:
	//-------------------------------------
	C_RecordData() : m_ui64Size(0), m_ui64Count(0) {};
	//-------------------------------------
	/**
	 * @brief 封包紀錄
	 */
	void Add(IN unsigned long ulSize)
	{
		_G_();

		m_ui64Size += ulSize;
		m_ui64Count++;
	};
	/**
	 * @brief 取得封包大小
	 * @return 封包大小
	 */
	unsigned __int64 Size() const
	{
		_G_();

		return m_ui64Size;
	};
	/**
	 * @brief 取得封包數量
	 * @return 封包數量
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
 * @brief 封包紀錄類別
 */
class C_Record
{
private:
	//-------------------------------------
	std::map<C_RecordKey, C_RecordData> m_Data; ///< 紀錄列表 <索引物件, 資料物件>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	typedef std::map<C_RecordKey, C_RecordData>::const_iterator const_iterator; ///< 迭代器型態
	//-------------------------------------

public:
	//-------------------------------------
	C_Record();
	virtual ~C_Record();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 網路紀錄
	 * @param Packet 封包物件
	 * @param szSource 來源位址
	 * @param szTatget 目標位址
	 * @param ulSize 封包大小
	 */
	void Record(IN LibCSNStandard::Packet ^Packet, IN const cstring &szSource, IN const cstring &szTatget, IN unsigned long ulSize);
	/**
	 * @brief 取得紀錄列表
	 * @return 紀錄列表
	 */
	std::map<C_RecordKey, C_RecordData> Record() const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------