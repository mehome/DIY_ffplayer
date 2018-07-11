#pragma once
class CNxLock
{
public:
	CNxLock();
	~CNxLock();
public:
	
	void Lock();
	void UnLock();

private:
	CRITICAL_SECTION m_cs;
};

