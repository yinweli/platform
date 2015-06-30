//-----------------------------------------------------------------------------
#include "json.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
#define JSON_ES_SIZE 6
//-----------------------------------------------------------------------------
// unicode�r���ഫ��json�r��
std::string unicode_to_json(IN const std::wstring &szInput)
{
	// �Nunicode�r���ഫ����h�ǦC��json�r��
	// �Ҧp : 
	// "�Ĥ@��012" �N�|�Q�ഫ�� "\u7b2c\u4e00\u7ae0012"
	// \u7b2c �N�� '��'
	// \u4e00 �N�� '�@'
	// \u7ae0 �N�� '��'
	// 0 �N�� '0'
	// 1 �N�� '1'
	// 2 �N�� '2'

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
// json�r���ഫ��unicode�r��
std::wstring json_to_unicode(IN const std::string &szInput)
{
	// �N��h�ǦC��json�r���ഫ����l�r��

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
// �M������
void C_Json::Clear()
{
	m_Value.clear();
}
//-----------------------------------------------------------------------------
// �פJ�r��
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
// �ץX�r��
std::string C_Json::Export() const
{
#ifdef _DEBUG
	std::string szJson = ExportStyled();
#else
	std::string szJson = ExportFast();
#endif

	/**
	 * �ѩ�jsoncpp���@�̹��r��'\'�H�Ψ�L�Q�Ψ�'\'���Ÿ������T������, �H�P��unicode�ϥΨ�'\u'���ɭ�
	 * �|�Q�����T���אּ'\\u', �ҥH�u�n�b�o�̰��ץ�
	 */
	return nsreplace(szJson, "\\\\", "\\");
}
//-----------------------------------------------------------------------------
// �ץX�r�� - ����Ʀr��
std::string C_Json::ExportStyled() const
{
	Json::StyledWriter Writer;

	return Writer.write(m_Value);
}
//-----------------------------------------------------------------------------
// �ץX�r�� - �ֳt�r��
std::string C_Json::ExportFast() const
{
	Json::FastWriter Writer;

	return Writer.write(m_Value);
}
//-----------------------------------------------------------------------------
// �s�W����
void C_Json::Add(IN const nstring &szName, IN bool value)
{
	m_Value[C_NString(szName)] = Json::Value(value);
}
//-----------------------------------------------------------------------------
// �s�W����
void C_Json::Add(IN const nstring &szName, IN char value)
{
	m_Value[C_NString(szName)] = Json::Value(static_cast<int>(value));
}
//-----------------------------------------------------------------------------
// �s�W����
void C_Json::Add(IN const nstring &szName, IN unsigned char value)
{
	m_Value[C_NString(szName)] = Json::Value(static_cast<unsigned int>(value));
}
//-----------------------------------------------------------------------------
// �s�W����
void C_Json::Add(IN const nstring &szName, IN short value)
{
	m_Value[C_NString(szName)] = Json::Value(static_cast<int>(value));
}
//-----------------------------------------------------------------------------
// �s�W����
void C_Json::Add(IN const nstring &szName, IN unsigned short value)
{
	m_Value[C_NString(szName)] = Json::Value(static_cast<unsigned int>(value));
}
//-----------------------------------------------------------------------------
// �s�W����
void C_Json::Add(IN const nstring &szName, IN long value)
{
	m_Value[C_NString(szName)] = Json::Value(static_cast<int>(value));
}
//-----------------------------------------------------------------------------
// �s�W����
void C_Json::Add(IN const nstring &szName, IN unsigned long value)
{
	m_Value[C_NString(szName)] = Json::Value(static_cast<unsigned int>(value));
}
//-----------------------------------------------------------------------------
// �s�W����
void C_Json::Add(IN const nstring &szName, IN int value)
{
	m_Value[C_NString(szName)] = Json::Value(static_cast<int>(value));
}
//-----------------------------------------------------------------------------
// �s�W����
void C_Json::Add(IN const nstring &szName, IN unsigned int value)
{
	m_Value[C_NString(szName)] = Json::Value(static_cast<unsigned int>(value));
}
//-----------------------------------------------------------------------------
// �s�W����
void C_Json::Add(IN const nstring &szName, IN float value)
{
	m_Value[C_NString(szName)] = Json::Value(value);
}
//-----------------------------------------------------------------------------
// �s�W����
void C_Json::Add(IN const nstring &szName, IN double value)
{
	m_Value[C_NString(szName)] = Json::Value(value);
}
//-----------------------------------------------------------------------------
// �s�W����
void C_Json::Add(IN const nstring &szName, IN const std::string &value)
{
	m_Value[C_NString(szName)] = unicode_to_json(C_NString(value));
}
//-----------------------------------------------------------------------------
// �s�W����
void C_Json::Add(IN const nstring &szName, IN const std::wstring &value)
{
	m_Value[C_NString(szName)] = unicode_to_json(value);
}
//-----------------------------------------------------------------------------
// �s�W�}�C����
void C_Json::Add(IN const nstring &szName, IN const std::vector<bool> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(array[uiIndex]);

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// �s�W�}�C����
void C_Json::Add(IN const nstring &szName, IN const std::vector<char> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(static_cast<int>(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// �s�W�}�C����
void C_Json::Add(IN const nstring &szName, IN const std::vector<unsigned char> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(static_cast<unsigned int>(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// �s�W�}�C����
void C_Json::Add(IN const nstring &szName, IN const std::vector<short> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(static_cast<int>(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// �s�W�}�C����
void C_Json::Add(IN const nstring &szName, IN const std::vector<unsigned short> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(static_cast<unsigned int>(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// �s�W�}�C����
void C_Json::Add(IN const nstring &szName, IN const std::vector<long> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(static_cast<int>(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// �s�W�}�C����
void C_Json::Add(IN const nstring &szName, IN const std::vector<unsigned long> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(static_cast<unsigned int>(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// �s�W�}�C����
void C_Json::Add(IN const nstring &szName, IN const std::vector<int> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(static_cast<int>(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// �s�W�}�C����
void C_Json::Add(IN const nstring &szName, IN const std::vector<unsigned int> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(static_cast<unsigned int>(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// �s�W�}�C����
void C_Json::Add(IN const nstring &szName, IN const std::vector<float> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(array[uiIndex]);

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// �s�W�}�C����
void C_Json::Add(IN const nstring &szName, IN const std::vector<double> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = Json::Value(array[uiIndex]);

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// �s�W�}�C����
void C_Json::Add(IN const nstring &szName, IN const std::vector<std::string> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = unicode_to_json(C_NString(array[uiIndex]));

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// �s�W�}�C����
void C_Json::Add(IN const nstring &szName, IN const std::vector<std::wstring> &array)
{
	Json::Value ValueArray(Json::arrayValue);

	for(unsigned int uiIndex = 0, ulMax = array.size(); uiIndex < ulMax; ++uiIndex)
		ValueArray[uiIndex] = unicode_to_json(array[uiIndex]);

	m_Value[C_NString(szName)] = ValueArray;
}
//-----------------------------------------------------------------------------
// �R������
void C_Json::Del(IN const nstring &szName)
{
	m_Value.removeMember(C_NString(szName));
}
//-----------------------------------------------------------------------------
// ���o����
bool C_Json::Get(IN const nstring &szName, OUT bool &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(false));

	if(Data.isBool() == false)
		return false; // �o�̤��ο�X���~

	value = Data.asBool();

	return true;
}
//-----------------------------------------------------------------------------
// ���o����
bool C_Json::Get(IN const nstring &szName, OUT char &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isIntegral() == false)
		return false; // �o�̤��ο�X���~

	value = static_cast<char>(Data.asInt());

	return true;
}
//-----------------------------------------------------------------------------
// ���o����
bool C_Json::Get(IN const nstring &szName, OUT unsigned char &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isIntegral() == false)
		return false; // �o�̤��ο�X���~

	value = static_cast<unsigned char>(Data.asUInt());

	return true;
}
//-----------------------------------------------------------------------------
// ���o����
bool C_Json::Get(IN const nstring &szName, OUT short &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isIntegral() == false)
		return false; // �o�̤��ο�X���~

	value = static_cast<short>(Data.asInt());

	return true;
}
//-----------------------------------------------------------------------------
// ���o����
bool C_Json::Get(IN const nstring &szName, OUT unsigned short &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isIntegral() == false)
		return false; // �o�̤��ο�X���~

	value = static_cast<unsigned short>(Data.asUInt());

	return true;
}
//-----------------------------------------------------------------------------
// ���o����
bool C_Json::Get(IN const nstring &szName, OUT long &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isIntegral() == false)
		return false; // �o�̤��ο�X���~

	value = static_cast<long>(Data.asInt());

	return true;
}
//-----------------------------------------------------------------------------
// ���o����
bool C_Json::Get(IN const nstring &szName, OUT unsigned long &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isIntegral() == false)
		return false; // �o�̤��ο�X���~

	value = static_cast<unsigned long>(Data.asUInt());

	return true;
}
//-----------------------------------------------------------------------------
// ���o����
bool C_Json::Get(IN const nstring &szName, OUT int &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isIntegral() == false)
		return false; // �o�̤��ο�X���~

	value = static_cast<int>(Data.asInt());

	return true;
}
//-----------------------------------------------------------------------------
// ���o����
bool C_Json::Get(IN const nstring &szName, OUT unsigned int &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isIntegral() == false)
		return false; // �o�̤��ο�X���~

	value = static_cast<unsigned int>(Data.asUInt());

	return true;
}
//-----------------------------------------------------------------------------
// ���o����
bool C_Json::Get(IN const nstring &szName, OUT float &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isDouble() == false)
		return false; // �o�̤��ο�X���~

	value = static_cast<float>(Data.asDouble());

	return true;
}
//-----------------------------------------------------------------------------
// ���o����
bool C_Json::Get(IN const nstring &szName, OUT double &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isDouble() == false)
		return false; // �o�̤��ο�X���~

	value = static_cast<double>(Data.asDouble());

	return true;
}
//-----------------------------------------------------------------------------
// ���o����
bool C_Json::Get(IN const nstring &szName, OUT std::string &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isString() == false)
		return false; // �o�̤��ο�X���~

	value = C_NString(json_to_unicode(Data.asString()));

	return true;
}
//-----------------------------------------------------------------------------
// ���o����
bool C_Json::Get(IN const nstring &szName, OUT std::wstring &value) const
{
	Json::Value Data = m_Value.get(C_NString(szName), Json::Value(0));

	if(Data.isString() == false)
		return false; // �o�̤��ο�X���~

	value = json_to_unicode(Data.asString());

	return true;
}
//-----------------------------------------------------------------------------
// ���o�}�C����
bool C_Json::Get(IN const nstring &szName, OUT std::vector<bool> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // �o�̤��ο�X���~

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isBool())
			value.push_back(Itor.asBool());
		else
			return false; // �o�̤��ο�X���~
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// ���o�}�C����
bool C_Json::Get(IN const nstring &szName, OUT std::vector<char> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // �o�̤��ο�X���~

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isIntegral())
			value.push_back(static_cast<char>(Itor.asInt()));
		else
			return false; // �o�̤��ο�X���~
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// ���o�}�C����
bool C_Json::Get(IN const nstring &szName, OUT std::vector<unsigned char> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // �o�̤��ο�X���~

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isIntegral())
			value.push_back(static_cast<unsigned char>(Itor.asUInt()));
		else
			return false; // �o�̤��ο�X���~
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// ���o�}�C����
bool C_Json::Get(IN const nstring &szName, OUT std::vector<short> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // �o�̤��ο�X���~

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isIntegral())
			value.push_back(static_cast<short>(Itor.asInt()));
		else
			return false; // �o�̤��ο�X���~
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// ���o�}�C����
bool C_Json::Get(IN const nstring &szName, OUT std::vector<unsigned short> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // �o�̤��ο�X���~

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isIntegral())
			value.push_back(static_cast<unsigned short>(Itor.asUInt()));
		else
			return false; // �o�̤��ο�X���~
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// ���o�}�C����
bool C_Json::Get(IN const nstring &szName, OUT std::vector<long> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // �o�̤��ο�X���~

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isIntegral())
			value.push_back(Itor.asInt());
		else
			return false; // �o�̤��ο�X���~
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// ���o�}�C����
bool C_Json::Get(IN const nstring &szName, OUT std::vector<unsigned long> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // �o�̤��ο�X���~

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isIntegral())
			value.push_back(Itor.asUInt());
		else
			return false; // �o�̤��ο�X���~
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// ���o�}�C����
bool C_Json::Get(IN const nstring &szName, OUT std::vector<int> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // �o�̤��ο�X���~

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isIntegral())
			value.push_back(Itor.asInt());
		else
			return false; // �o�̤��ο�X���~
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// ���o�}�C����
bool C_Json::Get(IN const nstring &szName, OUT std::vector<unsigned int> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // �o�̤��ο�X���~

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isIntegral())
			value.push_back(Itor.asUInt());
		else
			return false; // �o�̤��ο�X���~
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// ���o�}�C����
bool C_Json::Get(IN const nstring &szName, OUT std::vector<float> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // �o�̤��ο�X���~

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isDouble())
			value.push_back(static_cast<float>(Itor.asDouble()));
		else
			return false; // �o�̤��ο�X���~
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// ���o�}�C����
bool C_Json::Get(IN const nstring &szName, OUT std::vector<double> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // �o�̤��ο�X���~

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isDouble())
			value.push_back(Itor.asDouble());
		else
			return false; // �o�̤��ο�X���~
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// ���o�}�C����
bool C_Json::Get(IN const nstring &szName, OUT std::vector<std::string> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // �o�̤��ο�X���~

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isString())
			value.push_back(C_NString(json_to_unicode(Itor.asString())));
		else
			return false; // �o�̤��ο�X���~
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// ���o�}�C����
bool C_Json::Get(IN const nstring &szName, OUT std::vector<std::wstring> &value) const
{
	Json::Value Array = m_Value.get(C_NString(szName), Json::Value(Json::arrayValue));

	if(Array.isArray() == false)
		return false; // �o�̤��ο�X���~

	value.clear();

	for(const Json::Value &Itor : Array)
	{
		if(Itor.isString())
			value.push_back(json_to_unicode(Itor.asString()));
		else
			return false; // �o�̤��ο�X���~
	}//for

	return true;
}
//-----------------------------------------------------------------------------
// �H�r�ꫬ�A���o����
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
// �H�r�ꫬ�A���o����
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
// �H�r�ꫬ�A���o�}�C����
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
// �H�r�ꫬ�A���o�}�C����
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
// ���o�������A
Json::ValueType C_Json::Type(IN const nstring &szName) const
{
	return m_Value.get(C_NString(szName), Json::Value(0)).type();
}
//-----------------------------------------------------------------------------
// �ˬd�����O�_�s�b
bool C_Json::IsExist(IN const nstring &szName) const
{
	return m_Value.isMember(C_NString(szName));
}
//-----------------------------------------------------------------------------
// �ˬd�O�_����
bool C_Json::Empty() const
{
	return m_Value.empty();
}
//-----------------------------------------------------------------------------
// ���ojson��ƪ���W�٦C��
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