
// CallDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Call.h"
#include "CallDlg.h"
#include "afxdialogex.h"

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


// CCallDlg 대화 상자



CCallDlg::CCallDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CALL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hInstDll = NULL;	// 초기값 설정ㅌ
}

void CCallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCallDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_IMPORT_LIB, &CCallDlg::OnClickedImportLib)
	ON_BN_CLICKED(IDC_RUNTIME_LINK, &CCallDlg::OnClickedRuntimeLink)
	ON_BN_CLICKED(IDOK, &CCallDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCallDlg::OnBnClickedCancel)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CCallDlg 메시지 처리기

BOOL CCallDlg::OnInitDialog()
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

void CCallDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCallDlg::OnPaint()
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
HCURSOR CCallDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// [임포트 라이브러리를 이용한 연결 방법] 버튼을 누른 경우
void CCallDlg::OnClickedImportLib()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char szMail[40];
	TCHAR szPath[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH, szPath);	// 현재 작업 디렉토리 얻음
	if (ShowSetupDialog(szMail, (LPSTR)(LPWSTR)szPath))	// DLL 함수가 호출되어 다이얼로그 출력
	{
		CString strInfo;
		strInfo.Format(L"E-mail : %s\n설치 경로 : %s", szMail, szPath);
		AfxMessageBox(strInfo);	// DLL의 다이얼로그에서 입력한 데이터 출력
	}
}


void CCallDlg::OnClickedRuntimeLink()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_hInstDll == NULL)	// DLL이 로드된 상태인지 판단
	{
		m_hInstDll = LoadLibrary(_T("Help.dll"));	// Help.dll 로드, 해당 DLL모듈의 인스턴스 핸들을 리턴
		if (m_hInstDll == NULL)
		{
			AfxMessageBox(_T("Help.dll로드 실패"));
			return;
		}
	}
}


void CCallDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_hInstDll!=NULL)	// DLL이 로드된 상태인지 판단
	{
		if (!FreeLibrary(m_hInstDll))	// 인스턴스 핸들을 사용해 로드된 DLL해제
		{
			AfxMessageBox(_T("Help.dll해제 실패"));
		}
	}
	CDialogEx::OnOK();
}


void CCallDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_hInstDll!=NULL)	// DLL이 로드된 상태인지 판단
	{
		if (!FreeLibrary(m_hInstDll))	// 인스턴스 핸들을 사용해 로드된 DLL해제
		{
			AfxMessageBox(_T("Help.dll 해제 실패"));
		}
	}
	CDialogEx::OnCancel();
}


void CCallDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_hInstDll!=NULL)	// DLL이 로드된 상태인지 판단
	{
		BOOL(*pFunc)();	// 함수 포인터 선언
		pFunc = (BOOL(*)())GetProcAddress(m_hInstDll, "ShowHelp");
		if (pFunc==NULL)
		{
			AfxMessageBox(_T("ShowHelp() 함수 실패"));
			return;	// DLL이 익스포트하는 ShowHelp() 호출
		}
		pFunc();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CCallDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_hInstDll != NULL)	// DLL이 로드된 상태인지 판단
	{
		void(*pFunc)();	// 함수 포인터 선언
		pFunc = (void(*)())GetProcAddress(m_hInstDll, "DestroyHelp");
		if (pFunc == NULL)
		{
			AfxMessageBox(_T("DestroyHelp() 함수 실패"));
			return;	// DLL이 익스포트하는 DestroyHelp() 호출
		}
		pFunc();
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}
