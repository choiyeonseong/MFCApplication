
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "Image.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_NCCREATE()
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
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



BOOL CMainFrame::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (!CFrameWnd::OnNcCreate(lpCreateStruct))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	
	//// 직사각형 윈도우 생성
	//m_rgnWnd.CreateRoundRectRgn(7, 10, 400, 200, 40, 40);
	//SetWindowRgn((HRGN)m_rgnWnd, TRUE);
	
	// 역삼각형 모양의 윈도우 생성
	POINT points[5];
	CRect wrect;
	GetWindowRect(wrect);	// 메인 윈도우의 사각형 정보 얻음(스크린 좌표)
	points[0].x = points[0].y = points[1].x = points[4].y = 0;
	points[1].y = GetSystemMetrics(SM_CYMENU) + GetSystemMetrics(SM_CYCAPTION);
	points[3].x = points[4].x = wrect.right - wrect.left;
	points[3].y = GetSystemMetrics(SM_CYMENU) + GetSystemMetrics(SM_CYCAPTION);
	points[2].x = (wrect.right - wrect.left) / 2;
	points[2].y = wrect.bottom - wrect.top;

	m_rgnWnd.CreatePolygonRgn(points, 5, WINDING);	// 영역 오브젝트 생성
	SetWindowRgn((HRGN)m_rgnWnd, TRUE);
	
	return TRUE;
}
