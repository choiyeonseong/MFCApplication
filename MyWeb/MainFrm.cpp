
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "MyWeb.h"

#include "MainFrm.h"
#include "MyWebDoc.h"
#include "MyWebView.h"	// 뷰 클래스의 헤더파일을 편입할경우, 도큐먼트 클래스의 헤더파일을 먼저 편입해야한다.

#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_URL_COMBO, &CMainFrame::OnCbnSelchangeUrlCombo)
	ON_COMMAND(ID_VIEW_URLBAR, &CMainFrame::OnViewUrlbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_URLBAR, &CMainFrame::OnUpdateViewUrlbar)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_SEPARATOR,           // 프로그레스 컨트롤이 위치할 페인
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	InitProgress();	// 상태바에 프로그레스 컨트롤 생성

	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, CBRS_ALIGN_TOP, IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;
	}

	CComboBoxEx* pCombo = (CComboBoxEx*)(m_wndDlgBar.GetDlgItem(IDC_URL_COMBO));
	m_imgCombo.Create(IDB_BOOKMARK, 17, 0, (COLORREF)-1);
	pCombo->SetImageList(&m_imgCombo);	// 콤보박스에 이미지 리스트 추가

	//InitAnimation();	// 툴바에 애니메이션 컨트롤 생성

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.style &= ~FWS_ADDTOTITLE;
	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기



// 프로그레스 컨트롤 생성
void CMainFrame::InitProgress()
{
	m_wndStatusBar.SetPaneInfo(1, ID_SEPARATOR, ID_SEPARATOR, 100);
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | PBS_SMOOTH;
	m_Progress.Create(dwStyle, CRect(0, 0, 0, 0), &m_wndStatusBar, IDW_PROGRESS);
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	//// 애니메이션 컨트롤의 위치를 툴바 오른쪽 끝에 위치하도록 한다.
	//if (m_wndToolBar.GetSafeHwnd())	// 툴바가 생성되었는지 판단
	//{
	//	// 애니메이션 컨트롤의 위치를 적절히 조절한다.
	//	CRect rect;
	//	m_wndToolBar.GetClientRect(rect);
	//	rect.left = cx - 70;
	//	rect.right = cx;
	//	m_Animate.MoveWindow(rect);	// 애니메이션 컨트롤의 위치 이동
	//}

	// 상태바의 두번째 페인 크기에 맞게 프로그레스 컨트롤을 조정한다.
	if (m_wndStatusBar.GetSafeHwnd())
	{
		CRect rect;
		m_wndStatusBar.GetItemRect(1, &rect);	// 상태바의 두번째 페인 크기 얻음
		m_Progress.MoveWindow(rect);
	}

	// 메인 윈도우 크기 변경시 콤보 박스 위치도 변경한다.
	if (m_wndDlgBar.GetSafeHwnd())	// 다이얼로그 바가 생성되었는지 판단
	{
		CRect rect;
		m_wndDlgBar.GetClientRect(rect);
		rect.left += 100;
		rect.right = cx - 10;
		m_wndDlgBar.GetDlgItem(IDC_URL_COMBO)->MoveWindow(rect);
	}

}


BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CComboBoxEx* pCombo =(CComboBoxEx*)(m_wndDlgBar.GetDlgItem(IDC_URL_COMBO));
	CEdit* pEdit = pCombo->GetEditCtrl();	// 콤보박스의 에디트 컨트롤
	// URL 바의 콤보박스에서 Enter 키가 눌렸는지 확인
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
	{
		if (GetFocus() == pEdit)	// 콤보박스의 에디트 컨트롤이 포커스를 갖는지 판단
		{
			CString strUrl;
			// 콤보 박스의 에디트 컨트롤 설정된 문자열 얻음
			pCombo->GetEditCtrl()->GetWindowText(strUrl);
			// 현재 활성화된 뷰 객체의 포인터를 얻는다.
			CMyWebView* pView = (CMyWebView*)GetActiveView();
			pView->m_Web.Navigate(strUrl, NULL, NULL, NULL, NULL);
			AddUrl((LPCSTR)(LPCWSTR)strUrl);	// 콤보 박스에 인터넷 주소 추가
		}
	}
	return CFrameWnd::PreTranslateMessage(pMsg);
}

void CMainFrame::AddUrl(LPCSTR strUrl)	// 콤보박스에 Url추가하는 함수
{
	CComboBoxEx* pCombo = (CComboBoxEx*)(m_wndDlgBar.GetDlgItem(IDC_URL_COMBO));
	COMBOBOXEXITEM test;
	test.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_SELECTEDIMAGE;
	test.iItem = 0;					// 아이템 인덱스
	test.pszText = (LPWSTR)strUrl;	// 아이템의 텍스트
	test.iImage = 0;				// 아이템의 이미지 인덱스
	test.iSelectedImage = 0;		// 선택되었을때 아이템의 이미지 인덱스
	pCombo->InsertItem(&test);		// 확장된 콤보박스에 아이템 추가
	pCombo->SetCurSel(0);
}


void CMainFrame::OnCbnSelchangeUrlCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// Url 바의 콤보 박스에서 인터넷 주소를 선택할때
	CComboBoxEx* pCombo = (CComboBoxEx*)(m_wndDlgBar.GetDlgItem(IDC_URL_COMBO));
	int nIndex = pCombo->GetCurSel();	// 선택된 항목의 인덱스
	CString str;
	pCombo->GetLBText(nIndex, str);	// 인덱스에 해당하는 문자열 얻음
	pCombo->SetCurSel(nIndex);
	CMyWebView* pView = (CMyWebView*)GetActiveView();
	pView->m_Web.Navigate(str, NULL, NULL, NULL, NULL);	// 웹 사이트 이동
}


void CMainFrame::OnViewUrlbar()	// URL바를 표시하거나 숨긴다
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	BOOL bShow = (m_wndDlgBar.IsWindowVisible() != 0);	// URL바가 보이는지 판단
	ShowControlBar(&m_wndDlgBar, !bShow, FALSE);	// 토글 형식으로 URL바 표시/숨김
	RecalcLayout();	// 메인 윈도우를 재조정
}


void CMainFrame::OnUpdateViewUrlbar(CCmdUI *pCmdUI)	// URL바가 출력된 상태이면 메뉴에 옵션 마크를 표시
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetRadio(m_wndDlgBar.IsWindowVisible());
}


//// 애니메이션 컨트롤 생성
//void CMainFrame::InitAnimation()
//{
//	m_wndToolBar.SetButtonInfo(10, ID_SEPARATOR, TBBS_SEPARATOR, 70);
//	DWORD dwStyle = WS_CHILD | WS_VISIBLE | ACS_CENTER;	// 윈도우 스타일
//	m_Animate.Create(dwStyle, CRect(0, 0, 0, 0), &m_wndToolBar, IDW_ANIMATE);
//	m_Animate.Open(IDR_ANIMATION1);
//}
