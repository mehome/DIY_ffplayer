// CNxLog.h : CNxLog DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCNxLogApp
// �йش���ʵ�ֵ���Ϣ������� CNxLog.cpp
//

class CCNxLogApp : public CWinApp
{
public:
	CCNxLogApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
