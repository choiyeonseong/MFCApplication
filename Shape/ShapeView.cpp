
// ShapeView.cpp : CShapeView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Shape.h"
#endif

#include "ShapeDoc.h"
#include "ShapeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CShapeView

IMPLEMENT_DYNCREATE(CShapeView, CView)

BEGIN_MESSAGE_MAP(CShapeView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CShapeView 생성/소멸

CShapeView::CShapeView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CShapeView::~CShapeView()
{
}

BOOL CShapeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CShapeView 그리기

void CShapeView::OnDraw(CDC* pDC)
{
	CShapeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CBrush myBrush(RGB(0, 0, 255));	// 생성자를 이용하여 파란색 브러시를 생성
	CBrush* p01dBrush;	// 기존 브러시를 저장할 변수
	p01dBrush = pDC->SelectObject(&myBrush);	// 파란색 브러시 선택
	pDC->Rectangle(m_Rect);	// m_Rect 크기의 파란 사각형 그리기
	pDC->SelectObject(p01dBrush);	// 기존 브러시로 환원

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CShapeView 진단

#ifdef _DEBUG
void CShapeView::AssertValid() const
{
	CView::AssertValid();
}

void CShapeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShapeDoc* CShapeView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShapeDoc)));
	return (CShapeDoc*)m_pDocument;
}
#endif //_DEBUG


// CShapeView 메시지 처리기


void CShapeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//CRect rcClient;
	//GetClientRect(rcClient);	// 클라이언트 영역의 사각형 얻음
	//
	//CClientDC dc(this);	// 화면(클라이언트 영역)을 사용할수 있는 권한 얻음
	//CBrush myBrush(RGB(255, 0, 0));	// 생성자를 이용하여 빨간색 브러시를 생성
	//CBrush* p01dBrush;	// 기존 브러쉬를 저장할 변수

	//p01dBrush = dc.SelectObject(&myBrush);	// 빩간색 브러시 선택
	//dc.Ellipse(rcClient);		// 클라이언트 영역 크기의 빨간 타원 그리기
	//dc.SelectObject(p01dBrush);	// 기존 브러시로 환원

	// 클릭된 커서 위치를 기준으로 좌우 100픽셀, 상하  100픽셀 크기의 사각형 형성
	m_Rect = CRect(point.x - 100, point.y - 100, point.x + 100, point.y + 100);

	Invalidate();	// 강제적으로 메시지 WM_PAINT를 발생시킴

	CView::OnLButtonDown(nFlags, point);
}
