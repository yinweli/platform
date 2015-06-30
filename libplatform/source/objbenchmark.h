/**
 * @file objbenchmark.h
 * @note �į�����ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _OBJBENCHMARK
#define _OBJBENCHMARK
//-----------------------------------------------------------------------------
/**
 * @brief �į�������O
 */
class C_ObjBenchmark : public C_Object
{
public:
	//-------------------------------------
	C_ObjBenchmark(IN const cstring &server) : C_Object(server) {};
	//-------------------------------------
	/**
	 * @brief ���o�į��������
	 * @param szName �į�W��
	 * @return �į��������
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