
// GhostView.cpp : CGhostView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Ghost.h"
#endif

#include "GhostDoc.h"
#include "GhostView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGhostView

IMPLEMENT_DYNCREATE(CGhostView, CView)

BEGIN_MESSAGE_MAP(CGhostView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGhostView ����/�Ҹ�

CGhostView::CGhostView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CGhostView::~CGhostView()
{
}

BOOL CGhostView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CGhostView �׸���

void CGhostView::OnDraw(CDC* /*pDC*/)
{
	CGhostDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}

void CGhostView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGhostView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGhostView ����

#ifdef _DEBUG
void CGhostView::AssertValid() const
{
	CView::AssertValid();
}

void CGhostView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGhostDoc* CGhostView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGhostDoc)));
	return (CGhostDoc*)m_pDocument;
}
#endif //_DEBUG


// CGhostView �޽��� ó����


BOOL CGhostView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	::SetCursor(AfxGetApp()->LoadCursor(IDC_GHOST));	// ���θ��� Ŀ�� �ε� (*.cur)
	return TRUE;
}


void CGhostView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	// ĳ�� ���� �� ��ġ ����
	CreateSolidCaret(5, 30);	// 5x30 ũ���� ĳ�� ����
	SetCaretPos(point);	// ĳ���� ��ġ�� ���콺 ���� ��ư�� ���� ��ġ�� �����Ѵ�.
	ShowCaret();		// ĳ���� ȭ�鿡 �����ش�.

	// ���콺 Ŀ���� ���� ��ġ ���
	CString strInfo;
	strInfo.Format(_T("���� ��ġ\r\n X = %d, Y = %d"), point.x, point.y);
	MessageBox(strInfo, _T("���콺 ���� ��ư ����"), MB_ICONINFORMATION);
	
	CView::OnLButtonDown(nFlags, point);
}

void CGhostView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	// ĳ���� ������� �ϰ� �Ҹ��Ų��.
	HideCaret();	// ĳ���� ȭ�鿡 ������ �ʰ� �Ѵ�.
	DestroyCaret();	// ĳ���� �Ҹ��Ѵ�.

	// ���콺 Ŀ���� ���� ��ġ ���
	CString strInfo;
	strInfo.Format(_T("���� ��ġ\r\n X = %d, Y = %d"), point.x, point.y);
	MessageBox(strInfo, _T("���콺 ���� ��ư ����"), MB_ICONINFORMATION);

	CView::OnRButtonDown(nFlags, point);
}


void CGhostView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CPoint ptCurPos;	// ���� Ŀ���� ��ġ
	if (::GetCursorPos(&ptCurPos))	// ���� Ŀ�� ��ġ�� ��´�.(��ũ�� ��ǥ)
	{
		switch (nChar)	// Ű��(nChar)�� ���� ���ο� Ŀ�� ��ġ�� �����Ѵ�.
		{
		case VK_LEFT:
			ptCurPos.x -= 30;
			::SetCursorPos(ptCurPos.x, ptCurPos.y);
			break;
		case VK_RIGHT:
			ptCurPos.x += 30;
			::SetCursorPos(ptCurPos.x, ptCurPos.y);
			break;
		case VK_UP:
			ptCurPos.y -= 30;
			::SetCursorPos(ptCurPos.x, ptCurPos.y);
			break;
		case VK_DOWN:
			ptCurPos.y += 30;
			::SetCursorPos(ptCurPos.x, ptCurPos.y);
			break;
		}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
