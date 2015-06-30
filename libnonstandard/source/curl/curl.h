/**
 * @file curl.h
 * @note curl���O
 * @author yinweli
 */
/**
 * @page �p��ϥ�curl
 * curl�Ω�P�����W��web�A�ȷ��q\n\n
 * �b�ϥΤ��e�ݭn���I�s CURLInitialize() �禡�Ӫ�l��curl, ��{�������e�n�I�s CURLRelease() �禡�ӲM��curl\n
 * curl���T�ӥD�n���ե�, ���O�O :\n
 * C_CURLBase ��¦��curl���O, �L�ƹ�W�u�ʸˤF curl_easy_setopt �P curl_easy_perform �禡, �A�[�W�@�ǿ��~�^���\��\n
 * C_CURLMeta �i����curl���O, �L�֦� C_CURLBase ���\��, �[�W�i�H���o���G���󪺨禡\n
 * C_CURLMulti �o�O�H�D����Ҧ����檺�h��curl���O, ���i�H�P�ɰ���\�h�� C_CURLMeta ����, �P�ɷ|�N���檺���G���X�_�ӵ��ݨϥΪ̨���\n
 * �t�~�٦��@�Ǩ�L�����O :\n
 * C_ErrorCURL curl���~�^�����O\n
 * C_CURLResult curl���G���O\n
 * �аѦҥH�U���� :\n
 * @subpage �ϥ�C_CURLBase\n
 * @subpage �ϥ�C_CURLMeta\n
 * @subpage �ϥ�C_CURLMulti\n\n
 * --------------------------------------------------\n
 * Header           : curl.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref curl
 */
/** @defgroup curl */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CURL
#define _CURL
//-----------------------------------------------------------------------------
#ifdef _DEBUG
#pragma comment(lib, "..\\libthirdparty\\curl-7.39.0\\vc2013_lib_debug\\libcurld.lib")
#else
#pragma comment(lib, "..\\libthirdparty\\curl-7.39.0\\vc2013_lib_release\\libcurl.lib")
#endif
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
#include "..\..\..\libthirdparty\curl-7.39.0\include\curl.h"
//-----------------------------------------------------------------------------
#include "curlbase.h"
#include "curlmeta.h"
#include "curlmulti.h"
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------