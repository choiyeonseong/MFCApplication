
// Act.h : Act ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CActApp:
// �� Ŭ������ ������ ���ؼ��� Act.cpp�� �����Ͻʽÿ�.
//

class CActApp : public CWinApp
{
public:
	CActApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	void OnAppAbout();

// �����Դϴ�.
	COleTemplateServer m_server;
		// ���� ����⿡ ���� ���� ��ü�Դϴ�.
	DECLARE_MESSAGE_MAP()
};

extern CActApp theApp;
