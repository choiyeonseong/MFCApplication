
// Shape.h : Shape ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CShapeApp:
// �� Ŭ������ ������ ���ؼ��� Shape.cpp�� �����Ͻʽÿ�.
//

class CShapeApp : public CWinApp
{
public:
	CShapeApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CShapeApp theApp;
