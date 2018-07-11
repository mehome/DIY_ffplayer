#include "stdafx.h"
#include "CNxLock.h"


CNxLock::CNxLock()
{
	InitializeCriticalSection(&m_cs);
}
CNxLock::~CNxLock()
{
	DeleteCriticalSection(&m_cs);
}
void CNxLock::Lock()
{
	EnterCriticalSection(&m_cs);
}
void CNxLock::UnLock()
{
	LeaveCriticalSection(&m_cs);
}