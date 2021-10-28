
// MainFrm.cpp : CMainFrame 클래스의 구현
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

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

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


// CMainFrame 메시지 처리기



void CMainFrame::OnParentSend()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CEvent myEvent(FALSE, FALSE, _T("ParentEvent"));
	HANDLE hFileMapping = OpenFileMapping(FILE_MAP_WRITE, FALSE, _T("spy"));
	DWORD* pData = (DWORD*)MapViewOfFile(hFileMapping,FILE_MAP_WRITE, 0, 0, 0);
	*pData = GetCurrentProcessId();	// 현재 프로세스 ID를 설정
	myEvent.SetEvent();				// 부모 프로세스에 신호를 준다. lock 해제
	UnmapViewOfFile(pData);			// 맵핑된 파일의 포인터 해제
	CloseHandle(hFileMapping);		// 생성된 파일 맵핑 오브젝트를 닫는다.
}


void CMainFrame::OnDestroy()
{
	CFrameWnd::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CFrameWnd::OnDestroy();
	CEvent myEvent(FALSE, FALSE, _T("ParentEvent"));
	HANDLE hFileMapping = OpenFileMapping(FILE_MAP_WRITE, FALSE, _T("spy"));
	DWORD* pData = (DWORD*)MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, 0);
	*pData = -1;	// 종료되었음을 알리기 위해 -1을 설정
	myEvent.SetEvent();
	UnmapViewOfFile(pData);
	CloseHandle(hFileMapping);
}
