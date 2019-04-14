#include "stdafx.h"
#include "Timer.h"
#include "Engine_Define.h"

CTimer::CTimer(void)
{

}

CTimer::~CTimer(void)
{

}

HRESULT CTimer::Init_Timer(void)
{
	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceCounter(&m_LastTime);
	QueryPerformanceFrequency(&m_CpuTick);

	return S_OK;
}

void CTimer::Set_TimeDelta(void)
{
	QueryPerformanceCounter(&m_FrameTime);

	if(m_FrameTime.QuadPart - m_LastTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_LastTime.QuadPart = m_FrameTime.QuadPart;
	}

	m_fTimeDelta = float(m_FrameTime.QuadPart - m_FixTime.QuadPart) / m_CpuTick.QuadPart;

	m_FixTime = m_FrameTime;
}

CTimer* CTimer::Create(void)
{
	CTimer* pTimer = new CTimer;
	if(FAILED(pTimer->Init_Timer()))
	{
		if(Engine::Safe_Release(pTimer))
			msg_box("pTimer Safe_Release Failed");
	}
	return pTimer;
}

ULONG CTimer::Release(void)
{
	delete this;
	
	return 0;
}

