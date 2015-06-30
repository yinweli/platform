/**
 * @file _nstring.h
 * @note 非標準字串處理函式與類別
 * @author yinweli
 */
/**
 * @page 如何使用_nstring
 * _nstring是個字串工具程式庫, 其中包含了一個字串類別\n\n
 * _nstring包含了以下幾個部份:\n
 * 字串大小寫轉換 @ref nscase\n
 * 字串檢查 @ref nschk\n
 * 字串單/寬字元轉換 @ref nsconv\n
 * 字串編輯 @ref nsedit\n
 * 字串分割 @ref nstok\n
 * 字串轉換數值 @ref nston\n
 * 數值轉換字串 @ref nstox\n
 * 字串處理類別 @ref nstring\n
 * 計算字串長度 @ref nslen\n\n
 * --------------------------------------------------\n
 * Header           : _nstring.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref nscase\n
 * 詳細說明請參照 @ref nschk\n
 * 詳細說明請參照 @ref nsconv\n
 * 詳細說明請參照 @ref nsedit\n
 * 詳細說明請參照 @ref nstok\n
 * 詳細說明請參照 @ref nston\n
 * 詳細說明請參照 @ref nstox\n
 * 詳細說明請參照 @ref nstring\n
 * 詳細說明請參照 @ref nslen\n\n
 */
/** @defgroup nscase */
/** @defgroup nschk */
/** @defgroup nsconv */
/** @defgroup nsedit */
/** @defgroup nstok */
/** @defgroup nston */
/** @defgroup nstox */
/** @defgroup nstring */
/** @defgroup nslen */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef __NSTRING
#define __NSTRING
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
//-----------------------------------------------------------------------------
#include "nscase.h"
#include "nschk.h"
#include "nsconv.h"
#include "nsedit.h"
#include "nstok.h"
#include "nston.h"
#include "nstox.h"
#include "nstring.h"
#include "nstrlen.h"
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------