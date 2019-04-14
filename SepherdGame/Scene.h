#ifndef Scene_h__
#define Scene_h__

#include "Engine_Define.h"
#include "Scene_Option.h"

class CGameObject;
class CLayer;
class CScene
{
protected:
	explicit CScene(void);
	virtual ~CScene(void);
public:
	virtual _ulong Update(const _float& fTimeDelta);
	virtual void Render(void);
	virtual _ulong Release(void);
protected:
	HRESULT Add_Layer(const TCHAR* pLayerKey, CLayer* pLayer);
public:
	CLayer*	Find_Layer(const TCHAR* pLayerKey);
	std::list<CGameObject*>* Find_GameObjectList(const TCHAR* pLayerKey, const TCHAR* pObjectsKey);
protected:
	typedef std::map<const TCHAR*, CLayer*>  MAP_LAYER;
	MAP_LAYER							m_mapLayer;
public:
	static int g_iSceneID;
};

#endif // !Scene_h__
