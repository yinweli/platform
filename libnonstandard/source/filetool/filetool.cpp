//-----------------------------------------------------------------------------
#include "filetool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// �ˬd�ɮ׬O�_�s�b
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
// ���o�ɮת���
long fsize(IN FILE *f)
{
	return (f) ? _filelength(_fileno(f)) : 0;
}
//-----------------------------------------------------------------------------
// ���o�ɮת���
long fsize(IN const nstring &szFilePath)
{
	struct _stat statbuf;
	int r = _tstat(szFilePath.c_str(), &statbuf);

	return (r == 0) ? statbuf.st_size : 0;
}
//-----------------------------------------------------------------------------
// Ū����ƨ�r�ꤤ
bool freadstr(IN const nstring &szFilePath, OUT nstring &szData)
{
	// �}���ɮ�
	FILE *f = nullptr;

	if(_tfopen_s(&f, szFilePath.c_str(), __T("rb")) != 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("open file failed(") + szFilePath + __T(")"));

	if(f == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("open file failed(") + szFilePath + __T(")"));

	// ���o�ɮת���
	int iFSize = fsize(f);

	// �ǳƼȦs��
	char *szBuf = nstdnew char [iFSize + 1];

	if(szBuf == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create buffer failed(") + szFilePath + __T(")"));

	// Ū��
	fread(szBuf, iFSize, 1, f);
	// ����
	fclose(f);
	// �]�w����0
	szBuf[iFSize] = 0;
	// �ƻs���Ʀr��
	szData = C_NString(szBuf);

	return true;
}
//-----------------------------------------------------------------------------
// �g�J��ƨ��ɮפ�
bool fwritedata(IN const nstring &szFilePath, IN bool bAppend, IN const void *pData, IN unsigned long ulSize)
{
	if(szFilePath.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("file empty"));

	if(pData == nullptr || ulSize <= 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("data null(") + szFilePath + __T(")"));

	// �إߥؿ�
	for(const std::vector<nstring>::value_type &Itor : GetPathList(szFilePath))
		_tmkdir(Itor.c_str());

	// �}���ɮ�
	FILE *f = nullptr;

	if(_tfopen_s(&f, szFilePath.c_str(), bAppend ? __T("a+b") : __T("w+b")) != 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("open file failed(") + szFilePath + __T(")"));

	if(f == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("open file failed(") + szFilePath + __T(")"));

	fwrite(pData, ulSize, 1, f); // �g�J�ɮ�
	fclose(f);

	return true;
}
//-----------------------------------------------------------------------------
// �g�J�r����ɮפ�
bool fwritestr(IN const nstring &szFilePath, IN bool bAppend, IN const std::string &szData)
{
	if(szFilePath.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("file empty"));

	if(szData.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("data null(") + szFilePath + __T(")"));

	return fwritedata(szFilePath, bAppend, reinterpret_cast<const void *>(szData.c_str()), szData.size() * sizeof(char));
}
//-----------------------------------------------------------------------------
// �g�J�r����ɮפ�
bool fwritestr(IN const nstring &szFilePath, IN bool bAppend, IN const std::wstring &szData)
{
	return fwritestr(szFilePath, bAppend, static_cast<std::string>(C_NString(szData)));
}
//-----------------------------------------------------------------------------
// ���o�{���Ҧb���ؿ�
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
// ���o���|�r�ꤺ�]�t���ؿ��W�٦C��
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
// �M��ؿ����U�Ҧ��ɮ�
std::vector<S_FindFile> GetFileList(IN const nstring &szPath)
{
	if(szPath.empty())
		return std::vector<S_FindFile>();

	nstring szPathDir = szPath; // ��l���|�r��

	trimtail(szPathDir, __T("*")); // ����|�r����ݪ� '*' �Ÿ��R��
	trimtail(szPathDir, __T("\\")); // ����|�r����ݪ� '\' �Ÿ��R��
	szPathDir += __T("\\");

	nstring szPathFind = szPathDir + __T("*"); // �Ω�j�M�����|�r��
	WIN32_FIND_DATA sWFD;

	ZeroMemory(&sWFD, sizeof(sWFD));

	HANDLE hFindFile = FindFirstFile(szPathFind.c_str(), &sWFD);

	if(hFindFile == INVALID_HANDLE_VALUE)
		return std::vector<S_FindFile>();

	std::vector<S_FindFile> Result;

	while(FindNextFile(hFindFile, &sWFD))
	{
		// ����Ƨ�
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
// ���o�H������榡�����|�P�ɦW�r��
nstring GetDateFormatPath(IN const nstring &szPath, IN const nstring &szFile, IN bool bDirYear, IN bool bDirMonth, IN bool bDirDay, IN bool bFNDate, IN bool bFNTime)
{
	if(szPath.empty())
		return __T("");

	if(szFile.empty())
		return __T("");

	time_t tTime;
	struct tm sTMTime;
	nstring szResult;

	// ���o�{�b�ɶ�
	time(&tTime);
	localtime_s(&sTMTime, &tTime);

	sTMTime.tm_year += 1900;
	sTMTime.tm_mon += 1;

	// ���o��X�ɦW
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