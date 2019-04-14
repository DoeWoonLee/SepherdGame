#ifndef TestScene_h__
#define TestScene_h__

#include "Scene.h"

class CBackground;
class CTestScene : public CScene
{
public:
	HRESULT Init_TestScene(void);
	static CTestScene* Create(void);
	virtual _ulong Release(void);
public:
	virtual void Render(void)override;
private:
	CBackground* m_pBackground;
};

#endif // !TestScene_h__
