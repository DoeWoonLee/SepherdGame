#include "stdafx.h"
#include "Sheep.h"
#include "Transform.h"
#include "TextureMgr.h"
#include "Sprite.h"

CSheep::CSheep(void)
{
}

CSheep::~CSheep(void)
{
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
	Add_Component(COM_SPRITE, CSprite::Create(1, 1));

	this->Post_Initialize();

	return S_OK;
}