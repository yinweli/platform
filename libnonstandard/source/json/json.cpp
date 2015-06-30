//-----------------------------------------------------------------------------
#include "json.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
#define JSON_ES_SIZE 6
//-----------------------------------------------------------------------------
// unicode字串轉換成json字串
std::string unicode_to_json(IN const std::wstring &szInput)
{
	// 將unicode字串轉換成脫逸序列的json字串
	// 例如 : 
	// "第一章012" 將會被轉換成 "\u7b2c\u4e00\u7ae0012"
	// \u7b2c 代表 '第'
	// \u4e00 代表 '一'
	// \u7ae0 代表 '章'
	// 0 代表 '0'
	// 1 代表 '1'
	// 2 代表 '2'

	std::string szResult;
	unsigned long ulSize = szInput.size() * JSON_ES_SIZE + 1;
	char *szTemp = nstdnew char[ulSize];
	char *szData = szTemp;

	if(szTemp == nullptr)
		return "";

	memset(szTemp, 0, ulSize);

	for(const std::wstring::value_type &Itor : szInput)
	{
		if(isascii(static_cast<int>(Itor)))
		{
			*szData = static_cast<char>(Itor);
			szData += 1;
		}
		else
		{
			_snprintf_s(szData, JSON_ES_SIZE + 1, _TRUNCATE, "\\u%04x", Itor);
			szData += JSON_ES_SIZE;
		}//if
	}//for

	*szData = 0;
	szResult = szTemp;
	delete [] szTemp;

	return szResult;
}
//-----------------------------------------------------------------------------
// json字串轉換成unicode字串
std::wstring json_to_unicode(IN const std::string &szInput)
{
	// 將脫逸序列的json字串轉換成原始字串

	std::wstring szResult;
	unsigned long ulToken;
	char szToken[4];

	for(const char *szItor = szInput.c_str(), *szEnd = szItor + szInput.size(); szItor < szEnd; )
	{
		if(*szItor == '\\' && *(szItor + 1) == 'u')
		{
			if(sscanf_s(std::string(szItor, JSON_ES_SIZE).c_str(), "\\u%x", &ulToken) == 1)
				szResult += reinterpret_cast<wchar_t *>(&ulToken);

			szItor += JSON_ES_SIZE;
		}
		else
		{
			if(isascii(static_cast<int>(*szItor)))
			{
				szToken[0] = *szItor++;
				szToken[1] = 0;
				szToken[2] = 0;
				szToken[3] = 0;
				szResult += reinterpret_cast<wchar_t *>(szToken);
			}
			else
			{
				szToken[0] = *szItor++;
				szToken[1] = *szItor++;
				szToken[2] = 0;
				szToken[3] = 0;
				szResult += C_NString(szToken).w_str();
			}//if
		}//if
	}//for

	return szResult;
}
//-----------------------------------------------------------------------------
C_Json::C_Json() {}
//-----------------------------------------------------------------------------
C_Json::C_Json(IN const C_Json &data) : m_Value(data.m_Value) {}
//-----------------------------------------------------------------------------
C_Json::~C_Json() {}
//-----------------------------------------------------------------------------
C_Json &C_Json::operator = (IN const C_Json &ccJson)
{
	m_Value = ccJson.m_Value;

	return *this;
}
//-----------------------------------------------------------------------------
// 清除全部
void C_Json::Clear()
{
	m_Value.clear();
}
//-----------------------------------------------------------------------------
// 匯入字串
bool C_Json::Import(IN const std::string &szJson)
{
	if(szJson.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("json empty"));

	Json::Reader Reader;

	if(Reader.parse(szJson, m_Value) == false)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("parse failed"));

	return true;
}
//-----------------------------------------------------------------------------
// 匯出字串
std::string C_Json::Export() const
{
#ifdef _DEBUG
	std::string szJson = ExportStyled();
#else
	std::string szJson = ExportFast();
#endif

	/**
	 * 由於jsoncpp的作者對於字元'\'以及其他利用到'\'的符號不正確的策略, 以致當unicode使用到'\u'的時候
	 * 會被不正確的改為'\\u', 所以只好在這裡做修正
	 */
	return nsreplace(szJson, "\\\\", "\\");
}
//-----------------------------------------------------------------------------
// 匯出字串 - 風格化字串
std::string C_Json::ExportStyled() const
{
	Json::StyledWriter Writer;

	return Writer.write(m_Value);
}
//-----------------------------------------------------------------------------
// 匯出字串 - 快速字串
std::string C_Json::ExportFast() const
{
	Json::FastWriter Writer;

	return Writer.write(m_Value);
}
//-----------------------------------------------------------------------------
// 新增成員
void C_Json::Add(IN const nstring &szName, IN bool value)
{
	m_Value[C_NString(szName)] = Json::Value(value);
}
//-----------------------------------------------------------------------------
// 新增成員
void C_Json::Add(IN const nstring &szName, IN char value)
{
	m_Value[C_NString(szName)] = Json::Value(static_cast<int>(value));
}
//-----------------------------------------------------------------------------
// 新增成員
void C_Json::Add(IN const nstring &szName, IN unsigned char value)
{
	m_Value[C_NString(szName)] = Json::Value(static_cast<unsigned int>(value));
}
//-----------------------------------------------------------------------------
// 新增成員
void C_Json::Add(IN const nstring &szName, IN short value)
{
	m_Value[C_NString(szName)] = Json::Value(static_cast<int>(value));
}
//-----------------------------------------------------------------------------
// 新增成員
void C_Json::Add(IN const nstring &szName, IN unsigned short value)
{
	m_Value[C_NString(szName)] = Json::Value(static_cast<unsigned int>(value));
}
//-----------------------------------------------------------------------------
// 新增成員
void C_Json::Add(IN const nstring &szName, IN long value)
{
	m_Value[C_NString(szName)] = Json::Value(static_cast<int>(value));
}
//-----------------------------------------------------------------------------
// 新增成員
void C_Json::Add(IN const nstring &szName, IN unsigned long value)
{
	m_Value[C_NString(szName)] = Json::Value(static_cast<unsigned int>(value));
}
//-----------------------------------------------------------------------------
// 新增成員
void C_Json::Add(IN const nstring &szName, IN int value)
{
	m_Value[C_NString(szName)] = Json::Value(static_cast<int>(value));
}
//-----------------------------------------------------------------------------
// 新增成員
void C_Json::Add(IN const nstring &szName, IN unsigned int value)
{
	m_Value[C_NString(szName)] = Json::Value(static_cast<unsigned int>(value));
}
//-----------------------------------------------------------------------------
// 新增成員
void C_Json::Add(IN const nstring &szName, IN float value)
{
	m_Value[C_NString(szName)] = Json::Value(value);
}
//-----------------------------------------------------------------------------
// 新增成員
void C_Json::Add(IN const nstring &szName, IN double value)
{
	m_Value[C_NString(szName)] = Json::Value(value);
}
//-----------------------------------------------------------------------------
// 新增成員
void C_Json::Add(IN const nstring &szName, IN const std::string &value)
{
	m_Value[C_NString(szName)] = unicode_to_json(C_NString(value));
}
//-----------------------------------------------------------------------------
// 新增成員
void C_Json::Add(IN const nstring &szName, IN const std::wstring &value)
{
	m_Value[C_NString(szName)] = unicode_to_json(value);
}
//-----------------------------------------------------------------------------
// 新增陣列成員
void C_Json::Add(IN const nstring &szName, IN const std::vector<bool> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(array[uiIndex]);

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// 新增陣列成員
void C_Json::Add(IN const nstring &szName, IN const std::vector<char> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(static_cast<int>(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// 新增陣列成員
void C_Json::Add(IN const nstring &szName, IN const std::vector<unsigned char> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(static_cast<unsigned int>(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// 新增陣列成員
void C_Json::Add(IN const nstring &szName, IN const std::vector<short> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(static_cast<int>(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// 新增陣列成員
void C_Json::Add(IN const nstring &szName, IN const std::vector<unsigned short> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(static_cast<unsigned int>(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// 新增陣列成員
void C_Json::Add(IN const nstring &szName, IN const std::vector<long> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(static_cast<int>(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// 新增陣列成員
void C_Json::Add(IN const nstring &szName, IN const std::vector<unsigned long> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(static_cast<unsigned int>(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// 新增陣列成員
void C_Json::Add(IN const nstring &szName, IN const std::vector<int> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(static_cast<int>(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// 新增陣列成員
void C_Json::Add(IN const nstring &szName, IN const std::vector<unsigned int> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(static_cast<unsigned int>(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// 新增陣列成員
void C_Json::Add(IN const nstring &szName, IN const std::vector<float> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(array[uiIndex]);

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// 新增陣列成員
void C_Json::Add(IN const nstring &szName, IN const std::vector<double> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(array[uiIndex]);

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// 新增陣列成員
void C_Json::Add(IN const nstring &szName, IN const std::vector<std::string> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = unicode_to_json(C_NString(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// 新增陣列成員
void C_Json::Add(IN const nstring &szName, IN const std::vector<std::wstring> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = unicode_to_json(array[uiIndex]);

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// 刪除成員
void C_Json::Del(IN const nstring &szName)
{
	m_Value.removeMember(C_NString(szName));
}
//-----------------------------------------------------------------------------
// 取得成員
bool C_Json::Get(IN const nstring &szName, OUT bool &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(false));

	if(Data.isBool() == false)
		return false; // 這裡不用輸出錯誤

	value = Data.asBool();

	return true;
}
//-----------------------------------------------------------------------------
// 取得成員
bool C_Json::Get(IN const nstring &szName, OUT char &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isIntegral() == false)
		return false; // 這裡不用輸出錯誤

	value = static_cast<char>(Data.asInt());

	return true;
}
//-----------------------------------------------------------------------------
// 取得成員
bool C_Json::Get(IN const nstring &szName, OUT unsigned char &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isIntegral() == false)
		return false; // 這裡不用輸出錯誤

	value = static_cast<unsigned char>(Data.asUInt());

	return true;
}
//-----------------------------------------------------------------------------
// 取得成員
bool C_Json::Get(IN const nstring &szName, OUT short &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isIntegral() == false)
		return false; // 這裡不用輸出錯誤

	value = static_cast<short>(Data.asInt());

	return true;
}
//-----------------------------------------------------------------------------
// 取得成員
bool C_Json::Get(IN const nstring &szName, OUT unsigned short &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isIntegral() == false)
		return false; // 這裡不用輸出錯誤

	value = static_cast<unsigned short>(Data.asUInt());

	return true;
}
//-----------------------------------------------------------------------------
// 取得成員
bool C_Json::Get(IN const nstring &szName, OUT long &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isIntegral() == false)
		return false; // 這裡不用輸出錯誤

	value = static_cast<long>(Data.asInt());

	return true;
}
//-----------------------------------------------------------------------------
// 取得成員
bool C_Json::Get(IN const nstring &szName, OUT unsigned long &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isIntegral() == false)
		return false; // 這裡不用輸出錯誤

	value = static_cast<unsigned long>(Data.asUInt());

	return true;
}
//-----------------------------------------------------------------------------
// 取得成員
bool C_Json::Get(IN const nstring &szName, OUT int &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isIntegral() == false)
		return false; // 這裡不用輸出錯誤

	value = static_cast<int>(Data.asInt());

	return true;
}
//-----------------------------------------------------------------------------
// 取得成員
bool C_Json::Get(IN const nstring &szName, OUT unsigned int &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isIntegral() == false)
		return false; // 這裡不用輸出錯誤

	value = static_cast<unsigned int>(Data.asUInt());

	return true;
}
//-----------------------------------------------------------------------------
// 取得成員
bool C_Json::Get(IN const nstring &szName, OUT float &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isDouble() == false)
		return false; // 這裡不用輸出錯誤

	value = static_cast<float>(Data.asDouble());

	return true;
}
//-----------------------------------------------------------------------------
// 取得成員
bool C_Json::Get(IN const nstring &szName, OUT double &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isDouble() == false)
		return false; // 這裡不用輸出錯誤

	value = static_cast<double>(Data.asDouble());

	return true;
}
//-----------------------------------------------------------------------------
// 取得成員
bool C_Json::Get(IN const nstring &szName, OUT std::string &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isString() == false)
		return false; // 這裡不用輸出錯誤

	value = C_NString(json_to_unicode(Data.asString()));

	return true;
}
//-----------------------------------------------------------------------------
// 取得成員
bool C_Json::Get(IN const nstring &szName, OUT std::wstring &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isString() == false)
		return false; // 這裡不用輸出錯誤

	value = json_to_unicode(Data.asString());

	return true;
}
//-----------------------------------------------------------------------------
// 取得陣列成員
bool C_Json::Get(IN const nstring &szName, OUT std::vector<bool> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // 這裡不用輸出錯誤

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isBool())
			value.push_back(Itor.asBool());
		else
			return false; // 這裡不用輸出錯誤
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// 取得陣列成員
bool C_Json::Get(IN const nstring &szName, OUT std::vector<char> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // 這裡不用輸出錯誤

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isIntegral())
			value.push_back(static_cast<char>(Itor.asInt()));
		else
			return false; // 這裡不用輸出錯誤
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// 取得陣列成員
bool C_Json::Get(IN const nstring &szName, OUT std::vector<unsigned char> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // 這裡不用輸出錯誤

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isIntegral())
			value.push_back(static_cast<unsigned char>(Itor.asUInt()));
		else
			return false; // 這裡不用輸出錯誤
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// 取得陣列成員
bool C_Json::Get(IN const nstring &szName, OUT std::vector<short> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // 這裡不用輸出錯誤

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isIntegral())
			value.push_back(static_cast<short>(Itor.asInt()));
		else
			return false; // 這裡不用輸出錯誤
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// 取得陣列成員
bool C_Json::Get(IN const nstring &szName, OUT std::vector<unsigned short> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // 這裡不用輸出錯誤

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isIntegral())
			value.push_back(static_cast<unsigned short>(Itor.asUInt()));
		else
			return false; // 這裡不用輸出錯誤
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// 取得陣列成員
bool C_Json::Get(IN const nstring &szName, OUT std::vector<long> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // 這裡不用輸出錯誤

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isIntegral())
			value.push_back(Itor.asInt());
		else
			return false; // 這裡不用輸出錯誤
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// 取得陣列成員
bool C_Json::Get(IN const nstring &szName, OUT std::vector<unsigned long> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // 這裡不用輸出錯誤

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isIntegral())
			value.push_back(Itor.asUInt());
		else
			return false; // 這裡不用輸出錯誤
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// 取得陣列成員
bool C_Json::Get(IN const nstring &szName, OUT std::vector<int> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // 這裡不用輸出錯誤

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isIntegral())
			value.push_back(Itor.asInt());
		else
			return false; // 這裡不用輸出錯誤
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// 取得陣列成員
bool C_Json::Get(IN const nstring &szName, OUT std::vector<unsigned int> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // 這裡不用輸出錯誤

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isIntegral())
			value.push_back(Itor.asUInt());
		else
			return false; // 這裡不用輸出錯誤
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// 取得陣列成員
bool C_Json::Get(IN const nstring &szName, OUT std::vector<float> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // 這裡不用輸出錯誤

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isDouble())
			value.push_back(static_cast<float>(Itor.asDouble()));
		else
			return false; // 這裡不用輸出錯誤
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// 取得陣列成員
bool C_Json::Get(IN const nstring &szName, OUT std::vector<double> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // 這裡不用輸出錯誤

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isDouble())
			value.push_back(Itor.asDouble());
		else
			return false; // 這裡不用輸出錯誤
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// 取得陣列成員
bool C_Json::Get(IN const nstring &szName, OUT std::vector<std::string> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // 這裡不用輸出錯誤

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isString())
			value.push_back(C_NString(json_to_unicode(Itor.asString())));
		else
			return false; // 這裡不用輸出錯誤
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// 取得陣列成員
bool C_Json::Get(IN const nstring &szName, OUT std::vector<std::wstring> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // 這裡不用輸出錯誤

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isString())
			value.push_back(json_to_unicode(Itor.asString()));
		else
			return false; // 這裡不用輸出錯誤
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// 以字串型態取得成員
std::string C_Json::ToString(IN const nstring &szName) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	switch(Data.type())
	{
	case Json::booleanValue:
		return ntos(Data.asBool());

	case Json::intValue:
		return ntos(Data.asInt());

	case Json::uintValue:
		return ntos(Data.asUInt());

	case Json::realValue:
		return ntos(Data.asDouble());

	case Json::stringValue:
		return C_NString(json_to_unicode(Data.asString()));

	default:
		return "";
	}//switch
}
//-----------------------------------------------------------------------------
// 以字串型態取得成員
std::wstring C_Json::ToWString(IN const nstring &szName) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	switch(Data.type())
	{
	case Json::booleanValue:
		return ntow(Data.asBool());

	case Json::intValue:
		return ntow(Data.asInt());

	case Json::uintValue:
		return ntow(Data.asUInt());

	case Json::realValue:
		return ntow(Data.asDouble());

	case Json::stringValue:
		return json_to_unicode(Data.asString());

	default:
		return __T("");
	}//switch
}
//-----------------------------------------------------------------------------
// 以字串型態取得陣列成員
std::string C_Json::ToString(IN const nstring &szName, IN unsigned long ulIndex) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return "";

	Json::Value Data = Array.get(ulIndex, Json::Value(0));

	switch(Data.type())
	{
	case Json::booleanValue:
		return ntos(Data.asBool());

	case Json::intValue:
		return ntos(Data.asInt());

	case Json::uintValue:
		return ntos(Data.asUInt());

	case Json::realValue:
		return ntos(Data.asDouble());

	case Json::stringValue:
		return C_NString(json_to_unicode(Data.asString()));

	default:
		return "";
	}//switch
}
//-----------------------------------------------------------------------------
// 以字串型態取得陣列成員
std::wstring C_Json::ToWString(IN const nstring &szName, IN unsigned long ulIndex) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return __T("");

	Json::Value Data = Array.get(ulIndex, Json::Value(0));

	switch(Data.type())
	{
	case Json::booleanValue:
		return ntow(Data.asBool());

	case Json::intValue:
		return ntow(Data.asInt());

	case Json::uintValue:
		return ntow(Data.asUInt());

	case Json::realValue:
		return ntow(Data.asDouble());

	case Json::stringValue:
		return json_to_unicode(Data.asString());

	default:
		return __T("");
	}//switch
}
//-----------------------------------------------------------------------------
// 取得成員型態
Json::ValueType C_Json::Type(IN const nstring &szName) const
{
	return m_Value.get(C_NString(szName), Json::Value(0)).type();
}
//-----------------------------------------------------------------------------
// 檢查成員是否存在
bool C_Json::IsExist(IN const nstring &szName) const
{
	return m_Value.isMember(C_NString(szName));
}
//-----------------------------------------------------------------------------
// 檢查是否為空
bool C_Json::Empty() const
{
	return m_Value.empty();
}
//-----------------------------------------------------------------------------
// 取得json資料物件名稱列表
std::vector<nstring> C_Json::Member() const
{
	std::vector<nstring> Result;

	for(const Json::Value::Members::value_type &Itor : m_Value.getMemberNames())
		Result.push_back(C_NString(Itor));

	return Result;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------