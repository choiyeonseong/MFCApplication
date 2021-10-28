
// Map_SubView.cpp : CMap_SubView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Map_Sub.h"
#endif

#include "Map_SubDoc.h"
#include "Map_SubView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMap_SubView

IMPLEMENT_DYNCREATE(CMap_SubView, CView)

BEGIN_MESSAGE_MAP(CMap_SubView, CView)
END_MESSAGE_MAP()

// CMap_SubView ����/�Ҹ�

CMap_SubView::CMap_SubView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMap_SubView::~CMap_SubView()
{
}

BOOL CMap_SubView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMap_SubView �׸���

void CMap_SubView::OnDraw(CDC* /*pDC*/)
{
	CMap_SubDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CMap_SubView ����

#ifdef _DEBUG
void CMap_SubView::AssertValid() const
{
	CView::AssertValid();
}

void CMap_SubView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMap_SubDoc* CMap_SubView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMap_SubDoc)));
	return (CMap_SubDoc*)m_pDocument;
}
#endif //_DEBUG


// CMap_SubView �޽��� ó����


void CMap_SubView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	// ������ ���α׷��� ������ ���� ���� ������Ʈ("kitri")�� �����Ѵ�.
	m_Map = OpenFileMapping(FILE_MAP_READ, FALSE, _T("kitri"));
	if (!m_Map)
		AfxMessageBox(_T("���� ���� ������Ʈ ���� ����"));
	
	// ���� ���� ������Ʈ�� ���� ������ �ִ��� ���� ����
	// ���ε� �� �����͸� ��´�.
	m_ViewData = (CData*)MapViewOfFile(m_Map, FILE_MAP_READ, 0, 0, 0);
	if (!m_ViewData)
		AfxMessageBox(_T("�޸� �� ������ �б� ����"));
	AfxBeginThread(SpyInfo, this);
}


UINT CMap_SubView::SpyInfo(LPVOID lParam)
{
	CMap_SubView* pWnd = (CMap_SubView*)lParam;	// ���ڷ� ���޵� ���� ��ü ������
	while (1)	// ������� ������ ���� ���� ������Ʈ�� ���������� ����
	{
		switch (pWnd->m_ViewData->flag)	// ����� ���α׷��� �۾� ���� �м�
		{
		case DRAW_READY:	// �׸��� �غ� �����̸� ��� ����
			continue;
		case DRAW_START:	// �׸��� �۾� ���̸� �����ϰ� ���� ���
		{
			CClientDC dc(pWnd);
			CPen newPen(PS_SOLID, 10, pWnd->m_ViewData->color);	// ����
			CPen* pOldPen = dc.SelectObject(&newPen);
			dc.MoveTo(pWnd->m_ViewData->start);	// ���� ��ġ
			dc.LineTo(pWnd->m_ViewData->pt);	// ���� ��ġ
			dc.SelectObject(pOldPen);
			break;
		}
		case DRAW_STOP:	// �۽� ���α׷��� ����Ǿ� �׸��� �۾��� �ߴܵǸ�
			AfxMessageBox(_T("������ ���α׷��� ����Ǿ���"));
			AfxGetMainWnd()->PostMessage(WM_CLOSE);	// ���� ���α׷� ����
			return 0;
		}	// switch
	}
	return 0;
}
