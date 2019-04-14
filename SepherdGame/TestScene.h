#ifndef TestScene_h__
#define TestScene_h__

#include "Scene.h"

class CTestScene : public CScene
{
public:
	HRESULT Init_TestScene(void);
	static CTestScene* Create(void);
	virtual _ulong Release(void);
};

#endif // !TestScene_h__
