#include "stdafx.h"
#include "Sheep.h"
#include "Transform.h"
#include "TextureMgr.h"
#include "Sprite.h"
#include "SheepAI.h"

CSheep::CSheep(void)
{
}

CSheep::~CSheep(void)
{
}
_ulong CSheep::Release(void)
{
	_ulong dwRefCnt = CGameObject::Release();

	if (0 == dwRefCnt)
	{
		delete this;
	}
	return dwRefCnt;
}
CSheep* CSheep::Create(float fX, float fY)
{
	CSheep* pSheep = new CSheep();

	if (FAILED(pSheep->Initialize(fX, fY)))
	{
		SAFE_RELEASE(pSheep);
	}

	return pSheep;
}
HRESULT CSheep::Initialize(float fX, float fY)
{
	CTransform* pTransform = CTransform::Create();
	pTransform->Set_Position(fX, fY);
	Add_Component(COM_TRANSFORM, pTransform);

	Add_Component(COM_RESOURCE, reinterpret_cast<CComponent*>(CTextureMgr::GetInstance()->Get_Texture("Sheep")));
	Add_Component(COM_SPRITE, CSprite::Create(4, 6));
	Add_Component(COM_AI, CSheepAI::Create());


	CGameObject::Post_Initialize();

	return S_OK;
}