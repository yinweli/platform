//-----------------------------------------------------------------------------
#include "dbstore.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
// 取得索引字串
nstring DBStoreIndex(IN unsigned long ulLine, IN const nstring &szColumn)
{
	return ntox(ulLine) + __T(":") + szColumn;
}
//-----------------------------------------------------------------------------
// 取得資料
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
// 清除全部
void C_DBStore::Clear()
{
	m_Store.clear();
	m_ulSize = 0;
}
//-----------------------------------------------------------------------------
// 新增資料
void C_DBStore::Add(IN unsigned long ulLine, IN const nstring &szColumn, IN const std::string &szData)
{
	m_Store[DBStoreIndex(ulLine, szColumn)] = trimtailspace(szData);
	m_ulSize = std::max(m_ulSize, ulLine + 1);
}
//-----------------------------------------------------------------------------
// 新增資料
void C_DBStore::Add(IN unsigned long ulLine, IN const nstring &szColumn, IN const std::wstring &szData)
{
	m_Store[DBStoreIndex(ulLine, szColumn)] = trimtailspace(szData);
	m_ulSize = std::max(m_ulSize, ulLine + 1);
}
//-----------------------------------------------------------------------------
// 取得資料
bool C_DBStore::Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT bool &r) const
{
	return DBStoreGet(m_Store, ulLine, szColumn, r);
}
//-----------------------------------------------------------------------------
// 取得資料
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
// 取得資料
bool C_DBStore::Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT std::string &r) const
{
	return DBStoreGet(m_Store, ulLine, szColumn, r);
}
//-----------------------------------------------------------------------------
// 取得資料
bool C_DBStore::Get(IN unsigned long ulLine, IN const nstring &szColumn, OUT std::wstring &r) const
{
	return DBStoreGet(m_Store, ulLine, szColumn, r);
}
//-----------------------------------------------------------------------------
// 取得結果筆數
bool C_DBStore::Empty() const
{
	return m_ulSize <= 0;
}
//-----------------------------------------------------------------------------
// 取得結果筆數
unsigned long C_DBStore::Size() const
{
	return m_ulSize;
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------