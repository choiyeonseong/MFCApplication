
// Call.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCallApp:
// �� Ŭ������ ������ ���ؼ��� Call.cpp�� �����Ͻʽÿ�.
//



class CCallApp : public CWinApp
{
public:
	CCallApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCallApp theApp;

// ����Ʈ �Լ��� ���� ����
#ifdef __cplusplus
extern "C" {
#endif
	__declspec(dllimport) BOOL ShowSetupDialog(char* szMail, char* szPath);
#ifdef __cplusplus
}
#endif