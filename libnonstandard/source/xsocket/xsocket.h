/**
 * @file xsocket.h
 * @note IOCP��������
 * @author yinweli
 */
/**
 * @page �p��ϥ�xsocket
 * xsocket�O�ϥ�IOCP���֤ߪ���������\n\n
 * ���A���إߤ�k:\n
 * �����I�s XSocketInitialize() �禡�Ӫ�l��Winsock, ��S����������s�b�ɥi�H�I�s XSocketRelease() �禡������Winsock\n
 * �M��إߤ@�ӹ���ϥ� C_XServer �ŧi�p�U\n\n
 * C_XServer ccServer;\n\n
 * �M��I�s C_XServer.Start() �ӱҰʦ��A��\n
 * �M��I�s C_XServer.AddSocketNormal() �P C_XServer.AddSocketExtra() �ӷs�W�s�u(�p�G�S�I�s, �|�y���Ȥ�ݵL�k�s�u)\n
 * �����ɩI�s C_XServer.Stop() �Ӱ�����A��\n
 * �ǰe�ʥ]��Ȥ�ݭn�I�s C_XServer.Send()\n
 * ���_�P�Ȥ�ݪ��s�u�I�s C_XServer.Disconnect()\n
 * �p�G�n���D�O�_���ʥ]������������, �I�s C_XServer.Notice() �Ө��o��������, �q�L�ˬd��������O�_����ƨӽT�w�ʥ]�O�_�w�g��������\n
 * �p�G�ݭn���o�������󤺥]�t���ʥ]���, �I�s C_XNotice.Complete() �Ө��o�ʥ]��ƪ���\n
 * ��ϥΧ����ʥ]��ƪ����, �ЩI�s C_XComplete.Release() ������O����\n
 * ���A�����i�s�u�ƨ��M����� C_XServer.AddSocketNormal() �I�s���s�W�s�u�`��, �`�N�o�ӳs�u�`�ƥu��W�[, ������\n\n
 * �Ȥ�ݫإߤ�k:\n
 * �����I�s XSocketInitialize() �禡�Ӫ�l��Winsock, ��S����������s�b�ɥi�H�I�s XSocketRelease() �禡������Winsock\n
 * �M��إߤ@�ӹ���ϥ� C_XClient �ŧi�p�U\n\n
 * C_XClient ccClient;\n\n
 * �M��I�s C_XClient.Start() �ӳs�u����A��, �p�G�Q�n�s�u��h�Ӧ��A��, �i�H�Τ��P����}�h���I�s�o�Ө禡\n
 * �����ɩI�s C_XClient.Stop() �Ӱ���s�u\n
 * �ǰe�ʥ]����A���n�I�s C_XClient.Send()\n
 * �p�G�n���D�O�_���ʥ]������������, �I�s C_XClient.Notice() �Ө��o��������, �q�L�ˬd��������O�_����ƨӽT�w�ʥ]�O�_�w�g��������\n
 * ��ϥΧ����ʥ]��ƪ����, �ЩI�s C_XComplete.Release() ������O����\n\n
 * --------------------------------------------------\n
 * Header           : xsocket.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref xapi\n
 * �Բӻ����аѷ� @ref xlist\n
 * �Բӻ����аѷ� @ref xserver\n
 * �Բӻ����аѷ� @ref xclient\n
 */
/** @defgroup xapi */
/** @defgroup xlist */
/** @defgroup xserver */
/** @defgroup xclient */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _XSOCKET
#define _XSOCKET
//-----------------------------------------------------------------------------
#pragma comment(lib, "mswsock.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ws2_32.lib")
//-----------------------------------------------------------------------------
#define _WINSOCK2_ ///< �w�q�ϥ� winsock2.h �Ӥ��ϥ� windows.h
//#define XSOCKET_DEBUG ///< �����Ωw�q
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\_ntime\_ntime.h"
#include "..\benchmark\benchmark.h"
#include "..\flowrecord\flowrecord.h"
#include "..\ipdata\ipdata.h"
#include "..\threadlock\threadlock.h"
#include "..\threadobj\threadobj.h"
//-----------------------------------------------------------------------------
#include "xapi.h"
#include "xerror.h"
#include "xlistconnect.h"
#include "xlistnotice.h"
#include "xlistoverlapped.h"
#include "xlistrecv.h"
#include "xlistsend.h"
#include "xlistunit.h"
//-----------------------------------------------------------------------------
#include "xclient.h"
#include "xserver.h"
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------