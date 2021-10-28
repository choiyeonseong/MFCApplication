// Pass.cpp : �ش� DLL�� �ʱ�ȭ ��ƾ�� �����մϴ�.
//

#include "stdafx.h"
#include "Pass.h"
#include "SetupDlg.h"

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

// CPassApp

BEGIN_MESSAGE_MAP(CPassApp, CWinApp)
END_MESSAGE_MAP()


// CPassApp ����

CPassApp::CPassApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CPassApp ��ü�Դϴ�.

CPassApp theApp;


// CPassApp �ʱ�ȭ

BOOL CPassApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

#ifdef __cplusplus
// C++ �����Ϸ��� �������̸� extern "C" Ű���带 ����Ѵ�.
extern "C" {
#endif
	// DLL�� �ͽ���Ʈ�ϴ� �Լ��� �����Ѵ�.
	__declspec(dllexport) BOOL ShowSetupDialog(char* szMail, char* szPath)
	{
		CSetupDlg dlg;
		dlg.m_Path = szPath;	// ��ġ ���丮 ��� ����
		if (dlg.DoModal() == IDOK)
		{
			lstrcpy((LPWSTR)szMail, dlg.m_Mail);	// ����ڷκ��� �Է¹��� �� ����
			lstrcpy((LPWSTR)szPath, dlg.m_Path);	// ����ڷκ��� �Է¹��� �� ����
			return TRUE;
		}
		return FALSE;
	 }
	// �ͽ���Ʈ �Լ��� �� �߰��Ϸ��� �� �κп��� ����
#ifdef __cplusplus
	}
#endif




