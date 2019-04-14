#include "stdafx.h"
#include "Pillar.h"
#include "Transform.h"
#include "Sprite.h"
#include "TextureMgr.h"

CPillar::CPillar(void)
{
}

CPillar::~CPillar(void)
{
}
_ulong CPillar::Release(void)
{
	_ulong dwRefCnt = CGameObject::Release();
	if (0 == dwRefCnt)
	{
		delete this;
	}
	return dwRefCnt;
}
CPillar* CPillar::Create(_vec2 vPos)
{
	CPillar* pPillar = new CPillar();
	if (FAILED(pPillar->Initialize(vPos)))
	{
		SAFE_RELEASE(pPillar);
	}
	return pPillar;
}
HRESULT CPillar::Initialize(_vec2 vPos)
{
	CTransform* pTransform = CTransform::Create();
	pTransform->Set_Position(vPos.x, vPos.y);
	
	Add_Component(COM_TRANSFORM, pTransform);
	Add_Component(COM_SPRITE, CSprite::Create(1, 6));
	Add_Component(COM_RESOURCE,
		reinterpret_cast<CComponent*>
		(CTextureMgr::GetInstance()->Get_Texture("WoodPillar")));
	
	((CSprite*)Get_Component(COM_SPRITE))->Setting_Sprite(0, 0.08f);

	Post_Initialize();

	return S_OK;
}