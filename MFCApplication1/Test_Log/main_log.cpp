#include<stdio.h>
#include<thread>
#include"CNxLogINI.h"

void func1(CNxLogINI *p)
{
	for(int i = 0; i < 10000; i++)
	{
		p->LogDebug("Debug1", __func__);
	}
}
void func2(CNxLogINI *p)
{
	for (int i = 0; i < 10000; i++)
	{
		p->LogDebug("Debug2", __func__);
	}
}
int main(int argc, char*argv[])
{
	CNxLogINI *m_p = CNxLogINI::LogCreateInstance();
	
	m_p->LogSetPath("D:\\log.txt");
	m_p->LogDebug("Debug", __func__);
	
	std::thread th(func1,m_p);
	std::thread th2(func2, m_p);

	th.join();
	th2.join();
	return 0;
}