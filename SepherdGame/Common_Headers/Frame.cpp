#include "stdafx.h"
#include "Frame.h"
#include "Engine_Define.h"

CFrame::CFrame(void): m_fAccTimes(0.f)
{

}
CFrame::~CFrame(void)
{

}

bool CFrame::Get_FrameUpdate(const float& fTimeDelta)
{
	m_fAccTimes += fTimeDelta;

	if(m_fAccTimes > m_fFrameRate)
	{
		m_fAccTimes = 0.f;
		return true;
	}
	return false;
}

HRESULT CFrame::Init_FrameRate(const float& fLimitTime)
{
	m_fFrameRate = 1.f / fLimitTime;
	return S_OK;
}

ULONG CFrame::Release(void)
{

	delete this;
	return 0;
}

CFrame* CFrame::Create(const float& fLimitFrame)
{
	CFrame* pFrame = new CFrame;

	if(FAILED(pFrame->Init_FrameRate(fLimitFrame)))
		Engine::Safe_Release(pFrame);

	return pFrame;
}