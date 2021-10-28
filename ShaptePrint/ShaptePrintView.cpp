
// ShaptePrintView.cpp : CShaptePrintView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CShaptePrintView ����/�Ҹ�

CShaptePrintView::CShaptePrintView()
	: m_nPage(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CShaptePrintView::~CShaptePrintView()
{
}

BOOL CShaptePrintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CShaptePrintView �׸���

void CShaptePrintView::OnDraw(CDC* pDC)
{
	CShaptePrintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	int i, j;
	j = pDoc->m_ellipseArray.GetUpperBound();
	for ( i = 0; i < j; i++)
	{
		pDC->Ellipse(pDoc->m_ellipseArray[i]);
	}
}


// CShaptePrintView �μ�

BOOL CShaptePrintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	pInfo->SetMaxPage(GetDocument()->m_ellipseArray.GetUpperBound() / CShaptePrintDoc::nLinesPerPage + 1);	// ������ �� ���
	
	return DoPreparePrinting(pInfo);
}

void CShaptePrintView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	int nMaxPage = pInfo->GetMaxPage();
	CString strInfo;
	strInfo.Format(_T("[KITRI] �� %d ������ �� %d%d������\n[KITRI] �� %d ������ �� %%d-%%d������"), nMaxPage, nMaxPage);
	pInfo->m_strPageDesc = strInfo;
}

void CShaptePrintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CShaptePrintView ����

#ifdef _DEBUG
void CShaptePrintView::AssertValid() const
{
	CView::AssertValid();
}

void CShaptePrintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShaptePrintDoc* CShaptePrintView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShaptePrintDoc)));
	return (CShaptePrintDoc*)m_pDocument;
}
#endif //_DEBUG


// CShaptePrintView �޽��� ó����


void CShaptePrintView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	pDC->SetMapMode(MM_LOENGLISH);	// 0.01 ��ġ

	CView::OnPrepareDC(pDC, pInfo);
}


void CShaptePrintView::PageHeader_Footer(CDC* pDC)
{
	// �Ӹ��� ����
	CString str;
	CPoint point(0, 0);
	pDC->TextOut(point.x, point.y, _T("[KITRI] ���� ����մϴ�."));

	// ������ ����
	point = CPoint(0, -1100);
	CShaptePrintDoc* pDoc = GetDocument();
	str.Format(_T("����:%s"), (LPCWSTR)pDoc->GetTitle());
	pDC->TextOutW(point.x, point.y, str);

	str.Format(_T("������:%d"), m_nPage);
	point.x = 650;
	pDC->TextOutW(point.x, point.y, str);
}


void CShaptePrintView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CString str;
	CFont font;
	OnPrepareDC(pDC, pInfo);	// ���θ�� ����
	CShaptePrintDoc * pDoc = GetDocument();
	m_nPage = pInfo->m_nCurPage;	// PageHeader_Footer()���� ���
	// ����ü (Ʈ��Ÿ�� ��Ʈ) ����
	font.CreateFontW(-16, 0, 0, 0, 400, TRUE, TRUE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("����ü"));
	CFont* pOldFont = (CFont*)(pDC->SelectObject(&font));
	PageHeader_Footer(pDC);	// �Ӹ����� ������ ���
	pDC->SelectObject(pOldFont);
	CView::OnPrint(pDC, pInfo);
}
