#include "stdafx.h"
#include "Transform.h"
#include "GraphicDev.h"

IMPLEMENT_COMPONENT(CTransform, COM_TRANSFORM)

CTransform::CTransform(void)
{

}
CTransform::~CTransform(void)
{
}

void CTransform::Set_Position(float fX, float fY)
{
	m_vPosition.x = fX;
	m_vPosition.y = fY;
}
void CTransform::Render(void)
{
	CGraphicDev::GetInstance()->Set_Transform(this);
}
_ulong CTransform::Release(void)
{
	_ulong dwRefCnt = CComponent::Release();
	if (0 == dwRefCnt)
	{
		delete this;
	}
	return dwRefCnt;
}
CTransform* CTransform::Create(void)
{
	CTransform* pTransform = new CTransform();
	if (FAILED(pTransform->Initialize()))
	{
		SAFE_RELEASE(pTransform);
	}
	return pTransform;
}
HRESULT CTransform::Initialize(void)
{

	return S_OK;
}