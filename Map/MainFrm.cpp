
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include <afxmt.h>
#include "stdafx.h"
#include "Map.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND(ID_CHILD_PROCESS, &CMainFrame::OnChildProcess)
END_MESSAGE_MAP()

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return TRUE;
}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame �޽��� ó����



void CMainFrame::OnChildProcess()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxBeginThread(ChildInfo, NULL);	// �۾� ������ ����
}


// �����忡 ���� ����Ǵ� �Լ�
UINT CMainFrame::ChildInfo(LPVOID lParam)
{
	// �ڽ� ���μ���(Map_Sub.exe)���� ����ȭ�� ����� �̺�Ʈ ��ü ����
	// �̺�Ʈ �̸� : "ParentEvent"
	CEvent myEvent(FALSE, FALSE, _T("ParentEvent"));

	// �޸� �� ���� ����(���ε� ���� �̸��� "spy"�� ����)
	HANDLE hFileMapping = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, sizeof(DWORD), _T("spy"));

	// �ڽ� ���μ����� �����ϱ� ���� �غ� �۾�
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	// �ڽ� ���μ����� �����Ѵ�.
	if (CreateProcess(_T("D:\\repository\\MFCApplication\\Debug\\Map_Sub.exe"), NULL, NULL, NULL, NULL, //TRUE,
		NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
	{
		// ���μ����� ���� Ƚ���� 1�� ���߱� ���� �̸� �ѹ� �ݴ´�.
		CloseHandle(pi.hProcess);

		CSingleLock doKey(&myEvent);
		while (1)
		{
			// �ڽ� ���μ������� �̺�Ʈ�� �߻��Ҷ� ���� ������(lock)�� ��ٸ���.
			doKey.Lock();

			// �̺�Ʈ�� �߻��Ǹ� �޸� �� ���Ͽ� ���� ������ �ִ��� Ȯ��
			DWORD* pData = (DWORD*)MapViewOfFile(hFileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
			if (*pData == -1)	// �ڽ� ���μ����� ����� ���
			{
				AfxMessageBox(_T("�ڽ� ���μ��� ����"));
				break;
			}
			else /*�ڽ����μ����� �۵���*/
			{
				CString str;
				str.Format(_T("�ڽ� ���μ����� ID \r\n %X"), *pData);
				AfxMessageBox(str);
				doKey.Unlock(1);
				myEvent.ResetEvent();	// �ٽ� �����·� ����.
			}
		}
	}	// if
	else
	{
		AfxMessageBox(_T("�ڽ� ���μ��� ���� ����"));
		return 0;
	}
	return 0;
}
