#ifndef Component_h__
#define Component_h__

#include "Base.h"
#include "Engine_Define.h"
#include "Component_Options.h"
#include "Scene.h"
#include "PagingArray.h"
class CGameObject;
class  CComponent
	: public CBase
{
protected:
	explicit CComponent(void);
	virtual ~CComponent(void);
public:
	virtual HRESULT Post_Initialize(void) { return S_OK; } // Component가 OwnerObject 포인트를 가질때 호출
	virtual _ulong Update(const _float& fTimeDelta)
	{
		return 0;
	}
	virtual void Render(void) {}
public:
	virtual _ulong Release(void);
	// Static

public:
	void Fix_ObjectComponentInfo(COMPONENT_TYPE eType);
	void Set_ContainerIdx(_uint uiIdx);
	void Set_OwnerObject(CGameObject* pOwnerObject);

	static COM_ENUM_STRUCT* g_ComEnumStruct;
protected:	// =================================================
	CGameObject* m_pOwnerObject; // 이 컴포넌트를 가진 오브젝트
	_uint m_uiContainerIdx; // 컴포넌트 풀에서 어느 곳에 저장되어 있는지
};
// *******************************************************
// * 
// *******************************************************
#define COMPONENT_CREATE(CLASSTYPE) \
CLASSTYPE* pComponent = g_pComponentPool[CScene::g_SceneID].get_end(); \
pComponent->Set_ContainerIdx(g_pComponentPool[CScene::g_SceneID].size()-1);


#define DECLARE_COMPONENT(CLASSNAME)	\
public:									\
static void Setting_ComponentPool(const _ushort& usSceneSize, const _uint& uiPageSize); \
static void Release_ComponentPool(void);			\
private:											\
void Release_Swap(void);							\
static CPagingArray<CLASSNAME>* g_pComponentPool;	\
template<class T> friend class CPagingArray;		

#define IMPLEMENT_COMPONENT(CLASSNAME, COM_TYPE)				\
CPagingArray<CLASSNAME>*  CLASSNAME::g_pComponentPool = nullptr;\
void CLASSNAME::Setting_ComponentPool(const _ushort& usSceneSize, const _uint& uiPageSize) \
{																\
	g_pComponentPool = new CPagingArray<CLASSNAME>[usSceneSize];\
	for(_ushort i = 0; i < usSceneSize; ++i)					\
		g_pComponentPool[i].set_initdata(uiPageSize);			\
}																\
void CLASSNAME::Release_ComponentPool(void)						\
{																\
	delete [] g_pComponentPool;									\
}																\
void CLASSNAME::Release_Swap(void)								\
{																\
	g_pComponentPool[CScene::g_iSceneID].swap_end(m_uiContainerIdx).\
	Fix_ObjectComponentInfo(COM_TYPE); \
}

#endif // !Component_h__
