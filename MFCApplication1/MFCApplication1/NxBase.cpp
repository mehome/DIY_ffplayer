#include "stdafx.h"
#include "NxBase.h"

CNxBase::CNxBase()
{
}


CNxBase::~CNxBase()
{
}
void CNxBase::Pushback(CFrameInfo *pFrame)
{
	m_mapBase[0]->push_back(pFrame);
}
void CNxBase::InitMap(int index)
{
	m_mapBase[0] = new CNxQueue();
}