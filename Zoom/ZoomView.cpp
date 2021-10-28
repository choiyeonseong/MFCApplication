
// ZoomView.cpp : CZoomView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Zoom.h"
#endif

#include "ZoomDoc.h"
#include "ZoomView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CZoomView

IMPLEMENT_DYNCREATE(CZoomView, CView)

BEGIN_MESSAGE_MAP(CZoomView, CView)
	ON_WM_SETCURSOR()
//	ON_WM_PAINT()
//ON_WM_PAINT()
ON_WM_LBUTTONDOWN()
ON_WM_RBUTTONDOWN()
ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CZoomView 생성/소멸

CZoomView::CZoomView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_nZoom = 1000;	// 초기값이 크면 클수록 비트맵 크기는 작게 출력된다.
}

CZoomView::~CZoomView()
{
}

BOOL CZoomView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CZoomView 그리기

void CZoomView::OnDraw(CDC* pDC)
{
	CZoomDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CenterImage(pDC);
}


// CZoomView 진단

#ifdef _DEBUG
void CZoomView::AssertValid() const
{
	CView::AssertValid();
}

void CZoomView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CZoomDoc* CZoomView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CZoomDoc)));
	return (CZoomDoc*)m_pDocument;
}
#endif //_DEBUG


// CZoomView 메시지 처리기


void CZoomView::CenterImage(CDC* pDC)
{
	CBitmap myBit, *pOldBit;
	CDC memDC;	// 메모리 DC
	BITMAP bm;	// GDI 비트맵(DDB)의 정보를 저장할 구조체 변수
	myBit.LoadBitmapW(IDB_IMAGE);	// 비트맵 리소스를 로드한다. -> GDI 비트맵 생성
	myBit.GetObject(sizeof(BITMAP), &bm);	// 비트맵 오브젝트에 대한 정보를 얻는다.
	memDC.CreateCompatibleDC(pDC);	// 화면 DC와 호환되는 DC 생성, 메모리 DC는 화면을 나타내는 메모리 버퍼 역할을 한다.
	pOldBit = memDC.SelectObject(&myBit);	// 메모리 DC로 비트맵 선택
	CRect rc;
	GetClientRect(rc);
	int x = (rc.Width() - bm.bmWidth) / 2;
	int y = (rc.Height() - bm.bmHeight) / 2;

	pDC->BitBlt(x, y,						// 대상 DC 사각형의 좌측 꼭지점 좌표
		bm.bmWidth, bm.bmHeight,	// 전송되는 비트맵의 폭과 높이
		&memDC,						// 원본 DC
		0, 0,						// 원본 비트맵의 좌측 꼭지점 좌표
		SRCCOPY);					// ROP 코드
	memDC.SelectObject(pOldBit);	// 반환
}


BOOL CZoomView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SetCursor(AfxGetApp()->LoadCursorW(GID_ZOOM));	// 새로운 커서 설정
	return TRUE;
}




void CZoomView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	CRect rc;
	GetClientRect(rc);
	pDC->SetMapMode(MM_ISOTROPIC);	// 맵핑모드 설정
	pDC->SetWindowExt(m_nZoom, m_nZoom);	// 윈도우 크기(Extent) 설정
	pDC->SetViewportExt(rc.Width(), rc.Height());	// 뷰포트 크기(Extent) 설정
}


void CZoomView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_nZoom /= 2;	// m_nZoom 값이 작아지니까 비트맵이 확대되어 출력된다.
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void CZoomView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_nZoom *= 2;	// m_nZoom 값이 커지니까 비트맵이 축소되어 출력된다.
	Invalidate();
	CView::OnRButtonDown(nFlags, point);
}


void CZoomView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CClientDC dc(this);
	COLORREF color;
	color = dc.GetPixel(point);	// 현재 커서가 위치한 픽셀의 RGB 색상을 얻는다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CStatusBar* pStatus = pFrame->GetStatusBar();
	
	CString strInfo;
	strInfo.Format(_T("X:%3d, Y:%3d / R:%3d, G:%3d,B:%d"),
		point.x, point.y, GetRValue(color), GetGValue(color), GetBValue(color));
	pStatus->SetPaneText(1, strInfo);
	
	CView::OnMouseMove(nFlags, point);
}
