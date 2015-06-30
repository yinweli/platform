//-----------------------------------------------------------------------------
#include "_include.h"
#include "component.h"
//-----------------------------------------------------------------------------
C_ComponentObj::C_ComponentObj(IN const cstring &server, IN const cstring &type) : m_szServer(server), m_szType(type) {}
//-----------------------------------------------------------------------------
C_ComponentObj::~C_ComponentObj() {}
//-----------------------------------------------------------------------------
// ���o���A���W��
cstring C_ComponentObj::Server() const
{
	_G_();

	return m_szServer;
}
//-----------------------------------------------------------------------------
// ���o���A�W��
cstring C_ComponentObj::Type() const
{
	_G_();

	return m_szType;
}
//-----------------------------------------------------------------------------
// ���o�į�����ե�
C_ObjBenchmark C_ComponentObj::ObjBenchmark() const
{
	_G_();

	return C_ObjBenchmark(m_szServer);
}
//-----------------------------------------------------------------------------
// ���o�R�O�ե�
C_ObjCommand C_ComponentObj::ObjCommand() const
{
	_G_();

	return C_ObjCommand(m_szServer);
}
//-----------------------------------------------------------------------------
// ���o����ե�
C_ObjComponent C_ComponentObj::ObjComponent() const
{
	_G_();

	return C_ObjComponent(m_szServer);
}
//-----------------------------------------------------------------------------
// ���o��Ʈw�ե�
C_ObjDatabase C_ComponentObj::ObjDatabase() const
{
	_G_();

	return C_ObjDatabase(m_szServer);
}
//-----------------------------------------------------------------------------
// ���odbf�ե�
C_ObjDBF C_ComponentObj::ObjDBF() const
{
	_G_();

	return C_ObjDBF(m_szServer);
}
//-----------------------------------------------------------------------------
// ���o�ƥ�ե�
C_ObjEvent C_ComponentObj::ObjEvent() const
{
	_G_();

	return C_ObjEvent(m_szServer);
}
//-----------------------------------------------------------------------------
// ���o�w�ɳB�z�ե�
C_ObjHandle C_ComponentObj::ObjHandle() const
{
	_G_();

	return C_ObjHandle(m_szServer);
}
//-----------------------------------------------------------------------------
// ���o�����ե�
C_ObjNetwork C_ComponentObj::ObjNetwork() const
{
	_G_();

	return C_ObjNetwork(m_szServer);
}
//-----------------------------------------------------------------------------
// ���o��X�ե�
C_ObjOutput C_ComponentObj::ObjOutput() const
{
	_G_();

	return C_ObjOutput(m_szServer);
}
//-----------------------------------------------------------------------------
// ���o�ʥ]�B�z�ե�
C_ObjPacket C_ComponentObj::ObjPacket() const
{
	_G_();

	return C_ObjPacket(m_szServer);
}
//-----------------------------------------------------------------------------
C_Component::C_Component()
{
	InitializeCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
C_Component::~C_Component()
{
	Clear();
	DeleteCriticalSection(&m_csCommon);
}
//-----------------------------------------------------------------------------
// �M������
void C_Component::Clear()
{
	_G_();

	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Data.begin(), m_Data.end(), [] (std::map<cstring, C_ComponentInterface *>::value_type &Itor) { if(Itor.second) delete Itor.second; });
	std::for_each(m_Object.begin(), m_Object.end(), [] (std::map<C_ComponentKey, C_ComponentObj *>::value_type &Itor) { if(Itor.second) delete Itor.second; });
	m_Data.clear();
	m_Object.clear();
}
//-----------------------------------------------------------------------------
// ���o����
C_ComponentObj *C_Component::Get(IN const C_ComponentKey &ccKey)
{
	_G_();

	if(ccKey == false)
		return reinterpret_cast<C_ComponentObj *>(C_NOutput::Instance().Error(ERRORNSTD, __T("name empty")));

	C_ThreadLock ccLock(&m_csCommon);
	std::map<cstring, C_ComponentInterface *>::const_iterator ItorData = m_Data.find(ccKey.Name());

	if(ItorData == m_Data.end())
		return reinterpret_cast<C_ComponentObj *>(C_NOutput::Instance().Error(ERRORNSTD, __T("not found(") + ccKey.Key() + __T(")")));

	if(ItorData->second == nullptr)
		return reinterpret_cast<C_ComponentObj *>(C_NOutput::Instance().Error(ERRORNSTD, __T("data null(") + ccKey.Key() + __T(")")));

	std::map<C_ComponentKey, C_ComponentObj *>::iterator ItorObject = m_Object.find(ccKey);

	if(ItorObject != m_Object.end())
		return ItorObject->second;

	C_ComponentObj *pObject = ItorData->second->Create(ccKey);

	if(pObject == nullptr)
		return reinterpret_cast<C_ComponentObj *>(C_NOutput::Instance().Error(ERRORNSTD, __T("create object failed(") + ccKey.Key() + __T(")")));

	m_Object[ccKey] = pObject;

	return pObject;
};
//-----------------------------------------------------------------------------
// ���o�����C��
std::set<cstring> C_Component::Record(IN const cstring &szServer) const
{
	_G_();

	std::set<cstring> Result;
	C_ThreadLock ccLock(&m_csCommon);

	std::for_each(m_Object.begin(), m_Object.end(), [&szServer, &Result] (const std::map<C_ComponentKey, C_ComponentObj *>::value_type &Itor) { if(Itor.first.Server() == szServer) Result.insert(Itor.first.Key()); });

	return Result;
}
//-----------------------------------------------------------------------------