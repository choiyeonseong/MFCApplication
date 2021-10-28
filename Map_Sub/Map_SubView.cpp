
// Map_SubView.cpp : CMap_SubView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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

// CMap_SubView 생성/소멸

CMap_SubView::CMap_SubView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMap_SubView::~CMap_SubView()
{
}

BOOL CMap_SubView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMap_SubView 그리기

void CMap_SubView::OnDraw(CDC* /*pDC*/)
{
	CMap_SubDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMap_SubView 진단

#ifdef _DEBUG
void CMap_SubView::AssertValid() const
{
	CView::AssertValid();
}

void CMap_SubView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMap_SubDoc* CMap_SubView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMap_SubDoc)));
	return (CMap_SubDoc*)m_pDocument;
}
#endif //_DEBUG


// CMap_SubView 메시지 처리기


void CMap_SubView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// 상태편 프로그램이 생성한 파일 맵핑 오브젝트("kitri")를 오픈한다.
	m_Map = OpenFileMapping(FILE_MAP_READ, FALSE, _T("kitri"));
	if (!m_Map)
		AfxMessageBox(_T("파일 맵핑 오브젝트 열기 실패"));
	
	// 파일 맵핑 오브젝트에 무슨 내용이 있는지 보기 위해
	// 맵핑된 뷰 포인터를 얻는다.
	m_ViewData = (CData*)MapViewOfFile(m_Map, FILE_MAP_READ, 0, 0, 0);
	if (!m_ViewData)
		AfxMessageBox(_T("메모리 맵 데이터 읽기 실패"));
	AfxBeginThread(SpyInfo, this);
}


UINT CMap_SubView::SpyInfo(LPVOID lParam)
{
	CMap_SubView* pWnd = (CMap_SubView*)lParam;	// 인자로 전달된 뷰의 객체 포인터
	while (1)	// 상대편이 생성한 파일 맵핑 오브젝트를 지속적으로 감시
	{
		switch (pWnd->m_ViewData->flag)	// 상대편 프로그램의 작업 상태 분석
		{
		case DRAW_READY:	// 그리기 준비 상태이면 계속 감시
			continue;
		case DRAW_START:	// 그리기 작업 중이면 동일하게 선을 출력
		{
			CClientDC dc(pWnd);
			CPen newPen(PS_SOLID, 10, pWnd->m_ViewData->color);	// 색상
			CPen* pOldPen = dc.SelectObject(&newPen);
			dc.MoveTo(pWnd->m_ViewData->start);	// 시작 위치
			dc.LineTo(pWnd->m_ViewData->pt);	// 현재 위치
			dc.SelectObject(pOldPen);
			break;
		}
		case DRAW_STOP:	// 송신 프로그램이 종료되어 그리기 작업이 중단되면
			AfxMessageBox(_T("보내는 프로그램이 종료되었음"));
			AfxGetMainWnd()->PostMessage(WM_CLOSE);	// 수신 프로그램 종료
			return 0;
		}	// switch
	}
	return 0;
}
