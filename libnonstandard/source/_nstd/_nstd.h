/**
 * @file _nstd.h
 * @note ���tNonStandardLib����¦�w�q
 * @author yinweli
 */
/**
 * @mainpage NonStandardLib�ɤ�
 * NonStandardLib �O�� yinweli �إߪ����U�u��禡�w\n
 * �򥻤W�u���L���H�ۤv�b��XDD\n
 * �]���ҥH�R�W�� Non-standard library (�D�зǵ{���w), ��C++�x�誺 Standard library (�зǵ{���w)���ϧO\n
 * �{���w�������ϥ� nstd �@���R�W�Ŷ�\n\n
 * �U�禡�w�����Ьd�� �������� �άO �Ҳ�
 */
/**
 * @page �ܼ�, ���O, ���c�W�٫e��R�W�W�h
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
 * enum �w�q : ENUM_\n
 * enum �ŧi : em\n
 * point : p\n
 * function point �w�q : LPFN_\n
 * function point �ŧi : pf\n
 * struct �w�q : S_\n
 * struct �ŧi : s\n
 * class �w�q : C_\n
 * class �ŧi : cc\n
 * class member : m_\n
 * global : g_\n\n
 * ��x���άO�h���禡���|�Q�j�q�h�����Ѽƥi�H���βz�|�o���W�w\n
 * �Ҧp:\n\n
 * void Test(IN unsigned long ulData, IN bool value);\n
 * void Test(IN unsigned long ulData, IN char value);\n
 * void Test(IN unsigned long ulData, IN short value);\n
 * void Test(IN unsigned long ulData, IN long value);\n
 * void Test(IN unsigned long ulData, IN int value);\n\n
 * �o���ܼ� value �N�i�H�����W�[�e��R�W(���M�n���n�h�r�ܷЪ�������)
 */
/**
 * @page �p��ϥ�_nstd
 * _nstd�Ω�禡�w���R�W�Ŷ��H�Τ@�ǰ�¦�w�q\n
 * --------------------------------------------------\n
 * Header           : _nstd.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref _nstd
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
#define _CRTDBG_MAP_ALLOC ///< �]�m�O���鬪�|�����N�]�t�ɦW�P�渹 @ingroup _nstd
#include <stdlib.h> // ���F�O�ҰO���鬪�|�ˬd���`�B�@, �H�U���ޤJ���Ǥ�����
#include <crtdbg.h>
#include <xdebug>
#include <xlocale>
#include <xlocnum>
#include <xtree>
#include <fstream>
#define nstdnew new(_NORMAL_BLOCK, __FILE__, __LINE__) ///< ������ new �B��l @ingroup _nstd
#else
#include <stdlib.h>
#define nstdnew new ///< ���`�� new �B��l @ingroup _nstd
#endif
// �Ω�ѨM STL �P windows �� min, max �Ĭ���D
#define NOMINMAX
// �Ω�ѨM�ޤJ windows.h �P winsock2.h ���Ĭ���D
#ifndef _WINSOCK2_
#include <windows.h>
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <windows.h>
#endif
// �@�몺�ޤJ��
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
#define _NSTD nstd ///< �R�W�Ŷ�nstd�W��
#endif
#ifndef _NSTD_BEGIN
#define _NSTD_BEGIN namespace _NSTD { ///< �R�W�Ŷ�nstd�}�Y @ingroup _nstd
#endif
#ifndef _NSTD_END
#define _NSTD_END } ///< �R�W�Ŷ�nstd���� @ingroup _nstd
#endif
#ifndef _NSTD_USEING
#define _NSTD_USEING using namespace _NSTD ///< �ϥΩR�W�Ŷ�nstd @ingroup _nstd
#endif
// max enum value define
#ifndef ENUM_FORCE_DWORD
#define ENUM_FORCE_DWORD LONG_MAX ///< �C�|�̤j�� @ingroup _nstd
#endif
#endif
// IN, OUT define
#ifndef IN
#define IN ///< �Ω�׹��禡���ѼƬO�_����J���Ѽ� @ingroup _nstd
#endif
#ifndef OUT
#define OUT ///< �Ω�׹��禡���ѼƬO�_����X���Ѽ� @ingroup _nstd
#endif
// type id
#ifndef type_name
#define type_name(t) typeid(t).name()
// file, function define
#ifndef UNICODE
#define __FILEX__ __FILE__ ///< �ɮצW�٩w�q @ingroup _nstd
#define __FUNCTIONX__ __FUNCTION__ ///< �禡�W�٩w�q @ingroup _nstd
#else
#define __FILEX__ __FILEW__ ///< �ɮצW�٩w�q, �e�r������ @ingroup _nstd
#define __FUNCTIONX__ __FUNCTIONW__ ///< �禡�W�٩w�q, �e�r������ @ingroup _nstd
#endif
// string
#ifndef UNICODE
#define _var(v) #v ///< ���o�ܼƦW�� @ingroup _nstd
#else
#define _var(v) __T(#v) ///< ���o�ܼƦW��, �e�r������ @ingroup _nstd
#endif
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------