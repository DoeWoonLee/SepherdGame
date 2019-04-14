#ifndef MainGame_h__
#define MainGame_h__

#include "Engine_Define.h"

class CScene;
class CMainGame
{
private:
	explicit CMainGame(void);
	~CMainGame(void);
public:
	HRESULT Init_MainGame(void);
	static CMainGame* Create(void);

	void Update(const _float& fTimeDelta);
	void Render(void);
	_ulong Release(void);

private:
	CScene* m_pScene;
private:
	HDC m_hdc;
	int m_iFrame;
	int m_iAccFrame;
	float m_fFrameTime;
};

#endif // !MainGame_h__
