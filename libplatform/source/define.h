/**
 * @file define.h
 * @note 基礎定義
 * @author yinweli
 */
//-----------------------------------------------------------------------------
#ifndef _DEFINE_LIBPLATFORM
#define _DEFINE_LIBPLATFORM
//-----------------------------------------------------------------------------
_NSTD_USEING;
//-----------------------------------------------------------------------------
#define _B_() C_BMObj ccBMObj = ObjBenchmark().Get(__FUNCTIONX__) ///< 效能記錄巨集
#ifndef UNICODE
#define _BM_(token) C_BMObj ccBMObj = ObjBenchmark().Get(#token) ///< 效能記錄巨集
#else
#define _BM_(token) C_BMObj ccBMObj = ObjBenchmark().Get(L#token) ///< 效能記錄巨集
#endif
//-----------------------------------------------------------------------------
#define THREAD_SERVER __T("server") ///< 執行緒參數 - 伺服器物件
#define BMDATA_SERVER __T("process") ///< 效能紀錄 - 伺服器處理
#define COMPONENT_FIX __T("class ") ///< 元件型態修飾詞
#define CONNECT_EXTRA 100 ///< 額外連線數
#define CONNECT_INTERVAL 10000 ///< 連線間隔時間
#define PROCESS_NOTICE 200 ///< 處理通知數量
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------