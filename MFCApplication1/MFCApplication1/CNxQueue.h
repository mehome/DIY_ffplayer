#pragma once
#include<vector>
#include"DefInfo.h"
#include"NxSharedPtr.h"
#include<mutex>
class CNxQueue
{
public:
	CNxQueue();
	~CNxQueue();

private:
	std::vector<CFrameInfo *>m_vFrmae;
	int size();
	
	std::mutex m_Mutex;
	std::condition_variable m_cv;

public:
	void push_back(CFrameInfo *pFrame);
	CFrameInfo *pop_front();
};

