
// MyWeb.h : MyWeb ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMyWebApp:
// �� Ŭ������ ������ ���ؼ��� MyWeb.cpp�� �����Ͻʽÿ�.
//

class CMyWebApp : public CWinApp
{
public:
	CMyWebApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyWebApp theApp;
