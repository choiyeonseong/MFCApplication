
// NewComView.cpp : CNewComView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "NewCom.h"
#endif

#include "NewComDoc.h"
#include "NewComView.h"

#include "TabDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNewComView

IMPLEMENT_DYNCREATE(CNewComView, CFormView)

BEGIN_MESSAGE_MAP(CNewComView, CFormView)
	ON_BN_CLICKED(IDC_RESULT, &CNewComView::OnClickedResult)
	ON_CBN_SELCHANGE(IDC_COMBOBOXEX1, &CNewComView::OnSelchangeComboboxex1)
	ON_BN_CLICKED(IDC_TABDLG_BTN, &CNewComView::OnClickedTabdlgBtn)
END_MESSAGE_MAP()

// CNewComView 생성/소멸

CNewComView::CNewComView()
	: CFormView(IDD_NEWCOM_FORM)
	, m_Month(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CNewComView::~CNewComView()
{
}

void CNewComView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR1, m_Month);
	DDX_Control(pDX, IDC_COMBOBOXEX1, m_Combo);
}

BOOL CNewComView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CNewComView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CString strIP = _T("210.127.234.16");
	SetDlgItemText(IDC_IPADDRESS1, strIP);	// IP 주소 컨트롤의 초기값 설정
	m_Month = CTime::GetCurrentTime();		// 달력 컨트롤의 초기값 설정
	UpdateData(FALSE);
	// 드롭다운 달력의 텍스트와 배경 색상을 설정
	GetDlgItem(IDC_DATETIMEPICKER1)->SendMessage(DTM_SETMCCOLOR, MCSC_TITLEBK, (LPARAM)RGB(255, 255, 0));
	GetDlgItem(IDC_DATETIMEPICKER1)->SendMessage(DTM_SETMCCOLOR, MCSC_TITLETEXT, (LPARAM)RGB(255, 0, 0));
	GetDlgItem(IDC_DATETIMEPICKER1)->SendMessage(DTM_SETMCCOLOR, MCSC_MONTHBK, (LPARAM)RGB(0, 0, 255));

	FillComboBox();	// 확장된 콤보박스의 항목을 채운다.

	// 툴팁 설정
	m_Tip.Create(this);	// 툴팁 윈도우 생성
	m_Tip.SetTipBkColor(RGB(0, 0, 255));	// 툴팁 배경색 설정
	m_Tip.SetTipTextColor(RGB(255, 255, 255));	// 툴팁 텍스트 색상 설정
	m_Tip.AddTool(GetDlgItem(IDC_MONTHCALENDAR1), _T("Date Picker 컨트롤"));
	m_Tip.AddTool(GetDlgItem(IDC_DATETIMEPICKER1), _T("Date Picker 컨트롤"));
	m_Tip.AddTool(GetDlgItem(IDC_DATETIMEPICKER2), _T("Time Picker 컨트롤"));
	}


// CNewComView 진단

#ifdef _DEBUG
void CNewComView::AssertValid() const
{
	CFormView::AssertValid();
}

void CNewComView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CNewComDoc* CNewComView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNewComDoc)));
	return (CNewComDoc*)m_pDocument;
}
#endif //_DEBUG


// CNewComView 메시지 처리기


void CNewComView::OnClickedResult()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strInfo;
	CString strResult;
	GetDlgItemText(IDC_DATETIMEPICKER1, strInfo);	// Date Picker 값을 얻음
	strResult = _T("Date Time Picker 컨트롤1: ") + strInfo + _T("\r\n");
	GetDlgItemText(IDC_DATETIMEPICKER2, strInfo);	// Time Picker 값을 얻음
	strResult += _T("Date Time Picker 컨트롤2: ") + strInfo + _T("\r\n");
	GetDlgItemText(IDC_IPADDRESS1, strInfo);	// IP 주소 컨트롤의 값을 얻음
	strResult += _T("IP 주소 컨트롤: ") + strInfo + _T("\r\n");
	UpdateData(TRUE);
	strInfo.Format(_T("달력 컨트롤: %d년 %d월 %d일"), m_Month.GetYear(), m_Month.GetMonth(), m_Month.GetDay());
	strResult += strInfo;
	AfxMessageBox(strResult);
}


HRESULT CNewComView::accDoDefaultAction(VARIANT varChild)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFormView::accDoDefaultAction(varChild);
}


void CNewComView::FillComboBox()
{
	// 확장된 콤보박스의 항목에 사용할 텍스트
	char *stritem[10] =
	{
		"http://www.kitri.re.kr", "a:\\MFC 예제",
		"http://www.yahoo.com", "b:\\Image\\icons",
		"mailto:motungi@kitri.re.kr", "c:\\Temp",
		"http://www.visionx.com", "d:\\windows",
		"ftp://www.microsoft.com", "e:\\HNC",
	};
	// 확장된 콤보박스에서 사용할 이미지 설정
	CImageList imgList;
	imgList.Create(IDB_COMBO, 16, 0, (COLORREF)-1);
	m_Combo.SetImageList(&imgList);
	imgList.Detach();

	//확장된 콤보박스의 항목 설정
	COMBOBOXEXITEM test;
	test.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_INDENT | CBEIF_SELECTEDIMAGE;
	for (int i = 0; i < 10; i++)
	{
		test.iItem = i;				// 항목 인덱스
		test.pszText =(LPWSTR)(LPCWSTR)stritem[i];	// 항목에 출력될 문자열(깨짐)
		test.iImage = i;			// 항목의 이미지 인덱스
		test.iIndent = i;			// 들여쓰기 위치 설정(1은 10픽셀)
		test.iSelectedImage = i;	// 선택된 항목의 이미지 인덱스
		m_Combo.InsertItem(&test);	// 확장된 콤보 박스에 항목 추가
	}
	m_Combo.SetCurSel(0);
}


void CNewComView::OnSelchangeComboboxex1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex = m_Combo.GetCurSel();	// 선택된 항목의 인덱스
	CString str;
	m_Combo.GetLBText(nIndex, str);		// 인덱스로부터 문자열을 얻음
	SetDlgItemText(IDC_SELCOMBO, str);	// 선택된 항목의 문자열을 출력
}


void CNewComView::OnClickedTabdlgBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CTabDlg dlg;
	dlg.DoModal();
}

BOOL CNewComView::PreTranslateMessage(MSG* pMsg)
{
	m_Tip.RelayEvent(pMsg);
	return CFormView::PreTranslateMessage(pMsg);
}