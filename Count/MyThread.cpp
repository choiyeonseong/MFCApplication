// MyThread.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Count.h"
#include "MyThread.h"


// CMyThread

IMPLEMENT_DYNCREATE(CMyThread, CWinThread)

CMyThread::CMyThread()
	: m_pDlg(NULL)
{
}

CMyThread::~CMyThread()
{
}

BOOL CMyThread::InitInstance()
{
	// TODO:  ���⿡�� �� �����忡 ���� �ʱ�ȭ�� �����մϴ�.
	return TRUE;
}

int CMyThread::ExitInstance()
{
	// TODO:  ���⿡�� �� �����忡 ���� ������ �����մϴ�.
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMyThread, CWinThread)
END_MESSAGE_MAP()


// CMyThread �޽��� ó�����Դϴ�.


void CMyThread::SetOwner(CCountDlg* pDlg)
{
	m_pDlg = pDlg;	// ���̾�α��� ��ü �����͸� ������� m_pDlg�� ����
}


int CMyThread::Run()	// ����� �������̽� �����尡 �����ϴ� �κ�
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CProgressCtrl* pProgress = (CProgressCtrl*)m_pDlg->GetDlgItem(IDC_PROGRESS1);
	pProgress->SetRange(0, 1000);	// ���α׷��� ��Ʈ���� ��ȿ���� ����
	CString str;
	int idx = 0;
	for (int i = 0; i < 1000; i++)	// ���̾�α��� ���α׷��� ��Ʈ���� �����Ȳ�� ǥ�����ִ� ����
	{
		pProgress->SetPos(i);	// ���� ��ġ ����
		if (!(i % 10))
		{
			str.Format(_T("������ %d%%"), idx++);
			m_pDlg->SetDlgItemText(IDC_PERCENT, str);
			// ������ ǥ��
		}
	}
	m_pDlg->GetDlgItem(IDC_START_PROGRESS)->EnableWindow(TRUE);
	AfxEndThread(0);		// ������ ���ο��� ����� �������̽� ������ ����
	//TerminateThread();	// ������ �ܺο��� ���� ����
	return CWinThread::Run();
}
