//-----------------------------------------------------------------------------
#include "xmlstring.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 分析XML檔案並且增加字串
void ParseXML(IN TiXmlElement *pSource, IN nstring *pTitle, OUT std::map<nstring, nstring> &StringList)
{
	if(pSource == nullptr)
		return;

	// 建立Title字串
	nstring szTitle = nsoutf(__T("{}{}:")) << (pTitle ? *pTitle : __T("")) << pSource->Value();

	// 分析子節點
	for(TiXmlElement *pTemp = pSource->FirstChildElement(); pTemp; pTemp = pTemp->NextSiblingElement())
		ParseXML(pTemp, &szTitle, StringList);

	// 新增字串
	C_NString szID = pSource->Attribute(XMLSTRINGID);
	C_NString szText = pSource->GetText();

	if(szID.empty())
		return;

	if(szText.empty())
		return;

	StringList[szTitle + static_cast<nstring>(szID)] = szText;
}
//-----------------------------------------------------------------------------
C_ErrorXMLString::C_ErrorXMLString(IN const TiXmlDocument &xmldoc) : m_szError(__T("error in line ") + ntox(xmldoc.ErrorRow()) + __T(" : (") + ntox(xmldoc.ErrorId()) + __T(")") + static_cast<nstring>(C_NString(xmldoc.ErrorDesc()))) {}
//-----------------------------------------------------------------------------
C_ErrorXMLString::~C_ErrorXMLString() {}
//-----------------------------------------------------------------------------
C_ErrorXMLString::operator estring () const
{
	return m_szError;
}
//-----------------------------------------------------------------------------
C_XMLString::C_XMLString()
{
	m_Itor = m_StringList.begin();
}
//-----------------------------------------------------------------------------
C_XMLString::~C_XMLString() {}
//-----------------------------------------------------------------------------
// 清除全部
void C_XMLString::Clear()
{
	m_StringList.clear();
	m_Itor = m_StringList.begin();
}
//-----------------------------------------------------------------------------
// 讀取字串檔案
bool C_XMLString::Load(IN const nstring &szFile)
{
	TiXmlDocument ccXmlDoc;

	if(ccXmlDoc.LoadFile(C_NString(szFile).c_str()) == false)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorXMLString(ccXmlDoc), __T("load failed(") + szFile + __T(")"));

	ParseXML(ccXmlDoc.FirstChildElement(), nullptr, m_StringList);

	return true;
}
//-----------------------------------------------------------------------------
// 取得字串
nstring C_XMLString::Get(IN const nstring &szKey, IN const nstring &szDefault) const
{
	std::map<nstring, nstring>::const_iterator Itor = m_StringList.find(szKey);

	return Itor != m_StringList.end() ? Itor->second : szDefault;
}
//-----------------------------------------------------------------------------
// 取得字串
nstring C_XMLString::Get(IN const std::vector<nstring> &KeyList, IN int iID, IN const nstring &szDefault) const
{
	nstring szKey;

	std::for_each(KeyList.begin(), KeyList.end(), [&szKey] (const std::vector<nstring>::value_type &Itor) { szKey += Itor + __T(":"); });

	return Get(szKey + ntox(iID, 10), szDefault);
}
//-----------------------------------------------------------------------------
// 取得字串數量
int C_XMLString::Size() const
{
	return m_StringList.size();
}
//-----------------------------------------------------------------------------
// 重置迭代器
void C_XMLString::ResetItor()
{
	m_Itor = m_StringList.begin();
}
//-----------------------------------------------------------------------------
// 依序取得字串
bool C_XMLString::GetDataByOrder(OUT nstring &szKey, OUT nstring &szString)
{
	bool bResult = false;

	if(m_Itor != m_StringList.end())
	{
		bResult = true;
		szKey = m_Itor->first;
		szString = m_Itor->second;
		m_Itor++;
	}//if

	return bResult;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------