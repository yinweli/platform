/**
 * @file _nstd.h
 * @note 內含NonStandardLib的基礎定義
 * @author yinweli
 */
/**
 * @mainpage NonStandardLib導引
 * NonStandardLib 是由 yinweli 建立的輔助工具函式庫\n
 * 基本上只有他本人自己在用XDD\n
 * 因此所以命名為 Non-standard library (非標準程式庫), 跟C++官方的 Standard library (標準程式庫)做區別\n
 * 程式庫中全部使用 nstd 作為命名空間\n\n
 * 各函式庫說明請查看 相關頁面 或是 模組
 */
/**
 * @page 變數, 類別, 結構名稱前綴命名規則
 * bool : b\n
 * signed char : c\n
 * unsigned char : uc\n
 * signed short : w\n
 * unsigned short : uw\n
 * signed long : l\n
 * unsigned long : ul\n
 * signed int : i\n
 * unsigned int : ui\n
 * signed __int64 : i64\n
 * unsigned __int64 : ui64\n
 * float : f\n
 * double : d\n
 * array : n/a\n
 * string : sz\n
 * enum 定義 : ENUM_\n
 * enum 宣告 : em\n
 * point : p\n
 * function point 定義 : LPFN_\n
 * function point 宣告 : pf\n
 * struct 定義 : S_\n
 * struct 宣告 : s\n
 * class 定義 : C_\n
 * class 宣告 : cc\n
 * class member : m_\n
 * global : g_\n\n
 * 當泛型或是多型函式中會被大量多載的參數可以不用理會這項規定\n
 * 例如:\n\n
 * void Test(IN unsigned long ulData, IN bool value);\n
 * void Test(IN unsigned long ulData, IN char value);\n
 * void Test(IN unsigned long ulData, IN short value);\n
 * void Test(IN unsigned long ulData, IN long value);\n
 * void Test(IN unsigned long ulData, IN int value);\n\n
 * 這時變數 value 就可以不必增加前綴命名(不然要打好多字很煩阿阿阿阿)
 */
/**
 * @page 如何使用_nstd
 * _nstd用於函式庫的命名空間以及一些基礎定義\n
 * --------------------------------------------------\n
 * Header           : _nstd.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref _nstd
 */
/** @defgroup _nstd */
//-----------------------------------------------------------------------------
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef __NSTD
#define __NSTD
//-----------------------------------------------------------------------------
#pragma comment(lib, "winmm.lib")
//-----------------------------------------------------------------------------
// memory leak
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC ///< 設置記憶體洩漏紀錄將包含檔名與行號 @ingroup _nstd
#include <stdlib.h> // 為了保證記憶體洩漏檢查正常運作, 以下的引入順序不能更改
#include <crtdbg.h>
#include <xdebug>
#include <xlocale>
#include <xlocnum>
#include <xtree>
#include <fstream>
#define nstdnew new(_NORMAL_BLOCK, __FILE__, __LINE__) ///< 除錯用 new 運算子 @ingroup _nstd
#else
#include <stdlib.h>
#define nstdnew new ///< 正常用 new 運算子 @ingroup _nstd
#endif
// 用於解決 STL 與 windows 的 min, max 衝突問題
#define NOMINMAX
// 用於解決引入 windows.h 與 winsock2.h 的衝突問題
#ifndef _WINSOCK2_
#include <windows.h>
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <windows.h>
#endif
// 一般的引入檔
#include <algorithm>
#include <assert.h>
#include <comdef.h>
#include <conio.h>
#include <dbghelp.h>
#include <deque>
#include <direct.h>
#include <float.h>
#include <functional>
#include <io.h>
#include <limits.h>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <math.h>
#include <memory>
#include <numeric>
#include <process.h>
#include <queue>
#include <set>
#include <signal.h>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <tchar.h>
#include <time.h>
#include <tlhelp32.h>
#include <tuple>
#include <typeinfo.h>
#include <vcclr.h>
#include <vector>
// namespace define
#ifndef _NSTD
#define _NSTD nstd ///< 命名空間nstd名稱
#endif
#ifndef _NSTD_BEGIN
#define _NSTD_BEGIN namespace _NSTD { ///< 命名空間nstd開頭 @ingroup _nstd
#endif
#ifndef _NSTD_END
#define _NSTD_END } ///< 命名空間nstd結尾 @ingroup _nstd
#endif
#ifndef _NSTD_USEING
#define _NSTD_USEING using namespace _NSTD ///< 使用命名空間nstd @ingroup _nstd
#endif
// max enum value define
#ifndef ENUM_FORCE_DWORD
#define ENUM_FORCE_DWORD LONG_MAX ///< 列舉最大值 @ingroup _nstd
#endif
#endif
// IN, OUT define
#ifndef IN
#define IN ///< 用於修飾函式的參數是否為輸入型參數 @ingroup _nstd
#endif
#ifndef OUT
#define OUT ///< 用於修飾函式的參數是否為輸出型參數 @ingroup _nstd
#endif
// type id
#ifndef type_name
#define type_name(t) typeid(t).name()
// file, function define
#ifndef UNICODE
#define __FILEX__ __FILE__ ///< 檔案名稱定義 @ingroup _nstd
#define __FUNCTIONX__ __FUNCTION__ ///< 函式名稱定義 @ingroup _nstd
#else
#define __FILEX__ __FILEW__ ///< 檔案名稱定義, 寬字元版本 @ingroup _nstd
#define __FUNCTIONX__ __FUNCTIONW__ ///< 函式名稱定義, 寬字元版本 @ingroup _nstd
#endif
// string
#ifndef UNICODE
#define _var(v) #v ///< 取得變數名稱 @ingroup _nstd
#else
#define _var(v) __T(#v) ///< 取得變數名稱, 寬字元版本 @ingroup _nstd
#endif
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------