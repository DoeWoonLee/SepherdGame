#include "stdafx.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Texture.h"
#include "GraphicDev.h"
#include "Transform.h"

IMPLEMENT_COMPONENT(CSprite, COM_SPRITE)

CSprite::CSprite(void) noexcept
	:m_iColCnt(0),
	 m_iRowCnt(0),
	 m_iIndexX(0),
	 m_iIndexY(0),
	m_fSpriteTime(0.f),
	m_fProgressTime(0.f),
	m_bLoop(false),
	m_iEnd(-1)
{
}
CSprite::~CSprite(void) noexcept
{
}
HRESULT CSprite::Post_Initialize(void)
{
	m_pUsedTex = (CTexture*)m_pOwnerObject->Get_Component(COM_RESOURCE);

	m_iSpriteHeight = static_cast<int>(m_pUsedTex->Get_Height() / m_iColCnt);
	m_iSpriteWidth = static_cast<int>(m_pUsedTex->Get_Width()  / m_iRowCnt);



	return S_OK;
}

_ulong CSprite::Update(const _float& fTimeDelta)
{
	
	m_fProgressTime += fTimeDelta;
	if (m_fProgressTime > m_fSpriteTime)
	{
		m_iIndexX++;

		int iCompare = -1;
		if (m_iEnd == -1)
			iCompare = m_iRowCnt;
		else
			iCompare = m_iEnd;

		if (m_iIndexX == iCompare)
		{
			if (false == m_bLoop)
				m_iIndexX--;
			else
			{
				m_iIndexX = 0;
			}
			
		}
		m_fProgressTime = 0.f;
	}
	
	
	

	return 0;
}

void CSprite::Render(void)
{
	HDC m_MemDC = CGraphicDev::GetInstance()->Get_DC();

	//Rectangle(m_MemDC, 400, 300, 500, 400);


	HDC hMemDC = CreateCompatibleDC(m_MemDC);
	
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, m_pUsedTex->Get_Bitmap());
	
	CTransform* pTransform = CGraphicDev::GetInstance()->Get_Transform();

	/*TransparentBlt(m_MemDC, pTransform->m_vPosition.x - m_iSpriteWidth / 2.f,
		pTransform->m_vPosition.y - m_iSpriteHeight / 2.f,
		m_iSpriteWidth, m_iSpriteHeight, hMemDC,
		m_iIndexX * m_iSpriteWidth, m_iIndexY * m_iSpriteHeight,
		(m_iIndexX + 1) * m_iSpriteWidth, (m_iIndexY + 1) * m_iSpriteHeight 
		, RGB(255, 0, 255));*/

	TransparentBlt(m_MemDC, pTransform->m_vPosition.x - m_iSpriteWidth / 2.f,
		pTransform->m_vPosition.y - m_iSpriteHeight / 2.f,
		m_iSpriteWidth, m_iSpriteHeight, hMemDC,
		m_iIndexX * m_iSpriteWidth, m_iIndexY * m_iSpriteHeight,
		m_iSpriteWidth, m_iSpriteHeight
		, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}

void CSprite::Setting_Sprite(int iSequence, float fSpriteTime, int iEnd , bool bLoop)
{
	m_iIndexY = iSequence;
	m_fSpriteTime = fSpriteTime;
	m_bLoop = bLoop;
	m_iEnd = iEnd;
}

void CSprite::Start_Sprite(int iSequence, float fSpriteTime, int iEnd, bool bLoop)
{
	Setting_Sprite(iSequence, fSpriteTime, iEnd, bLoop);
	m_iIndexX = 0;
}


CSprite* CSprite::Create(int iColCnt, int iRowCnt)
{
	CSprite* pSprite = new CSprite();

	if (FAILED(pSprite->Initialize(iColCnt, iRowCnt)))
	{
		SAFE_RELEASE(pSprite);
	}
	return pSprite;
}
HRESULT CSprite::Initialize(int iColCnt, int iRowCnt)
{
	m_iColCnt = iColCnt;
	m_iRowCnt = iRowCnt;

	return S_OK;
}
_ulong CSprite::Release(void)
{
	_ulong dwRef = CComponent::Release();
	if (0 == dwRef)
	{
		delete this;
	}
	return dwRef;
}