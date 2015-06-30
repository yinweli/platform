//-----------------------------------------------------------------------------
#include "stringlist.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 以編號索引取得 std::list<nstring> 的迭代器
std::list<nstring>::iterator GetItor(IN std::list<nstring> &r, IN unsigned long ulPos)
{
	if(ulPos >= r.size())
		return r.end();

	std::list<nstring>::iterator Itor = r.begin();
	std::advance(Itor, ulPos);

	return Itor;
}
//-----------------------------------------------------------------------------
// 以編號索引取得 std::list<nstring> 的迭代器
std::list<nstring>::const_iterator GetItor(IN const std::list<nstring> &r, IN unsigned long ulPos)
{
	if(ulPos >= r.size())
		return r.end();

	std::list<nstring>::const_iterator Itor = r.begin();
	std::advance(Itor, ulPos);

	return Itor;
}
//-----------------------------------------------------------------------------
C_StringList::C_StringList() : m_bLoadFile(false) {}
//-----------------------------------------------------------------------------
// 解構子
C_StringList::~C_StringList()
{
	Clear();
}
//-----------------------------------------------------------------------------
// 清除全部
void C_StringList::Clear()
{
	m_bLoadFile = false;
	m_StringList.clear();
}
//-----------------------------------------------------------------------------
// 取得讀取檔案旗標
bool C_StringList::IsLoad() const
{
	return m_bLoadFile;
}
//-----------------------------------------------------------------------------
// 加入一行
void C_StringList::AddLine(IN const TCHAR *szInput, IN unsigned long ulPos)
{
	m_StringList.insert(GetItor(m_StringList, ulPos), szInput ? szInput : __T(""));
}
//-----------------------------------------------------------------------------
// 加入一行
void C_StringList::AddLineEx(IN const TCHAR *szInput, ...)
{
	nstring szTemp;

	if(szInput && _tcslen(szInput) > 0)
	{
		va_list	valist;

		va_start(valist, szInput);
		setprintf(szTemp, szInput, &valist);
		va_end(valist);
	}
	else
		szTemp = __T("");

	AddLine(szTemp.c_str());
}
//-----------------------------------------------------------------------------
// 刪除一行
void C_StringList::DelLine(IN unsigned long ulPos)
{
	std::list<nstring>::iterator Itor = GetItor(m_StringList, ulPos);

	if(Itor == m_StringList.end())
		return;

	m_StringList.erase(Itor);
}
//-----------------------------------------------------------------------------
// 取得一行
const TCHAR *C_StringList::GetLine(IN unsigned long ulPos) const
{
	std::list<nstring>::const_iterator Itor = GetItor(m_StringList, ulPos);

	return Itor != m_StringList.end() ? (*Itor).c_str() : NULL;
}
//-----------------------------------------------------------------------------
// 取得一行
nstring C_StringList::GetLineStr(IN unsigned long ulPos) const
{
	std::list<nstring>::const_iterator Itor = GetItor(m_StringList, ulPos);

	return Itor != m_StringList.end() ? *Itor : __T("");
}
//-----------------------------------------------------------------------------
// 取得一行的字數
unsigned long C_StringList::GetLineLen(IN unsigned long ulPos) const
{
	std::list<nstring>::const_iterator Itor = GetItor(m_StringList, ulPos);

	return Itor != m_StringList.end() ? (*Itor).size() : 0;
}
//-----------------------------------------------------------------------------
// 取得行數
unsigned long C_StringList::GetLineCount() const
{
	return m_StringList.size();
}
//-----------------------------------------------------------------------------
// 取得字串列表開頭迭代器
C_StringList::const_iterator C_StringList::Begin() const
{
	return m_StringList.begin();
}
//-----------------------------------------------------------------------------
// 取得字串列表結尾迭代器
C_StringList::const_iterator C_StringList::End() const
{
	return m_StringList.end();
}
//-----------------------------------------------------------------------------
// 存檔
bool C_StringList::Save(IN const nstring &szFilePath, IN bool bAppend, IN bool bAutoWrap, IN unsigned long ulPos, IN unsigned long ulLines)
{
	if(szFilePath.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("file empty"));

	if(ulPos >= m_StringList.size())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("pos error(") + szFilePath + __T(")"));

	std::vector<nstring> DirList;
	std::list<nstring>::iterator ItorS = GetItor(m_StringList, ulPos); // 開始位置
	std::list<nstring>::iterator ItorE = GetItor(m_StringList, ulPos + ulLines); // 結束位置
	std::list<nstring>::iterator Itor = ItorS;
	std::string szTemp;

	// 取得目錄列表
	FindPathDir(szFilePath, DirList, true);

	// 建立目錄
	for(unsigned long ulCount = 0, iMax = DirList.size() - 1; ulCount < iMax; ++ulCount)
		_tmkdir(DirList[ulCount].c_str());

	// 開啟檔案
	FILE *f = NULL;

	if(_tfopen_s(&f, szFilePath.c_str(), bAppend ? __T("a+b") : __T("w+b")) != 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("open file failed(") + szFilePath + __T(")"));

	if(f == NULL)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("open file failed(") + szFilePath + __T(")"));

	while(Itor != ItorE)
	{
		// 取得要存檔的字串
		szTemp = C_NString(*Itor).c_str();
		// 添加換行字元
		szTemp += bAutoWrap ? "\n" : "";
		// 存檔
		fwrite(szTemp.c_str(), szTemp.size(), 1, f);

		++Itor;
	}//while

	// 關檔
	fclose(f);

	return true;
}
//-----------------------------------------------------------------------------
// 存檔
bool C_StringList::Save(IN const nstring &szFilePath, IN bool bAppend, IN bool bAutoWrap)
{
	return Save(szFilePath, bAppend, bAutoWrap, 0, m_StringList.size());
}
//-----------------------------------------------------------------------------
// 讀檔
bool C_StringList::Load(IN const nstring &szFilePath)
{
	if(szFilePath.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("file empty"));

	// 清除之前儲存的資料
	Clear();

	// 開啟檔案
	FILE *f = NULL;

	if(_tfopen_s(&f, szFilePath.c_str(), __T("rb")) != 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("open file failed(") + szFilePath + __T(")"));

	if(f == NULL)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("open file failed(") + szFilePath + __T(")"));

	// 取得檔案長度
	int iFSize = fsize(f);

	// 準備暫存區
	char *szBuf = nstdnew char [iFSize + 1];

	if(szBuf == NULL)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create buffer failed(") + szFilePath + __T(")"));

	// 讀檔
	fread(szBuf, iFSize, 1, f);
	// 關檔
	fclose(f);
	// 設定結尾0
	szBuf[iFSize] = 0;

	std::vector<std::string> TempList;

	nstrtok(szBuf, "\n", TempList);
	delete [] szBuf;

	for(std::vector<std::string>::iterator Itor = TempList.begin(); Itor != TempList.end(); ++Itor)
		m_StringList.push_back(C_NString(*Itor).t_str());

	m_bLoadFile = true;

	return true;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------