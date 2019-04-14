#include "stdafx.h"
#include "TestScene.h"
#include "Layer.h"
#include "Player.h"
#include "Sheep.h"
#include "Pillar.h"

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
	/*for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			pLayer->Add_Object( _T("Sheep"),CSheep::Create(i * 100.f, j * 100.f));
		}
	}*/

	return S_OK;
}


_ulong CTestScene::Release(void)
{
	_ulong dwRefCnt = CScene::Release();
	if (0 == dwRefCnt)
	{
		delete this;
	}
	return dwRefCnt;
}
