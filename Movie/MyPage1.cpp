// MyPage1.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Movie.h"
#include "MyPage1.h"
#include "afxdialogex.h"

#include "resource.h"

// CMyPage1 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMyPage1, CPropertyPage)

CMyPage1::CMyPage1()
	: CPropertyPage(IDD_PROPPAGE1)
{

}

CMyPage1::~CMyPage1()
{
}

void CMyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ANIMATE1, m_Animate);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_SPIN1, m_Spin);
}


BEGIN_MESSAGE_MAP(CMyPage1, CPropertyPage)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CMyPage1 메시지 처리기입니다.



void CMyPage1::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int value = m_Spin.GetPos();	// 스핀 컨트롤의 현재 위치 얻음
	m_Progress.SetPos(value * 5);	// 프로그레스 컨트롤의 위치 설정
	CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CMyPage1::OnInitDialog()	// 첫번째 프로퍼티 페이지에 대한 코드
{
	CPropertyPage::OnInitDialog();
	m_Spin.SetRange(0, 20);		// 스핀 버튼 컨트롤의 범위 설정
	m_Spin.SetPos(0);			// 스핀 버튼 컨트롤의 초기 위치 설정

	m_Progress.SetRange(0, 100);	// 프로그레스 컨트롤의 범위 설정
	m_Progress.SetPos(0);			// 프로그레스 컨트롤의 초기 위치 설정
	m_Animate.Open(IDR_AVI1);		// 애니메이션 열기(리소스 이용)
	return TRUE;
}


BOOL CMyPage1::OnSetActive()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();	// 페이지의 부모 윈도우에 대한 객체포인터를 사용
	pSheet->SetWizardButtons(PSWIZB_NEXT);	// 다음 버튼 활성화
	return CPropertyPage::OnSetActive();

}


LRESULT CMyPage1::OnWizardNext()	// 다음 버튼 클릭 시
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	int nCount = GetDlgItemInt(IDC_EDIT1);
	if (nCount != 7)
	{
		AfxMessageBox(_T("Key count는 7입니다."), MB_ICONINFORMATION);
		return -1;	// 다음 페이지로의 이동을 막는다.
	}
	return CPropertyPage::OnWizardNext();
}
