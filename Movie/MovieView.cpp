
// MovieView.cpp : CMovieView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Movie.h"
#endif

#include "MovieDoc.h"
#include "MovieView.h"
#include "DataDlg.h"
#include "MySheet.h"

#include "resource.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMovieView

IMPLEMENT_DYNCREATE(CMovieView, CFormView)

BEGIN_MESSAGE_MAP(CMovieView, CFormView)
	ON_BN_CLICKED(IDC_FORM_MODAL, &CMovieView::OnFormModal)
	ON_BN_CLICKED(IDC_FORM_MODALESS2, &CMovieView::OnCFormModaless)
	ON_BN_CLICKED(IDC_FORM_PROPERTY, &CMovieView::OnClickedFormProperty)
	ON_BN_CLICKED(IDC_FORM_WIZARD, &CMovieView::OnClickedFormWizard)
	ON_COMMAND(ID_POPUP_OPEN, &CMovieView::OnPopupOpen)
	ON_COMMAND(ID_POPUP_COLOR, &CMovieView::OnPopupColor)
	ON_COMMAND(ID_POPUP_EXIT, &CMovieView::OnPopupExit)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

// CMovieView 생성/소멸

CMovieView::CMovieView() : CFormView(IDD_MOVIE_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_pDlg = NULL;	// 초기화
}

CMovieView::~CMovieView()
{
}

void CMovieView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMovieView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMovieView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	
}


// CMovieView 진단

#ifdef _DEBUG
void CMovieView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMovieView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMovieDoc* CMovieView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMovieDoc)));
	return (CMovieDoc*)m_pDocument;
}
#endif //_DEBUG


// CMovieView 메시지 처리기


void CMovieView::OnFormModal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDataDlg dlg;


	if (dlg.DoModal() == IDOK)	// OK 버튼 누르면
		SetDlgItemText(IDC_FORM_COUNT, dlg.m_strCount);
}


void CMovieView::OnCFormModaless()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pDlg->GetSafeHwnd() == NULL)	// 현재 모달리스 다이얼로그가 있는지 판단
	{
		m_pDlg = new CPixelDlg;	// 힙 메모리에 다이얼로그 객체를 생성한다.
		m_pDlg->Create(IDD_MODALESS);
		m_pDlg->ShowWindow(SW_SHOW);

	}
}


void CMovieView::OnProperties()
{
	// 컴포넌트 갤러리에 의해 추가된 코드부분으로
	// 프로퍼티 다이얼로그를 화면에 출력한다.
	CMySheet propSheet;
	propSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;	// 적용 버튼 제거
	propSheet.DoModal();

}


void CMovieView::OnClickedFormProperty()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnProperties();	// 컴포넌트 갤러리에 의해 추가된 함수를 호출
}


void CMovieView::OnClickedFormWizard()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMySheet propSheet;
	propSheet.SetWizardMode();	// 위저드 다이얼로그 형식 설정
	propSheet.DoModal();
}


void CMovieView::OnPopupOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFileDialog dlg(TRUE);	// 열기 다이얼로그 객체 생성/ FALSE면 저장 다이얼로그 생성
	if (dlg.DoModal() == IDOK)	// 열기 다이얼로그 출력
	{
		ShellExecute(NULL, _T("open"), dlg.GetFileName(), NULL, NULL, SW_SHOW);	// 시스템에 등록된 확장자와 연결된 프로그램을 실행하고 선택된 파일을 오픈
	}
}


void CMovieView::OnPopupColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		COLORREF color = dlg.GetColor();	// 현재 선택된 색상을 얻음
		CString strInfo;
		strInfo.Format(_T("Red: %d, Green: %d, Blue: %d"), GetRValue(color), GetGValue(color), GetBValue(color));
		AfxMessageBox(strInfo);
	}
}


void CMovieView::OnPopupExit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxGetMainWnd()->PostMessageW(WM_QUIT);	// 프로그램 종료
}


void CMovieView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect rc;
	CStatic* pFrame = (CStatic*)GetDlgItem(IDC_FORM_IMAGE);
	pFrame->GetWindowRect(rc);	// 스크린 좌표계를 기준으로한 사각형 정보
	if (rc.PtInRect(point))	// 마우스 커서가 픽쳐 컨트롤 내에 있는지 판단
	{
		CMenu menu;
		menu.LoadMenuW(IDR_POPUP);	// 메뉴 리소스 로드
		CMenu* pPopup = menu.GetSubMenu(0);	// 사용할 서브 메뉴의 객체 포인터
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}
