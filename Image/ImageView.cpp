
// ImageView.cpp : CImageView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Image.h"
#endif

#include "ImageDoc.h"
#include "ImageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageView

IMPLEMENT_DYNCREATE(CImageView, CView)

BEGIN_MESSAGE_MAP(CImageView, CView)
	ON_COMMAND(ID_IMAGE_CENTER, &CImageView::OnImageCenter)
	ON_COMMAND(ID_IMAGE_TILE, &CImageView::OnImageTile)
	ON_COMMAND(ID_IMAGE_STRETCH, &CImageView::OnImageStretch)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_CENTER, &CImageView::OnUpdateImageCenter)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_STRETCH, &CImageView::OnUpdateImageStretch)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_TILE, &CImageView::OnUpdateImageTile)
END_MESSAGE_MAP()

// CImageView ����/�Ҹ�

CImageView::CImageView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_Type = CENTER;	// ��Ʈ���� Ŭ���̾�Ʈ ������ �߾ӿ� ��ġ
}

CImageView::~CImageView()
{
}

BOOL CImageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CImageView �׸���

void CImageView::OnDraw(CDC* pDC)
{
	CImageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	switch (m_Type)
	{
	case CImageView::CENTER:	// ��Ʈ���� �߾ӿ� ���
		CenterImage(pDC);
		break;
	case CImageView::TILE:		// ��Ʈ���� �ٵ��� ������� ���
		TileImage(pDC);
		break;
	case CImageView::STRETCH:	// ��Ʈ���� Ŭ���̾�Ʈ ������ �°� ���
		StretchImage(pDC);
		break;
	}

}


// CImageView ����

#ifdef _DEBUG
void CImageView::AssertValid() const
{
	CView::AssertValid();
}

void CImageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageDoc* CImageView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageDoc)));
	return (CImageDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageView �޽��� ó����


void CImageView::CenterImage(CDC* pDC)
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


// ��Ʈ���� �ٵ��� ������� ���
void CImageView::TileImage(CDC* pDC)
{
	CBitmap myBit, *pOldBit;
	CDC memDC;
	BITMAP bm;
	myBit.LoadBitmapW(IDB_IMAGE);
	myBit.GetObject(sizeof(BITMAP), &bm);

	memDC.CreateCompatibleDC(pDC);
	pOldBit = memDC.SelectObject(&myBit);
	CRect rc;
	GetClientRect(rc);
	int x, y;
	for (y = 0; y < rc.bottom; y += bm.bmHeight)
		for (x = 0; x < rc.right; x += bm.bmWidth)
			pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBit);
}


// ��Ʈ���� Ŭ���̾�Ʈ ������ ũ�⿡ �°� ���
void CImageView::StretchImage(CDC* pDC)
{
	CBitmap myBit, *pOldBit;
	CDC memDC;
	BITMAP bm;
	myBit.LoadBitmapW(IDB_IMAGE);
	myBit.GetObject(sizeof(BITMAP), &bm);

	memDC.CreateCompatibleDC(pDC);
	pOldBit = memDC.SelectObject(&myBit);
	CRect rc;
	GetClientRect(rc);
	int x = rc.Width();		// Ŭ���̾�Ʈ ������ ��
	int y = rc.Height();	// Ŭ���̾�Ʈ ������ ����
	pDC->StretchBlt(0, 0, 
					x, y, 
					&memDC, 
					0, 0,
					bm.bmWidth, bm.bmHeight, 
					SRCINVERT);
	memDC.SelectObject(pOldBit);
}

// �޴��׸��̳� ���� ��ư�� ���� �� ������ ���� m_Type�� ���� ����ȴ�.

void CImageView::OnImageCenter()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_Type = CENTER;	// ��Ʈ���� �߾ӿ� ��ġ
	Invalidate();
}


void CImageView::OnImageTile()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_Type = TILE;	// ��Ʈ���� �ٵ��� ������� ��ġ
	Invalidate();
}


void CImageView::OnImageStretch()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_Type = STRETCH;
	Invalidate();
}


void CImageView::OnUpdateImageCenter(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(m_Type == CENTER);
}



void CImageView::OnUpdateImageTile(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetRadio(m_Type == TILE);
}


void CImageView::OnUpdateImageStretch(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(m_Type == STRETCH);
}


