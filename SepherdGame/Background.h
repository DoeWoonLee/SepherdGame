#ifndef Background_h__
#define Background_h__

#include "GameObject.h"

class CBackground : public CGameObject
{
	DECLARE_CREATOR(CBackground, std::string strKey)
private:
	explicit CBackground(void);
	virtual ~CBackground(void);
public:
	virtual _ulong Release(void);

};
#endif // !Background_h__
