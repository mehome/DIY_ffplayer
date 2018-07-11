#pragma once
#include<mutex>
class CNxLogINI
{
private:
	CNxLogINI() {};
	static CNxLogINI *m_pInstance;

public:
	
	static CNxLogINI *LogCreateInstance();
	
	void DestoryInstance();
public:
	void LogSetPath(char *info);
	void LogDebug(const char *info, const char *Func);
	void LogDebug(wchar_t *infor, wchar_t *Func);
private:
	static FILE *m_pFile;
	static std::mutex m_lock;
};

