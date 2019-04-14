#include "stdafx.h"
#include "Scene.h"
#include "Layer.h"
#include "ComponenetMgr.h"

int CScene::g_iSceneID = -1;

CScene::CScene(void)
{

}

CScene::~CScene(void)
{

}


_ulong CScene::Update(const _float& fTimeDelta)
{
	//CComponentMgr::GetInstance()->Update_Components(fTimeDelta);


	MAP_LAYER::iterator iter = m_mapLayer.begin();
	MAP_LAYER::iterator iter_end = m_mapLayer.end();

	for (; iter != iter_end; ++iter)
	{
		iter->second->Update(fTimeDelta);
	}



	return 0;
}

void CScene::Render(void)
{
	MAP_LAYER::iterator iter = m_mapLayer.begin();
	MAP_LAYER::iterator iter_end = m_mapLayer.end();

	for (; iter != iter_end; ++iter)
	{
		iter->second->Render();
	}


}

std::list<CGameObject*>* CScene::Find_GameObjectList(const TCHAR* pLayerKey, const TCHAR* pObjectsKey)
{
	return Find_Layer(pLayerKey)->Find_ObjectList(pObjectsKey);
}

CLayer* CScene::Find_Layer(const TCHAR* pLayerKey)
{
	MAP_LAYER::iterator iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), Engine::CTagFinder(pLayerKey));

	if (iter == m_mapLayer.end())
	{
		return nullptr;
	}

	return iter->second;
}

_ulong CScene::Release(void)
{

	for_each(m_mapLayer.begin(), m_mapLayer.end(), Engine::CReleasePair());
	m_mapLayer.clear();

	return 0;
}

HRESULT CScene::Add_Layer(const TCHAR * pLayerKey, CLayer * pLayer)
{
	if (nullptr != Find_Layer(pLayerKey))
		return E_FAIL;

	m_mapLayer.insert(MAP_LAYER::value_type(pLayerKey, pLayer));

	return S_OK;
}

