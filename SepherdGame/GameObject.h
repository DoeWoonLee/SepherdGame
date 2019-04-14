#ifndef GameObject_h__
#define GameObject_h__

#include "Base.h"
#include "Component_Options.h"
#include "Engine_Define.h"

class CComponent;
class CGameObject : public CBase
{
	// For Interactive With Component
	friend class CComponent;
protected:
	explicit CGameObject(void);
	virtual ~CGameObject(void);
protected:
	HRESULT Initialize(void);
	HRESULT Post_Initialize(void);
public:
	virtual _ulong Update(const _float& fTimeDelta);
	virtual void Render(void);
protected:
	bool Add_Component(COMPONENT_TYPE eType, CComponent* pComponent);
	bool Pop_Component(COMPONENT_TYPE eType);
	void Add_Component_NoCheck(COMPONENT_TYPE eType, CComponent* pComponent);
public:
	CComponent* Get_Component(COMPONENT_TYPE eComType);
protected:
	CComponent* Find_Component(COMPONENT_TYPE eComType);
	CComponent** Find_Component_DPtr(COMPONENT_TYPE eComType);
private:
	void Fix_Component(COMPONENT_TYPE& eComType, CComponent* pComponent);
public:
	virtual _ulong Release(void);
private:
	typedef std::map<COMPONENT_TYPE, CComponent*> MAP_COMPONENT;
	MAP_COMPONENT m_mapComponent;

	UINT m_uiUseComponent;
	
};

#endif // !GameObject_h__
