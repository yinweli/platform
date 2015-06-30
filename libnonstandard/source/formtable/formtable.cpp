//-----------------------------------------------------------------------------
#include "formtable.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 取得長度列表
std::vector<int> C_FormTable::Length() const
{
	std::vector<int> Result;

	for(int iX = 0; iX < m_iSizeX; ++iX)
	{
		Result.push_back(0);

		for(int iY = 0; iY < m_iSizeY; ++iY)
		{
			std::map<nstring, nstring>::const_iterator Itor = m_Data.find(StringCoor(iX, iY));

			if(Itor != m_Data.end())
				Result.back() = std::max(Result.back(), static_cast<int>(mbbytes(Itor->second)));
		}//for
	}//for

	return Result;
}
//-----------------------------------------------------------------------------
// 取得座標字串
nstring C_FormTable::StringCoor(IN int iX, IN int iY) const
{
	return nsoutf(__T("{}:{}")) << iY << iX;
}
//-----------------------------------------------------------------------------
// 建立格線字串
nstring C_FormTable::StringLine(IN const std::vector<int> &Len) const
{
	nstring szResult;

	for(int iPos = 0, iMax = Len.size(); iPos < iMax; ++iPos)
	{
		szResult += nstring(Len[iPos], Horizontal);

		if(iPos + 1 < iMax)
			szResult += Cross;
	}//for

	return szResult;
}
//-----------------------------------------------------------------------------
// 建立內容字串
nstring C_FormTable::StringData(IN const std::vector<int> &Len, IN const std::vector<nstring> &Data, IN bool bAlign) const
{
	if(Len.size() != Data.size())
		return __T("");

	nstring szResult;

	for(int iPos = 0, iMax = Data.size(); iPos < iMax; ++iPos)
	{
		nstring szData = Data[iPos];
		int iLenColumn = Len[iPos];
		int iLenData = mbbytes(szData);
		int iSpaceF = bAlign ? std::max(0, (iLenColumn - iLenData) / 2) : 0; // 計算前置的cFill字元數量
		int iSpaceB = std::max(0, iLenColumn - iSpaceF - iLenData); // 計算後置的cFill字元數量

		szResult += nstring(iSpaceF, __T(' ')) + szData + nstring(iSpaceB, __T(' '));

		if(iPos + 1 < iMax)
			szResult += Vertical;
	}//for

	return szResult;
}
//-----------------------------------------------------------------------------
C_FormTable::C_FormTable() : m_iSizeX(0), m_iSizeY(0), Vertical(__T('|')), Horizontal(__T('-')), Cross(__T('+')) {}
//-----------------------------------------------------------------------------
C_FormTable::~C_FormTable() {}
//-----------------------------------------------------------------------------
// 清除全部
void C_FormTable::Clear()
{
	m_Data.clear();
	m_iSizeX = 0;
	m_iSizeY = 0;
}
//-----------------------------------------------------------------------------
// 設定內容
void C_FormTable::Set(IN int iX, IN int iY, IN const C_Argu &ccData)
{
	m_Data[StringCoor(iX, iY)] = ccData;
	m_iSizeX = std::max(m_iSizeX, iX + 1);
	m_iSizeY = std::max(m_iSizeY, iY + 1);
}
//-----------------------------------------------------------------------------
// 新增內容
void C_FormTable::Add(IN const std::vector<nstring> &Data)
{
	for(int iPos = 0, iMax = Data.size(); iPos < iMax; ++iPos)
		m_Data[StringCoor(iPos, m_iSizeY)] = Data[iPos];

	m_iSizeX = std::max(m_iSizeX, static_cast<int>(Data.size()));
	++m_iSizeY;
}
//-----------------------------------------------------------------------------
// 新增內容
void C_FormTable::Add(IN const C_Argv &ccData)
{
	for(int iPos = 0, iMax = ccData.size(); iPos < iMax; ++iPos)
		m_Data[StringCoor(iPos, m_iSizeY)] = ccData.get(iPos);

	m_iSizeX = std::max(m_iSizeX, static_cast<int>(ccData.size()));
	++m_iSizeY;
}
//-----------------------------------------------------------------------------
// 輸出表格
std::vector<nstring> C_FormTable::ExportList() const
{
	if(m_Data.empty())
		return std::vector<nstring>();

	std::vector<nstring> Result;
	std::vector<int> Len = Length();
	nstring szLine = StringLine(Len);

	Result.push_back(szLine);

	for(int iY = 0; iY < m_iSizeY; ++iY)
	{
		std::vector<nstring> Data;

		for(int iX = 0; iX < m_iSizeX; ++iX)
		{
			std::map<nstring, nstring>::const_iterator Itor = m_Data.find(StringCoor(iX, iY));

			Data.push_back(Itor != m_Data.end() ? Itor->second : __T(""));
		}//for

		Result.push_back(StringData(Len, Data, iY == 0));
		Result.push_back(szLine);
	}//for

	return Result;
}
//-----------------------------------------------------------------------------
// 輸出表格
nstring C_FormTable::ExportString() const
{
	nstring szResult;

	for(const std::vector<nstring>::value_type &Itor : ExportList())
		szResult += Itor + __T("\n");

	return szResult;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------