
// Map_Sub.h : Map_Sub ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMap_SubApp:
// �� Ŭ������ ������ ���ؼ��� Map_Sub.cpp�� �����Ͻʽÿ�.
//

class CMap_SubApp : public CWinApp
{
public:
	CMap_SubApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMap_SubApp theApp;
