
// GhostView.cpp : CGhostView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Ghost.h"
#endif

#include "GhostDoc.h"
#include "GhostView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGhostView

IMPLEMENT_DYNCREATE(CGhostView, CView)

BEGIN_MESSAGE_MAP(CGhostView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGhostView 생성/소멸

CGhostView::CGhostView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGhostView::~CGhostView()
{
}

BOOL CGhostView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGhostView 그리기

void CGhostView::OnDraw(CDC* /*pDC*/)
{
	CGhostDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CGhostView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGhostView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGhostView 진단

#ifdef _DEBUG
void CGhostView::AssertValid() const
{
	CView::AssertValid();
}

void CGhostView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGhostDoc* CGhostView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGhostDoc)));
	return (CGhostDoc*)m_pDocument;
}
#endif //_DEBUG


// CGhostView 메시지 처리기


BOOL CGhostView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	::SetCursor(AfxGetApp()->LoadCursor(IDC_GHOST));	// 새로만든 커서 로드 (*.cur)
	return TRUE;
}


void CGhostView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 캐럿 생성 및 위치 설정
	CreateSolidCaret(5, 30);	// 5x30 크기의 캐럿 생성
	SetCaretPos(point);	// 캐럿의 위치를 마우스 좌측 버튼이 눌린 위치로 설정한다.
	ShowCaret();		// 캐럿을 화면에 보여준다.

	// 마우스 커서의 현재 위치 출력
	CString strInfo;
	strInfo.Format(_T("현재 위치\r\n X = %d, Y = %d"), point.x, point.y);
	MessageBox(strInfo, _T("마우스 좌측 버튼 정보"), MB_ICONINFORMATION);
	
	CView::OnLButtonDown(nFlags, point);
}

void CGhostView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// 캐럿을 사라지게 하고 소멸시킨다.
	HideCaret();	// 캐럿을 화면에 보이지 않게 한다.
	DestroyCaret();	// 캐럿을 소멸한다.

	// 마우스 커서의 현재 위치 출력
	CString strInfo;
	strInfo.Format(_T("현재 위치\r\n X = %d, Y = %d"), point.x, point.y);
	MessageBox(strInfo, _T("마우스 우측 버튼 정보"), MB_ICONINFORMATION);

	CView::OnRButtonDown(nFlags, point);
}


void CGhostView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CPoint ptCurPos;	// 현재 커서의 위치
	if (::GetCursorPos(&ptCurPos))	// 현재 커서 위치를 얻는다.(스크린 좌표)
	{
		switch (nChar)	// 키값(nChar)에 따라 새로운 커서 위치를 설정한다.
		{
		case VK_LEFT:
			ptCurPos.x -= 30;
			::SetCursorPos(ptCurPos.x, ptCurPos.y);
			break;
		case VK_RIGHT:
			ptCurPos.x += 30;
			::SetCursorPos(ptCurPos.x, ptCurPos.y);
			break;
		case VK_UP:
			ptCurPos.y -= 30;
			::SetCursorPos(ptCurPos.x, ptCurPos.y);
			break;
		case VK_DOWN:
			ptCurPos.y += 30;
			::SetCursorPos(ptCurPos.x, ptCurPos.y);
			break;
		}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
