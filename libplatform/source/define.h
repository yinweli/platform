/**
 * @file define.h
 * @note ��¦�w�q
 * @author yinweli
 */
//-----------------------------------------------------------------------------
#ifndef _DEFINE_LIBPLATFORM
#define _DEFINE_LIBPLATFORM
//-----------------------------------------------------------------------------
_NSTD_USEING;
//-----------------------------------------------------------------------------
#define _B_() C_BMObj ccBMObj = ObjBenchmark().Get(__FUNCTIONX__) ///< �į�O������
#ifndef UNICODE
#define _BM_(token) C_BMObj ccBMObj = ObjBenchmark().Get(#token) ///< �į�O������
#else
#define _BM_(token) C_BMObj ccBMObj = ObjBenchmark().Get(L#token) ///< �į�O������
#endif
//-----------------------------------------------------------------------------
#define THREAD_SERVER __T("server") ///< ������Ѽ� - ���A������
#define BMDATA_SERVER __T("process") ///< �į���� - ���A���B�z
#define COMPONENT_FIX __T("class ") ///< ���󫬺A�׹���
#define CONNECT_EXTRA 100 ///< �B�~�s�u��
#define CONNECT_INTERVAL 10000 ///< �s�u���j�ɶ�
#define PROCESS_NOTICE 200 ///< �B�z�q���ƶq
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------