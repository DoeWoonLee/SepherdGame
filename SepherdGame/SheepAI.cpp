#include "stdafx.h"
#include "SheepAI.h"
#include "GameObject.h"
#include "Transform.h"

CSheepAI::CSheepAI(void)
	: m_pTransform(nullptr)
{
}

CSheepAI::~CSheepAI(void)
{
}

_ulong CSheepAI::Update(const float & fTimeDelta)
{

	return _ulong();
}

HRESULT CSheepAI::Post_Initialize(void)
{
	m_pTransform = reinterpret_cast<CTransform*>(m_pOwnerObject->Get_Component(COM_TRANSFORM));

	return E_NOTIMPL;
}

_ulong CSheepAI::Release(void)
{
	_ulong dwRefCnt = CComponent::Release();
	if (0 == dwRefCnt)
	{
		SAFE_RELEASE(m_pTransform);
		delete this;
	}
	return dwRefCnt;
}
