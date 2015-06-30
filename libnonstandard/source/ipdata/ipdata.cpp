//-----------------------------------------------------------------------------
#include "ipdata.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
#define IP_TOKEN __T(":") // ��}�r����j�Ÿ�
//-----------------------------------------------------------------------------
// ���o�ե���}�r��
nstring C_IPData::CorrectIP() const
{
	nstring szResult;

	for(const std::vector<nstring>::value_type &Itor : nstok(m_szIP, __T(".")))
		szResult += (nsoutf(__T("{03}")) << Itor);

	return szResult;
}
//-----------------------------------------------------------------------------
C_IPData::C_IPData() : m_ulPort(0) {}
//-----------------------------------------------------------------------------
C_IPData::C_IPData(IN const nstring &data)
{
	Import(data);
}
//-----------------------------------------------------------------------------
C_IPData::C_IPData(IN const nstring &ip, IN unsigned long port) : m_szIP(ip), m_ulPort(port) {}
//-----------------------------------------------------------------------------
C_IPData::~C_IPData() {}
//-----------------------------------------------------------------------------
bool C_IPData::operator < (IN const C_IPData &rhs) const
{
	nstring szIPLhs = CorrectIP();
	nstring szIPRhs = rhs.CorrectIP();

	return szIPLhs == szIPRhs ? m_ulPort < rhs.m_ulPort : szIPLhs < szIPRhs;
}
//-----------------------------------------------------------------------------
bool C_IPData::operator > (IN const C_IPData &rhs) const
{
	nstring szIPLhs = CorrectIP();
	nstring szIPRhs = rhs.CorrectIP();

	return szIPLhs == szIPRhs ? m_ulPort > rhs.m_ulPort : szIPLhs > szIPRhs;
}
//-----------------------------------------------------------------------------
bool C_IPData::operator <= (IN const C_IPData &rhs) const
{
	nstring szIPLhs = CorrectIP();
	nstring szIPRhs = rhs.CorrectIP();

	return szIPLhs == szIPRhs ? m_ulPort <= rhs.m_ulPort : szIPLhs <= szIPRhs;
}
//-----------------------------------------------------------------------------
bool C_IPData::operator >= (IN const C_IPData &rhs) const
{
	nstring szIPLhs = CorrectIP();
	nstring szIPRhs = rhs.CorrectIP();

	return szIPLhs == szIPRhs ? m_ulPort >= rhs.m_ulPort : szIPLhs >= szIPRhs;
}
//-----------------------------------------------------------------------------
bool C_IPData::operator == (IN const C_IPData &rhs) const
{
	nstring szIPLhs = CorrectIP();
	nstring szIPRhs = rhs.CorrectIP();

	return szIPLhs == szIPRhs && m_ulPort == rhs.m_ulPort;
}
//-----------------------------------------------------------------------------
bool C_IPData::operator != (IN const C_IPData &rhs) const
{
	nstring szIPLhs = CorrectIP();
	nstring szIPRhs = rhs.CorrectIP();

	return szIPLhs != szIPRhs || m_ulPort != rhs.m_ulPort;
}
//-----------------------------------------------------------------------------
// �פJ�r��
bool C_IPData::Import(IN const nstring &szData)
{
	if(szData.empty())
		return C_NOutput::Instance().Error(ERRORNSTD, __T("data empty"));

	std::vector<nstring> Result = nstok(szData, IP_TOKEN);

	if(Result.size() < 2)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("format failed"));

	m_szIP = Result[0];
	nton(Result[1], m_ulPort);

	return true;
}
//-----------------------------------------------------------------------------
// �פJ���
bool C_IPData::Import(IN const nstring &szIP, IN unsigned long ulPort)
{
	m_szIP = szIP;
	m_ulPort = ulPort;

	return true;
}
//-----------------------------------------------------------------------------
// �ץX�r��
nstring C_IPData::Export() const
{
	return nsoutf(__T("{}{}{}")) << m_szIP << IP_TOKEN << m_ulPort;
}
//-----------------------------------------------------------------------------
// ���o��}�r��
nstring C_IPData::IP() const
{
	return m_szIP;
}
//-----------------------------------------------------------------------------
// ���o��
unsigned long C_IPData::Port() const
{
	return m_ulPort;
}
//-----------------------------------------------------------------------------
// ���o�O�_����
bool C_IPData::Empty() const
{
	return m_szIP.empty();
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------