//-----------------------------------------------------------------------------
#include "_nstroutf.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 取得格式結果
nstring GetResult(IN const nstring &szFormat, IN const nstring &szData)
{
	if(szFormat.empty())
		return szData;

	if(szData.empty())
		return __T("");

	nstring szResult;
	nstring::const_iterator Itor = szFormat.begin();
	nstring::size_type Width = 0;
	bool bOct = false;
	bool bHex1 = false;
	bool bHex2 = false;
	bool bZero = false;
	bool bAlign = false; // 對齊旗標, true表示靠左對齊, false表示靠右對齊

	// 檢查旗標
	while(Itor != szFormat.end() && _tcschr(__T("oxX0LR"), *Itor))
	{
		switch(*Itor++)
		{
		case __T('o'): bOct = true; break;
		case __T('x'): bHex1 = true; break;
		case __T('X'): bHex2 = true; break;
		case __T('0'): bZero = true; break;
		case __T('L'): bAlign = true; break;
		case __T('R'): bAlign = false; break;
		default: break;
		}//switch
	}//while

	// 取得寬度
	{
		nstring szWidth;

		while(Itor != szFormat.end() && _istdigit(*Itor))
			szWidth += *Itor++;

		nton(szWidth, Width);
		Width = std::max(Width, szData.size());
	}

	// 內容設置
	{
		int iData = 0;

		nton(szData, iData);

		if(bOct && iData != 0)
			szResult = noct(iData);

		if(bHex1 && iData != 0)
			szResult = nhex(iData);

		if(bHex2 && iData != 0)
			szResult = nsupper(nhex(iData));
	}

	if(szResult.empty())
		szResult = szData;

	// 內容填充
	if(Width > szResult.size())
	{
		if(bAlign)
			szResult.insert(szResult.end(), Width - szResult.size(), __T(' '));
		else
			szResult.insert(szResult.begin(), Width - szResult.size(), bZero ? __T('0') : __T(' '));
	}//if

	return szResult;
}
//-----------------------------------------------------------------------------
C_NStrOutf::C_NStrOutf(IN const nstring &format) : m_szFormat(format) {}
//-----------------------------------------------------------------------------
C_NStrOutf::~C_NStrOutf() {}
//-----------------------------------------------------------------------------
C_NStrOutf::operator nstring () const
{
	bool bFormat = false;
	nstring szResult;
	nstring szFormat;
	std::vector<nstring>::size_type Pos = 0;

	for(const nstring::value_type &Itor : m_szFormat)
	{
		if(Itor == __T('{'))
		{
			bFormat = true;

			continue;
		}//if

		if(Itor == __T('}'))
		{
			bFormat = false;
			szResult += GetResult(szFormat, m_Data.size() > Pos ? m_Data[Pos] : __T(''));
			szFormat.clear();
			++Pos;

			continue;
		}//if

		if(bFormat)
			szFormat += Itor;
		else
			szResult += Itor;
	}//for

	return szResult;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN bool v)
{
	m_Data.push_back(ntox(v));

	return *this;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN char v)
{
	m_Data.push_back(ntox(v));

	return *this;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN unsigned char v)
{
	m_Data.push_back(ntox(v));

	return *this;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN short v)
{
	m_Data.push_back(ntox(v));

	return *this;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN unsigned short v)
{
	m_Data.push_back(ntox(v));

	return *this;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN long v)
{
	m_Data.push_back(ntox(v));

	return *this;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN unsigned long v)
{
	m_Data.push_back(ntox(v));

	return *this;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN int v)
{
	m_Data.push_back(ntox(v));

	return *this;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN unsigned int v)
{
	m_Data.push_back(ntox(v));

	return *this;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN __int64 v)
{
	m_Data.push_back(ntox(v));

	return *this;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN unsigned __int64 v)
{
	m_Data.push_back(ntox(v));

	return *this;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN float v)
{
	m_Data.push_back(ntox(v));

	return *this;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN double v)
{
	m_Data.push_back(ntox(v));

	return *this;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN const char *v)
{
	m_Data.push_back(C_NString(v));

	return *this;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN const wchar_t *v)
{
	m_Data.push_back(C_NString(v));

	return *this;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN const std::string &v)
{
	m_Data.push_back(C_NString(v));

	return *this;
}
//-----------------------------------------------------------------------------
// << 運算子
C_NStrOutf &C_NStrOutf::operator << (IN const std::wstring &v)
{
	m_Data.push_back(C_NString(v));

	return *this;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------