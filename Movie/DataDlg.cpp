// DataDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Movie.h"
#include "DataDlg.h"
#include "afxdialogex.h"
#include "resource.h"


// CDataDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDataDlg, CDialog)

CDataDlg::CDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_strEdit3(_T(""))
	, m_strCount(_T(""))
	, m_strStatic3(_T(""))
{

}

CDataDlg::~CDataDlg()
{
}

void CDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_ctlEdit2);
	DDX_Text(pDX, IDC_EDIT3, m_strEdit3);
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
	DDX_Text(pDX, IDC_STATIC_COUNT, m_strCount);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_ImageCtrl);
	DDX_Control(pDX, IDC_STATIC2, m_ctlStatic2);
	DDX_Text(pDX, IDC_STATIC3, m_strStatic3);
}


BEGIN_MESSAGE_MAP(CDataDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDataDlg::OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDataDlg::OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDataDlg::OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDataDlg::OnButton4)
	ON_BN_CLICKED(IDC_COMBO_ADD, &CDataDlg::OnComboAdd)
	ON_BN_CLICKED(IDC_LIST_ADD, &CDataDlg::OnListAdd)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDataDlg::OnSelchangeCombo1)
	ON_LBN_DBLCLK(IDC_LIST1, &CDataDlg::OnDblclkList1)
	ON_COMMAND(IDC_RADIO1, &CDataDlg::OnRadio1)
	ON_COMMAND(IDC_RADIO2, &CDataDlg::OnRadio2)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CDataDlg 메시지 처리기입니다.


void CDataDlg::OnButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemText(IDC_EDIT1, str);		// IDC_EDIT1에 입력한 문자열을 얻음
	SetDlgItemText(IDC_STATIC1, str);	// IDC_STATIC1에 문자열을 출력
}


void CDataDlg::OnButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 컨트롤을 이용하는 방법(Category - Control)
	CString str;
	m_ctlEdit2.GetWindowTextW(str);		// CEdit형 멤버변수
	m_ctlStatic2.SetWindowTextW(str);	// CStatic형 멤버변수
}


void CDataDlg::OnButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 데이터 값을 이용하는 방법(Category - Value)
	UpdateData(TRUE);
	m_strStatic3 = m_strEdit3;	// CString형 멤버변수
	UpdateData(FALSE);
}


void CDataDlg::OnButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 객체 포인터를 이용하는 방법
	CString str;
	CEdit* pE4 = (CEdit*)GetDlgItem(IDC_EDIT4);	// 컨트롤 ID에 해당하는 객체에 대한 포인터를 리턴
	pE4->GetWindowTextW(str);

	CStatic* pS4 = (CStatic*)GetDlgItem(IDC_STATIC4);
	pS4->SetWindowTextW(str);
}


void CDataDlg::OnComboAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemText(IDC_EDIT1, str);
	m_Combo.AddString(str);

	GetDlgItemText(IDC_EDIT2, str);
	m_Combo.AddString(str);

	GetDlgItemText(IDC_EDIT3, str);
	m_Combo.AddString(str);

	GetDlgItemText(IDC_EDIT4, str);
	m_Combo.AddString(str);
	m_Combo.SetCurSel(0);	// 첫번째 항목을 현재 선택된 항목으로 설정한다.
}


void CDataDlg::OnListAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST1);
	GetDlgItemText(IDC_EDIT1, str);
	pList->AddString(str);

	GetDlgItemText(IDC_EDIT2, str);
	pList->AddString(str);

	GetDlgItemText(IDC_EDIT3, str);
	pList->AddString(str);

	GetDlgItemText(IDC_EDIT4, str);
	pList->AddString(str);

	pList->SetCurSel(2);	// 세번째 항목을 현재 선택된 항목으로 설정한다.
}


void CDataDlg::OnSelchangeCombo1()	// 콤보 박스의 항목을 변경할 때
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex;
	nIndex = m_Combo.GetCurSel();	// 현재 선택된 항목의 인덱스를 얻음

	CString str;
	m_Combo.GetLBText(nIndex, str);	// 인덱스에 해당하는 항목의 문자열 얻음
	SetDlgItemText(IDC_STATIC_COMBO, str);	// 선택된 항목의 문자열 출력
}


void CDataDlg::OnDblclkList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex;
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST1);
	nIndex = pList->GetCurSel();	// 현재 선택된 항목의 인덱스를 얻음
	
	CString str;
	pList->GetText(nIndex, str);	// 인덱스에 해당하는 항목의 문자열 얻음
	SetDlgItemText(IDC_STATIC_LIST, str);	// 선택된 항목의 문자열 출력
}

BOOL CDataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// 라디오 버튼 컨트롤
	CButton* pOption = (CButton*)GetDlgItem(IDC_RADIO1);
	pOption->SetCheck(1);	// 라디오 버튼 [배트맨]을 설정
	m_imgBatman.LoadBitmapW(IDB_CHUN);			// 비트맵 리소스 로드
	m_imgBatgirl.LoadBitmapW(IDB_BATGIRL);		// 비트맵 리소스 로드
	
	// 스크롤바 컨트롤
	CScrollBar* pScroll = (CScrollBar*)GetDlgItem(IDC_SCROLLBAR1);
	pScroll->SetScrollRange(0, 100);	// 스크롤바의 범위 설정
	pScroll->SetScrollPos(0);			// 스크롤바의 초기 위치 설정

	return TRUE;
}


void CDataDlg::OnRadio1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_ImageCtrl.SetBitmap(m_imgBatman);
}


void CDataDlg::OnRadio2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_ImageCtrl.SetBitmap(m_imgBatgirl);
}


void CDataDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	UINT nTemp;
	nTemp = pScrollBar->GetScrollPos();	// 현재 스크롤 박스(Thumb)의 위치
	switch (nSBCode)	// 스크롤바의 어느 부분을 클릭했는지 판단
	{
	case SB_LINELEFT:	// 좌측 화살표 버튼 클릭시
		if (nTemp > 0)
			nTemp -= 5;	// 현재 위치에서 좌로 5만큼 이동
		else
			nTemp = 0;
		pScrollBar->SetScrollPos(nTemp);
		break;
	case SB_PAGELEFT:	// Thumb과 좌측 화살표 버튼 사이 클릭시
		if (nTemp >= 0)
			nTemp -= 20;	// 현재 위치에서 좌로 20만큼 이동
		else
			nTemp = 0;
		pScrollBar->SetScrollPos(nTemp);
		break;
	case SB_LINERIGHT:	// 우측 화살표 버튼 클릭시
		if (nTemp <100)
			nTemp += 5;	// 현재 위치에서 우로 5만큼 이동
		else
			nTemp = 100;
		pScrollBar->SetScrollPos(nTemp);
		break;
	case SB_PAGERIGHT:	// Thumb과 우측 화살표 버튼사이 클릭시
		if (nTemp <= 90)
			nTemp += 20;	// 현재 위치에서 우로 20만큼 이동
		else
			nTemp = 0;
		pScrollBar->SetScrollPos(nTemp);
		break;
	case SB_THUMBTRACK:	// Thumb을 드래그&드롭할 때
		nTemp = nPos;
		pScrollBar->SetScrollPos(nTemp);
		break;
	}
	CString str;
	str.Format(_T("%d%%"), nTemp);
	m_strCount = str;
	UpdateData(FALSE);		// 멤버변수의 데이터 값을 출력한다.
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
