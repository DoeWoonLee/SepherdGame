#ifndef Layer_h__
#define Layer_h__

#include "Base.h"
#include "Engine_Define.h"

class CGameObject;
class CLayer: public CBase
{
public:
	static const char LAYER_KEY_LENGTH = 25;
protected:
	explicit CLayer(void);
	virtual ~CLayer(void);
public:
	virtual HRESULT Init_Layer(void);
	virtual _ulong Update(const _float& fTimeDelta);
	virtual void Render(void);
	virtual _ulong Release(void);
	void Release_AllObject(void);
public:
	void Add_Object(const TCHAR* pObjectsKey, CGameObject* pGameObject);
	std::list<CGameObject*>* Add_EmptyObject(const TCHAR* pObjectsKey);
	std::list<CGameObject*>*	Find_ObjectList(const TCHAR* pObjectsKey);
	std::map<const TCHAR*, std::list<CGameObject*>>* Get_AllObjects(void);
public:
	static CLayer* Create(void);

public:
	//void Load_ObjectFile(const TCHAR* pFilePath);
protected:
	typedef std::map<const TCHAR*, std::list<CGameObject*>> MAP_OBJECT;
	MAP_OBJECT										m_mapObjects;
};


#endif // !Layer_h__
