
// FtpDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Ftp.h"
#include "FtpDlg.h"
#include "afxdialogex.h"
#include <afxinet.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CFtpDlg ��ȭ ����



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


// CFtpDlg �޽��� ó����

BOOL CFtpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CFtpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CFtpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// ���ø���Ʈ �ʱ�ȭ
void CFtpDlg::InitLocalList()
{
}


// ���� ����Ʈ�� ����
BOOL CFtpDlg::RefreshLocalList()
{
	return 0;
}


// ����Ʈ ����Ʈ�� �ʱ�ȭ
void CFtpDlg::InitRemoteList()
{
}

// ����Ʈ ����Ʈ�� ����, ���ο� ������ ���
BOOL CFtpDlg::RefreshRemoteList()
{
	m_remoteList.DeleteAllItems();	// ������ ��µ� �׸��� ��� �����.
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
		nIndex++;	// ����Ʈ �ε����� �����Ѵ�.
	}
	//m_remoteList.SortInImageOrder(0, TRUE);	// �̹��� �ε������� ���� // ��������
	m_remoteList.SetColumnWidth(0, LVSCW_AUTOSIZE);	// ��� ũ��
	findRemote->Close();
	delete findRemote;
	return TRUE;
}


// ���� ����
void CFtpDlg::InitToolBar()
{
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("���� ���� ����\n");
		return;
	}
	// RepositionBars()�� reposQuery�ɼ��� ����Ͽ� ���ٰ� �����ϴ� ������ ���
	CRect rcClientNow;
	CRect rcClientStart;
	GetClientRect(rcClientStart);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, CWnd::reposQuery, rcClientNow);
	// ���ٰ� �����ϴ� ������ ����Ͽ� ��� ��Ʈ���� �̵��Ѵ�.
	// ���̾�αװ� �޴��� ���� ������ �޴��� �����ϴ� ������ ����Ѵ�.
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
	// ���ٰ� �����ϴ� ������ŭ ���̾�α��� ũ�⸦ �����Ѵ�.
	CRect rcWindow;
	GetWindowRect(rcWindow);
	rcWindow.right += rcClientStart.Width() - rcClientNow.Width();
	rcWindow.bottom += rcClientStart.Height() - rcClientNow.Height();
	MoveWindow(rcWindow, FALSE);
	// RepositionBars()�� ����Ͽ� ���ٸ� ��ġ��Ŵ
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

}


void CFtpDlg::OnConnect()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	OnDisconnect();	// ������ ����� ��ü�� ������ ����
	CConnectDlg dlg;
	// ���̾�α��� �ʱⰪ�� �����ϴ� �κ�
	dlg.m_Address = "ftp.microsoft.com";
	dlg.m_UserId = "anonymous";
	dlg.m_Password = "hihi@hihi.com";
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_UserID == "anonymous")	/// anonymous�� ����
			m_pFtp = m_session.GetFtpConnection(dlg.m_Address);
		else // ����� �̸��� �н����带 �̿��Ͽ� ����
			m_pFtp = m_session.GetFtpConnection(dlg.m_aAddress, dlg.m_UserIP, dlg.m_Password);

		if (m_pFtp == NULL)	// ���� ���н�
		{
			AfxMessageBox(_T("FTP ���� ����"));
			return;
		}
		RefreshRemoteList();	// ����Ʈ ����Ʈ�� ����
	}
}


void CFtpDlg::OnDisconnect()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (m_pFtp)	// ���� FTP ���� �����Ͱ� �ִ� ���
	{
		m_remoteList.DeleteAllItems();	// ����Ʈ �׸��� ��� �����.
		m_pFtp->Close();	// ���� FTP ������ �ݴ´�.
		m_pFtp = NULL;
		m_curRemoteDir = "";	// ����Ʈ���丮 �ʱ�ȭ
		SetDlgItemText(IDC_REMOTE_PATH, m_curRemoteDir);
	}
}


void CFtpDlg::OnDblclkRemoteList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nSel = pNMListView->iItem;	// ���õ� �׸��� �ε���
	if (nSel!=-1)	// �׸��� ����� �����ߴ��� �Ǵ�
	{
		// ���õ� �׸��� ���ڿ�
		CString strName = m_remoteList.GetItemText(nSel, 0);
		// ���õ� �׸��� �̹��� �ε���
		//int nIndex = m_remoteList.GetItemImageIndex(nSel, 0);

		m_curRemoteDir = m_curRemoteDir + _T("\\") + strName;
		m_pFtp->SetCurrentDirectory(m_curRemoteDir);
	RefreshRemoteList();
	}
	*pResult = 0;
}


void CFtpDlg::OnItemchangedRemoteList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int sel = pNMListView->iItem;
	if (sel!=-1)
	{
		m_updownFile = m_remoteList.GetItemText(sel, 0);
		m_updownFile = m_curRemoteDir + _T("\\") + m_updownFile;	// ���� ���
	}
	*pResult = 0;
}
