#include "stdafx.h"
#include "GraphicDev.h"

IMPLEMENT_SINGLETON(CGraphicDev)
CGraphicDev::CGraphicDev(void):
	m_pTransform(nullptr)
{

}
CGraphicDev::~CGraphicDev(void)
{
}

void CGraphicDev::Set_DC(HDC BackDC)
{
	m_RenderedDC = BackDC;
}
HDC CGraphicDev::Get_DC(void)
{
	return m_RenderedDC;
}

void CGraphicDev::Set_Transform(CTransform * pTransform)
{
	m_pTransform = pTransform;
}

CTransform * CGraphicDev::Get_Transform(void)
{
	return m_pTransform;
}
