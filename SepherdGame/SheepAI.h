#ifndef SheepAI_h__
#define SheepAI_h__

#include "Component.h"

class CTransform;
class CSprite;
class CSheepAI : public CComponent
{
	DECLARE_CREATOR(CSheepAI, void)
private:
	explicit CSheepAI(void);
	virtual ~CSheepAI(void);
public:
	virtual _ulong Update(const float& fTimeDelta)override;
	virtual HRESULT Post_Initialize(void)override;
	virtual _ulong Release(void)override;
private:
	void Check_Direction(void);
	void RandomMoving(const _float& fTimeDelta);
	void Setting_MovingInfo(void);
	void Move_Update(const _float& fTImeDelta);
private:
	CTransform* m_pTransform;
	CSprite* m_pSprite;

	_vec2 m_vDir;
	float m_fMovingTime;
	float m_fThinkingTime;
	bool m_bDir; //flase = left / true = right
	bool m_bMove; // false = no / true = yes
};
#endif // !SheepAI_h__
