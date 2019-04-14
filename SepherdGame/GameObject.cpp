#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"


CGameObject::CGameObject(void)
{

}

CGameObject::~CGameObject(void)
{

}

HRESULT CGameObject::Initialize(void)
{
	return S_OK;
}

HRESULT CGameObject::Post_Initialize(void)
{
	auto iter = m_mapComponent.begin();
	auto iter_End = m_mapComponent.end();

	for (; iter != iter_End; ++iter)
	{
		if (FAILED(iter->second->Post_Initialize()))
			return E_FAIL;
	}

	return S_OK;
}


_ulong CGameObject::Update(const _float& fTimeDelta)
{

	MAP_COMPONENT::iterator iter = m_mapComponent.begin();
	MAP_COMPONENT::iterator iter_end = m_mapComponent.end();

	for (; iter != iter_end; ++iter)
	{
		if (nullptr != iter->second)
			iter->second->Update(fTimeDelta);
	}

	return 0;
}

void CGameObject::Render(void)
{
	auto iter = m_mapComponent.begin();
	auto iter_End = m_mapComponent.end();

	for (; iter != iter_End; ++iter)
	{
		if (true == CComponent::g_ComEnumStruct[iter->first].bRenderOption)
			iter->second->Render();
	}
}
bool CGameObject::Add_Component(COMPONENT_TYPE eType, CComponent * pComponent)
{
	if (!BIT_OPERATE_CHECK(m_uiUseComponent, CComponent::g_ComEnumStruct[eType].uiBit))
	{
		pComponent->Set_OwnerObject(this);
		if (eType != COM_RESOURCE) // ������ Ÿ�� ������!
			pComponent->Add_Ref();
		// Post Initialize�� ȣ�� ������ �̻��ϴ�
		// ��� ������Ʈ���� Add�� �� �Ŀ� �̷������ �ϴµ�
		// �̰� ��� ����� ���� ���� �ʿ䰡 �ִ�!

		m_mapComponent.insert(MAP_COMPONENT::value_type(eType, pComponent));
		BIT_OPERATE_ADD(m_uiUseComponent, CComponent::g_ComEnumStruct[eType].uiBit);
		return true;
	}
	return false;
}

bool CGameObject::Pop_Component(COMPONENT_TYPE eType)
{
	if (BIT_OPERATE_CHECK(m_uiUseComponent, CComponent::g_ComEnumStruct[eType].uiBit))
	{
		BIT_OERPATE_SUB(m_uiUseComponent, CComponent::g_ComEnumStruct[eType].uiBit);

		auto iter = m_mapComponent.find(eType);
		SAFE_RELEASE(iter->second);
		m_mapComponent.erase(iter);

		return true;
	}
	return false;
}

void CGameObject::Add_Component_NoCheck(COMPONENT_TYPE eType, CComponent * pComponent)
{
	pComponent->Set_OwnerObject(this);
	m_mapComponent.insert(MAP_COMPONENT::value_type(eType, pComponent));
}
// �ܺο��� ������Ʈ ������
CComponent * CGameObject::Get_Component(COMPONENT_TYPE eComType)
{
	if (!BIT_OPERATE_CHECK(m_uiUseComponent, CComponent::g_ComEnumStruct[eComType].uiBit))
		return nullptr;

	auto iter = m_mapComponent.find(eComType);
	iter->second->Add_Ref();

	return iter->second;
}

// ���ο��� ������Ʈ ����
CComponent * CGameObject::Find_Component(COMPONENT_TYPE eComType)
{
	//bsearch()
	if (!BIT_OPERATE_CHECK(m_uiUseComponent, CComponent::g_ComEnumStruct[eComType].uiBit))
		return nullptr;

	auto iter = m_mapComponent.find(eComType);


	return iter->second;
}

CComponent ** CGameObject::Find_Component_DPtr(COMPONENT_TYPE eComType)
{
	if (!BIT_OPERATE_CHECK(m_uiUseComponent, CComponent::g_ComEnumStruct[eComType].uiBit))
		return nullptr;

	auto iter = m_mapComponent.find(eComType);
	return &iter->second;
}
// Only Called By Component
void CGameObject::Fix_Component(COMPONENT_TYPE& eComType, CComponent* pComponent)
{
	m_mapComponent.find(eComType)->second = pComponent;
	
}

_ulong CGameObject::Release(void)
{
	_ulong dwRefCnt = CBase::Release();


	if (0 == dwRefCnt)
	{
		for_each(m_mapComponent.begin(), m_mapComponent.end(), Engine::CReleasePair());
		m_mapComponent.clear();
	}

	return dwRefCnt;
}

