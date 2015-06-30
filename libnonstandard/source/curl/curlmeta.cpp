//-----------------------------------------------------------------------------
#include "curl.h"
#include "curlmeta.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
C_CURLChip::C_CURLChip() : m_pData(nullptr), m_ulSize(0) {}
//-----------------------------------------------------------------------------
C_CURLChip::C_CURLChip(IN void *data, IN unsigned long size) : m_pData(nullptr), m_ulSize(0)
{
	if(size <= 0)
		return;

	void *pTemp = static_cast<void *>(nstdnew char [size]);

	if(pTemp == nullptr)
		return;

	if(data)
		memcpy(pTemp, data, size);
	else
		memset(pTemp, 0, size);

	m_pData = pTemp;
	m_ulSize = size;
}
//-----------------------------------------------------------------------------
C_CURLChip::~C_CURLChip()
{
	if(m_pData)
		delete [] m_pData;

	m_pData = nullptr;
	m_ulSize = 0;
}
//-----------------------------------------------------------------------------
C_CURLChip::operator bool () const
{
	return m_pData && m_ulSize > 0;
}
//-----------------------------------------------------------------------------
C_CURLChip::operator void * () const
{
	return m_pData;
}
//-----------------------------------------------------------------------------
C_CURLChip::operator unsigned long () const
{
	return m_ulSize;
}
//-----------------------------------------------------------------------------
C_CURLResult::C_CURLResult() : m_pData(nullptr), m_ulSize(0) {}
//-----------------------------------------------------------------------------
C_CURLResult::C_CURLResult(IN const std::vector<C_CURLChip> &chip) : m_pData(nullptr), m_ulSize(0)
{
	unsigned long ulSize = 0;
	unsigned long ulPos = 0;

	for(const std::vector<C_CURLChip>::value_type &Itor : chip)
		ulSize += static_cast<unsigned long>(Itor);

	if(ulSize <= 0)
		return;

	void *pTemp = static_cast<void *>(nstdnew char [ulSize]);

	if(pTemp == nullptr)
		return;

	// 複製結果資料
	for(const std::vector<C_CURLChip>::value_type &Itor : chip)
	{
		memcpy(static_cast<char *>(pTemp) + ulPos, static_cast<void *>(Itor), static_cast<unsigned long>(Itor));
		ulPos += static_cast<unsigned long>(Itor);
	}//for

	m_pData = pTemp;
	m_ulSize = ulSize;
}
//-----------------------------------------------------------------------------
C_CURLResult::~C_CURLResult() {}
//-----------------------------------------------------------------------------
C_CURLResult::operator bool () const
{
	return m_pData && m_ulSize > 0;
}
//-----------------------------------------------------------------------------
C_CURLResult::operator void * () const
{
	return m_pData;
}
//-----------------------------------------------------------------------------
C_CURLResult::operator unsigned long () const
{
	return m_ulSize;
}
//-----------------------------------------------------------------------------
// 清除全部
void C_CURLResult::Clear()
{
	if(m_pData)
		delete [] m_pData;

	m_pData = nullptr;
	m_ulSize = 0;
}
//-----------------------------------------------------------------------------
// 寫入結果函式
size_t C_CURLMeta::WriteResult(void *pResult, size_t count, size_t size, void *pData)
{
	C_CURLMeta *pCurl = static_cast<C_CURLMeta *>(pData);

	if(pCurl == nullptr)
		return C_NOutput::Instance().Error(ERRORNSTD, __T("curl null")) + count * size;

	pCurl->m_Chip.push_back(C_CURLChip(pResult, size));

	return count * size;
}
//-----------------------------------------------------------------------------
C_CURLMeta::C_CURLMeta()
{
	Option(CURLOPT_WRITEFUNCTION, reinterpret_cast<unsigned long>(&WriteResult));
	Option(CURLOPT_WRITEDATA, reinterpret_cast<unsigned long>(this));
}
//-----------------------------------------------------------------------------
C_CURLMeta::~C_CURLMeta()
{
	m_Chip.clear();
}
//-----------------------------------------------------------------------------
// 執行curl
bool C_CURLMeta::Perform()
{
	m_Chip.clear();

	return static_cast<C_CURLBase *>(this)->Perform();
}
//-----------------------------------------------------------------------------
// 取得結果物件
C_CURLResult C_CURLMeta::Result() const
{
	C_CURLResult ccResult(m_Chip);

	return ccResult;
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------