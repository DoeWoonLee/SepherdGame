#include "stdafx.h"
#include "TestScene.h"
#include "Layer.h"
#include "Player.h"
#include "Sheep.h"
#include "Pillar.h"
#include "Background.h"

CTestScene * CTestScene::Create(void)
{
	CTestScene* pScene = new CTestScene();
	if (FAILED(pScene->Init_TestScene()))
	{
		SAFE_RELEASE(pScene);
	}
	return pScene;
}

HRESULT CTestScene::Init_TestScene(void)
{
	g_iSceneID = SCENE_TEST;
	
	CLayer* pLayer = CLayer::Create();
	Add_Layer(_T("Object"), pLayer);

	pLayer->Add_EmptyObject(_T("Pillar"));
	pLayer->Add_Object(_T("Player"), CPlayer::Create(pLayer->Find_ObjectList(_T("Pillar"))));
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			pLayer->Add_Object( _T("Sheep"),CSheep::Create(i * 80.f + 200.f, j * 80.f + 200.f));
		}
	}
	m_pBackground = CBackground::Create("Background");

	return S_OK;
}

void CTestScene::Render(void)
{
	m_pBackground->Render();

	CScene::Render();
}
_ulong CTestScene::Release(void)
{
	_ulong dwRefCnt = CScene::Release();
	if (0 == dwRefCnt)
	{
		SAFE_RELEASE(m_pBackground);
		delete this;
	}
	return dwRefCnt;
}


