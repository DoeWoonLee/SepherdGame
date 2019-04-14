#include "stdafx.h"
#include "Background.h"
#include "TextureMgr.h"
#include "Sprite.h"
#include "Transform.h"

CBackground::CBackground(void)
{
}

CBackground::~CBackground(void)
{
}
_ulong CBackground::Release(void)
{
	_ulong dwRefCnt = CGameObject::Release();
	if (0 == dwRefCnt)
	{
		delete this;
	}
	return dwRefCnt;
}
CBackground* CBackground::Create(std::string strKey)
{
	CBackground* pBackground = new CBackground();
	
	if (FAILED(pBackground->Initialize(strKey)))
	{
		SAFE_RELEASE(pBackground);
	}
	return pBackground;
}
HRESULT CBackground::Initialize(std::string strKey)
{
	Add_Component(COM_TRANSFORM, CTransform::Create());
	Add_Component(COM_SPRITE, CSprite::Create(1, 1));
	Add_Component(COM_RESOURCE, reinterpret_cast<CComponent*>(
		CTextureMgr::GetInstance()->
		Get_Texture(strKey)));

	((CTransform*)Get_Component(COM_TRANSFORM))->Set_Position(400, 300);

	Post_Initialize();

	return S_OK;
}
