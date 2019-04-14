#include "stdafx.h"
#include "MainGame.h"
//#include "Engine_Define.h"
#include "ComponenetMgr.h"
#include "Scene.h"
#include "Scene_Option.h"
#include "TestScene.h"
#include "GraphicDev.h"
#include "ResourceInclude.h"

CMainGame::CMainGame(void):
	m_iFrame(0),
	m_iAccFrame(0),
	m_fFrameTime(0.f),
	m_pScene(nullptr)
{
}

CMainGame::~CMainGame(void)
{
}

HRESULT CMainGame::Init_MainGame(void)
{
	CLIENT::PreLoadTextoures();

	CComponentMgr::GetInstance()->Init_ComponentMgr(SCENE_END);
	
	m_hdc = GetDC(g_hWnd);

	m_pScene = CTestScene::Create();

	

	return S_OK;
}

CMainGame * CMainGame::Create(void)
{
	CMainGame* pMainGame = new CMainGame();
	if (FAILED(pMainGame->Init_MainGame()))
	{
		Engine::Safe_Release(pMainGame);
	}

	return pMainGame;
}

void CMainGame::Update(const _float & fTimeDelta)
{
	m_fFrameTime += fTimeDelta;
	m_iAccFrame++;

	if (m_fFrameTime >= 1.f)
	{
		m_fFrameTime = 0.f;

		m_iFrame = m_iAccFrame;
		m_iAccFrame = 0;
	}

	m_pScene->Update(fTimeDelta);
}

void CMainGame::Render(void)
{
	// Buffering
	HDC MemDC;

	MemDC = CreateCompatibleDC(m_hdc);
	HBITMAP Bitmap = CreateCompatibleBitmap(m_hdc, 800, 600);
	HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, (HGDIOBJ)Bitmap);


	// Rendering
	Rectangle(MemDC, 0, 0, WIN_CX, WIN_CY);
	CGraphicDev::GetInstance()->Set_DC(MemDC);

	m_pScene->Render();


	// Frame Render
	TCHAR wszFrame[10] = _T("");
	wsprintf(wszFrame, _T("%d\n"), m_iFrame);
	RECT rcText;
	rcText.left = 0; rcText.top = 0; rcText.right = 30; rcText.bottom = 15;

	DrawText(MemDC, wszFrame, 50, &rcText, 0);

	// Rendering On Back Buffer
	BitBlt(m_hdc, 0, 0, WIN_CX, WIN_CY, MemDC, 0, 0, SRCCOPY);

	// RollBackData
	SelectObject(m_hdc, OldBitmap);

	DeleteObject(Bitmap);
	DeleteObject(MemDC);
}

_ulong CMainGame::Release(void)
{
	ReleaseDC(g_hWnd, m_hdc);
	CComponentMgr::GetInstance()->DestroyInstance();


	SAFE_RELEASE(m_pScene);

	delete this;
	return 0;
}
