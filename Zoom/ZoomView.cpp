
// ZoomView.cpp : CZoomView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CZoomView ����/�Ҹ�

CZoomView::CZoomView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_nZoom = 1000;	// �ʱⰪ�� ũ�� Ŭ���� ��Ʈ�� ũ��� �۰� ��µȴ�.
}

CZoomView::~CZoomView()
{
}

BOOL CZoomView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CZoomView �׸���

void CZoomView::OnDraw(CDC* pDC)
{
	CZoomDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CenterImage(pDC);
}


// CZoomView ����

#ifdef _DEBUG
void CZoomView::AssertValid() const
{
	CView::AssertValid();
}

void CZoomView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CZoomDoc* CZoomView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CZoomDoc)));
	return (CZoomDoc*)m_pDocument;
}
#endif //_DEBUG


// CZoomView �޽��� ó����


void CZoomView::CenterImage(CDC* pDC)
{
	CBitmap myBit, *pOldBit;
	CDC memDC;	// �޸� DC
	BITMAP bm;	// GDI ��Ʈ��(DDB)�� ������ ������ ����ü ����
	myBit.LoadBitmapW(IDB_IMAGE);	// ��Ʈ�� ���ҽ��� �ε��Ѵ�. -> GDI ��Ʈ�� ����
	myBit.GetObject(sizeof(BITMAP), &bm);	// ��Ʈ�� ������Ʈ�� ���� ������ ��´�.
	memDC.CreateCompatibleDC(pDC);	// ȭ�� DC�� ȣȯ�Ǵ� DC ����, �޸� DC�� ȭ���� ��Ÿ���� �޸� ���� ������ �Ѵ�.
	pOldBit = memDC.SelectObject(&myBit);	// �޸� DC�� ��Ʈ�� ����
	CRect rc;
	GetClientRect(rc);
	int x = (rc.Width() - bm.bmWidth) / 2;
	int y = (rc.Height() - bm.bmHeight) / 2;

	pDC->BitBlt(x, y,						// ��� DC �簢���� ���� ������ ��ǥ
		bm.bmWidth, bm.bmHeight,	// ���۵Ǵ� ��Ʈ���� ���� ����
		&memDC,						// ���� DC
		0, 0,						// ���� ��Ʈ���� ���� ������ ��ǥ
		SRCCOPY);					// ROP �ڵ�
	memDC.SelectObject(pOldBit);	// ��ȯ
}


BOOL CZoomView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	SetCursor(AfxGetApp()->LoadCursorW(GID_ZOOM));	// ���ο� Ŀ�� ����
	return TRUE;
}




void CZoomView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	CRect rc;
	GetClientRect(rc);
	pDC->SetMapMode(MM_ISOTROPIC);	// ���θ�� ����
	pDC->SetWindowExt(m_nZoom, m_nZoom);	// ������ ũ��(Extent) ����
	pDC->SetViewportExt(rc.Width(), rc.Height());	// ����Ʈ ũ��(Extent) ����
}


void CZoomView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	m_nZoom /= 2;	// m_nZoom ���� �۾����ϱ� ��Ʈ���� Ȯ��Ǿ� ��µȴ�.
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void CZoomView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	m_nZoom *= 2;	// m_nZoom ���� Ŀ���ϱ� ��Ʈ���� ��ҵǾ� ��µȴ�.
	Invalidate();
	CView::OnRButtonDown(nFlags, point);
}


void CZoomView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CClientDC dc(this);
	COLORREF color;
	color = dc.GetPixel(point);	// ���� Ŀ���� ��ġ�� �ȼ��� RGB ������ ��´�.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CStatusBar* pStatus = pFrame->GetStatusBar();
	
	CString strInfo;
	strInfo.Format(_T("X:%3d, Y:%3d / R:%3d, G:%3d,B:%d"),
		point.x, point.y, GetRValue(color), GetGValue(color), GetBValue(color));
	pStatus->SetPaneText(1, strInfo);
	
	CView::OnMouseMove(nFlags, point);
}
