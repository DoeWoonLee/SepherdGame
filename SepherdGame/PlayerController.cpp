#include "stdafx.h"
#include "PlayerController.h"
#include "GameObject.h"
#include "Transform.h"
#include "Pillar.h"
#include "GraphicDev.h"

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
void CPlayerController::Render(void)
{
	HDC hdc = CGraphicDev::GetInstance()->Get_DC();

	if (m_TestConveList.size() > 0)
	{
		auto iter = m_TestConveList.begin();
		_vec2 vPos = (*iter)->m_vPosition;
		MoveToEx(hdc, vPos.x, vPos.y, nullptr);

		for (++iter; iter != m_TestConveList.end(); ++iter)
		{
			LineTo(hdc, (*iter)->m_vPosition.x, (*iter)->m_vPosition.y);
		}
		LineTo(hdc, vPos.x, vPos.y);
	}
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

			if (ptMouse.x > 0 && ptMouse.x < 800 && ptMouse.y > 0 && ptMouse.y < 600)
			{
				m_pPillarList->push_back(CPillar::Create(_vec2(ptMouse.x, ptMouse.y)));

				//Make_ConvexHull();
			}
				
		}
	}


	m_bToggle2 = m_bToggle1;
}
void CPlayerController::Make_ConvexHull(void)
{
	CTransform* pTransform = nullptr;
	float fMinY = 1000.f;
	float fMinX = 1000.f;
	CTransform* pMinTransform = nullptr;

	if (m_pPillarList->size() < 3) return;

	// Y값이 가장 작은 점 찾기
	for each (auto var in *m_pPillarList)
	{
		pTransform = reinterpret_cast<CTransform*>(var->Get_Component(COM_TRANSFORM));

		float fReversY = pTransform->m_vPosition.y * (-1.f);
		if (fMinY > fReversY)
		{
			fMinY = fReversY;
			fMinX = pTransform->m_vPosition.x;
			pMinTransform = pTransform;
		}
		else if (fMinY == fReversY)
		{
			if (fMinX > pTransform->m_vPosition.x)
			{
				fMinX = pTransform->m_vPosition.x;
				pMinTransform = pTransform;
			}
		}
	}

	// Angle값 자동 정렬용 
	std::multimap<float, CTransform*> mapAngleTransform;

	mapAngleTransform.insert(std::multimap<float, CTransform*>::value_type(0.f, pMinTransform));
	std::list<CGameObject*>::iterator var = ++m_pPillarList->begin();
	
	for (; var != m_pPillarList->end(); var++)
	{
		pTransform = reinterpret_cast<CTransform*>((*var)->Get_Component(COM_TRANSFORM));

		_vec2 vDir = pTransform->m_vPosition - pMinTransform->m_vPosition;
		vDir.Normalize();
		float fAngle = acosf(vDir.Dot(_vec2(1.f, 0.f)));

		mapAngleTransform.insert(std::multimap<float, CTransform*>::value_type(fAngle, pTransform));
	}

	// Convex Hull 만들기
	std::list<CTransform*> ConvexList;

	auto iter = mapAngleTransform.begin();
	ConvexList.push_back(iter->second);
	++iter;
	ConvexList.push_back(iter->second);
	CTransform* pSeedTransform = iter->second;
	++iter;
	CTransform* pPreViewTransform = pMinTransform;
	
	for (; iter != mapAngleTransform.end() ;/*++iter*/)
	{

		/*_vec2 vDir1 =   - pPreViewTransform->m_vPosition;
		_vec2 vDir2 = iter->second->m_vPosition - pPreViewTransform->m_vPosition;
		vDir1.Normalize();
		vDir2.Normalize();

		_vec3 vCross(XMVector2Cross(vDir1.ToSIMD(), vDir2.ToSIMD()));
		
		if (vCross.z < 0)
		{
			ConvexList.push_back(iter->second);
			pSeedTransform = iter->second;
			iter++;
		}
		else
		{
			ConvexList.push_back(TempIter->second);
			pSeedTransform = TempIter->second;
			iter = ++TempIter;
		}*/
		//pSeedTransform
	}
	m_TestConveList = ConvexList;
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