/**
 * @file filetool.h
 * @note 檔案工具系列函式
 * @author yinweli
 */
/**
 * @page 如何使用filetool
 * filetool內的函式用於檔案操作\n\n
 * --------------------------------------------------\n
 * Header           : filetool.h\n
 * Library(debug)   : nstd_debug.lib\n
 * Library(release) : nstd_release.lib\n
 * --------------------------------------------------\n
 * 詳細說明請參照 @ref filetool
 */
/** @defgroup filetool */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _FILETOOL
#define _FILETOOL
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
#include "..\_nstring\_nstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief 尋找檔案結構, 用於 FindFileInDir 函式
 * @ingroup filetool
 */
struct S_FindFile
{
	nstring szPath; ///< 目錄字串
	nstring szName; ///< 檔案名稱
};
//-----------------------------------------------------------------------------
/**
 * @brief 檢查檔案是否存在
 * @param szFilePath 要檢查的檔名(包含路徑與檔名)
 * @return true表示檔案存在, false則否
 * @ingroup filetool
 */
bool fexist(IN const nstring &szFilePath);
/**
 * @brief 取得檔案長度
 * @param f 以 fopen 函式開啟的檔案指標
 * @return 檔案長度(byte)
 * @ingroup filetool
 */
long fsize(IN FILE *f);
/**
 * @brief 取得檔案長度
 * @param szFilePath 要取得長度的檔名(包含路徑與檔名)
 * @return 檔案長度(byte)
 * @ingroup filetool
 */
long fsize(IN const nstring &szFilePath);
/**
 * @brief 讀取資料到字串中
 * @param szFilePath 要讀取的檔名(包含路徑與檔名)
 * @param szData 資料字串
 * @return true表示讀取成功, false則否
 * @ingroup filetool
 */
bool freadstr(IN const nstring &szFilePath, OUT nstring &szData);
/**
 * @brief 寫入資料到檔案中
 * @param szFilePath 要寫入的檔名(包含路徑與檔名)
 * @param bAppend true表示添加到檔案後, false則否
 * @param pData 資料指標
 * @param ulSize 資料長度
 * @return true表示寫入成功, false則否
 * @ingroup filetool
 */
bool fwritedata(IN const nstring &szFilePath, IN bool bAppend, IN const void *pData, IN unsigned long ulSize);
/**
 * @brief 寫入字串到檔案中
 * @param szFilePath 要寫入的檔名(包含路徑與檔名)
 * @param bAppend true表示添加到檔案後, false則否
 * @param szData 資料字串
 * @return true表示寫入成功, false則否
 * @ingroup filetool
 */
bool fwritestr(IN const nstring &szFilePath, IN bool bAppend, IN const std::string &szData);
/**
 * @brief 寫入字串到檔案中
 * @param szFilePath 要寫入的檔名(包含路徑與檔名)
 * @param bAppend true表示添加到檔案後, false則否
 * @param szData 資料字串
 * @return true表示寫入成功, false則否
 * @ingroup filetool
 */
bool fwritestr(IN const nstring &szFilePath, IN bool bAppend, IN const std::wstring &szData);
/**
 * @brief 取得程式所在的目錄
 * @return 程式所在的目錄字串
 * @ingroup filetool
 */
nstring GetCurrentDirectoryEx();
/**
 * @brief 取得路徑字串內包含的目錄名稱列表
 * @param szPath 路徑字串
 * @param bFull 如果為true, 則輸出的字串會包含父路徑
 * @param bSkip 如果為true, 不會輸出最後一項路徑
 * @return 結果列表
 * @ingroup filetool
 */
std::vector<nstring> GetPathList(IN const nstring &szPath, IN bool bFull = true, IN bool bSkip = true);
/**
 * @brief 尋找目錄底下所有檔案
 * @param szPath 路徑字串
 * @return 結果列表
 * @ingroup filetool
 */
std::vector<S_FindFile> GetFileList(IN const nstring &szPath);
/**
 * @brief 取得以日期為格式的路徑與檔名字串
 * @note 格式如下\n
 *       路徑\\年\\月\\日\\yyyy-mm-dd hh-mm-ss 檔名
 * @param szPath 路徑
 * @param szFile 檔名
 * @param bDirYear 路徑是否要包含 年 資料夾
 * @param bDirMonth 路徑是否要包含 月 資料夾
 * @param bDirDay 路徑是否要包含 日 資料夾
 * @param bFNDate 檔名是否要包含 yyyy-mm-dd 字串
 * @param bFNTime 檔名是否要包含 hh-mm-ss 字串
 * @return 路徑與檔名字串
 * @ingroup filetool
 */
nstring GetDateFormatPath(IN const nstring &szPath, IN const nstring &szFile, IN bool bDirYear = true, IN bool bDirMonth = true, IN bool bDirDay = true, IN bool bFNDate = true, IN bool bFNTime = true);
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------