/**
 * @file cstring.h
 * @note C#�r��ե�
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CSTRING
#define _CSTRING
//-----------------------------------------------------------------------------
/**
 * @brief C#�r���ഫ��C++�r��
 * @param szInput ��J�r��
 * @return ���G�r��
 */
inline std::string ConvertAnsi(IN System::String ^szInput)
{
	_G_();

	const char *pTemp = static_cast<const char *>((System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(szInput)).ToPointer());
	std::string szResult = pTemp ? pTemp : "";

	System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void *)pTemp));

	return szResult;
};
/**
 * @brief C#�r���ഫ��C++�r��
 * @param szInput ��J�r��
 * @return ���G�r��
 */
inline std::wstring ConvertUni(IN System::String ^szInput)
{
	_G_();

	const wchar_t *pTemp = static_cast<const wchar_t *>((System::Runtime::InteropServices::Marshal::StringToHGlobalUni(szInput)).ToPointer());
	std::wstring szResult = pTemp ? pTemp : __T("");

	System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void *)pTemp));

	return szResult;
};
/**
 * @brief C#�r���ഫ��C++�r��
 * @param szInput ��J�r��
 * @return ���G�r��
 */
inline nstring Convert(IN System::String ^szInput)
{
#ifndef UNICODE
	return ConvertAnsi(szInput);
#else
	return ConvertUni(szInput);
#endif
};
/**
 * @brief C++�r���ഫ��C#�r��
 * @param szInput ��J�r��
 * @return ���G�r��
 */
inline System::String ^Convert(IN const std::string &szInput)
{
	_G_();

	return gcnew System::String(szInput.c_str());
};
/**
 * @brief C++�r���ഫ��C#�r��
 * @param szInput ��J�r��
 * @return ���G�r��
 */
inline System::String ^Convert(IN const std::wstring &szInput)
{
	_G_();

	return gcnew System::String(szInput.c_str());
};
/**
 * @brief ���o�줸�r��
 * @param uiBytes �줸��
 * @return �줸�r��
 */
inline nstring ByteString(IN unsigned int uiBytes)
{
	_G_();

	return nsoutf(__T("{}.{}")) << uiBytes / 1024 << static_cast<unsigned int>((uiBytes % 1024) / 1024.0f * 10);
};
/**
 * @brief ���o�줸�r��
 * @param ui64Bytes �줸��
 * @return �줸�r��
 */
inline nstring ByteString(IN unsigned __int64 ui64Bytes)
{
	_G_();

	return nsoutf(__T("{}.{}")) << ui64Bytes / 1024 << static_cast<unsigned __int64>((ui64Bytes % 1024) / 1024.0f * 10);
};
//-----------------------------------------------------------------------------
/**
 * @brief C#�r�����O
 * @note ���n�~�ӳo�����O, �o�����O�w�g�ܦM�I���~��nstring�F
 */
class cstring : public nstring
{
public:
	//-------------------------------------
#ifndef UNICODE
	cstring() {};
	cstring(IN const cstring &sz) : nstring(sz.c_str()) {};
	cstring(IN const void *data) : nstring(data ? static_cast<const char *>(data) : "") {};
	cstring(IN const char *sz) : nstring(sz ? sz : "") {};
	cstring(IN const wchar_t *sz) : nstring(sz ? nsconv(sz) : "") {};
	cstring(IN const std::string &sz) : nstring(sz) {};
	cstring(IN const std::wstring &sz) : nstring(nsconv(sz)) {};
	cstring(IN const C_NStrOutf &sz) : nstring(sz) {};
	cstring(IN const C_NString &sz) : nstring(sz) {};
	cstring(IN const C_Argu &data) : nstring(data) {}
	cstring(IN System::Object ^obj) : nstring(nsconvn(obj->ToString())) {};;
	cstring(IN System::String ^sz) : nstring(nsconvn(sz)) {};
	cstring(IN LibCSNStandard::Packet ^packet) : nstring(nsconvn(LibCSNStandard::Json::ToString(packet))) {};
	virtual ~cstring() {};
#else
	cstring() {};
	cstring(IN const cstring &sz) : nstring(sz.c_str()) {};
	cstring(IN const void *data) : nstring(data ? nsconv(static_cast<const char *>(data)) : __T("")) {};
	cstring(IN const char *sz) : nstring(sz ? nsconv(sz) : __T("")) {};
	cstring(IN const wchar_t *sz) : nstring(sz ? sz : __T("")) {};
	cstring(IN const std::string &sz) : nstring(nsconv(sz)) {};
	cstring(IN const std::wstring &sz) : nstring(sz) {};
	cstring(IN const C_NStrOutf &sz) : nstring(sz) {};
	cstring(IN const C_NString &sz) : nstring(sz) {};
	cstring(IN const C_Argu &data) : nstring(data) {};
	cstring(IN System::Object ^obj) : nstring(nsconvn(obj->ToString())) {};
	cstring(IN System::String ^sz) : nstring(nsconvn(sz)) {};
	cstring(IN LibCSNStandard::Packet ^packet) : nstring(nsconvn(LibCSNStandard::Json::ToString(packet))) {};
	virtual ~cstring() {};
#endif
	//-------------------------------------

public:
	//-------------------------------------
	using nstring::operator [];
	using nstring::operator +=;
	using nstring::operator =;
	//-------------------------------------
	/**
	 * @brief ���o�Ѧ�
	 * @return �Ѧ�
	 */
	nstring &toref()
	{
		return *this;
	};
	/**
	 * @brief ���o nstring ���A�r��
	 * @return �r��
	 */
	nstring totstr() const
	{
		return *this;
	};
#ifndef UNICODE
	/**
	 * @brief ���o std::string ���A�r��
	 * @return �r��
	 */
	std::string tocstr() const
	{
		return *this;
	};
	/**
	 * @brief ���o std::wstring ���A�r��
	 * @return �r��
	 */
	std::wstring towstr() const
	{
		return nsconv(*this);
	};
	/**
	 * @brief ���o System::String �r��
	 * @return �r��
	 */
	System::String ^tostring() const
	{
		return Convert(*this);
	};
#else
	/**
	 * @brief ���o std::string ���A�r��
	 * @return �r��
	 */
	std::string tocstr() const
	{
		return nsconv(*this);
	};
	/**
	 * @brief ���o std::wstring ���A�r��
	 * @return �r��
	 */
	std::wstring towstr() const
	{
		return *this;
	};
	/**
	 * @brief ���o System::String �r��
	 * @return �r��
	 */
	System::String ^tostring() const
	{
		return Convert(*this);
	};
#endif
	//-------------------------------------
	/**
	 * @brief ���o���ΦC��
	 * @param tok ���Φr��
	 * @return ���ΦC��
	 */
	std::vector<cstring> split(IN const cstring &tok) const
	{
		std::vector<cstring> Result;

		for(const std::vector<nstring>::value_type &Itor : nstok(*this, tok))
			Result.push_back(Itor);

		return Result;
	};
	//-------------------------------------
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------