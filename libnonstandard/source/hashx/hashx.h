/**
 * @file hashx
 * @note hash類別
 * @author yinweli
 */
/**
 * @page 如何使用hashx
 * hashx是個取得各種hash值的類別集合, 包含了 CRC32, Keccak, MD5, SHA1, SHA3, SHA256 這些類別\n\n
 * --------------------------------------------------\n
 * Header           : hashx.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _HASHX
#define _HASHX
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
//-----------------------------------------------------------------------------
#include "crc32.h"
#include "hash.h"
#include "keccak.h"
#include "md5.h"
#include "sha1.h
#include "sha3.h
#include "sha256.h
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------