
// MyWebView.cpp : CMyWebView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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

// CMyWebView 생성/소멸

CMyWebView::CMyWebView()
	: CFormView(IDD_MYWEB_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

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
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMyWebView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	m_Web.GoHome();	// 이미 등록된 홈 페이지로 이동한다.

}


// CMyWebView 진단

#ifdef _DEBUG
void CMyWebView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMyWebView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMyWebDoc* CMyWebView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyWebDoc)));
	return (CMyWebDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyWebView 메시지 처리기


void CMyWebView::OnBack()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_Web.GoBack();	// 이전 페이지로 이동
}


void CMyWebView::OnNext()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_Web.GoForward();	// 다음 페이지로 이동
}


void CMyWebView::OnStop()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_Web.Stop();	// 멈춤
}


void CMyWebView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_Web.GetSafeHwnd())		
		m_Web.MoveWindow(0, 0, cx, cy);
}


void CMyWebView::OnBookmark()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	static int count = AfxGetApp()->GetProfileInt(_T("북마크"), _T("Count"), 0);	// 북마크 개수
	if (count == 0)	// 프로그램이 처음 실행되는 시스템의 경우
		count = 1;	// 레지스트리에 등록된 내용이 없으므로

	CString strUrl, entry;
	strUrl = _T("[") + m_Web.get_LocationName() + _T("]");	// 웹페이지 제목
	strUrl += m_Web.get_LocationURL();	// 인터넷 주소
	// 북마크의 개수를 레지스트리에 저장한다
	AfxGetApp()->WriteProfileInt(_T("북마크"), _T("Count"), count);

	entry.Format(_T("URL %d"), count);
	// 웹페이지의 제목과 인터넷주소를 레지스트리에 저장한다
	AfxGetApp()->WriteProfileString(_T("북마크"), entry, strUrl);
	count++;	// 북마크 개수 증가
}

void CMyWebView::OnBookmarkView()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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


void CMyWebView::OnTitlechangeExplorer1(LPCTSTR Text)	// 접속중인 웹 사이트의 제목을 캡션바에 출력
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	GetParentFrame()->SetWindowText(Text);	// 캡션바에 타이틀 출력
}


void CMyWebView::OnStatustextchangeExplorer1(LPCTSTR Text)	// 상태바의 첫번째 페인에 접속상태 출력
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CStatusBar* pStatus = (CStatusBar*)GetParentFrame()->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	pStatus->SetPaneText(0, Text);	// 상태바의 첫번째 페인에 Text 문자열 출력
}


void CMyWebView::OnProgresschangeExplorer1(long Progress, long ProgressMax)	// 상태바의 두번째 페인에 작업 진행율 표시
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_Progress.SetRange(0, (int)ProgressMax);	// 진행바의 범위 설정
	pFrame->m_Progress.SetPos(Progress);	// 진행바의 현재 위치 설정
}

// 다운로드 시작/종료에 따라 애니메이션 움직이기(ERROR)
void CMyWebView::OnDownloadbeginExplorer1()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CAnimateCtrl* pAnimate = (CAnimateCtrl*)AfxGetMainWnd()->GetDescendantWindow(IDW_ANIMATE);	// 애니메이션 컨트롤의 객체 포인터
	pAnimate->Play(0, -1, -1);	//  애니메이션 시작
}


void CMyWebView::OnDownloadcompleteExplorer1()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CAnimateCtrl* pAnimate = (CAnimateCtrl*)AfxGetMainWnd()->GetDescendantWindow(IDW_ANIMATE);	// 애니메이션 컨트롤의 객체 포인터
	pAnimate->Stop();	// 애니메이션 중지
	pAnimate->Seek(0);	// 애니메이션 처음으로 이동
}
