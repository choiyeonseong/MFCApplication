
// NewCom.h : NewCom ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CNewComApp:
// �� Ŭ������ ������ ���ؼ��� NewCom.cpp�� �����Ͻʽÿ�.
//

class CNewComApp : public CWinApp
{
public:
	CNewComApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CNewComApp theApp;
