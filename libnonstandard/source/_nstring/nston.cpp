//-----------------------------------------------------------------------------
#include "_nstring.h"
#include "nston.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// �N�r���ഫ�� bool
void ston(IN const std::string &s, OUT bool &r)
{
	r = atol(s.c_str()) ? true : false;
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� bool, �e�r������
void wton(IN const std::wstring &s, OUT bool &r)
{
	r = _wtol(s.c_str()) ? true : false;
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� char
void ston(IN const std::string &s, OUT char &r)
{
	r = static_cast<char>(atol(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� char, �e�r������
void wton(IN const std::wstring &s, OUT char &r)
{
	r = static_cast<char>(_wtol(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� unsigned char
void ston(IN const std::string &s, OUT unsigned char &r)
{
	r = static_cast<unsigned char>(atol(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� unsigned char, �e�r������
void wton(IN const std::wstring &s, OUT unsigned char &r)
{
	r = static_cast<unsigned char>(_wtol(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� short
void ston(IN const std::string &s, OUT short &r)
{
	r = static_cast<short>(atol(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� short, �e�r������
void wton(IN const std::wstring &s, OUT short &r)
{
	r = static_cast<short>(_wtol(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� unsigned short
void ston(IN const std::string &s, OUT unsigned short &r)
{
	r = static_cast<unsigned short>(atol(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� unsigned short, �e�r������
void wton(IN const std::wstring &s, OUT unsigned short &r)
{
	r = static_cast<unsigned short>(_wtol(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� long
void ston(IN const std::string &s, OUT long &r)
{
	r = atol(s.c_str());
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� long, �e�r������
void wton(IN const std::wstring &s, OUT long &r)
{
	r = _wtol(s.c_str());
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� unsigned long
void ston(IN const std::string &s, OUT unsigned long &r)
{
	r = static_cast<unsigned long>(atol(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� unsigned long, �e�r������
void wton(IN const std::wstring &s, OUT unsigned long &r)
{
	r = static_cast<unsigned long>(_wtol(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� int
void ston(IN const std::string &s, OUT int &r)
{
	r = static_cast<int>(atol(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� int, �e�r������
void wton(IN const std::wstring &s, OUT int &r)
{
	r = static_cast<int>(_wtol(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� unsigned int
void ston(IN const std::string &s, OUT unsigned int &r)
{
	r = static_cast<unsigned int>(atol(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� unsigned long, �e�r������
void wton(IN const std::wstring &s, OUT unsigned int &r)
{
	r = static_cast<unsigned int>(_wtol(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� __int64
void ston(IN const std::string &s, OUT __int64 &r)
{
	r = _atoi64(s.c_str());
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� __int64, �e�r������
void wton(IN const std::wstring &s, OUT __int64 &r)
{
	r = _wtoi64(s.c_str());
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� unsigned __int64
void ston(IN const std::string &s, OUT unsigned __int64 &r)
{
	r = static_cast<unsigned __int64>(_atoi64(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� unsigned long, �e�r������
void wton(IN const std::wstring &s, OUT unsigned __int64 &r)
{
	r = static_cast<unsigned __int64>(_wtoi64(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� float
void ston(IN const std::string &s, OUT float &r)
{
	r = static_cast<float>(atof(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� float, �e�r������
void wton(IN const std::wstring &s, OUT float &r)
{
	r = static_cast<float>(_wtof(s.c_str()));
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� double
void ston(IN const std::string &s, OUT double &r)
{
	r = atof(s.c_str());
}
//-----------------------------------------------------------------------------
// �N�r���ഫ�� double, �e�r������
void wton(IN const std::wstring &s, OUT double &r)
{
	r = _wtof(s.c_str());
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------