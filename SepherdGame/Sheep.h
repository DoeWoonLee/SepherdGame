#ifndef Sheep_h__
#define Sheep_h__

#include "GameObject.h"


class CSheep : public CGameObject
{
private:
	explicit CSheep(void);
	virtual ~CSheep(void);

	DECLARE_CREATOR(CSheep, float fX, float fY);
public:
	virtual _ulong Release(void);
};

#endif // !Sheep_h__
