
// ActView.cpp : CActView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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

// CActView 생성/소멸

CActView::CActView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CActView::~CActView()
{
}

BOOL CActView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CRichEditView::PreCreateWindow(cs);
}

void CActView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// 인쇄 여백(720 twips = 1/2 inch)을 설정합니다.
	SetMargins(CRect(720, 720, 720, 720));
}

void CActView::OnDestroy()
{
	// 소멸 중인 항목을 비활성화합니다.
	// 분할 창이 사용될 경우 이 작업은 중요합니다.
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
   CRichEditView::OnDestroy();
}


// OLE 서버 지원

// 다음 명령 처리기는 표준 키보드 사용자 인터페이스를 제공하여
//  내부 편집 세션을 취소합니다.  그러면
//  서버(컨테이너가 아님)가 비활성화됩니다.
void CActView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}


// CActView 진단

#ifdef _DEBUG
void CActView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CActView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CActDoc* CActView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CActDoc)));
	return (CActDoc*)m_pDocument;
}
#endif //_DEBUG


// CActView 메시지 처리기
