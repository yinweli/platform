//-----------------------------------------------------------------------------
#include "dbstore.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// ���o���ަr��
nstring DBStoreIndex(IN unsigned long ulLine, IN const nstring &szColumn)
{
	return ntox(ulLine) + __T(":") + szColumn;
}
//-----------------------------------------------------------------------------
// ���o���
template<typename T> bool DBStoreGet(IN const std::map<nstring, C_Argu> &Store, IN unsigned long ulLine, IN const nstring &szColumn, OUT T &value)
{
	std::map<nstring, C_Argu>::const_iterator Itor = Store.find(DBStoreIndex(ulLine, szColumn));

	if(Itor == Store.end())
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorDBStore(ulLine, szColumn));

	value = static_cast<T>(Itor->second);

	return true;
}
//-----------------------------------------------------------------------------
C_ErrorDBStore::C_ErrorDBStore(IN unsigned long line) : m_szError(__T("data not found(") + ntox(line) + __T(")")) {}
//-----------------------------------------------------------------------------
C_ErrorDBStore::C_ErrorDBStore(IN unsigned long line, IN const estring &column) : m_szError(__T("data not found(") + ntox(line) + __T(", ") + column + __T(")")) {}
//-----------------------------------------------------------------------------
C_ErrorDBStore::~C_ErrorDBStore() {}
//-----------------------------------------------------------------------------
C_ErrorDBStore::operator estring () const
{
	return m_szError;
}
//-----------------------------------------------------------------------------
C_DBStore::C_DBStore() {}
//-----------------------------------------------------------------------------
C_DBStore::~C_DBStore() {}
//-----------------------------------------------------------------------------
// �M������
void C_DBStore::Clear()
{
	m_Store.clear();
	m_ulSize = 0;
}
//-----------------------------------------------------------------------------
// �s�W���
void C_DBStore::Add(IN unsigned long ulLine, IN const nstring &szColumn, IN const std::string &szData)
{
	m_Store[DBStoreIndex(ulLine, szColumn)] = trimtailspace(szData);
	m_ulSize = std::max(m_ulSize, ulLine + 1);
}
//-----------------------------------------------------------------------------
// �s�W���
void C_DBStore::Add(IN unsigned long ulLine, IN const nstring &szColumn, IN const std::wstring &szData)
{
	m_Store[DBStoreIndex(ulLine, szColumn)] = trimtailspace(szData);
	m_ulSize = std::max(m_ulSize, ulLine + 1);
}
//-----------------------------------------------------------------------------
// ���o���
bool C_DBStore::Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT bool &r) const
{
	return DBStoreGet(m_Store, ulLine, szColumn, r);
}
//-----------------------------------------------------------------------------
// ���o���
bool C_DBStore::Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT char &r) const
{
	return DBStoreGet(m_Store, ulLine, szColumn, r);
}
//-----------------------------------------------------------------------------
bool C_DBStore::Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT short &r) const
{
	return DBStoreGet(m_Store, ulLine, szColumn, r);
}
//-----------------------------------------------------------------------------
bool C_DBStore::Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT unsigned short &r) const
{
	return DBStoreGet(m_Store, ulLine, szColumn, r);
}
//-----------------------------------------------------------------------------
bool C_DBStore::Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT long &r) const
{
	return DBStoreGet(m_Store, ulLine, szColumn, r);
}
//-----------------------------------------------------------------------------
bool C_DBStore::Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT unsigned long &r) const
{
	return DBStoreGet(m_Store, ulLine, szColumn, r);
}
//-----------------------------------------------------------------------------
bool C_DBStore::Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT int &r) const
{
	return DBStoreGet(m_Store, ulLine, szColumn, r);
}
//-----------------------------------------------------------------------------
bool C_DBStore::Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT unsigned int &r) const
{
	return DBStoreGet(m_Store, ulLine, szColumn, r);
}
//-----------------------------------------------------------------------------
bool C_DBStore::Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT float &r) const
{
	return DBStoreGet(m_Store, ulLine, szColumn, r);
}
//-----------------------------------------------------------------------------
bool C_DBStore::Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT double &r) const
{
	return DBStoreGet(m_Store, ulLine, szColumn, r);
}
//-----------------------------------------------------------------------------
// ���o���
bool C_DBStore::Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT std::string &r) const
{
	return DBStoreGet(m_Store, ulLine, szColumn, r);
}
//-----------------------------------------------------------------------------
// ���o���
bool C_DBStore::Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT std::wstring &r) const
{
	return DBStoreGet(m_Store, ulLine, szColumn, r);
}
//-----------------------------------------------------------------------------
// ���o���G����
bool C_DBStore::Empty() const
{
	return m_ulSize <= 0;
}
//-----------------------------------------------------------------------------
// ���o���G����
unsigned long C_DBStore::Size() const
{
	return m_ulSize;
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------