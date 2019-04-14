#include "stdafx.h"
#include "SheepAI.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"

CSheepAI::CSheepAI(void)
	: m_pTransform(nullptr),
	 m_pSprite(nullptr),
	m_bDir(false),
	m_bMove(false),
	m_fMovingTime(0.f),
	m_fThinkingTime(0.f)
{
}

CSheepAI::~CSheepAI(void)
{
}


CSheepAI* CSheepAI::Create(void)
{
	CSheepAI* pSheepAI = new CSheepAI();
	if (FAILED(pSheepAI->Initialize()))
	{
		SAFE_RELEASE(pSheepAI);
	}
	return pSheepAI;
}
HRESULT CSheepAI::Initialize(void)
{
	m_bDir = rand() % 2;
	return S_OK;
}
enum SHEEP_SPRITE
{
	SHEEP_RIGHT_MOVE,
	SHEEP_RIGHT_IDLE,
	SHEEP_LEFT_MOVE,
	SHEEP_LEFT_IDLE,
	SHEEP_END
};
HRESULT CSheepAI::Post_Initialize(void)
{
	m_pTransform = reinterpret_cast<CTransform*>(m_pOwnerObject->Get_Component(COM_TRANSFORM));
	m_pSprite = reinterpret_cast<CSprite*>(m_pOwnerObject->Get_Component(COM_SPRITE));

	Setting_MovingInfo();

	return S_OK;
}
_ulong CSheepAI::Update(const float & fTimeDelta)
{
	RandomMoving(fTimeDelta);
	//Check_Direction();
	Move_Update(fTimeDelta);

	return 0;
}
void CSheepAI::Check_Direction(void)
{

	if (!m_bDir)
	{
		m_pSprite->Start_Sprite(SHEEP_LEFT_IDLE - m_bMove, 0.3f, 5 + m_bMove, true);
	}
	else
	{
		m_pSprite->Start_Sprite(SHEEP_RIGHT_IDLE - m_bMove, 0.3f , 5 + m_bMove,true);
	}
}

void CSheepAI::RandomMoving(const _float & fTimeDelta)
{
	// 가만히 서있을때
	if (m_bMove == false)
	{
		m_fThinkingTime -= fTimeDelta;
		if (m_fThinkingTime < 0.00001f) // 근사값
		{
			m_fMovingTime = (rand() % 5 + 10) / 10.f;
			Setting_MovingInfo();
		}
	}
	else // 움직일떄
	{
		m_fMovingTime -= fTimeDelta;
		if (m_fMovingTime < 0.00001f)
		{
			m_fThinkingTime = (rand() % 10 + 15) / 10.f;
			m_bMove = false;

			Check_Direction();

		}
	}


	
}

void CSheepAI::Setting_MovingInfo(void)
{
	m_vDir.x = rand() % 100 - 50.f;
	m_vDir.y = rand() % 100 - 50.f;

	m_vDir.Normalize();

	if (m_vDir.x < 0.f)
		m_bDir = false;
	else
		m_bDir = true;

	m_bMove = true;


	Check_Direction();
}
void CSheepAI::Move_Update(const _float & fTImeDelta)
{
	if(m_bMove)
		m_pTransform->m_vPosition += m_vDir * fTImeDelta * 10.f;
}


_ulong CSheepAI::Release(void)
{
	_ulong dwRefCnt = CComponent::Release();
	if (0 == dwRefCnt)
	{
		SAFE_RELEASE(m_pTransform);
		delete this;
	}
	return dwRefCnt;
}


