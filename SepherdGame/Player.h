#ifndef Player_h__
#define Player_h__

#include "GameObject.h"


class CPlayer : public CGameObject
{
private:
	explicit CPlayer(void);
	virtual ~CPlayer(void);
	DECLARE_CREATOR(CPlayer, std::list<CGameObject*>* pPillarList);
public:
	virtual _ulong Release(void);
};
#endif // !Player_h__
