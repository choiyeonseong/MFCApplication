
// CapturePrint.h : CapturePrint ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CCapturePrintApp:
// �� Ŭ������ ������ ���ؼ��� CapturePrint.cpp�� �����Ͻʽÿ�.
//

class CCapturePrintApp : public CWinApp
{
public:
	CCapturePrintApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCapturePrintApp theApp;
