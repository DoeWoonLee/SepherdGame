#ifndef GraphicDev_h__
#define GraphicDev_h__

#include "Engine_Define.h"

class CTransform;
class CGraphicDev
{
DECLARE_SINGLETON(CGraphicDev)
private:
	explicit CGraphicDev(void);
	~CGraphicDev(void);
public:
	void Set_DC(HDC BackDC);
	HDC Get_DC(void);
	void Set_Transform(CTransform* pTransform);
	CTransform* Get_Transform(void);
private:
	HDC m_RenderedDC;
	CTransform* m_pTransform;
};

#endif // !GraphicDev_h__
