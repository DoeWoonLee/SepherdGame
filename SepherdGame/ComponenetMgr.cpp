#include "stdafx.h"
#include "ComponenetMgr.h"
#include "Component.h"

IMPLEMENT_SINGLETON(CComponentMgr)

CComponentMgr::CComponentMgr(void)
{

}
CComponentMgr::~CComponentMgr(void)
{
	Release();
}

void CComponentMgr::Init_ComponentMgr(const _ushort & usSceneSize)
{
	CComponent::g_ComEnumStruct[COM_TRANSFORM].Set(BIT_COM_TRANSFORM, true, true);
	CComponent::g_ComEnumStruct[COM_RESOURCE].Set(BIT_COM_RESOURCE, false, false);
	CComponent::g_ComEnumStruct[COM_SPRITE].Set(BIT_COM_SPRITE, false, true);
	CComponent::g_ComEnumStruct[COM_COLLIDER].Set(BIT_COM_COLLIDER, true, false);
	CComponent::g_ComEnumStruct[COM_CONTROLLER].Set(BIT_CONTROLLER, true, false);
	CComponent::g_ComEnumStruct[COM_RENDERCONTROLLER].Set(BIT_RENDERCONTROLLER, false, true);


}

void CComponentMgr::Release(void)
{
}

void CComponentMgr::Update_Components(const _float & fTimeDelta)
{
}
