#include "stdafx.h"
#include "TextureMgr.h"
#include "Texture.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr(void)
{

}
CTextureMgr::~CTextureMgr(void)
{
	for each (auto var in m_mapTextures)
	{
		SAFE_RELEASE(var.second);
	}
	m_mapTextures.clear();
}

CTexture* CTextureMgr::Get_Texture(std::string strKey)
{
	auto iter = m_mapTextures.find(strKey);
	if (iter == m_mapTextures.end()) return nullptr;

	return iter->second;
}

void CTextureMgr::Ready_Texture(std::string strKey,const TCHAR* pStrPath)
{
	if (nullptr != Get_Texture(strKey))
		return;

	m_mapTextures.insert(MAP_TEXTURE::value_type(strKey, CTexture::LoadTexture(pStrPath)));
}
