
// ActView.cpp : CActView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Act.h"
#endif

#include "ActDoc.h"
#include "CntrItem.h"
#include "resource.h"
#include "ActView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CActView

IMPLEMENT_DYNCREATE(CActView, CRichEditView)

BEGIN_MESSAGE_MAP(CActView, CRichEditView)
	ON_WM_DESTROY()
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, &CActView::OnCancelEditSrvr)
END_MESSAGE_MAP()

// CActView ����/�Ҹ�

CActView::CActView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CActView::~CActView()
{
}

BOOL CActView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CRichEditView::PreCreateWindow(cs);
}

void CActView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// �μ� ����(720 twips = 1/2 inch)�� �����մϴ�.
	SetMargins(CRect(720, 720, 720, 720));
}

void CActView::OnDestroy()
{
	// �Ҹ� ���� �׸��� ��Ȱ��ȭ�մϴ�.
	// ���� â�� ���� ��� �� �۾��� �߿��մϴ�.
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
   CRichEditView::OnDestroy();
}


// OLE ���� ����

// ���� ��� ó����� ǥ�� Ű���� ����� �������̽��� �����Ͽ�
//  ���� ���� ������ ����մϴ�.  �׷���
//  ����(�����̳ʰ� �ƴ�)�� ��Ȱ��ȭ�˴ϴ�.
void CActView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}


// CActView ����

#ifdef _DEBUG
void CActView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CActView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CActDoc* CActView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CActDoc)));
	return (CActDoc*)m_pDocument;
}
#endif //_DEBUG


// CActView �޽��� ó����
