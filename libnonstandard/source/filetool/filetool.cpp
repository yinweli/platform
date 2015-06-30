//-----------------------------------------------------------------------------
#include "filetool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 檢查檔案是否存在
bool fexist(IN const nstring &szFilePath)
{
	FILE *f = nullptr;

	if(_tfopen_s(&f, szFilePath.c_str(), __T("r")) != 0)
		return false;

	if(f == nullptr)
		return false;

	fclose(f);

	return true;
}
//-----------------------------------------------------------------------------
// 取得檔案長度
long fsize(IN FILE *f)
{
	return (f) ? _filelength(_fileno(f)) : 0;
}
//-----------------------------------------------------------------------------
// 取得檔案長度
long fsize(IN const nstring &szFilePath)
{
	struct _stat statbuf;
	int r = _tstat(szFilePath.c_str(), &statbuf);

	return (r == 0) ? statbuf.st_size : 0;
}
//-----------------------------------------------------------------------------
// 讀取資料到字串中
bool freadstr(IN const nstring &szFilePath, OUT nstring &szData)
{
	// 開啟檔案
	FILE *f = nullptr;

	if(_tfopen_s(&f, szFilePath.c_str(), __T("rb")) != 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("open file failed(") + szFilePath + __T(")"));

	if(f == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("open file failed(") + szFilePath + __T(")"));

	// 取得檔案長度
	int iFSize = fsize(f);

	// 準備暫存區
	char *szBuf = nstdnew char [iFSize + 1];

	if(szBuf == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create buffer failed(") + szFilePath + __T(")"));

	// 讀檔
	fread(szBuf, iFSize, 1, f);
	// 關檔
	fclose(f);
	// 設定結尾0
	szBuf[iFSize] = 0;
	// 複製到資料字串
	szData = C_NString(szBuf);

	return true;
}
//-----------------------------------------------------------------------------
// 寫入資料到檔案中
bool fwritedata(IN const nstring &szFilePath, IN bool bAppend, IN const void *pData, IN unsigned long ulSize)
{
	if(szFilePath.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("file empty"));

	if(pData == nullptr || ulSize <= 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("data null(") + szFilePath + __T(")"));

	// 建立目錄
	for(const std::vector<nstring>::value_type &Itor : GetPathList(szFilePath))
		_tmkdir(Itor.c_str());

	// 開啟檔案
	FILE *f = nullptr;

	if(_tfopen_s(&f, szFilePath.c_str(), bAppend ? __T("a+b") : __T("w+b")) != 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("open file failed(") + szFilePath + __T(")"));

	if(f == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("open file failed(") + szFilePath + __T(")"));

	fwrite(pData, ulSize, 1, f); // 寫入檔案
	fclose(f);

	return true;
}
//-----------------------------------------------------------------------------
// 寫入字串到檔案中
bool fwritestr(IN const nstring &szFilePath, IN bool bAppend, IN const std::string &szData)
{
	if(szFilePath.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("file empty"));

	if(szData.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("data null(") + szFilePath + __T(")"));

	return fwritedata(szFilePath, bAppend, reinterpret_cast<const void *>(szData.c_str()), szData.size() * sizeof(char));
}
//-----------------------------------------------------------------------------
// 寫入字串到檔案中
bool fwritestr(IN const nstring &szFilePath, IN bool bAppend, IN const std::wstring &szData)
{
	return fwritestr(szFilePath, bAppend, static_cast<std::string>(C_NString(szData)));
}
//-----------------------------------------------------------------------------
// 取得程式所在的目錄
nstring GetCurrentDirectoryEx()
{
	unsigned long ulSize = GetCurrentDirectory(0, nullptr);

	if(ulSize <= 0)
		return __T("");

	TCHAR *pTemp = nstdnew TCHAR[ulSize];

	if(pTemp == nullptr)
		return __T("");

	memset(pTemp, 0, sizeof(TCHAR) * ulSize);

	nstring szResult;

	szResult = GetCurrentDirectory(ulSize, pTemp) > 0 ? pTemp : __T("");
	szResult += szResult.empty() == false ? __T("\\") : __T("");

	delete[] pTemp;

	return szResult;
}
//-----------------------------------------------------------------------------
// 取得路徑字串內包含的目錄名稱列表
std::vector<nstring> GetPathList(IN const nstring &szPath, IN bool bFull, IN bool bSkip)
{
	if(szPath.empty())
		return std::vector<nstring>();

	std::vector<nstring> Result;
	nstring szFullPath;

	for(const std::vector<nstring>::value_type &Itor : nstok(szPath, __T("\\/")))
		Result.push_back(bFull ? (szFullPath += szFullPath.empty() ? Itor : __T("\\") + Itor) : Itor);

	if(bSkip)
		Result.pop_back();

	return Result;
}
//-----------------------------------------------------------------------------
// 尋找目錄底下所有檔案
std::vector<S_FindFile> GetFileList(IN const nstring &szPath)
{
	if(szPath.empty())
		return std::vector<S_FindFile>();

	nstring szPathDir = szPath; // 原始路徑字串

	trimtail(szPathDir, __T("*")); // 把路徑字串尾端的 '*' 符號刪除
	trimtail(szPathDir, __T("\\")); // 把路徑字串尾端的 '\' 符號刪除
	szPathDir += __T("\\");

	nstring szPathFind = szPathDir + __T("*"); // 用於搜尋的路徑字串
	WIN32_FIND_DATA sWFD;

	ZeroMemory(&sWFD, sizeof(sWFD));

	HANDLE hFindFile = FindFirstFile(szPathFind.c_str(), &sWFD);

	if(hFindFile == INVALID_HANDLE_VALUE)
		return std::vector<S_FindFile>();

	std::vector<S_FindFile> Result;

	while(FindNextFile(hFindFile, &sWFD))
	{
		// 找到資料夾
		if(sWFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(_tcscmp(sWFD.cFileName, __T(".")) == 0)
				continue;

			if(_tcscmp(sWFD.cFileName, __T("..")) == 0)
				continue;

			for(const std::vector<S_FindFile>::value_type &Itor : GetFileList(nsoutf(__T("{}{}")) << szPathDir << sWFD.cFileName))
				Result.push_back(Itor);
		}
		else
		{
			S_FindFile sData;

			sData.szPath = szPathDir;
			sData.szName = sWFD.cFileName;

			Result.push_back(sData);
		}//if
	}//while

	FindClose(hFindFile);

	return Result;
}
//-----------------------------------------------------------------------------
// 取得以日期為格式的路徑與檔名字串
nstring GetDateFormatPath(IN const nstring &szPath, IN const nstring &szFile, IN bool bDirYear, IN bool bDirMonth, IN bool bDirDay, IN bool bFNDate, IN bool bFNTime)
{
	if(szPath.empty())
		return __T("");

	if(szFile.empty())
		return __T("");

	time_t tTime;
	struct tm sTMTime;
	nstring szResult;

	// 取得現在時間
	time(&tTime);
	localtime_s(&sTMTime, &tTime);

	sTMTime.tm_year += 1900;
	sTMTime.tm_mon += 1;

	// 取得輸出檔名
	szResult = szPath;
	trimtail(szResult, __T("\\"));
	szResult += __T("\\");

	if(bDirYear)
		szResult += (nsoutf(__T("{}\\")) << sTMTime.tm_year);

	if(bDirMonth)
		szResult += (nsoutf(__T("{02}\\")) << sTMTime.tm_mon);

	if(bDirDay)
		szResult += (nsoutf(__T("{02}\\")) << sTMTime.tm_mday);

	if(bFNDate)
		szResult += (nsoutf(__T("{04}-{02}-{02} ")) << sTMTime.tm_year << sTMTime.tm_mon << sTMTime.tm_mday);

	if(bFNTime)
		szResult += (nsoutf(__T("{02}-{02}-{02} ")) << sTMTime.tm_hour << sTMTime.tm_min << sTMTime.tm_sec);

	szResult += szFile;

	return szResult;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------