// Help.h : Help DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include "HelpWnd.h"


// CHelpApp
// �� Ŭ������ ������ ������ Help.cpp�� �����Ͻʽÿ�.
//

class CHelpApp : public CWinApp
{
public:
	CHelpApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
public:
	// CHelpWnd ������ ��ü ������
	CHelpWnd* m_pHelpWnd;
	// CHelpWnd �����츦 �����ϰ� ȭ�鿡 ����ϴ� �Լ�
	BOOL ShowHelpWnd();
	// CHelpWnd �����츦 �����ϴ� �Լ�
	void DestroyHelpWnd();
};
