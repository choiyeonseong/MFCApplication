
// ShapeExView.cpp : CShapeExView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ShapeEx.h"
#endif

#include "ShapeExDoc.h"
#include "ShapeExView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CShapeExView

IMPLEMENT_DYNCREATE(CShapeExView, CView)

BEGIN_MESSAGE_MAP(CShapeExView, CView)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CShapeExView 생성/소멸

CShapeExView::CShapeExView()
	: m_curPos(0)
	, m_bShape(TRUE)	// 도형이 그려지는 화면을 설정
	, m_nLine(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CShapeExView::~CShapeExView()
{
}

BOOL CShapeExView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CShapeExView 그리기

void CShapeExView::OnDraw(CDC* pDC)
{
	CShapeExDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	if (m_bShape)	// 각종 도형 출력
	{
		// 각 역할 별로 멤버함수를 작성함으로써 함수 내부가 간결해짐
		ShowRect(pDC);
		ShowCircle(pDC);
		ShowLine(pDC);
		ShowRainbow(pDC);
		ShowCursorPos(pDC);	// 현재 커서의 위치를 출력한다.
	}
	else
	{
		m_nLine = 0;
		for (int i = 20; i <= 60; i += 5)
			ShowFont(pDC, i);
	}
}


// CShapeExView 진단

#ifdef _DEBUG
void CShapeExView::AssertValid() const
{
	CView::AssertValid();
}

void CShapeExView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShapeExDoc* CShapeExView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShapeExDoc)));
	return (CShapeExDoc*)m_pDocument;
}
#endif //_DEBUG


// CShapeExView 메시지 처리기

// 사각형을 출력한다.
void CShapeExView::ShowRect(CDC* pDC)
{
	CPen myPen, *pOldPen;
	CBrush myBrush, *pOldBrush;
	myPen.CreatePen(PS_SOLID, 5, RGB(0, 0, 255)); // 굵기 5 픽셀의 파란색 펜 생성
	myBrush.CreateSolidBrush(RGB(255, 255, 0));	//노란색 솔리드 브러시 생성

	pOldPen = pDC->SelectObject(&myPen);	// 파란색 펜 선택
	pOldBrush = pDC->SelectObject(&myBrush);	// 노란색 브러시 선택
	pDC->Rectangle(10, 10, 300, 200);	// 실제 사각형을 그린다.
	pDC->SelectObject(pOldPen);	// 기존 펜 반환
	pDC->SelectObject(pOldBrush);	// 기존 브러시 반환

	// 커서의 현재 위치를 출력할 프레임을 만든다.
	CRect rc;
	GetClientRect(rc);
	m_rcStatus.SetRect(rc.left, rc.Height() - 30, rc.right, rc.bottom);	// 프레임 위치 설명
	pDC->DrawFrameControl(m_rcStatus, DFC_BUTTON | DFCS_BUTTONPUSH, 0);
}

// 타원을 출력한다.
void CShapeExView::ShowCircle(CDC* pDC)
{
	CPen myPen, *pOldPen;
	CBrush *pOldBrush;
	myPen.CreatePen(PS_DOT, 1, RGB(255, 0, 0));	// 빨간색 점선 펜 생성
	pOldPen = pDC->SelectObject(&myPen);	// 빨간색 점선 펜 선택
	pOldBrush = (CBrush*)pDC->SelectStockObject(LTGRAY_BRUSH);	// 내장 브러시 선택
	pDC->Ellipse(150, 100, 300, 300);	// 타원을 그린다.
	pDC->SelectObject(pOldPen);	// 기존 펜 반환
	pDC->SelectObject(pOldBrush);	// 기존 펜 반환
}

// 선을 출력한다.
void CShapeExView::ShowLine(CDC* pDC)
{
	CPen* pOldPen;
	pOldPen = (CPen*)pDC->SelectStockObject(BLACK_PEN);	//내장 펜 사용
	pDC->MoveTo(10, 10);	// 시작점으로 이동
	pDC->LineTo(300, 200);	// 선을 그린다.

	pDC->MoveTo(10, 200);	// 시작점으로 이동
	pDC->LineTo(300, 10);	// 선을 그린다.
	pDC->SelectObject(pOldPen);	// 기존 펜 반환
}

// 무지개 모양을 출력한다.
void CShapeExView::ShowRainbow(CDC* pDC)
{
	COLORREF color;
	CPen myPen, *pOldPen;
	for (int i = 0; i < 20; i++)
	{
		color = RGB(rand() % 256, rand() % 256, rand() % 256);	// 임의의 색상 설정
		myPen.CreatePen(PS_SOLID, 3, color);	// 펜 오브젝트 생성
		pOldPen = pDC->SelectObject(&myPen);	// 생성한 펜 선택
		pDC->Arc(300 + i, 50 + i, 500 - i, 260 - i, 600, 160, 0, 160);	// 원호를 그린다.
		pDC->SelectObject(pOldPen);	// 기존 펜 반환
		myPen.DeleteObject();	// 생성된 펜을 제거한다.(소멸자가 호출되지 않고 for루프를 돌아야 하기때문에 DeleteObject() 직접 호출)
	}
}


void CShapeExView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bShape)
	{
		m_curPos = point;	// 현재 커서의 위치를 설정

		InvalidateRect(m_rcStatus, FALSE);	// m_rcStatus의 사각형 영역을 다시 그린다.
	}

	CView::OnMouseMove(nFlags, point);
}


// 마우스가 움직일때 마다 변경된 커서의 위치를 얻어와 화면에 출력
void CShapeExView::ShowCursorPos(CDC* pDC)
{
	CString str;
	str.Format(_T("X좌표:%3d, Y좌표:%3d"), m_curPos.x, m_curPos.y);
	//pDC->SetBkMode(OPAQUE);	// 배경 불투명 모드 설정(default)
	pDC->SetBkMode(TRANSPARENT);	// 배경 투명 모드 설정
	pDC->SetTextColor(RGB(0, 0, 255));	// 텍스트 색상 설정
	pDC->DrawText(str, m_rcStatus, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	// 텍스트를 출력한다.
}


// 크기에 따른 글자 변화를 화면에 출력
void CShapeExView::ShowFont(CDC* pDC, int nPoint)
{
	TEXTMETRIC tm;	// 구조체
	CFont myFont, *pOldFont;
	// 폰트 생성
	myFont.CreateFont(nPoint, 0, 0, 0, 700, TRUE, TRUE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	pOldFont = pDC->SelectObject(&myFont);	// 새로운 폰트 선택
	pDC->SetBkMode(TRANSPARENT);	// 투명 모드 설정
	pDC->TextOutW(10, m_nLine, _T("한국정보기술연구원"));	// 텍스트 출력
	pDC->GetTextMetrics(&tm);	// 현재 화면에 출력된 텍스트의 정보 얻음
	pDC->SelectObject(pOldFont);	// 반환
	m_nLine += (tm.tmHeight + tm.tmExternalLeading);	// 문자의 전체 높이
}

void CShapeExView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_bShape = !m_bShape;	// 마우스 우측 버튼이 눌릴 때마다 m_bShape 값이 변경된다.
	Invalidate();	// 클라이언트 영역을 다시 그린다.

	CView::OnRButtonDown(nFlags, point);
}


BOOL CShapeExView::OnEraseBkgnd(CDC* pDC)	// 클라이언트 영역을 변경한다.
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CBrush myBrush, *pOldBrush;
	myBrush.CreateHatchBrush(HS_VERTICAL, RGB(0, 255, 0));	// 수직 해칭 브러시 생성
	pOldBrush = pDC->SelectObject(&myBrush);	// 수직 해칭 브러시 선택
	CRect rc;
	GetClientRect(rc);	// 클라이언트 영역의 사각형 정보 얻음
	pDC->FillRect(rc, &myBrush);	// 클라이언트 영역을 수직 해칭 브러시로 채운다.
	pDC->SelectObject(pOldBrush);	// 반환
	return TRUE;
}
