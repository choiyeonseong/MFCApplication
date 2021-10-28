
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "Map_Sub.h"

#include "MainFrm.h"
#include <afxmt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND(ID_PARENT_SEND, &CMainFrame::OnParentSend)
	ON_WM_DESTROY()
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
	if( !CFrameWnd::PreCreateWindow(cs) )
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



void CMainFrame::OnParentSend()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CEvent myEvent(FALSE, FALSE, _T("ParentEvent"));
	HANDLE hFileMapping = OpenFileMapping(FILE_MAP_WRITE, FALSE, _T("spy"));
	DWORD* pData = (DWORD*)MapViewOfFile(hFileMapping,FILE_MAP_WRITE, 0, 0, 0);
	*pData = GetCurrentProcessId();	// ���� ���μ��� ID�� ����
	myEvent.SetEvent();				// �θ� ���μ����� ��ȣ�� �ش�. lock ����
	UnmapViewOfFile(pData);			// ���ε� ������ ������ ����
	CloseHandle(hFileMapping);		// ������ ���� ���� ������Ʈ�� �ݴ´�.
}


void CMainFrame::OnDestroy()
{
	CFrameWnd::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	CFrameWnd::OnDestroy();
	CEvent myEvent(FALSE, FALSE, _T("ParentEvent"));
	HANDLE hFileMapping = OpenFileMapping(FILE_MAP_WRITE, FALSE, _T("spy"));
	DWORD* pData = (DWORD*)MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, 0);
	*pData = -1;	// ����Ǿ����� �˸��� ���� -1�� ����
	myEvent.SetEvent();
	UnmapViewOfFile(pData);
	CloseHandle(hFileMapping);
}
