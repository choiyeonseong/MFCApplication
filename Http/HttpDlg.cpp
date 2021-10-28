
// HttpDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Http.h"
#include "HttpDlg.h"
#include "afxdialogex.h"
#include <afxinet.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHttpDlg 대화 상자



CHttpDlg::CHttpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HTTP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHttpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHttpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_URL, &CHttpDlg::OnSelchangeUrl)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CHttpDlg 메시지 처리기

BOOL CHttpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CHttpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CHttpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CHttpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CHttpDlg::PreTranslateMessage(MSG * pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CComboBoxEx* pCombo = (CComboBoxEx*)GetDlgItem(IDC_URL);
	CEdit* pEdit = pCombo->GetEditCtrl();
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CString strUrl;
		pEdit->GetWindowTextW(strUrl);	// 확장된 콤보박스의 문자열 얻음
										// 서비스 타입에 따른 URL 분석
		DWORD dwServiceType = AFX_INET_SERVICE_HTTP;
		CString strServer;
		CString strObject;
		INTERNET_PORT nPort;
		if (!AfxParseURL(strUrl, dwServiceType, strServer, strObject, nPort))
		{
			strUrl = _T("http://") + strUrl;
			DisplayData(strUrl);	// HTML 문서 출력
			SetUrlCombo(strUrl);	// 콤보박스에 URL 추가
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CHttpDlg::DisplayData(CString strUrl)
{
	BeginWaitCursor();
	CInternetSession session;
	CInternetFile* pFile = (CInternetFile*)session.OpenURL(strUrl);
	if (pFile)	// 파일을 성공적으로 오픈하면
	{
		CString strData;		// 한 라인의 데이터
		CString totalData;		// 총 데이터
		pFile->SetReadBufferSize(4096);	// 전송된 데이터를 받는 버퍼 설정
		while (pFile->ReadString(strData))	// 한 라인씩 끊어 읽는다.
		{
			totalData = totalData + CA2W((LPCSTR)strData.GetBuffer(), CP_UTF8) + _T("\r\n");
		}
		EndWaitCursor();
		SetDlgItemTextW(IDC_DATA, totalData);	// 에디트 컨트롤에 내용 출력
		pFile->Close();
	}
}


void CHttpDlg::SetUrlCombo(CString strUrl)
{
	CComboBoxEx* pCombo = (CComboBoxEx*)GetDlgItem(IDC_URL);
	static UINT idx = 0;
	COMBOBOXEXITEM test;
	test.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_INDENT | CBEIF_SELECTEDIMAGE;
	test.iItem = idx;	// 항목 인덱스
	test.pszText = (LPWSTR)(LPCTSTR)strUrl;	// 항목에 출력될 문자열
	test.iImage = 1;	// 항목의 이미지 인덱스
	test.iIndent = 1;	// 들여쓰기 위치 설정
	test.iSelectedImage = 0;	// 선택된 항목의 이미지 인덱스
	pCombo->InsertItem(&test);	// 확장된 콤보 박스에 항목 추가
	pCombo->SetCurSel(idx++);
}


void CHttpDlg::OnSelchangeUrl()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CComboBoxEx* pCombo = (CComboBoxEx*)GetDlgItem(IDC_URL);
	int nIndex = pCombo->GetCurSel();	// 선택한 URL 항목의 인덱스
	CString str;
	pCombo->GetLBText(nIndex, str);	// 인덱스로부터 문자열을 얻음
	DisplayData(str);	// 선택된 URL로 이동 후 내용을 출력한다.
}


HBRUSH CHttpDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (pWnd->GetDlgCtrlID() == IDC_DATA)
	{
		pDC->SetBkColor(RGB(255, 255, 0));	// 배경색 설정
		pDC->SetTextColor(RGB(0, 0, 255));	// 문자색 설정
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
