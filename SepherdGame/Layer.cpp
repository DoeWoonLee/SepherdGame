#include "stdafx.h"
#include "Layer.h"
#include "GameObject.h"

CLayer::CLayer(void)
{

}

CLayer::~CLayer(void)
{

}

HRESULT CLayer::Init_Layer(void)
{
	return S_OK;
}

_ulong CLayer::Update(const _float& fTimeDelta)
{
	MAP_OBJECT::iterator iter = m_mapObjects.begin();
	MAP_OBJECT::iterator iter_end = m_mapObjects.end();

	for (; iter != iter_end; ++iter)
	{
		std::list<CGameObject*>::iterator List_iter = iter->second.begin();
		std::list<CGameObject*>::iterator List_iter_end = iter->second.end();

		for (; List_iter != List_iter_end; ++List_iter)
		{
			(*List_iter)->Update(fTimeDelta);
		}
	}
	return 0;
}

void CLayer::Render(void)
{
	MAP_OBJECT::iterator iter = m_mapObjects.begin();
	MAP_OBJECT::iterator iter_end = m_mapObjects.end();

	for (; iter != iter_end; ++iter)
	{
		std::list<CGameObject*>::iterator List_iter = iter->second.begin();
		std::list<CGameObject*>::iterator List_iter_end = iter->second.end();

		for (; List_iter != List_iter_end; ++List_iter)
		{
			(*List_iter)->Render();
		}
	}
}
void CLayer::Add_Object(const TCHAR* pObjectsKey, CGameObject* pGameObject)
{
	std::list<CGameObject*>* pGameObjectList = Add_EmptyObject(pObjectsKey);

	pGameObjectList->push_back(pGameObject);

}
std::list<CGameObject*>* CLayer::Add_EmptyObject(const TCHAR * pObjectsKey)
{
	std::list<CGameObject*>* pFindList = Find_ObjectList(pObjectsKey);
	if (nullptr != pFindList) return pFindList;

	auto Iter = m_mapObjects.insert(MAP_OBJECT::value_type(Engine::Create_DynamicTCHAR(pObjectsKey, LAYER_KEY_LENGTH), std::list<CGameObject*>()));
	
	return &Iter.first->second;
}
std::list<CGameObject*>* CLayer::Find_ObjectList(const TCHAR* pObjectsKey)
{
	MAP_OBJECT::iterator iter = find_if(m_mapObjects.begin(), m_mapObjects.end(), Engine::CTagFinder(pObjectsKey));

	if (iter == m_mapObjects.end())
	{
		return nullptr;
	}

	return &iter->second;
}

std::map<const TCHAR*, std::list<CGameObject*>>* CLayer::Get_AllObjects(void)
{
	return &m_mapObjects;
}

CLayer* CLayer::Create(void)
{
	CLayer* pLayer = new CLayer();

	if (FAILED(pLayer->Init_Layer()))
	{
		Engine::Safe_Release(pLayer);
	}
	return pLayer;
}

_ulong CLayer::Release(void)
{
	_ulong dwRefCnt = CBase::Release();

	if (0 == dwRefCnt)
	{
		MAP_OBJECT::iterator iter = m_mapObjects.begin();
		MAP_OBJECT::iterator iter_end = m_mapObjects.end();

		for (; iter != iter_end; ++iter)
		{
			delete[] iter->first;
			for_each(iter->second.begin(), iter->second.end(), Engine::CReleaseSingle());
			iter->second.clear();
		}
		m_mapObjects.clear();

		delete this;
	}


	return dwRefCnt;

}

void CLayer::Release_AllObject(void)
{
	MAP_OBJECT::iterator iter = m_mapObjects.begin();
	MAP_OBJECT::iterator iter_end = m_mapObjects.end();

	for (; iter != iter_end; ++iter)
	{
		delete[] iter->first;
		for_each(iter->second.begin(), iter->second.end(), Engine::CReleaseSingle());
		iter->second.clear();
	}
	m_mapObjects.clear();
}



