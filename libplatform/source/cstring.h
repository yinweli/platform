/**
 * @file cstring.h
 * @note C#字串組件
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _CSTRING
#define _CSTRING
//-----------------------------------------------------------------------------
/**
 * @brief C#字串轉換為C++字串
 * @param szInput 輸入字串
 * @return 結果字串
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
 * @brief C#字串轉換為C++字串
 * @param szInput 輸入字串
 * @return 結果字串
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
 * @brief C#字串轉換為C++字串
 * @param szInput 輸入字串
 * @return 結果字串
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
 * @brief C++字串轉換為C#字串
 * @param szInput 輸入字串
 * @return 結果字串
 */
inline System::String ^Convert(IN const std::string &szInput)
{
	_G_();

	return gcnew System::String(szInput.c_str());
};
/**
 * @brief C++字串轉換為C#字串
 * @param szInput 輸入字串
 * @return 結果字串
 */
inline System::String ^Convert(IN const std::wstring &szInput)
{
	_G_();

	return gcnew System::String(szInput.c_str());
};
/**
 * @brief 取得位元字串
 * @param uiBytes 位元值
 * @return 位元字串
 */
inline nstring ByteString(IN unsigned int uiBytes)
{
	_G_();

	return nsoutf(__T("{}.{}")) << uiBytes / 1024 << static_cast<unsigned int>((uiBytes % 1024) / 1024.0f * 10);
};
/**
 * @brief 取得位元字串
 * @param ui64Bytes 位元值
 * @return 位元字串
 */
inline nstring ByteString(IN unsigned __int64 ui64Bytes)
{
	_G_();

	return nsoutf(__T("{}.{}")) << ui64Bytes / 1024 << static_cast<unsigned __int64>((ui64Bytes % 1024) / 1024.0f * 10);
};
//-----------------------------------------------------------------------------
/**
 * @brief C#字串類別
 * @note 不要繼承這個類別, 這個類別已經很危險的繼承nstring了
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
	 * @brief 取得參考
	 * @return 參考
	 */
	nstring &toref()
	{
		return *this;
	};
	/**
	 * @brief 取得 nstring 型態字串
	 * @return 字串
	 */
	nstring totstr() const
	{
		return *this;
	};
#ifndef UNICODE
	/**
	 * @brief 取得 std::string 型態字串
	 * @return 字串
	 */
	std::string tocstr() const
	{
		return *this;
	};
	/**
	 * @brief 取得 std::wstring 型態字串
	 * @return 字串
	 */
	std::wstring towstr() const
	{
		return nsconv(*this);
	};
	/**
	 * @brief 取得 System::String 字串
	 * @return 字串
	 */
	System::String ^tostring() const
	{
		return Convert(*this);
	};
#else
	/**
	 * @brief 取得 std::string 型態字串
	 * @return 字串
	 */
	std::string tocstr() const
	{
		return nsconv(*this);
	};
	/**
	 * @brief 取得 std::wstring 型態字串
	 * @return 字串
	 */
	std::wstring towstr() const
	{
		return *this;
	};
	/**
	 * @brief 取得 System::String 字串
	 * @return 字串
	 */
	System::String ^tostring() const
	{
		return Convert(*this);
	};
#endif
	//-------------------------------------
	/**
	 * @brief 取得分割列表
	 * @param tok 分割字元
	 * @return 分割列表
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