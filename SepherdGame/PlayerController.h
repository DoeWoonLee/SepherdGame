#ifndef PlayerController_h__
#define PlayerController_h__

#include "Component.h"

class CTransform;
class CPlayerController : public CComponent
{
private:
	explicit CPlayerController(void);
	virtual ~CPlayerController(void);
public:
	virtual _ulong Release(void)override;
	DECLARE_CREATOR(CPlayerController, std::list<CGameObject*>* pPillarList);
public:
	virtual _ulong Update(const _float& fTimeDelta);
	virtual HRESULT Post_Initialize(void)override;
private:
	void Click_LBMouse(void);
private:
	CTransform* m_pObjectTransform;
	std::list<CGameObject*>* m_pPillarList;

	bool m_bToggle1;
	bool m_bToggle2;
};

#endif // !PlayerController_h__
