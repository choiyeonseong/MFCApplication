
// Http.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CHttpApp:
// �� Ŭ������ ������ ���ؼ��� Http.cpp�� �����Ͻʽÿ�.
//

class CHttpApp : public CWinApp
{
public:
	CHttpApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CHttpApp theApp;