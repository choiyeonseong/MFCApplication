
// ShapeExView.cpp : CShapeExView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CShapeExView ����/�Ҹ�

CShapeExView::CShapeExView()
	: m_curPos(0)
	, m_bShape(TRUE)	// ������ �׷����� ȭ���� ����
	, m_nLine(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CShapeExView::~CShapeExView()
{
}

BOOL CShapeExView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CShapeExView �׸���

void CShapeExView::OnDraw(CDC* pDC)
{
	CShapeExDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	if (m_bShape)	// ���� ���� ���
	{
		// �� ���� ���� ����Լ��� �ۼ������ν� �Լ� ���ΰ� ��������
		ShowRect(pDC);
		ShowCircle(pDC);
		ShowLine(pDC);
		ShowRainbow(pDC);
		ShowCursorPos(pDC);	// ���� Ŀ���� ��ġ�� ����Ѵ�.
	}
	else
	{
		m_nLine = 0;
		for (int i = 20; i <= 60; i += 5)
			ShowFont(pDC, i);
	}
}


// CShapeExView ����

#ifdef _DEBUG
void CShapeExView::AssertValid() const
{
	CView::AssertValid();
}

void CShapeExView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShapeExDoc* CShapeExView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShapeExDoc)));
	return (CShapeExDoc*)m_pDocument;
}
#endif //_DEBUG


// CShapeExView �޽��� ó����

// �簢���� ����Ѵ�.
void CShapeExView::ShowRect(CDC* pDC)
{
	CPen myPen, *pOldPen;
	CBrush myBrush, *pOldBrush;
	myPen.CreatePen(PS_SOLID, 5, RGB(0, 0, 255)); // ���� 5 �ȼ��� �Ķ��� �� ����
	myBrush.CreateSolidBrush(RGB(255, 255, 0));	//����� �ָ��� �귯�� ����

	pOldPen = pDC->SelectObject(&myPen);	// �Ķ��� �� ����
	pOldBrush = pDC->SelectObject(&myBrush);	// ����� �귯�� ����
	pDC->Rectangle(10, 10, 300, 200);	// ���� �簢���� �׸���.
	pDC->SelectObject(pOldPen);	// ���� �� ��ȯ
	pDC->SelectObject(pOldBrush);	// ���� �귯�� ��ȯ

	// Ŀ���� ���� ��ġ�� ����� �������� �����.
	CRect rc;
	GetClientRect(rc);
	m_rcStatus.SetRect(rc.left, rc.Height() - 30, rc.right, rc.bottom);	// ������ ��ġ ����
	pDC->DrawFrameControl(m_rcStatus, DFC_BUTTON | DFCS_BUTTONPUSH, 0);
}

// Ÿ���� ����Ѵ�.
void CShapeExView::ShowCircle(CDC* pDC)
{
	CPen myPen, *pOldPen;
	CBrush *pOldBrush;
	myPen.CreatePen(PS_DOT, 1, RGB(255, 0, 0));	// ������ ���� �� ����
	pOldPen = pDC->SelectObject(&myPen);	// ������ ���� �� ����
	pOldBrush = (CBrush*)pDC->SelectStockObject(LTGRAY_BRUSH);	// ���� �귯�� ����
	pDC->Ellipse(150, 100, 300, 300);	// Ÿ���� �׸���.
	pDC->SelectObject(pOldPen);	// ���� �� ��ȯ
	pDC->SelectObject(pOldBrush);	// ���� �� ��ȯ
}

// ���� ����Ѵ�.
void CShapeExView::ShowLine(CDC* pDC)
{
	CPen* pOldPen;
	pOldPen = (CPen*)pDC->SelectStockObject(BLACK_PEN);	//���� �� ���
	pDC->MoveTo(10, 10);	// ���������� �̵�
	pDC->LineTo(300, 200);	// ���� �׸���.

	pDC->MoveTo(10, 200);	// ���������� �̵�
	pDC->LineTo(300, 10);	// ���� �׸���.
	pDC->SelectObject(pOldPen);	// ���� �� ��ȯ
}

// ������ ����� ����Ѵ�.
void CShapeExView::ShowRainbow(CDC* pDC)
{
	COLORREF color;
	CPen myPen, *pOldPen;
	for (int i = 0; i < 20; i++)
	{
		color = RGB(rand() % 256, rand() % 256, rand() % 256);	// ������ ���� ����
		myPen.CreatePen(PS_SOLID, 3, color);	// �� ������Ʈ ����
		pOldPen = pDC->SelectObject(&myPen);	// ������ �� ����
		pDC->Arc(300 + i, 50 + i, 500 - i, 260 - i, 600, 160, 0, 160);	// ��ȣ�� �׸���.
		pDC->SelectObject(pOldPen);	// ���� �� ��ȯ
		myPen.DeleteObject();	// ������ ���� �����Ѵ�.(�Ҹ��ڰ� ȣ����� �ʰ� for������ ���ƾ� �ϱ⶧���� DeleteObject() ���� ȣ��)
	}
}


void CShapeExView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (m_bShape)
	{
		m_curPos = point;	// ���� Ŀ���� ��ġ�� ����

		InvalidateRect(m_rcStatus, FALSE);	// m_rcStatus�� �簢�� ������ �ٽ� �׸���.
	}

	CView::OnMouseMove(nFlags, point);
}


// ���콺�� �����϶� ���� ����� Ŀ���� ��ġ�� ���� ȭ�鿡 ���
void CShapeExView::ShowCursorPos(CDC* pDC)
{
	CString str;
	str.Format(_T("X��ǥ:%3d, Y��ǥ:%3d"), m_curPos.x, m_curPos.y);
	//pDC->SetBkMode(OPAQUE);	// ��� ������ ��� ����(default)
	pDC->SetBkMode(TRANSPARENT);	// ��� ���� ��� ����
	pDC->SetTextColor(RGB(0, 0, 255));	// �ؽ�Ʈ ���� ����
	pDC->DrawText(str, m_rcStatus, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	// �ؽ�Ʈ�� ����Ѵ�.
}


// ũ�⿡ ���� ���� ��ȭ�� ȭ�鿡 ���
void CShapeExView::ShowFont(CDC* pDC, int nPoint)
{
	TEXTMETRIC tm;	// ����ü
	CFont myFont, *pOldFont;
	// ��Ʈ ����
	myFont.CreateFont(nPoint, 0, 0, 0, 700, TRUE, TRUE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	pOldFont = pDC->SelectObject(&myFont);	// ���ο� ��Ʈ ����
	pDC->SetBkMode(TRANSPARENT);	// ���� ��� ����
	pDC->TextOutW(10, m_nLine, _T("�ѱ��������������"));	// �ؽ�Ʈ ���
	pDC->GetTextMetrics(&tm);	// ���� ȭ�鿡 ��µ� �ؽ�Ʈ�� ���� ����
	pDC->SelectObject(pOldFont);	// ��ȯ
	m_nLine += (tm.tmHeight + tm.tmExternalLeading);	// ������ ��ü ����
}

void CShapeExView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	m_bShape = !m_bShape;	// ���콺 ���� ��ư�� ���� ������ m_bShape ���� ����ȴ�.
	Invalidate();	// Ŭ���̾�Ʈ ������ �ٽ� �׸���.

	CView::OnRButtonDown(nFlags, point);
}


BOOL CShapeExView::OnEraseBkgnd(CDC* pDC)	// Ŭ���̾�Ʈ ������ �����Ѵ�.
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CBrush myBrush, *pOldBrush;
	myBrush.CreateHatchBrush(HS_VERTICAL, RGB(0, 255, 0));	// ���� ��Ī �귯�� ����
	pOldBrush = pDC->SelectObject(&myBrush);	// ���� ��Ī �귯�� ����
	CRect rc;
	GetClientRect(rc);	// Ŭ���̾�Ʈ ������ �簢�� ���� ����
	pDC->FillRect(rc, &myBrush);	// Ŭ���̾�Ʈ ������ ���� ��Ī �귯�÷� ä���.
	pDC->SelectObject(pOldBrush);	// ��ȯ
	return TRUE;
}
