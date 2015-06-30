/**
 * @file objbenchmark.h
 * @note 效能紀錄組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJBENCHMARK
#define _OBJBENCHMARK
//-----------------------------------------------------------------------------
/**
 * @brief 效能紀錄類別
 */
class C_ObjBenchmark : public C_Object
{
public:
	//-------------------------------------
	C_ObjBenchmark(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief 取得效能紀錄物件
	 * @param szName 效能名稱
	 * @return 效能紀錄物件
	 */
	C_BMObj Get(IN const cstring &szName)
	{
		_G_();

		return C_BMObj(C_Platform::Instance().GetBMData(), C_BMDataKey(m_szServer, szName));
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------