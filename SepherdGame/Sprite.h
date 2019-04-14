#ifndef Sprite_h__
#define Sprite_h__

#include "Component.h"

class CTexture;
class CGameObject;
class CSprite : public CComponent
{
private:
	explicit CSprite(void)noexcept;
	virtual ~CSprite(void)noexcept override;

	DECLARE_COMPONENT(CSprite)
	DECLARE_CREATOR(CSprite, int iColCnt, int iRowCnt)
public:
	virtual _ulong Release(void)override;
	virtual HRESULT Post_Initialize(void)override;
	virtual _ulong Update(const _float& fTimeDelta)override;
	virtual void Render(void)override;

public:
	void Setting_Sprite(int iSequence, float fSpriteTime);
private:
	CTexture* m_pUsedTex;
	int m_iIndexX;
	int m_iIndexY;
	float m_fSpriteTime;
	float m_fProgressTime;

	int m_iColCnt;
	int m_iRowCnt;
	int m_iSpriteWidth;
	int m_iSpriteHeight;
};

#endif // !Sprite_h__
