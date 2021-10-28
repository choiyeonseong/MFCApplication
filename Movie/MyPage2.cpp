// MyPage2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Movie.h"
#include "MyPage2.h"
#include "afxdialogex.h"
#include "Resource.h"

// CMyPage2 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMyPage2, CPropertyPage)

CMyPage2::CMyPage2()
	: CPropertyPage(IDD_PROPPAGE2)
{

}

CMyPage2::~CMyPage2()
{
}

void CMyPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CMyPage2, CPropertyPage)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CMyPage2 메시지 처리기입니다.


BOOL CMyPage2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	// 3개의 슬라이더 컨트롤에 대한 객체 포인터 얻음
	CSliderCtrl* pSlider1 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	CSliderCtrl* pSlider2 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
	CSliderCtrl* pSlider3 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER3);

	pSlider1->SetRange(0, 255);	// 첫번째 트랙바의 범위 설정
	pSlider2->SetRange(0, 255);	// 두번째 트랙바의 범위 설정
	pSlider3->SetRange(0, 255);	// 세번째 트랙바의 범위 설정
	pSlider1->SetPos(128);	// 첫번째 트랙바의 초기 위치 설정
	pSlider2->SetPos(0);	// 두번째 트랙바의 초기 위치 설정
	pSlider3->SetPos(128);	// 세번째 트랙바의 초기 위치 설정

							// 슬라이더 컨트롤에 대응하는 정적 텍스트에 초기값 설정
	SetDlgItemInt(IDC_RED, 128);
	SetDlgItemInt(IDC_GREEN, 0);
	SetDlgItemInt(IDC_BLUE, 128);

	return TRUE;
}

void CMyPage2::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 3개의 슬라이더 컨트롤에 대해 개별 처리한다.
	CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;
	switch (pSlider->GetDlgCtrlID())
	{
	case IDC_SLIDER1:
		SetDlgItemInt(IDC_RED, pSlider->GetPos());
		break;
	case IDC_SLIDER2:
		SetDlgItemInt(IDC_GREEN, pSlider->GetPos());
		break;
	case IDC_SLIDER3:
		SetDlgItemInt(IDC_BLUE, pSlider->GetPos());
		break;
	}
	CurrentFillColor();	// 현재 색상 표시
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CMyPage2::CurrentFillColor()
{
	UINT nRed, nGreen, nBlue;
	nRed = GetDlgItemInt(IDC_RED);
	nGreen = GetDlgItemInt(IDC_GREEN);
	nBlue = GetDlgItemInt(IDC_BLUE);

	COLORREF color = RGB(nRed, nGreen, nBlue);
	CRect rc;
	CStatic* pFrame = (CStatic*)GetDlgItem(IDC_COLOR_SHOW);
	pFrame->GetClientRect(rc);

	CClientDC dc(pFrame);
	CBrush br(color);
	CBrush* pOld = dc.SelectObject(&br);
	dc.FillRect(rc, &br);	// 현재 픽셀의 색상으로 사각형을 채운다.
	dc.SelectObject(pOld);
}


BOOL CMyPage2::OnSetActive()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_BACK|PSWIZB_NEXT);	// 뒤로, 다음 버튼 활성화
	return CPropertyPage::OnSetActive();
}
