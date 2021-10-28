
// CapturePrintView.cpp : CCapturePrintView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "CapturePrint.h"
#endif

#include "CapturePrintDoc.h"
#include "CapturePrintView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCapturePrintView

IMPLEMENT_DYNCREATE(CCapturePrintView, CView)

BEGIN_MESSAGE_MAP(CCapturePrintView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SCREEN_CAPTURE, &CCapturePrintView::OnScreenCapture)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

// CCapturePrintView 생성/소멸

CCapturePrintView::CCapturePrintView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_Tracker.m_rect.SetRect(0, 0, 100, 100);	// 객체 m_Tracker 초기화
}

CCapturePrintView::~CCapturePrintView()
{
}

BOOL CCapturePrintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CCapturePrintView 그리기

void CCapturePrintView::OnDraw(CDC* pDC)
{
	CCapturePrintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CBrush br(RGB(0, 0, 255));
	CBrush* pOld = pDC->SelectObject(&br);
	CRect rcEllipse;
	m_Tracker.GetTrueRect(rcEllipse);
	pDC->Ellipse(rcEllipse);	// 타원 출력
	m_Tracker.Draw(pDC);		// 트랙커 사각형을 그린다
	pDC->SelectObject(pOld);
}


// CCapturePrintView 인쇄

BOOL CCapturePrintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CCapturePrintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CCapturePrintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CCapturePrintView 진단

#ifdef _DEBUG
void CCapturePrintView::AssertValid() const
{
	CView::AssertValid();
}

void CCapturePrintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCapturePrintDoc* CCapturePrintView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCapturePrintDoc)));
	return (CCapturePrintDoc*)m_pDocument;
}
#endif //_DEBUG


// CCapturePrintView 메시지 처리기

// [전체 화면 캡처 >>] 메뉴를 선택한 경우
void CCapturePrintView::OnScreenCapture()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CBitmap bitmap;
	CClientDC screenDC(NULL);	// 바탕 화면에 대한 DC
	CDC memDC;
	CRect rect;

	CWnd* pWnd = CWnd::GetDesktopWindow();	// 바탕화면에 대한 객체 포인터
	memDC.CreateCompatibleDC(&screenDC);
	pWnd->GetWindowRect(rect);		// 전체 화면의 크기를 얻는다
	// 전체 화면을 저장할 비트맵 생성
	bitmap.CreateCompatibleBitmap(&screenDC, rect.Width(), rect.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);	// 메모리 DC로 비트맵 선택
	// 현재 화면에 출력된 내용을 메모리 DC로 전송
	memDC.BitBlt(0, 0, rect.Width(), rect.Height(), &screenDC, 0, 0, SRCCOPY);

	// 클립보드에 캡처한 비트맵을 설정
	pWnd->OpenClipboard();	// 클립보드 오픈
	EmptyClipboard();	// 현재 클립보드에 있는 내용 제거
	SetClipboardData(CF_BITMAP, bitmap.GetSafeHandle());	// 캡처한 비트맵 설정
	CloseClipboard();	// 클립보드를 닫는다

	memDC.SelectObject(pOldBitmap);	// 반환
	bitmap.Detach();	// 비트맵 객체 제거
}


void CCapturePrintView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
	CBitmap bitmap;
	CWindowDC dc(pFrame);	// 메인 윈도우에 대한 DC
	CDC memDC;
	CRect rect;

	memDC.CreateCompatibleDC(&dc);
	pFrame->GetWindowRect(rect);	// 메인 윈도우의 크기 정보 얻음.
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);	// 메모리 DC로 비트맵 선택
	memDC.BitBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);

	// 메모리 DC의 캡처된 비트맵을 프린트 DC로 전송한다.
	pDC->SetMapMode(MM_ANISOTROPIC);	// 맵핑 모드 설정
	pDC->SetWindowExt(memDC.GetDeviceCaps(LOGPIXELSX), memDC.GetDeviceCaps(LOGPIXELSY));
	pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX), pDC->GetDeviceCaps(LOGPIXELSY));
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
	memDC.SelectObject(pOldBitmap);	// 반환
	bitmap.Detach();	// 비트맵 객체 제거


	//CView::OnPrint(pDC, pInfo);
}


void CCapturePrintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	BOOL bRet = m_Tracker.HitTest(point);	// 현재 커서가 위치한 곳을 알아낸다
	if (bRet != CRectTracker::hitNothing)	// 트랙커 사각형 내부에 커서가 위치한 경우
	{
		m_Tracker.m_nStyle = CRectTracker::resizeInside | CRectTracker::solidLine;	// 트랙커 사각형의 형태 설정
		m_Tracker.Track(this, point, TRUE);	// 드래그&드롭 처리
		Invalidate();
	}
	else
	{	// 트랙커 사각형 외부에 커서가 위치한 경우
		m_Tracker.m_nStyle = 0;	// 트랙커 사각형을 안보이게 한다.
		Invalidate();
	}

	CView::OnLButtonDown(nFlags, point);
}


BOOL CCapturePrintView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if ((m_Tracker.m_nStyle & CRectTracker::resizeInside) && (m_Tracker.SetCursor(this, nHitTest)))	// 트랙커 사각형에서 커서 모양 변경
		return TRUE;

	return CView::OnSetCursor(pWnd, nHitTest, message);
}
