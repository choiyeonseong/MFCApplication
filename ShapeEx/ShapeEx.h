
// ShapeEx.h : ShapeEx ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CShapeExApp:
// �� Ŭ������ ������ ���ؼ��� ShapeEx.cpp�� �����Ͻʽÿ�.
//

class CShapeExApp : public CWinApp
{
public:
	CShapeExApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CShapeExApp theApp;
