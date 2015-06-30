/**
 * @file bmdata.h
 * @note �į�����ե�
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
 * @brief �į�������c
 */
struct S_RecordBMData
{
	int iCount; ///< �`���榸��
	int iFPS; ///< �C����榸��
	int iTotal; ///< �`����ɶ�
	int iLongest; ///< �̪�����ɶ�
	int iAverage; ///< ��������ɶ�

	S_RecordBMData() : iCount(0), iFPS(0), iTotal(0), iLongest(0), iAverage(0) {};
	S_RecordBMData(IN const C_Benchmark &benchmark) : iCount(benchmark.Count()), iFPS(benchmark.FPS()), iTotal(benchmark.Total()), iLongest(benchmark.Longest()), iAverage(benchmark.Average()) {};
};
//-----------------------------------------------------------------------------
/**
 * @brief �į�O���������O
 */
class C_BMDataKey
{
private:
	//-------------------------------------
	cstring m_szServer; ///< ���A���W��
	cstring m_szName; ///< �ѧO�W��
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
	 * @brief ���o���ަr��
	 * @return ���ަr��
	 */
	cstring Key() const
	{
		return m_szServer + __T(":") + m_szName;
	};
	/**
	 * @brief ���o���A���W��
	 * @return ���A���W��
	 */
	cstring Server() const
	{
		_G_();

		return m_szServer;
	};
	/**
	 * @brief ���o�ѧO�W��
	 * @return �ѧO�W��
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
 * @brief �į�������O
 */
class C_BMObj
{
private:
	//-------------------------------------
	C_BMData *m_pBMData; ///< �į�C�����
	C_BMDataKey m_ccKey; ///< ���ު���
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
 * @brief �į�C�����O
 */
class C_BMData
{
private:
	//-------------------------------------
	std::map<C_BMDataKey, C_Benchmark> m_Data; ///< �į�C�� <���ު���, �įફ��>
	//-------------------------------------
	CRITICAL_SECTION m_csCommon; ///< �@�ΦP�B��
	//-------------------------------------

public:
	//-------------------------------------
	C_BMData();
	virtual ~C_BMData();
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
	 * @brief �}�l�O��
	 * @param ccKey ���ު���
	 */
	void Start(IN const C_BMDataKey &ccKey);
	/**
	 * @brief �����O��
	 * @param ccKey ���ު���
	 */
	void End(IN const C_BMDataKey &ccKey);
	/**
	 * @brief ���o�����C��
	 * @param szServer ���A���W��
	 * @return �����C��
	 */
	std::map<cstring, S_RecordBMData> Record(IN const cstring &szServer) const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------