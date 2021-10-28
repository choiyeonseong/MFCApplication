
// MapView.cpp : CMapView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CMapView ����/�Ҹ�

CMapView::CMapView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMapView::~CMapView()
{
}

BOOL CMapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMapView �׸���

void CMapView::OnDraw(CDC* /*pDC*/)
{
	CMapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CMapView ����

#ifdef _DEBUG
void CMapView::AssertValid() const
{
	CView::AssertValid();
}

void CMapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapDoc* CMapView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapDoc)));
	return (CMapDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapView �޽��� ó����


void CMapView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_Map = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, sizeof(CData), _T("kitri"));	// ���� ������Ʈ ����
	if (!m_Map)
		AfxMessageBox(_T("���� ���� ������Ʈ ���� ����"));

	// ������ ���� ���� ������Ʈ�� �����͸� �����ϱ�����
	// ���ε� �� �����͸� ��´�
	m_ViewData = (CData*)MapViewOfFile(m_Map, FILE_MAP_WRITE, 0, 0, 0);	// ���ε� ���Ͽ� ������ �аų� ����
	if (!m_ViewData)
		AfxMessageBox(_T("�޸� �� ���Ͽ� ���� ����"));
	m_ViewData->flag = DRAW_READY;	// �׸��� �غ� ���� ����
}


void CMapView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	// ���콺 Ŀ���� �ش� �����츦 �����
	// ���콺 �޽����� ������ �ֵ��� �Ѵ�.
	SetCapture();
	m_start = point;	// �巡�װ� ���۵� ��ġ ����

	CView::OnLButtonDown(nFlags, point);
}

void CMapView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (GetCapture() == this)	// �巡�� ���̸�
	{
		// ���� 10�� �Ķ��� �Ǽ����� ������� �׸���.
		CClientDC dc(this);
		CPen newPen(PS_SOLID, 10, m_color);
		CPen* pOldPen = dc.SelectObject(&newPen);
		dc.MoveTo(m_start);
		dc.LineTo(point);
		// �޸� �� ���� ���� ����
		m_ViewData->flag = DRAW_START;	// �׸��� ���� ����
		m_ViewData->color = m_color;	// ���� ����
		m_ViewData->start = m_start;	// ���� ��ġ ����
		m_ViewData->pt = point;			// ���� ��ġ ����
		
		m_start = point;				// ó�� ���� ��ġ�� ���� ��ġ ����
		dc.SelectObject(pOldPen);
	}
	CView::OnMouseMove(nFlags, point);
}

void CMapView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (GetCapture() == this)
	{
		m_ViewData->flag = DRAW_READY;	// �׸��� �غ� ���� ����
		ReleaseCapture();	// SetCapture() ����
	}
	CView::OnLButtonUp(nFlags, point);
}




void CMapView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_color = dlg.GetColor();	// ���� ����
	}

	CView::OnRButtonDown(nFlags, point);
}


void CMapView::OnDestroy()
{
	CView::OnDestroy();
	m_ViewData->flag = DRAW_STOP;	// �׸��� �ߴ� ���� ����
	CloseHandle(m_Map);	// �޸� �� ������ �ݴ´�.

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
