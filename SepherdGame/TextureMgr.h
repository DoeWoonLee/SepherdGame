#ifndef TextureMgr_h__
#define TextureMgr_h__

#include "Engine_Define.h"

class CTexture;
class CTextureMgr							
{
	DECLARE_SINGLETON(CTextureMgr)
private:
	explicit CTextureMgr(void);
	~CTextureMgr(void);
public:
	CTexture* Get_Texture(std::string strKey);
	void Ready_Texture(std::string strKey, const TCHAR* pStrPath);
private:
	typedef std::map<std::string, CTexture*> MAP_TEXTURE;
	MAP_TEXTURE m_mapTextures;
};
#endif // !TextureMgr_h__
