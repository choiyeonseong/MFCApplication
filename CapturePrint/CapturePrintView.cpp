
// CapturePrintView.cpp : CCapturePrintView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "CapturePrint.h"
#endif

#include "CapturePrintDoc.h"
#include "CapturePrintView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCapturePrintView

IMPLEMENT_DYNCREATE(CCapturePrintView, CView)

BEGIN_MESSAGE_MAP(CCapturePrintView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SCREEN_CAPTURE, &CCapturePrintView::OnScreenCapture)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

// CCapturePrintView ����/�Ҹ�

CCapturePrintView::CCapturePrintView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_Tracker.m_rect.SetRect(0, 0, 100, 100);	// ��ü m_Tracker �ʱ�ȭ
}

CCapturePrintView::~CCapturePrintView()
{
}

BOOL CCapturePrintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CCapturePrintView �׸���

void CCapturePrintView::OnDraw(CDC* pDC)
{
	CCapturePrintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CBrush br(RGB(0, 0, 255));
	CBrush* pOld = pDC->SelectObject(&br);
	CRect rcEllipse;
	m_Tracker.GetTrueRect(rcEllipse);
	pDC->Ellipse(rcEllipse);	// Ÿ�� ���
	m_Tracker.Draw(pDC);		// Ʈ��Ŀ �簢���� �׸���
	pDC->SelectObject(pOld);
}


// CCapturePrintView �μ�

BOOL CCapturePrintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CCapturePrintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CCapturePrintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CCapturePrintView ����

#ifdef _DEBUG
void CCapturePrintView::AssertValid() const
{
	CView::AssertValid();
}

void CCapturePrintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCapturePrintDoc* CCapturePrintView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCapturePrintDoc)));
	return (CCapturePrintDoc*)m_pDocument;
}
#endif //_DEBUG


// CCapturePrintView �޽��� ó����

// [��ü ȭ�� ĸó >>] �޴��� ������ ���
void CCapturePrintView::OnScreenCapture()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CBitmap bitmap;
	CClientDC screenDC(NULL);	// ���� ȭ�鿡 ���� DC
	CDC memDC;
	CRect rect;

	CWnd* pWnd = CWnd::GetDesktopWindow();	// ����ȭ�鿡 ���� ��ü ������
	memDC.CreateCompatibleDC(&screenDC);
	pWnd->GetWindowRect(rect);		// ��ü ȭ���� ũ�⸦ ��´�
	// ��ü ȭ���� ������ ��Ʈ�� ����
	bitmap.CreateCompatibleBitmap(&screenDC, rect.Width(), rect.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);	// �޸� DC�� ��Ʈ�� ����
	// ���� ȭ�鿡 ��µ� ������ �޸� DC�� ����
	memDC.BitBlt(0, 0, rect.Width(), rect.Height(), &screenDC, 0, 0, SRCCOPY);

	// Ŭ�����忡 ĸó�� ��Ʈ���� ����
	pWnd->OpenClipboard();	// Ŭ������ ����
	EmptyClipboard();	// ���� Ŭ�����忡 �ִ� ���� ����
	SetClipboardData(CF_BITMAP, bitmap.GetSafeHandle());	// ĸó�� ��Ʈ�� ����
	CloseClipboard();	// Ŭ�����带 �ݴ´�

	memDC.SelectObject(pOldBitmap);	// ��ȯ
	bitmap.Detach();	// ��Ʈ�� ��ü ����
}


void CCapturePrintView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
	CBitmap bitmap;
	CWindowDC dc(pFrame);	// ���� �����쿡 ���� DC
	CDC memDC;
	CRect rect;

	memDC.CreateCompatibleDC(&dc);
	pFrame->GetWindowRect(rect);	// ���� �������� ũ�� ���� ����.
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);	// �޸� DC�� ��Ʈ�� ����
	memDC.BitBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);

	// �޸� DC�� ĸó�� ��Ʈ���� ����Ʈ DC�� �����Ѵ�.
	pDC->SetMapMode(MM_ANISOTROPIC);	// ���� ��� ����
	pDC->SetWindowExt(memDC.GetDeviceCaps(LOGPIXELSX), memDC.GetDeviceCaps(LOGPIXELSY));
	pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX), pDC->GetDeviceCaps(LOGPIXELSY));
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
	memDC.SelectObject(pOldBitmap);	// ��ȯ
	bitmap.Detach();	// ��Ʈ�� ��ü ����


	//CView::OnPrint(pDC, pInfo);
}


void CCapturePrintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	BOOL bRet = m_Tracker.HitTest(point);	// ���� Ŀ���� ��ġ�� ���� �˾Ƴ���
	if (bRet != CRectTracker::hitNothing)	// Ʈ��Ŀ �簢�� ���ο� Ŀ���� ��ġ�� ���
	{
		m_Tracker.m_nStyle = CRectTracker::resizeInside | CRectTracker::solidLine;	// Ʈ��Ŀ �簢���� ���� ����
		m_Tracker.Track(this, point, TRUE);	// �巡��&��� ó��
		Invalidate();
	}
	else
	{	// Ʈ��Ŀ �簢�� �ܺο� Ŀ���� ��ġ�� ���
		m_Tracker.m_nStyle = 0;	// Ʈ��Ŀ �簢���� �Ⱥ��̰� �Ѵ�.
		Invalidate();
	}

	CView::OnLButtonDown(nFlags, point);
}


BOOL CCapturePrintView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if ((m_Tracker.m_nStyle & CRectTracker::resizeInside) && (m_Tracker.SetCursor(this, nHitTest)))	// Ʈ��Ŀ �簢������ Ŀ�� ��� ����
		return TRUE;

	return CView::OnSetCursor(pWnd, nHitTest, message);
}
