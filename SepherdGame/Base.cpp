#include "stdafx.h"
#include "Base.h"

CBase::CBase(void)
	: m_dwRefCnt(0)
{

}

CBase::CBase(const CBase& Instance)
	: m_dwRefCnt(Instance.m_dwRefCnt)
{

}

CBase::~CBase(void)
{

}

