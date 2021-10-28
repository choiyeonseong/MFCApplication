
// FtpDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Ftp.h"
#include "FtpDlg.h"
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


// CFtpDlg 대화 상자



CFtpDlg::CFtpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FTP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFtpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOCAL_LIST, m_localList);
	DDX_Control(pDX, IDC_REMOTE_LIST, m_remoteList);
}

BEGIN_MESSAGE_MAP(CFtpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDC_CONNECT, &CFtpDlg::OnConnect)
	ON_COMMAND(IDC_DISCONNECT, &CFtpDlg::OnDisconnect)
	ON_NOTIFY(NM_DBLCLK, IDC_REMOTE_LIST, &CFtpDlg::OnDblclkRemoteList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_REMOTE_LIST, &CFtpDlg::OnItemchangedRemoteList)
END_MESSAGE_MAP()


// CFtpDlg 메시지 처리기

BOOL CFtpDlg::OnInitDialog()
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

void CFtpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFtpDlg::OnPaint()
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
HCURSOR CFtpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// 로컬리스트 초기화
void CFtpDlg::InitLocalList()
{
}


// 로컬 리스트를 갱신
BOOL CFtpDlg::RefreshLocalList()
{
	return 0;
}


// 리모트 리스트를 초기화
void CFtpDlg::InitRemoteList()
{
}

// 리모트 리스트를 갱신, 새로운 데이터 출력
BOOL CFtpDlg::RefreshRemoteList()
{
	m_remoteList.DeleteAllItems();	// 기존에 출력된 항목을 모두 지운다.
	CFtpFileFind* findRemote = new CFtpFileFind(m_pFtp);
	CString strFile;
	DWORD dwSize;
	CTime time;
	int nIndex = 0;
	BOOL bFind = findRemote->FindFile();
	while (bFind)
	{
		bFind = findRemote->FindNextFile();
		strFile = findRemote->GetFileName();
		dwSize = findRemote->GetLength();
		findRemote->GetLastWriteTime(time);
		if (findRemote->IsDirectory())
		{
			if (strFile == ".")
				continue;
			else if (strFile == "..")
				m_remoteList.InsertItem(nIndex, strFile, 0);
			else
				m_remoteList.InsertItem(nIndex, strFile, 1);
		}
		else
		{
			CString strSize, strTime;
			strSize.Format(_T("%d KB"), dwSize / 1024);
			strTime = time.Format(_T("%Y-%m-%d %H:%M"));
			m_remoteList.InsertItem(nIndex, strFile, 0);
			m_remoteList.InsertItem(nIndex, strSize, 1);
			m_remoteList.InsertItem(nIndex, strTime, 2);
		}
		nIndex++;	// 리스트 인덱스를 증가한다.
	}
	//m_remoteList.SortInImageOrder(0, TRUE);	// 이미지 인덱스별로 정렬 // 지원안함
	m_remoteList.SetColumnWidth(0, LVSCW_AUTOSIZE);	// 헤더 크기
	findRemote->Close();
	delete findRemote;
	return TRUE;
}


// 툴바 생성
void CFtpDlg::InitToolBar()
{
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("툴바 생성 실패\n");
		return;
	}
	// RepositionBars()의 reposQuery옵션을 사용하여 툴바가 차지하는 영역을 계산
	CRect rcClientNow;
	CRect rcClientStart;
	GetClientRect(rcClientStart);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, CWnd::reposQuery, rcClientNow);
	// 툴바가 차지하는 영역을 고려하여 모든 컨트롤을 이동한다.
	// 다이얼로그가 메뉴를 갖고 있으면 메뉴가 차지하는 공간도 고려한다.
	CPoint ptOffset(rcClientNow.left - rcClientStart.left, rcClientNow.top - rcClientStart.top);

	//ptOffset.y += GetSystemMetrics(SM_CYMENU);
	CRect rcChild;
	CWnd* pwndChild = GetWindow(GW_CHILD);
	while (pwndChild)
	{
		pwndChild->GetWindowRect(rcChild);
		ScreenToClient(rcChild);
		rcChild.OffsetRect(ptOffset);
		pwndChild->MoveWindow(rcChild, FALSE);
		pwndChild = pwndChild->GetNextWindow();
	}
	// 툴바가 차지하는 영역만큼 다이얼로그의 크기를 조절한다.
	CRect rcWindow;
	GetWindowRect(rcWindow);
	rcWindow.right += rcClientStart.Width() - rcClientNow.Width();
	rcWindow.bottom += rcClientStart.Height() - rcClientNow.Height();
	MoveWindow(rcWindow, FALSE);
	// RepositionBars()을 사용하여 툴바를 위치시킴
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

}


void CFtpDlg::OnConnect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnDisconnect();	// 기존에 연결된 객체가 있으면 해제
	CConnectDlg dlg;
	// 다이얼로그의 초기값을 설정하는 부분
	dlg.m_Address = "ftp.microsoft.com";
	dlg.m_UserId = "anonymous";
	dlg.m_Password = "hihi@hihi.com";
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_UserID == "anonymous")	/// anonymous로 연결
			m_pFtp = m_session.GetFtpConnection(dlg.m_Address);
		else // 사용자 이름과 패스워드를 이용하여 연결
			m_pFtp = m_session.GetFtpConnection(dlg.m_aAddress, dlg.m_UserIP, dlg.m_Password);

		if (m_pFtp == NULL)	// 연결 실패시
		{
			AfxMessageBox(_T("FTP 연결 실패"));
			return;
		}
		RefreshRemoteList();	// 리모트 리스트를 갱신
	}
}


void CFtpDlg::OnDisconnect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_pFtp)	// 기존 FTP 연결 포인터가 있는 경우
	{
		m_remoteList.DeleteAllItems();	// 리스트 항목을 모두 지운다.
		m_pFtp->Close();	// 기존 FTP 연결을 닫는다.
		m_pFtp = NULL;
		m_curRemoteDir = "";	// 리모트디렉토리 초기화
		SetDlgItemText(IDC_REMOTE_PATH, m_curRemoteDir);
	}
}


void CFtpDlg::OnDblclkRemoteList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nSel = pNMListView->iItem;	// 선택된 항목의 인덱스
	if (nSel!=-1)	// 항목을 제대로 선택했는지 판단
	{
		// 선택된 항목의 문자열
		CString strName = m_remoteList.GetItemText(nSel, 0);
		// 선택된 항목의 이미지 인덱스
		//int nIndex = m_remoteList.GetItemImageIndex(nSel, 0);

		m_curRemoteDir = m_curRemoteDir + _T("\\") + strName;
		m_pFtp->SetCurrentDirectory(m_curRemoteDir);
	RefreshRemoteList();
	}
	*pResult = 0;
}


void CFtpDlg::OnItemchangedRemoteList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int sel = pNMListView->iItem;
	if (sel!=-1)
	{
		m_updownFile = m_remoteList.GetItemText(sel, 0);
		m_updownFile = m_curRemoteDir + _T("\\") + m_updownFile;	// 파일 경로
	}
	*pResult = 0;
}
