//-----------------------------------------------------------------------------
#include "argument.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
C_Argu::C_Argu() {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN bool value) : m_szValue(ntox(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN char value) : m_szValue(ntox(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN unsigned char value) : m_szValue(ntox(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN short value) : m_szValue(ntox(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN unsigned short value) : m_szValue(ntox(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN long value) : m_szValue(ntox(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN unsigned long value) : m_szValue(ntox(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN int value) : m_szValue(ntox(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN unsigned int value) : m_szValue(ntox(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN __int64 value) : m_szValue(ntox(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN unsigned __int64 value) : m_szValue(ntox(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN float value) : m_szValue(ntox(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN double value) : m_szValue(ntox(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN const char *value) : m_szValue(C_NString(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN const wchar_t *value) : m_szValue(C_NString(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN const std::string &value) : m_szValue(C_NString(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN const std::wstring &value) : m_szValue(C_NString(value)) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN void *value) : m_szValue(ntox(reinterpret_cast<unsigned long>(value))) {}
//-----------------------------------------------------------------------------
C_Argu::C_Argu(IN const C_Argu &argu) : m_szValue(argu.m_szValue) {}
//-----------------------------------------------------------------------------
C_Argu::~C_Argu() {}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN bool value)
{
	m_szValue = ntox(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN char value)
{
	m_szValue = ntox(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN unsigned char value)
{
	m_szValue = ntox(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN short value)
{
	m_szValue = ntox(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN unsigned short value)
{
	m_szValue = ntox(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN long value)
{
	m_szValue = ntox(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN unsigned long value)
{
	m_szValue = ntox(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN int value)
{
	m_szValue = ntox(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN unsigned int value)
{
	m_szValue = ntox(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN __int64 value)
{
	m_szValue = ntox(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN unsigned __int64 value)
{
	m_szValue = ntox(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN float value)
{
	m_szValue = ntox(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN double value)
{
	m_szValue = ntox(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN const char *value)
{
	m_szValue = C_NString(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN const wchar_t *value)
{
	m_szValue = C_NString(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN const std::string &value)
{
	m_szValue = C_NString(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN const std::wstring &value)
{
	m_szValue = C_NString(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN void *value)
{
	m_szValue = ntox(reinterpret_cast<unsigned long>(value));

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu &C_Argu::operator = (IN const C_Argu &argu)
{
	m_szValue = argu.m_szValue;

	return *this;
}
//-----------------------------------------------------------------------------
C_Argu::operator bool () const
{
	bool value;

	nton(m_szValue, value);

	return value;
}
//-----------------------------------------------------------------------------
C_Argu::operator char () const
{
	char value;

	nton(m_szValue, value);

	return value;
}
//-----------------------------------------------------------------------------
C_Argu::operator unsigned char () const
{
	unsigned char value;

	nton(m_szValue, value);

	return value;
}
//-----------------------------------------------------------------------------
C_Argu::operator short () const
{
	short value;

	nton(m_szValue, value);

	return value;
}
//-----------------------------------------------------------------------------
C_Argu::operator unsigned short () const
{
	unsigned short value;

	nton(m_szValue, value);

	return value;
}
//-----------------------------------------------------------------------------
C_Argu::operator long () const
{
	long value;

	nton(m_szValue, value);

	return value;
}
//-----------------------------------------------------------------------------
C_Argu::operator unsigned long () const
{
	unsigned long value;

	nton(m_szValue, value);

	return value;
}
//-----------------------------------------------------------------------------
C_Argu::operator int () const
{
	int value;

	nton(m_szValue, value);

	return value;
}
//-----------------------------------------------------------------------------
C_Argu::operator unsigned int () const
{
	unsigned int value;

	nton(m_szValue, value);

	return value;
}
//-----------------------------------------------------------------------------
C_Argu::operator __int64 () const
{
	__int64 value;

	nton(m_szValue, value);

	return value;
}
//-----------------------------------------------------------------------------
C_Argu::operator unsigned __int64 () const
{
	unsigned __int64 value;

	nton(m_szValue, value);

	return value;
}
//-----------------------------------------------------------------------------
C_Argu::operator float () const
{
	float value;

	nton(m_szValue, value);

	return value;
}
//-----------------------------------------------------------------------------
C_Argu::operator double () const
{
	double value;

	nton(m_szValue, value);

	return value;
}
//-----------------------------------------------------------------------------
C_Argu::operator std::string () const
{
	return C_NString(m_szValue);
}
//-----------------------------------------------------------------------------
C_Argu::operator std::wstring () const
{
	return C_NString(m_szValue);
}
//-----------------------------------------------------------------------------
C_Argu::operator void * () const
{
	void *value;

	nton(m_szValue, reinterpret_cast<unsigned long &>(value));

	return value;
}
//-----------------------------------------------------------------------------
// 眔
unsigned long C_Argu::size() const
{
	return m_szValue.size();
}
//-----------------------------------------------------------------------------
// 浪琩琌
bool C_Argu::empty() const
{
	return m_szValue.empty();
}
//-----------------------------------------------------------------------------
C_Argp::C_Argp() {}
//-----------------------------------------------------------------------------
C_Argp::C_Argp(IN const C_Argp &argp) : m_Argument(argp.m_Argument) {}
//-----------------------------------------------------------------------------
C_Argp::~C_Argp() {}
//-----------------------------------------------------------------------------
// 睲埃场
void C_Argp::clear()
{
	m_Argument.clear();
}
//-----------------------------------------------------------------------------
// 砞﹚把计
void C_Argp::set(IN const nstring &szName, IN const C_Argu &value)
{
	m_Argument[szName] = value;
}
//-----------------------------------------------------------------------------
// 砞﹚把计
void C_Argp::set(IN const C_Argp &value)
{
	m_Argument.insert(value.m_Argument.begin(), value.m_Argument.end());
}
//-----------------------------------------------------------------------------
// 眔把计
C_Argu C_Argp::get(IN const nstring &szName) const
{
	std::map<nstring, C_Argu>::const_iterator Itor = m_Argument.find(szName);

	return Itor != m_Argument.end() ? Itor->second : C_Argu();
}
//-----------------------------------------------------------------------------
// 眔把计
std::map<nstring, C_Argu> C_Argp::get() const
{
	return m_Argument;
}
//-----------------------------------------------------------------------------
// 眔把计秨繷竟
C_Argp::iterator C_Argp::begin()
{
	return m_Argument.begin();
}
//-----------------------------------------------------------------------------
// 眔把计挡Ю竟
C_Argp::iterator C_Argp::end()
{
	return m_Argument.end();
}
//-----------------------------------------------------------------------------
// 眔把计秨繷竟
C_Argp::const_iterator C_Argp::begin() const
{
	return m_Argument.begin();
}
//-----------------------------------------------------------------------------
// 眔把计挡Ю竟
C_Argp::const_iterator C_Argp::end() const
{
	return m_Argument.end();
}
//-----------------------------------------------------------------------------
// 眔把计计秖
unsigned long C_Argp::size() const
{
	return m_Argument.size();
}
//-----------------------------------------------------------------------------
// 眔琌
bool C_Argp::empty() const
{
	return m_Argument.empty();
}
//-----------------------------------------------------------------------------
// 眔把计琌
bool C_Argp::exist(IN const nstring &szName) const
{
	return m_Argument.find(szName) != m_Argument.end();
}
//-----------------------------------------------------------------------------
C_Argv::C_Argv() {}
//-----------------------------------------------------------------------------
C_Argv::C_Argv(IN const C_Argv &argv) : m_Argument(argv.m_Argument) {}
//-----------------------------------------------------------------------------
C_Argv::~C_Argv() {}
//-----------------------------------------------------------------------------
C_Argv &C_Argv::operator << (IN const C_Argu &value)
{
	m_Argument.push_back(value);

	return *this;
}
//-----------------------------------------------------------------------------
C_Argv &C_Argv::operator << (IN const C_Argv &value)
{
	m_Argument.insert(m_Argument.end(), value.m_Argument.begin(), value.m_Argument.end());

	return *this;
}
//-----------------------------------------------------------------------------
// 睲埃场
void C_Argv::clear()
{
	m_Argument.clear();
}
//-----------------------------------------------------------------------------
// 砞﹚把计
void C_Argv::set(IN const C_Argv &value)
{
	m_Argument.insert(m_Argument.end(), value.m_Argument.begin(), value.m_Argument.end());
}
//-----------------------------------------------------------------------------
// 砞﹚把计
void C_Argv::set(IN unsigned long ulPos, IN const C_Argu &value)
{
	while(m_Argument.size() < ulPos)
		m_Argument.push_back(C_Argu());

	m_Argument.push_back(value);
}
//-----------------------------------------------------------------------------
// 眔把计
C_Argu C_Argv::get(IN unsigned long ulPos) const
{
	return ulPos < m_Argument.size() ? m_Argument[ulPos] : C_Argu();
}
//-----------------------------------------------------------------------------
// 眔场把计
std::vector<C_Argu> C_Argv::get() const
{
	return m_Argument;
}
//-----------------------------------------------------------------------------
// 眔把计秨繷竟
C_Argv::iterator C_Argv::begin()
{
	return m_Argument.begin();
}
//-----------------------------------------------------------------------------
// 眔把计挡Ю竟
C_Argv::iterator C_Argv::end()
{
	return m_Argument.end();
}
//-----------------------------------------------------------------------------
// 眔把计秨繷竟
C_Argv::const_iterator C_Argv::begin() const
{
	return m_Argument.begin();
}
//-----------------------------------------------------------------------------
// 眔把计挡Ю竟
C_Argv::const_iterator C_Argv::end() const
{
	return m_Argument.end();
}
//-----------------------------------------------------------------------------
// 眔把计计秖
unsigned long C_Argv::size() const
{
	return m_Argument.size();
}
//-----------------------------------------------------------------------------
// 眔琌
bool C_Argv::empty() const
{
	return m_Argument.empty();
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------