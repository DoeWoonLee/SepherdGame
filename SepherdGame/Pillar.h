#ifndef Pillar_h__
#define Pillar_h__

#include "GameObject.h"

class CPillar : public CGameObject
{
	DECLARE_CREATOR(CPillar, _vec2 vPos);
private:
	explicit CPillar(void);
	virtual ~CPillar(void);
public:
	virtual _ulong Release(void);
	
};

#endif // !Pillar_h__
