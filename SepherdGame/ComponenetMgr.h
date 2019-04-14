#ifndef ComponenetMgr_h__
#define ComponenetMgr_h__

#include "Engine_Define.h"

class CComponent;
class CComponentMgr
{
	DECLARE_SINGLETON(CComponentMgr)
private:
	explicit CComponentMgr(void);
	~CComponentMgr(void);
	void Release(void);
public:
	void Init_ComponentMgr(const _ushort& usSceneSize);
public:
	// Thread
	void Update_Components(const _float& fTimeDelta);

};

#endif // !ComponenetMgr_h__
