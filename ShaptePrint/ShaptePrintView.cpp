
// ShaptePrintView.cpp : CShaptePrintView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ShaptePrint.h"
#endif

#include "ShaptePrintDoc.h"
#include "ShaptePrintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CShaptePrintView

IMPLEMENT_DYNCREATE(CShaptePrintView, CView)

BEGIN_MESSAGE_MAP(CShaptePrintView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CShaptePrintView 생성/소멸

CShaptePrintView::CShaptePrintView()
	: m_nPage(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CShaptePrintView::~CShaptePrintView()
{
}

BOOL CShaptePrintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CShaptePrintView 그리기

void CShaptePrintView::OnDraw(CDC* pDC)
{
	CShaptePrintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int i, j;
	j = pDoc->m_ellipseArray.GetUpperBound();
	for ( i = 0; i < j; i++)
	{
		pDC->Ellipse(pDoc->m_ellipseArray[i]);
	}
}


// CShaptePrintView 인쇄

BOOL CShaptePrintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	pInfo->SetMaxPage(GetDocument()->m_ellipseArray.GetUpperBound() / CShaptePrintDoc::nLinesPerPage + 1);	// 페이지 수 계산
	
	return DoPreparePrinting(pInfo);
}

void CShaptePrintView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
	int nMaxPage = pInfo->GetMaxPage();
	CString strInfo;
	strInfo.Format(_T("[KITRI] 총 %d 페이지 중 %d%d페이지\n[KITRI] 총 %d 페이지 중 %%d-%%d페이지"), nMaxPage, nMaxPage);
	pInfo->m_strPageDesc = strInfo;
}

void CShaptePrintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CShaptePrintView 진단

#ifdef _DEBUG
void CShaptePrintView::AssertValid() const
{
	CView::AssertValid();
}

void CShaptePrintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShaptePrintDoc* CShaptePrintView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShaptePrintDoc)));
	return (CShaptePrintDoc*)m_pDocument;
}
#endif //_DEBUG


// CShaptePrintView 메시지 처리기


void CShaptePrintView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	pDC->SetMapMode(MM_LOENGLISH);	// 0.01 인치

	CView::OnPrepareDC(pDC, pInfo);
}


void CShaptePrintView::PageHeader_Footer(CDC* pDC)
{
	// 머리글 설정
	CString str;
	CPoint point(0, 0);
	pDC->TextOut(point.x, point.y, _T("[KITRI] 원을 출력합니다."));

	// 꼬리글 설정
	point = CPoint(0, -1100);
	CShaptePrintDoc* pDoc = GetDocument();
	str.Format(_T("문서:%s"), (LPCWSTR)pDoc->GetTitle());
	pDC->TextOutW(point.x, point.y, str);

	str.Format(_T("페이지:%d"), m_nPage);
	point.x = 650;
	pDC->TextOutW(point.x, point.y, str);
}


void CShaptePrintView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString str;
	CFont font;
	OnPrepareDC(pDC, pInfo);	// 맵핑모드 설정
	CShaptePrintDoc * pDoc = GetDocument();
	m_nPage = pInfo->m_nCurPage;	// PageHeader_Footer()에서 사용
	// 바탕체 (트루타입 폰트) 설정
	font.CreateFontW(-16, 0, 0, 0, 400, TRUE, TRUE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("바탕체"));
	CFont* pOldFont = (CFont*)(pDC->SelectObject(&font));
	PageHeader_Footer(pDC);	// 머리말과 꼬리말 출력
	pDC->SelectObject(pOldFont);
	CView::OnPrint(pDC, pInfo);
}
