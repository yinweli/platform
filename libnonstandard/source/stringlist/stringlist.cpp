//-----------------------------------------------------------------------------
#include "stringlist.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// �H�s�����ި��o std::list<nstring> �����N��
std::list<nstring>::iterator GetItor(IN std::list<nstring> &r, IN unsigned long ulPos)
{
	if(ulPos >= r.size())
		return r.end();

	std::list<nstring>::iterator Itor = r.begin();
	std::advance(Itor, ulPos);

	return Itor;
}
//-----------------------------------------------------------------------------
// �H�s�����ި��o std::list<nstring> �����N��
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
// �Ѻc�l
C_StringList::~C_StringList()
{
	Clear();
}
//-----------------------------------------------------------------------------
// �M������
void C_StringList::Clear()
{
	m_bLoadFile = false;
	m_StringList.clear();
}
//-----------------------------------------------------------------------------
// ���oŪ���ɮ׺X��
bool C_StringList::IsLoad() const
{
	return m_bLoadFile;
}
//-----------------------------------------------------------------------------
// �[�J�@��
void C_StringList::AddLine(IN const TCHAR *szInput, IN unsigned long ulPos)
{
	m_StringList.insert(GetItor(m_StringList, ulPos), szInput ? szInput : __T(""));
}
//-----------------------------------------------------------------------------
// �[�J�@��
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
// �R���@��
void C_StringList::DelLine(IN unsigned long ulPos)
{
	std::list<nstring>::iterator Itor = GetItor(m_StringList, ulPos);

	if(Itor == m_StringList.end())
		return;

	m_StringList.erase(Itor);
}
//-----------------------------------------------------------------------------
// ���o�@��
const TCHAR *C_StringList::GetLine(IN unsigned long ulPos) const
{
	std::list<nstring>::const_iterator Itor = GetItor(m_StringList, ulPos);

	return Itor != m_StringList.end() ? (*Itor).c_str() : NULL;
}
//-----------------------------------------------------------------------------
// ���o�@��
nstring C_StringList::GetLineStr(IN unsigned long ulPos) const
{
	std::list<nstring>::const_iterator Itor = GetItor(m_StringList, ulPos);

	return Itor != m_StringList.end() ? *Itor : __T("");
}
//-----------------------------------------------------------------------------
// ���o�@�檺�r��
unsigned long C_StringList::GetLineLen(IN unsigned long ulPos) const
{
	std::list<nstring>::const_iterator Itor = GetItor(m_StringList, ulPos);

	return Itor != m_StringList.end() ? (*Itor).size() : 0;
}
//-----------------------------------------------------------------------------
// ���o���
unsigned long C_StringList::GetLineCount() const
{
	return m_StringList.size();
}
//-----------------------------------------------------------------------------
// ���o�r��C��}�Y���N��
C_StringList::const_iterator C_StringList::Begin() const
{
	return m_StringList.begin();
}
//-----------------------------------------------------------------------------
// ���o�r��C�������N��
C_StringList::const_iterator C_StringList::End() const
{
	return m_StringList.end();
}
//-----------------------------------------------------------------------------
// �s��
bool C_StringList::Save(IN const nstring &szFilePath, IN bool bAppend, IN bool bAutoWrap, IN unsigned long ulPos, IN unsigned long ulLines)
{
	if(szFilePath.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("file empty"));

	if(ulPos >= m_StringList.size())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("pos error(") + szFilePath + __T(")"));

	std::vector<nstring> DirList;
	std::list<nstring>::iterator ItorS = GetItor(m_StringList, ulPos); // �}�l��m
	std::list<nstring>::iterator ItorE = GetItor(m_StringList, ulPos + ulLines); // ������m
	std::list<nstring>::iterator Itor = ItorS;
	std::string szTemp;

	// ���o�ؿ��C��
	FindPathDir(szFilePath, DirList, true);

	// �إߥؿ�
	for(unsigned long ulCount = 0, iMax = DirList.size() - 1; ulCount < iMax; ++ulCount)
		_tmkdir(DirList[ulCount].c_str());

	// �}���ɮ�
	FILE *f = NULL;

	if(_tfopen_s(&f, szFilePath.c_str(), bAppend ? __T("a+b") : __T("w+b")) != 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("open file failed(") + szFilePath + __T(")"));

	if(f == NULL)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("open file failed(") + szFilePath + __T(")"));

	while(Itor != ItorE)
	{
		// ���o�n�s�ɪ��r��
		szTemp = C_NString(*Itor).c_str();
		// �K�[����r��
		szTemp += bAutoWrap ? "\n" : "";
		// �s��
		fwrite(szTemp.c_str(), szTemp.size(), 1, f);

		++Itor;
	}//while

	// ����
	fclose(f);

	return true;
}
//-----------------------------------------------------------------------------
// �s��
bool C_StringList::Save(IN const nstring &szFilePath, IN bool bAppend, IN bool bAutoWrap)
{
	return Save(szFilePath, bAppend, bAutoWrap, 0, m_StringList.size());
}
//-----------------------------------------------------------------------------
// Ū��
bool C_StringList::Load(IN const nstring &szFilePath)
{
	if(szFilePath.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("file empty"));

	// �M�����e�x�s�����
	Clear();

	// �}���ɮ�
	FILE *f = NULL;

	if(_tfopen_s(&f, szFilePath.c_str(), __T("rb")) != 0)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("open file failed(") + szFilePath + __T(")"));

	if(f == NULL)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("open file failed(") + szFilePath + __T(")"));

	// ���o�ɮת���
	int iFSize = fsize(f);

	// �ǳƼȦs��
	char *szBuf = nstdnew char [iFSize + 1];

	if(szBuf == NULL)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("create buffer failed(") + szFilePath + __T(")"));

	// Ū��
	fread(szBuf, iFSize, 1, f);
	// ����
	fclose(f);
	// �]�w����0
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