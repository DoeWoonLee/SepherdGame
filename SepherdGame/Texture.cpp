#include "stdafx.h"
#include "Texture.h"

#pragma comment(lib, "msimg32.lib")
CTexture::CTexture(void):
	m_lWidth(0),
	m_lHeight(0)
{
}

CTexture::~CTexture(void)
{
}

HRESULT CTexture::Init_Texture(const TCHAR * pStrPath)
{
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance, pStrPath, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	
	BITMAP blt;
	GetObject(m_hBitmap,sizeof(BITMAP), &blt);
	
	m_lWidth = blt.bmWidth;
	m_lHeight = blt.bmHeight;

	if (nullptr == m_hBitmap)
	{
		msg_box("Image Load Fail");
		return E_FAIL;
	}
		

	return S_OK;
}

CTexture * CTexture::LoadTexture(const TCHAR * pStrPath)
{
	CTexture* pTexture = new CTexture();
	if (FAILED(pTexture->Init_Texture(pStrPath)))
	{
		SAFE_RELEASE(pTexture);
	}
	return pTexture;
}

long CTexture::Get_Width(void)
{
	return m_lWidth;
}

long CTexture::Get_Height(void)
{
	return m_lHeight;
}

HBITMAP CTexture::Get_Bitmap(void)
{
	return m_hBitmap;
}

_ulong CTexture::Release(void)
{
	_ulong dwRefCnt = CComponent::Release();
	if (0 == dwRefCnt)
	{
		DeleteObject(m_hBitmap);
		delete this;
	}
	return dwRefCnt;
}
