
// Zoom.h : Zoom ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CZoomApp:
// �� Ŭ������ ������ ���ؼ��� Zoom.cpp�� �����Ͻʽÿ�.
//

class CZoomApp : public CWinApp
{
public:
	CZoomApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CZoomApp theApp;
