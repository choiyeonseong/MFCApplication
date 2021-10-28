
// ImageLView.cpp : CImageLView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ImageL.h"
#endif

#include "ImageLDoc.h"
#include "ImageLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageLView

IMPLEMENT_DYNCREATE(CImageLView, CView)

BEGIN_MESSAGE_MAP(CImageLView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CImageLView ����/�Ҹ�

CImageLView::CImageLView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_pImage = NULL;


}

CImageLView::~CImageLView()
{
}

BOOL CImageLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CImageLView �׸���

void CImageLView::OnDraw(CDC* pDC)
{
	CImageLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	if (m_pImage->GetSafeHandle())		// ���õ� ��Ʈ���� �ִ��� �Ǵ�
		CenterImage(pDC);				// ��Ʈ���� ���� ���� �߾ӿ� ���
}

void CImageLView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageLView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageLView ����

#ifdef _DEBUG
void CImageLView::AssertValid() const
{
	CView::AssertValid();
}

void CImageLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageLDoc* CImageLView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageLDoc)));
	return (CImageLDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageLView �޽��� ó����

void CImageLView::RefreshImage(CString strPath)	// strPath : ��Ʈ�� ������ ���� ���
{
	if (m_pImage->GetSafeHandle())	// ������ ��µ� ��Ʈ���� �ִ��� �Ǵ�
	{
		m_pImage->DeleteObject();	// ���� ��Ʈ���� ����
		delete m_pImage;			// �� ������ �Ҵ�� �޸� ����
		m_pImage = NULL;
	}
	// ���Ϸκ��� ��Ʈ�� �̹����� �о���δ�.
	m_hBitmap = (HBITMAP)LoadImage(NULL, strPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | DI_DEFAULTSIZE);
	m_pImage = new CBitmap;			// �� �޸� �Ҵ�
	m_pImage->Attach(m_hBitmap);	// ��Ʈ�� �ڵ��� CBitmap�� ����
	Invalidate();					// �� �����츦 ����
}


void CImageLView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if (m_pImage->GetSafeHandle())
	{
		m_pImage->DeleteObject();	// ���� ��Ʈ���� ����
		delete m_pImage;			// �� ������ �Ҵ�� �޸� ����
		m_pImage = NULL;
	}
}

void CImageLView::CenterImage(CDC* pDC)
{
	CDC memDC;	// �޸� DC
	BITMAP bm;	// GDI ��Ʈ��(DDB)�� ������ ������ ����ü ����
	m_pImage->GetObject(sizeof(BITMAP), &bm);	// ��Ʈ�ʿ� ���� ������ ��´�.
	memDC.CreateCompatibleDC(pDC);	// ȭ�� DC�� ȣȯ�Ǵ� �޸� DC ����
	CBitmap* pOldBit = memDC.SelectObject(m_pImage);	// �޸� DC�� ��Ʈ�� ����
	CRect rc;
	GetClientRect(rc);
	int x = (rc.Width() - bm.bmWidth) / 2;
	int y = (rc.Height() - bm.bmHeight) / 2;
	pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBit);	// ��ȯ
}
