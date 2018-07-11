#include "stdafx.h"
#include "CNxLogINI.h"

std::mutex 	 CNxLogINI::m_lock;
CNxLogINI	*CNxLogINI::m_pInstance = nullptr;
FILE		*CNxLogINI::m_pFile = nullptr;


CNxLogINI *CNxLogINI::LogCreateInstance()
{
	
	if (m_pInstance != nullptr)
	{	
		return m_pInstance;
	}
	else
	{
		m_lock.lock();
		m_pInstance = new CNxLogINI();
		m_lock.unlock();
	}
	
	return m_pInstance;
}
void CNxLogINI::DestoryInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
	if (m_pFile != nullptr)
	{
		fclose(m_pFile);
		m_pFile = nullptr;
	}
}
void CNxLogINI::LogSetPath(char *info)
{
	m_lock.lock();

	if (m_pFile == nullptr)
	{
		fopen_s(&m_pFile, info, "wb+");
	}

	m_lock.unlock();
}
void CNxLogINI::LogDebug(const char *info, const char *Func)
{
	m_lock.lock();

	char buf[_MAX_PATH] = {0};
	sprintf_s(buf, "%s:%s", Func, info);

	fprintf(m_pFile, buf);
	fprintf(m_pFile, "\n");
	
	m_lock.unlock();
}
void CNxLogINI::LogDebug(wchar_t *infor, wchar_t *Func)
{

}