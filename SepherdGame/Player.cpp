#include "stdafx.h"
#include "Player.h"
#include "TextureMgr.h"
#include "Transform.h"
#include "Sprite.h"
#include "PlayerController.h"

CPlayer::CPlayer(void)
{
}

CPlayer::~CPlayer(void)
{
}

_ulong CPlayer::Release(void)
{
	_ulong dwRefCnt = CGameObject::Release();
	if (0 == dwRefCnt)
	{
		delete this;
	}
	return dwRefCnt;
}

CPlayer* CPlayer::Create(std::list<CGameObject*>* pPillarList)
{
	CPlayer* pPlayer = new CPlayer();
	if (FAILED(pPlayer->Initialize(pPillarList)))
	{
		SAFE_RELEASE(pPlayer);
	}
	return pPlayer;
}
HRESULT CPlayer::Initialize(std::list<CGameObject*>* pPillarList)
{

	CTransform* pTransform = CTransform::Create();
	pTransform->Set_Position(400.f, 300.f);
	Add_Component(COM_TRANSFORM, pTransform);

	//Add_Component(COM_RESOURCE, 
	//	reinterpret_cast<CComponent*>(
	//		CTextureMgr::GetInstance()->Get_Texture("Player")));
	//Add_Component(COM_SPRITE, CSprite::Create(1, 1));
	Add_Component(COM_CONTROLLER, CPlayerController::Create(pPillarList));

	this->Post_Initialize();

	return S_OK;
}