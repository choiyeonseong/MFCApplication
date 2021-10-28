
// MapView.cpp : CMapView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Map.h"
#endif

#include "MapDoc.h"
#include "MapView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapView

IMPLEMENT_DYNCREATE(CMapView, CView)

BEGIN_MESSAGE_MAP(CMapView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CMapView 생성/소멸

CMapView::CMapView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMapView::~CMapView()
{
}

BOOL CMapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMapView 그리기

void CMapView::OnDraw(CDC* /*pDC*/)
{
	CMapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMapView 진단

#ifdef _DEBUG
void CMapView::AssertValid() const
{
	CView::AssertValid();
}

void CMapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapDoc* CMapView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapDoc)));
	return (CMapDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapView 메시지 처리기


void CMapView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_Map = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, sizeof(CData), _T("kitri"));	// 맵핑 오브젝트 생성
	if (!m_Map)
		AfxMessageBox(_T("파일 맵핑 오브젝트 생성 실패"));

	// 생성된 파일 맵핑 오브젝트에 데이터를 저장하기위해
	// 맵핑된 뷰 포인터를 얻는다
	m_ViewData = (CData*)MapViewOfFile(m_Map, FILE_MAP_WRITE, 0, 0, 0);	// 맵핑된 파일에 내용을 읽거나 저장
	if (!m_ViewData)
		AfxMessageBox(_T("메모리 맵 파일에 쓰기 실패"));
	m_ViewData->flag = DRAW_READY;	// 그리기 준비 상태 설정
}


void CMapView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 마우스 커서가 해당 윈도우를 벗어나도
	// 마우스 메시지를 받을수 있도록 한다.
	SetCapture();
	m_start = point;	// 드래그가 시작된 위치 설정

	CView::OnLButtonDown(nFlags, point);
}

void CMapView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (GetCapture() == this)	// 드래그 중이면
	{
		// 굵기 10인 파란색 실선으로 자유곡선을 그린다.
		CClientDC dc(this);
		CPen newPen(PS_SOLID, 10, m_color);
		CPen* pOldPen = dc.SelectObject(&newPen);
		dc.MoveTo(m_start);
		dc.LineTo(point);
		// 메모리 맵 파일 조작 관련
		m_ViewData->flag = DRAW_START;	// 그리기 상태 설정
		m_ViewData->color = m_color;	// 색상 설정
		m_ViewData->start = m_start;	// 시작 위치 설정
		m_ViewData->pt = point;			// 현재 위치 설정
		
		m_start = point;				// 처음 시작 위치에 현재 위치 설정
		dc.SelectObject(pOldPen);
	}
	CView::OnMouseMove(nFlags, point);
}

void CMapView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (GetCapture() == this)
	{
		m_ViewData->flag = DRAW_READY;	// 그리기 준비 상태 설정
		ReleaseCapture();	// SetCapture() 해제
	}
	CView::OnLButtonUp(nFlags, point);
}




void CMapView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_color = dlg.GetColor();	// 색상 설정
	}

	CView::OnRButtonDown(nFlags, point);
}


void CMapView::OnDestroy()
{
	CView::OnDestroy();
	m_ViewData->flag = DRAW_STOP;	// 그리기 중단 상태 설정
	CloseHandle(m_Map);	// 메모리 맵 파일을 닫는다.

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
