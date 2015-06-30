//-----------------------------------------------------------------------------
#include "_ntime.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
#define _NTime_TokDate __T("-")
#define _NTime_TokTime __T(":")
#define _NTime_TokMid __T(" ")
#define _NTime_Tok __T("-: ")
//-----------------------------------------------------------------------------
C_NTime::C_NTime() : m_wYear(0), m_wMon(0), m_wDay(0), m_wHour(0), m_wMin(0), m_wSec(0) {}
//-----------------------------------------------------------------------------
C_NTime::C_NTime(IN ENUM_NTime emNTime) : m_wYear(0), m_wMon(0), m_wDay(0), m_wHour(0), m_wMin(0), m_wSec(0)
{
	SYSTEMTIME sTime;

	memset(&sTime, 0, sizeof(sTime));

	if(emNTime == ENUM_NTime_GMT)
		GetSystemTime(&sTime);

	if(emNTime == ENUM_NTime_Local)
		GetLocalTime(&sTime);

	m_wYear = sTime.wYear;
	m_wMon = sTime.wMonth;
	m_wDay = sTime.wDay;
	m_wHour = sTime.wHour;
	m_wMin = sTime.wMinute;
	m_wSec = sTime.wSecond;
}
//-----------------------------------------------------------------------------
C_NTime::C_NTime(IN __int64 second) : m_wYear(0), m_wMon(0), m_wDay(0), m_wHour(0), m_wMin(0), m_wSec(0)
{
	struct tm sTime;

	if(_localtime64_s(&sTime, &second) == 0)
	{
		m_wYear = static_cast<short>(sTime.tm_year + 1900);
		m_wMon = static_cast<short>(sTime.tm_mon + 1);
		m_wDay = static_cast<short>(sTime.tm_mday);
		m_wHour = static_cast<short>(sTime.tm_hour);
		m_wMin = static_cast<short>(sTime.tm_min);
		m_wSec = static_cast<short>(sTime.tm_sec);
	}//if
}
//-----------------------------------------------------------------------------
C_NTime::C_NTime(IN const struct tm &time) : m_wYear(0), m_wMon(0), m_wDay(0), m_wHour(0), m_wMin(0), m_wSec(0)
{
	m_wYear = static_cast<short>(time.tm_year + 1900);
	m_wMon = static_cast<short>(time.tm_mon + 1);
	m_wDay = static_cast<short>(time.tm_mday);
	m_wHour = static_cast<short>(time.tm_hour);
	m_wMin = static_cast<short>(time.tm_min);
	m_wSec = static_cast<short>(time.tm_sec);
}
//-----------------------------------------------------------------------------
C_NTime::C_NTime(IN const SYSTEMTIME &time) : m_wYear(0), m_wMon(0), m_wDay(0), m_wHour(0), m_wMin(0), m_wSec(0)
{
	m_wYear = time.wYear;
	m_wMon = time.wMonth;
	m_wDay = time.wDay;
	m_wHour = time.wHour;
	m_wMin = time.wMinute;
	m_wSec = time.wSecond;
}
//-----------------------------------------------------------------------------
C_NTime::C_NTime(IN const nstring &time) : m_wYear(0), m_wMon(0), m_wDay(0), m_wHour(0), m_wMin(0), m_wSec(0)
{
	std::vector<nstring> Result = nstok(time, _NTime_Tok);

	if(Result.size() >= 6)
	{
		nton(Result[0], m_wYear);
		nton(Result[1], m_wMon);
		nton(Result[2], m_wDay);
		nton(Result[3], m_wHour);
		nton(Result[4], m_wMin);
		nton(Result[5], m_wSec);
	}//if
}
//-----------------------------------------------------------------------------
C_NTime::C_NTime(IN const nstring &time, IN const nstring &tok) : m_wYear(0), m_wMon(0), m_wDay(0), m_wHour(0), m_wMin(0), m_wSec(0)
{
	std::vector<nstring> Result = nstok(time, tok);

	if(Result.size() >= 6)
	{
		nton(Result[0], m_wYear);
		nton(Result[1], m_wMon);
		nton(Result[2], m_wDay);
		nton(Result[3], m_wHour);
		nton(Result[4], m_wMin);
		nton(Result[5], m_wSec);
	}//if
}
//-----------------------------------------------------------------------------
C_NTime::C_NTime(IN short year, IN short mon, IN short day, IN short hour, IN short min, IN short sec) : m_wYear(year), m_wMon(mon), m_wDay(day), m_wHour(hour), m_wMin(min), m_wSec(sec) {}
//-----------------------------------------------------------------------------
C_NTime::~C_NTime() {}
//-----------------------------------------------------------------------------
// = �B��l
C_NTime &C_NTime::operator = (IN const C_NTime &time)
{
	m_wYear = time.m_wYear;
	m_wMon = time.m_wMon;
	m_wDay = time.m_wDay;
	m_wHour = time.m_wHour;
	m_wMin = time.m_wMin;
	m_wSec = time.m_wSec;

	return *this;
}
//-----------------------------------------------------------------------------
// = �B��l
C_NTime &C_NTime::operator = (IN __int64 second)
{
	return (*this = C_NTime(second));
}
//-----------------------------------------------------------------------------
// = �B��l
C_NTime &C_NTime::operator = (IN const struct tm &time)
{
	return (*this = C_NTime(time));
}
//-----------------------------------------------------------------------------
// = �B��l
C_NTime &C_NTime::operator = (IN const SYSTEMTIME &time)
{
	return (*this = C_NTime(time));
}
//-----------------------------------------------------------------------------
// + �B��l
const C_NTime C_NTime::operator + (IN __int64 second) const
{
	return C_NTime(static_cast<__int64>(*this) + second);
}
//-----------------------------------------------------------------------------
// - �B��l
const C_NTime C_NTime::operator - (IN __int64 second) const
{
	return C_NTime(static_cast<__int64>(*this) - second);
}
//-----------------------------------------------------------------------------
// += �B��l
C_NTime &C_NTime::operator += (IN __int64 second)
{
	return (*this = C_NTime(static_cast<__int64>(*this) + second));
}
//-----------------------------------------------------------------------------
// -= �B��l
C_NTime &C_NTime::operator -= (IN __int64 second)
{
	return (*this = C_NTime(static_cast<__int64>(*this) - second));
}
//-----------------------------------------------------------------------------
// == �B��l
bool C_NTime::operator == (IN const C_NTime &time) const
{
	return *this == static_cast<__int64>(time);
}
//-----------------------------------------------------------------------------
// == �B��l
bool C_NTime::operator == (IN __int64 second) const
{
	return static_cast<__int64>(*this) == second;
}
//-----------------------------------------------------------------------------
// == �B��l
bool C_NTime::operator == (IN const struct tm &time) const
{
	return *this == C_NTime(time);
}
//-----------------------------------------------------------------------------
// == �B��l
bool C_NTime::operator == (IN const SYSTEMTIME &time) const
{
	return *this == C_NTime(time);
}
//-----------------------------------------------------------------------------
// != �B��l
bool C_NTime::operator != (IN const C_NTime &time) const
{
	return *this != static_cast<__int64>(time);
}
//-----------------------------------------------------------------------------
// != �B��l
bool C_NTime::operator != (IN __int64 second) const
{
	return static_cast<__int64>(*this) != second;
}
//-----------------------------------------------------------------------------
// != �B��l
bool C_NTime::operator != (IN const struct tm &time) const
{
	return *this != C_NTime(time);
}
//-----------------------------------------------------------------------------
// != �B��l
bool C_NTime::operator != (IN const SYSTEMTIME &time) const
{
	return *this != C_NTime(time);
}
//-----------------------------------------------------------------------------
// < �B��l
bool C_NTime::operator < (IN const C_NTime &time) const
{
	return *this < static_cast<__int64>(time);
}
//-----------------------------------------------------------------------------
// < �B��l
bool C_NTime::operator < (IN __int64 second) const
{
	return static_cast<__int64>(*this) < second;
}
//-----------------------------------------------------------------------------
// < �B��l
bool C_NTime::operator < (IN const struct tm &time) const
{
	return *this < C_NTime(time);
}
//-----------------------------------------------------------------------------
// < �B��l
bool C_NTime::operator < (IN const SYSTEMTIME &time) const
{
	return *this < C_NTime(time);
}
//-----------------------------------------------------------------------------
// > �B��l
bool C_NTime::operator > (IN const C_NTime &time) const
{
	return *this > static_cast<__int64>(time);
}
//-----------------------------------------------------------------------------
// > �B��l
bool C_NTime::operator > (IN __int64 second) const
{
	return static_cast<__int64>(*this) > second;
}
//-----------------------------------------------------------------------------
// > �B��l
bool C_NTime::operator > (IN const struct tm &time) const
{
	return *this > C_NTime(time);
}
//-----------------------------------------------------------------------------
// > �B��l
bool C_NTime::operator > (IN const SYSTEMTIME &time) const
{
	return *this > C_NTime(time);
}
//-----------------------------------------------------------------------------
// <= �B��l
bool C_NTime::operator <= (IN const C_NTime &time) const
{
	return *this <= static_cast<__int64>(time);
}
//-----------------------------------------------------------------------------
// <= �B��l
bool C_NTime::operator <= (IN __int64 second) const
{
	return static_cast<__int64>(*this) <= second;
}
//-----------------------------------------------------------------------------
// <= �B��l
bool C_NTime::operator <= (IN const struct tm &time) const
{
	return *this <= C_NTime(time);
}
//-----------------------------------------------------------------------------
// <= �B��l
bool C_NTime::operator <= (IN const SYSTEMTIME &time) const
{
	return *this <= C_NTime(time);
}
//-----------------------------------------------------------------------------
// >= �B��l
bool C_NTime::operator >= (IN const C_NTime &time) const
{
	return *this >= static_cast<__int64>(time);
}
//-----------------------------------------------------------------------------
// >= �B��l
bool C_NTime::operator >= (IN __int64 second) const
{
	return static_cast<__int64>(*this) >= second;
}
//-----------------------------------------------------------------------------
// >= �B��l
bool C_NTime::operator >= (IN const struct tm &time) const
{
	return *this >= C_NTime(time);
}
//-----------------------------------------------------------------------------
// >= �B��l
bool C_NTime::operator >= (IN const SYSTEMTIME &time) const
{
	return *this >= C_NTime(time);
}
//-----------------------------------------------------------------------------
// �૬�B��l
C_NTime::operator __int64 () const
{
	struct tm sTime = *this;

	return _mktime64(&sTime);
}
//-----------------------------------------------------------------------------
// �૬�B��l
C_NTime::operator struct tm () const
{
	struct tm sTime;

	memset(&sTime, 0, sizeof(sTime));
	sTime.tm_year = m_wYear - 1900;
	sTime.tm_mon = m_wMon - 1;
	sTime.tm_mday = m_wDay;
	sTime.tm_hour = m_wHour;
	sTime.tm_min = m_wMin;
	sTime.tm_sec = m_wSec;

	return sTime;
}
//-----------------------------------------------------------------------------
// �૬�B��l
C_NTime::operator SYSTEMTIME () const
{
	SYSTEMTIME sTime;

	memset(&sTime, 0, sizeof(sTime));
	sTime.wYear = m_wYear;
	sTime.wMonth = m_wMon;
	sTime.wDay = m_wDay;
	sTime.wHour = m_wHour;
	sTime.wMinute = m_wMin;
	sTime.wSecond = m_wSec;

	return sTime;
}
//-----------------------------------------------------------------------------
// �૬�B��l
C_NTime::operator nstring () const
{
	return Time(_NTime_TokDate, _NTime_TokTime);
}
//-----------------------------------------------------------------------------
// ���o�ɶ��r��
nstring C_NTime::Time(IN const nstring &szTokDate, IN const nstring &szTokTime) const
{
	return nsoutf(__T("{}{}{02}{}{02}{}{02}{}{02}{}{02}")) << m_wYear << szTokDate << m_wMon << szTokDate << m_wDay << _NTime_TokMid << m_wHour << szTokTime << m_wMin << szTokTime << m_wSec;
}
//-----------------------------------------------------------------------------
// �]�w�~
void C_NTime::Year(IN short wYear)
{
	m_wYear = wYear;
}
//-----------------------------------------------------------------------------
// �]�w��
void C_NTime::Mon(IN short wMon)
{
	m_wMon = wMon;
}
//-----------------------------------------------------------------------------
// �]�w��
void C_NTime::Day(IN short wDay)
{
	m_wDay = wDay;
}
//-----------------------------------------------------------------------------
// �]�w��
void C_NTime::Hour(IN short wHour)
{
	m_wHour = wHour;
}
//-----------------------------------------------------------------------------
// �]�w��
void C_NTime::Min(IN short wMin)
{
	m_wMin = wMin;
}
//-----------------------------------------------------------------------------
// �]�w��
void C_NTime::Sec(IN short wSec)
{
	m_wSec = wSec;
}
//-----------------------------------------------------------------------------
// ���o�~
short C_NTime::Year() const
{
	return m_wYear;
}
//-----------------------------------------------------------------------------
// ���o��
short C_NTime::Mon() const
{
	return m_wMon;
}
//-----------------------------------------------------------------------------
// ���o��
short C_NTime::Day() const
{
	return m_wDay;
}
//-----------------------------------------------------------------------------
// ���o�P��
short C_NTime::Week() const
{
	struct tm sTime;
	__int64 i64Sec = *this;

	return _localtime64_s(&sTime, &i64Sec) == 0 ? static_cast<short>(sTime.tm_wday) : -1;
}
//-----------------------------------------------------------------------------
// ���o��
short C_NTime::Hour() const
{
	return m_wHour;
}
//-----------------------------------------------------------------------------
// ���o��
short C_NTime::Min() const
{
	return m_wMin;
}
//-----------------------------------------------------------------------------
// ���o��
short C_NTime::Sec() const
{
	return m_wSec;
}
//-----------------------------------------------------------------------------
// ���o��L�ªv�ɶ��r��
nstring TimeStringGTM()
{
	return C_NTime(ENUM_NTime_GMT);
}
//-----------------------------------------------------------------------------
// ���o��L�ªv�ɶ��r��
nstring TimeStringGTM(IN const nstring &szTokDate, IN const nstring &szTokTime)
{
	return C_NTime(ENUM_NTime_GMT).Time(szTokDate, szTokTime);
}
//-----------------------------------------------------------------------------
// ���o���a�ɶ��r��
nstring TimeStringLocal()
{
	return C_NTime(ENUM_NTime_Local);
}
//-----------------------------------------------------------------------------
// ���o���a�ɶ��r��
nstring TimeStringLocal(IN const nstring &szTokDate, IN const nstring &szTokTime)
{
	return C_NTime(ENUM_NTime_Local).Time(szTokDate, szTokTime);
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------