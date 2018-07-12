#pragma once
#include<map>
#include"CNxQueue.h"
#include"DefInfo.h"
class CNxBase
{
public:
	CNxBase();
	~CNxBase();

	void InitMap(int index = 0);
	void Pushback(CFrameInfo *pFrame);
public:
	std::map<int, CNxQueue*, std::less<int>>m_mapBase;
};

