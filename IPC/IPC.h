
// IPC.h : IPC ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CIPCApp:
// �� Ŭ������ ������ ���ؼ��� IPC.cpp�� �����Ͻʽÿ�.
//

class CIPCApp : public CWinApp
{
public:
	CIPCApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CIPCApp theApp;
