/**
 * @file bmdata.h
 * @note 效能紀錄組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _BMDATA
#define _BMDATA
//-----------------------------------------------------------------------------
class C_BMData;
//-----------------------------------------------------------------------------
/**
 * @brief 效能紀錄結構
 */
struct S_RecordBMData
{
	int iCount; ///< 總執行次數
	int iFPS; ///< 每秒執行次數
	int iTotal; ///< 總執行時間
	int iLongest; ///< 最長執行時間
	int iAverage; ///< 平均執行時間

	S_RecordBMData() : iCount(0), iFPS(0), iTotal(0), iLongest(0), iAverage(0) {};
	S_RecordBMData(IN const C_Benchmark &benchmark) : iCount(benchmark.Count()), iFPS(benchmark.FPS()), iTotal(benchmark.Total()), iLongest(benchmark.Longest()), iAverage(benchmark.Average()) {};
};
//-----------------------------------------------------------------------------
/**
 * @brief 效能記錄索引類別
 */
class C_BMDataKey
{
private:
	//-------------------------------------
	cstring m_szServer; ///< 伺服器名稱
	cstring m_szName; ///< 識別名稱
	//-------------------------------------

public:
	//-------------------------------------
	C_BMDataKey() {};
	C_BMDataKey(IN const cstring &server, IN const cstring &name) : m_szServer(server), m_szName(name) {};
	//-------------------------------------
	bool operator < (IN const C_BMDataKey &rhs) const
	{
		return Key() < rhs.Key();
	};
	operator bool () const
	{
		return Key().empty() == false;
	};
	//-------------------------------------
	/**
	 * @brief 取得索引字串
	 * @return 索引字串
	 */
	cstring Key() const
	{
		return m_szServer + __T(":") + m_szName;
	};
	/**
	 * @brief 取得伺服器名稱
	 * @return 伺服器名稱
	 */
	cstring Server() const
	{
		_G_();

		return m_szServer;
	};
	/**
	 * @brief 取得識別名稱
	 * @return 識別名稱
	 */
	cstring Name() const
	{
		_G_();

		return m_szName;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 效能紀錄類別
 */
class C_BMObj
{
private:
	//-------------------------------------
	C_BMData *m_pBMData; ///< 效能列表指標
	C_BMDataKey m_ccKey; ///< 索引物件
	//-------------------------------------

public:
	//-------------------------------------
	C_BMObj();
	C_BMObj(IN C_BMData &bmdata, IN const C_BMDataKey &key);
	virtual ~C_BMObj();
	//-------------------------------------
};
//-----------------------------------------------------------------------------
/**
 * @brief 效能列表類別
 */
class C_BMData
{
private:
	//-------------------------------------
	std::map<C_BMDataKey, C_Benchmark> m_Data; ///< 效能列表 <索引物件, 效能物件>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< 共用同步鎖
	//-------------------------------------

public:
	//-------------------------------------
	C_BMData();
	virtual ~C_BMData();
	//-------------------------------------
	/**
	 * @brief 清除全部
	 */
	void Clear();
	/**
	 * @brief 定時處理
	 */
	void Process();
	/**
	 * @brief 開始記錄
	 * @param ccKey 索引物件
	 */
	void Start(IN const C_BMDataKey &ccKey);
	/**
	 * @brief 結束記錄
	 * @param ccKey 索引物件
	 */
	void End(IN const C_BMDataKey &ccKey);
	/**
	 * @brief 取得紀錄列表
	 * @param szServer 伺服器名稱
	 * @return 紀錄列表
	 */
	std::map<cstring, S_RecordBMData> Record(IN const cstring &szServer) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------