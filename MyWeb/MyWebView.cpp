
// MyWebView.cpp : CMyWebView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MyWeb.h"
#endif

#include "MyWebDoc.h"
#include "MyWebView.h"
#include "BookmarkDlg.h"
#include "MainFrm.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyWebView

IMPLEMENT_DYNCREATE(CMyWebView, CFormView)

BEGIN_MESSAGE_MAP(CMyWebView, CFormView)
	ON_COMMAND(ID_BACK, &CMyWebView::OnBack)
	ON_COMMAND(ID_NEXT, &CMyWebView::OnNext)
	ON_COMMAND(ID_STOP, &CMyWebView::OnStop)
	ON_WM_SIZE()
	ON_COMMAND(ID_BOOKMARK, &CMyWebView::OnBookmark)
	ON_COMMAND(ID_BOOKMARK_VIEW, &CMyWebView::OnBookmarkView)
END_MESSAGE_MAP()

// CMyWebView ����/�Ҹ�

CMyWebView::CMyWebView()
	: CFormView(IDD_MYWEB_FORM)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMyWebView::~CMyWebView()
{
}

void CMyWebView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_Web);
}

BOOL CMyWebView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CMyWebView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	m_Web.GoHome();	// �̹� ��ϵ� Ȩ �������� �̵��Ѵ�.

}


// CMyWebView ����

#ifdef _DEBUG
void CMyWebView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMyWebView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMyWebDoc* CMyWebView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyWebDoc)));
	return (CMyWebDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyWebView �޽��� ó����


void CMyWebView::OnBack()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_Web.GoBack();	// ���� �������� �̵�
}


void CMyWebView::OnNext()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_Web.GoForward();	// ���� �������� �̵�
}


void CMyWebView::OnStop()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_Web.Stop();	// ����
}


void CMyWebView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if (m_Web.GetSafeHwnd())		
		m_Web.MoveWindow(0, 0, cx, cy);
}


void CMyWebView::OnBookmark()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	static int count = AfxGetApp()->GetProfileInt(_T("�ϸ�ũ"), _T("Count"), 0);	// �ϸ�ũ ����
	if (count == 0)	// ���α׷��� ó�� ����Ǵ� �ý����� ���
		count = 1;	// ������Ʈ���� ��ϵ� ������ �����Ƿ�

	CString strUrl, entry;
	strUrl = _T("[") + m_Web.get_LocationName() + _T("]");	// �������� ����
	strUrl += m_Web.get_LocationURL();	// ���ͳ� �ּ�
	// �ϸ�ũ�� ������ ������Ʈ���� �����Ѵ�
	AfxGetApp()->WriteProfileInt(_T("�ϸ�ũ"), _T("Count"), count);

	entry.Format(_T("URL %d"), count);
	// ���������� ����� ���ͳ��ּҸ� ������Ʈ���� �����Ѵ�
	AfxGetApp()->WriteProfileString(_T("�ϸ�ũ"), entry, strUrl);
	count++;	// �ϸ�ũ ���� ����
}

void CMyWebView::OnBookmarkView()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CBookmarkDlg dlg;
	dlg.DoModal();
}
BEGIN_EVENTSINK_MAP(CMyWebView, CFormView)
	ON_EVENT(CMyWebView, IDC_EXPLORER1, 113, CMyWebView::OnTitlechangeExplorer1, VTS_BSTR)
	ON_EVENT(CMyWebView, IDC_EXPLORER1, 102, CMyWebView::OnStatustextchangeExplorer1, VTS_BSTR)
	ON_EVENT(CMyWebView, IDC_EXPLORER1, 108, CMyWebView::OnProgresschangeExplorer1, VTS_I4 VTS_I4)
	ON_EVENT(CMyWebView, IDC_EXPLORER1, 106, CMyWebView::OnDownloadbeginExplorer1, VTS_NONE)
	ON_EVENT(CMyWebView, IDC_EXPLORER1, 104, CMyWebView::OnDownloadcompleteExplorer1, VTS_NONE)
END_EVENTSINK_MAP()


void CMyWebView::OnTitlechangeExplorer1(LPCTSTR Text)	// �������� �� ����Ʈ�� ������ ĸ�ǹٿ� ���
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	GetParentFrame()->SetWindowText(Text);	// ĸ�ǹٿ� Ÿ��Ʋ ���
}


void CMyWebView::OnStatustextchangeExplorer1(LPCTSTR Text)	// ���¹��� ù��° ���ο� ���ӻ��� ���
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CStatusBar* pStatus = (CStatusBar*)GetParentFrame()->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	pStatus->SetPaneText(0, Text);	// ���¹��� ù��° ���ο� Text ���ڿ� ���
}


void CMyWebView::OnProgresschangeExplorer1(long Progress, long ProgressMax)	// ���¹��� �ι�° ���ο� �۾� ������ ǥ��
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_Progress.SetRange(0, (int)ProgressMax);	// ������� ���� ����
	pFrame->m_Progress.SetPos(Progress);	// ������� ���� ��ġ ����
}

// �ٿ�ε� ����/���ῡ ���� �ִϸ��̼� �����̱�(ERROR)
void CMyWebView::OnDownloadbeginExplorer1()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CAnimateCtrl* pAnimate = (CAnimateCtrl*)AfxGetMainWnd()->GetDescendantWindow(IDW_ANIMATE);	// �ִϸ��̼� ��Ʈ���� ��ü ������
	pAnimate->Play(0, -1, -1);	//  �ִϸ��̼� ����
}


void CMyWebView::OnDownloadcompleteExplorer1()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CAnimateCtrl* pAnimate = (CAnimateCtrl*)AfxGetMainWnd()->GetDescendantWindow(IDW_ANIMATE);	// �ִϸ��̼� ��Ʈ���� ��ü ������
	pAnimate->Stop();	// �ִϸ��̼� ����
	pAnimate->Seek(0);	// �ִϸ��̼� ó������ �̵�
}
