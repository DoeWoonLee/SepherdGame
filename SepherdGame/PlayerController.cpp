#include "stdafx.h"
#include "PlayerController.h"
#include "GameObject.h"
#include "Transform.h"
#include "Pillar.h"

CPlayerController::CPlayerController(void)
	: m_pPillarList(nullptr),
	m_bToggle1(false),
	m_bToggle2(false)
{
}

CPlayerController::~CPlayerController(void)
{
}

_ulong CPlayerController::Release(void)
{
	_ulong dwRefCnt = CComponent::Release();
	if (0 == dwRefCnt)
	{
		SAFE_RELEASE(m_pObjectTransform);
		delete this;
	}
	return dwRefCnt;
}
_ulong CPlayerController::Update(const _float & fTimeDelta)
{
	Click_LBMouse();
	
	return 0;
}
HRESULT CPlayerController::Post_Initialize(void)
{
	m_pObjectTransform = reinterpret_cast<CTransform*>(m_pOwnerObject->Get_Component(COM_TRANSFORM));
	return S_OK;
}
void CPlayerController::Click_LBMouse(void)
{
	m_bToggle1 = false;

	if (GetAsyncKeyState(VK_LBUTTON)) // 마우스 좌클릭
	{
		m_bToggle1 = true;

		if (m_bToggle1 != m_bToggle2)// One Clickk
		{
			POINT ptMouse;
			GetCursorPos(&ptMouse);
			ScreenToClient(g_hWnd, &ptMouse);

			if(ptMouse.x > 0 && ptMouse.x < 800 && ptMouse.y > 0 && ptMouse.y <600)
				m_pPillarList->push_back(CPillar::Create(_vec2(ptMouse.x, ptMouse.y)));
		}
	}


	m_bToggle2 = m_bToggle1;
}
CPlayerController* CPlayerController::Create(std::list<CGameObject*>* pPillarList)
{
	CPlayerController* pPlayerController = new CPlayerController();

	if (FAILED(pPlayerController->Initialize(pPillarList)))
	{
		SAFE_RELEASE(pPlayerController);
	}

	return pPlayerController;
}
HRESULT CPlayerController::Initialize(std::list<CGameObject*>* pPillarList)
{
	m_pPillarList = pPillarList;
	return S_OK;
}