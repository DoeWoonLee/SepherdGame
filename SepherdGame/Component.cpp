#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"

COM_ENUM_STRUCT* CComponent::g_ComEnumStruct = new COM_ENUM_STRUCT[COM_END];

CComponent::CComponent(void) :
	m_pOwnerObject(nullptr),
	m_uiContainerIdx(0) // Get New Index
{

}

CComponent::~CComponent(void)
{

}

_ulong CComponent::Release(void)
{
	_ulong dwRefCnt = CBase::Release();


	if (1 >= dwRefCnt)
	{
		m_pOwnerObject = nullptr;
	}
	return dwRefCnt;
}
void CComponent::Fix_ObjectComponentInfo(COMPONENT_TYPE eType)
{
	m_pOwnerObject->Fix_Component(eType, this);
}
void CComponent::Set_ContainerIdx(_uint uiIdx)
{
	m_uiContainerIdx = uiIdx;
}

void CComponent::Set_OwnerObject(CGameObject * pOwnerObject)
{
	m_pOwnerObject = pOwnerObject;
	//m_pOwnerObject->Add_Ref();
}