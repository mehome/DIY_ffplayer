#include "stdafx.h"
#include "CNxQueue.h"


CNxQueue::CNxQueue()
{

}


CNxQueue::~CNxQueue()
{

}

void CNxQueue::push_back(CFrameInfo *pFrame)
{
	std::unique_lock<std::mutex>lock(m_Mutex);

	m_vFrmae.push_back(pFrame);

	m_cv.notify_one();
}
CFrameInfo *CNxQueue::pop_front()
{
	std::unique_lock<std::mutex>lock(m_Mutex);

	if (size() == 0)
	{
		m_cv.wait(lock);
	}
	
	CFrameInfo *p = nullptr;
	
	p = m_vFrmae.front();

	return p;
}
int CNxQueue::size()
{	
	return  m_vFrmae.size();
}