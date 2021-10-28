// Help.cpp : �ش� DLL�� �ʱ�ȭ ��ƾ�� �����մϴ�.
//

#include "stdafx.h"
#include "Help.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: �� DLL�� MFC DLL�� ���� �������� ��ũ�Ǿ� �ִ� ���
//		MFC�� ȣ��Ǵ� �� DLL���� ���������� ��� �Լ���
//		���� �κп� AFX_MANAGE_STATE ��ũ�ΰ�
//		��� �־�� �մϴ�.
//
//		��:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �Ϲ����� �Լ� ������ ���⿡ �ɴϴ�.
//		}
//
//		�� ��ũ�δ� MFC�� ȣ���ϱ� ����
//		�� �Լ��� �ݵ�� ��� �־�� �մϴ�.
//		��, ��ũ�δ� �Լ��� ù ��° ���̾�� �ϸ� 
//		��ü ������ �����ڰ� MFC DLL��
//		ȣ���� �� �����Ƿ� ��ü ������ ����Ǳ� ����
//		���;� �մϴ�.
//
//		�ڼ��� ������
//		MFC Technical Note 33 �� 58�� �����Ͻʽÿ�.
//

// CHelpApp

BEGIN_MESSAGE_MAP(CHelpApp, CWinApp)
END_MESSAGE_MAP()


// CHelpApp ����

CHelpApp::CHelpApp()
	: m_pHelpWnd(NULL)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CHelpApp ��ü�Դϴ�.

CHelpApp theApp;


// CHelpApp �ʱ�ȭ

BOOL CHelpApp::InitInstance()
{
	m_pHelpWnd = NULL;	// �ʱⰪ ����
	CWinApp::InitInstance();

	return TRUE;
}


// CHelpWnd �����츦 �����ϰ� ȭ�鿡 ����ϴ� �Լ�
BOOL CHelpApp::ShowHelpWnd()
{
	if (m_pHelpWnd)	// �̹� �����찡 �����ϸ� �ٷ� ����
		return FALSE;
	m_pHelpWnd = new CHelpWnd;	// �� �޸𸮿� CHelpWnd ��ü �Ҵ�
	if (!m_pHelpWnd->Create(NULL, _T("DLL�� ������ ������")))	// CHelpWnd ������ ����
		return FALSE;
	m_pHelpWnd->ShowWindow(SW_SHOW);	// CHelpWnd �����츦 ȭ�鿡 ���
	m_pHelpWnd->UpdateWindow();
	return TRUE;
}


// CHelpWnd �����츦 �����ϴ� �Լ�
void CHelpApp::DestroyHelpWnd()
{
	if (m_pHelpWnd)	// ���� �����찡 �����ϸ� �� �޸� ����
	{
		delete m_pHelpWnd;
		m_pHelpWnd = NULL;
	}
}

#ifdef __cplusplus
	extern "C" {
#endif // __cplusplus
		__declspec(dllexport) BOOL ShowHelp()	// �ͽ���Ʈ �Ǵ� �Լ�
		{
			return theApp.ShowHelpWnd();	// DLL ���������� ���Ǵ� �Լ� ȣ��
		}
		__declspec(dllexport) void DestroyHelp()	// �ͽ���Ʈ �Ǵ� �Լ�
		{
			theApp.DestroyHelpWnd();	// DLL ���������� ���Ǵ� �Լ� ȣ��
		}
#ifdef __cplusplus
	}
#endif // __cplusplus

