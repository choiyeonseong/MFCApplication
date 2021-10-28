
// ShapeView.cpp : CShapeView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CShapeView ����/�Ҹ�

CShapeView::CShapeView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CShapeView::~CShapeView()
{
}

BOOL CShapeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CShapeView �׸���

void CShapeView::OnDraw(CDC* pDC)
{
	CShapeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CBrush myBrush(RGB(0, 0, 255));	// �����ڸ� �̿��Ͽ� �Ķ��� �귯�ø� ����
	CBrush* p01dBrush;	// ���� �귯�ø� ������ ����
	p01dBrush = pDC->SelectObject(&myBrush);	// �Ķ��� �귯�� ����
	pDC->Rectangle(m_Rect);	// m_Rect ũ���� �Ķ� �簢�� �׸���
	pDC->SelectObject(p01dBrush);	// ���� �귯�÷� ȯ��

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CShapeView ����

#ifdef _DEBUG
void CShapeView::AssertValid() const
{
	CView::AssertValid();
}

void CShapeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShapeDoc* CShapeView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShapeDoc)));
	return (CShapeDoc*)m_pDocument;
}
#endif //_DEBUG


// CShapeView �޽��� ó����


void CShapeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	//CRect rcClient;
	//GetClientRect(rcClient);	// Ŭ���̾�Ʈ ������ �簢�� ����
	//
	//CClientDC dc(this);	// ȭ��(Ŭ���̾�Ʈ ����)�� ����Ҽ� �ִ� ���� ����
	//CBrush myBrush(RGB(255, 0, 0));	// �����ڸ� �̿��Ͽ� ������ �귯�ø� ����
	//CBrush* p01dBrush;	// ���� �귯���� ������ ����

	//p01dBrush = dc.SelectObject(&myBrush);	// �ð��� �귯�� ����
	//dc.Ellipse(rcClient);		// Ŭ���̾�Ʈ ���� ũ���� ���� Ÿ�� �׸���
	//dc.SelectObject(p01dBrush);	// ���� �귯�÷� ȯ��

	// Ŭ���� Ŀ�� ��ġ�� �������� �¿� 100�ȼ�, ����  100�ȼ� ũ���� �簢�� ����
	m_Rect = CRect(point.x - 100, point.y - 100, point.x + 100, point.y + 100);

	Invalidate();	// ���������� �޽��� WM_PAINT�� �߻���Ŵ

	CView::OnLButtonDown(nFlags, point);
}
