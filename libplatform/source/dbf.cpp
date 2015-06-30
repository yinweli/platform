//-----------------------------------------------------------------------------
#include "_include.h"
#include "dbf.h"
//-----------------------------------------------------------------------------
S_RecordDBF::S_RecordDBF() {}
//-----------------------------------------------------------------------------
S_RecordDBF::S_RecordDBF(IN const cstring &filepath, IN int size) : szFilePath(filepath), iSize(size) {}
//-----------------------------------------------------------------------------
C_DBF::C_DBF()
{
	m_Data = gcnew LibCSNStandard::DBFData();
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_DBF::~C_DBF()
{
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// 新增dbf
bool C_DBF::Add(IN const cstring &szName, IN const cstring &szClass, IN const cstring &szComponent, IN const cstring &szFilePath)
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	return m_Data->Add(szName.tostring(), szClass.tostring(), szComponent.tostring(), szFilePath.tostring());
}
//-----------------------------------------------------------------------------
// 重新讀取dbf
bool C_DBF::Reload()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	return m_Data->Reload();
}
//-----------------------------------------------------------------------------
// 重新讀取dbf
bool C_DBF::Reload(IN const cstring &szName)
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	return m_Data->Reload(szName.tostring());
}
//-----------------------------------------------------------------------------
// 取得dbf
LibCSNStandard::DBF ^C_DBF::Get(IN const cstring &szName, IN const C_Argu &ccGUID)
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	return m_Data->Get(szName.tostring(), cstring(ccGUID).tostring());
}
//-----------------------------------------------------------------------------
// 取得dbf迭代器
LibCSNStandard::DBFItor ^C_DBF::Get(IN const cstring &szName)
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	return m_Data->Get(szName.tostring());
}
//-----------------------------------------------------------------------------
// 取得紀錄列表
std::map<cstring, S_RecordDBF> C_DBF::Record() const
{
	_G_();

	std::map<cstring, S_RecordDBF> Result;
	C_ThreadLock ccLock(&m_csCommon);

	for(System::Collections::IEnumerator ^Itor = m_Data->GetEnumerator(); Itor->MoveNext(); )
	{
		if(Itor->Current == nullptr)
			continue;

		System::Collections::Generic::KeyValuePair<System::String ^, LibCSNStandard::DBFInterface ^> ^Data = (System::Collections::Generic::KeyValuePair<System::String ^, LibCSNStandard::DBFInterface ^> ^)Itor->Current;

		if(Data->Value == nullptr)
			continue;

		Result[Data->Key] = S_RecordDBF(Data->Value->FilePath(), Data->Value->Count());
	}//for

	return Result;
}
//-----------------------------------------------------------------------------