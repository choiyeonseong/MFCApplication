
// CountDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Count.h"
#include "CountDlg.h"
#include "afxdialogex.h"
#include "MyThread.h"


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


// CCountDlg ��ȭ ����



CCountDlg::CCountDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COUNT_DIALOG, pParent)
	, m_pMyThread(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCountDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_COUNT, &CCountDlg::OnClickedStartCount)
	ON_BN_CLICKED(IDC_START_PROGRESS, &CCountDlg::OnClickedStartProgress)
	ON_BN_CLICKED(IDC_CHECK1, &CCountDlg::OnClickedCheck1)
END_MESSAGE_MAP()


// CCountDlg �޽��� ó����

BOOL CCountDlg::OnInitDialog()
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

void CCountDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCountDlg::OnPaint()
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
HCURSOR CCountDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// [1���� 100000������ ��] ��ư ���� ���
void CCountDlg::OnClickedStartCount()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//// 1. single thread�� ������� �ٸ� �۾��� ����ó�� �Ҽ� ����.
	//int nResult = 0;
	//for (int i = 0; i <= 100000; i++)	// 100000�� �ؾ� �����ɸ�
	//{
	//	nResult += i;
	//	SetDlgItemInt(IDC_RESULT, nResult);
	//}

	// 2. ���� ������ + �۾� ������ : multi thread program
	AfxBeginThread(MySumProc, this);	// ���ο� �۾� ������ ����
	GetDlgItem(IDC_START_COUNT)->EnableWindow(FALSE);
}


// �۾� ������ �Լ� ����
UINT CCountDlg::MySumProc(void* lParam)
{
	int nResult = 0;
	CCountDlg* pDlg = (CCountDlg *)lParam;	// ����ȯ�Ͽ� ����ؾ� �Ѵ�.
	for (int i = 0; i < 10000; i++)
	{
		nResult += i;
		pDlg->SetDlgItemInt(IDC_RESULT, nResult);
	}
	pDlg->GetDlgItem(IDC_START_COUNT)->EnableWindow(TRUE);
	return 0;
}

// [UI ������ ����] ��ư�� ���� ���
void CCountDlg::OnClickedStartProgress()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_pMyThread = (CMyThread*)AfxBeginThread(RUNTIME_CLASS(CMyThread), THREAD_PRIORITY_LOWEST, 0, CREATE_SUSPENDED);	// UI ������ ������ �Բ� �����带 �ߴ�(suspended)
	m_pMyThread->SetOwner(this);	// ���� ������� UI �����尣 ����� ����
	m_pMyThread->ResumeThread();	// �����带 �簳�Ѵ�
	GetDlgItem(IDC_START_PROGRESS)->EnableWindow(FALSE);
}

// [�ߴ�] üũ�ڽ��� ���� ���
void CCountDlg::OnClickedCheck1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CButton* pCheck = (CButton*)GetDlgItem(IDC_CHECK1);
	BOOL bSuspend = pCheck->GetCheck();
	if (bSuspend)	// üũ�� �Ǿ����� �Ǵ�
		m_pMyThread->SuspendThread();	// ������ �ߴ�
	else
		m_pMyThread->ResumeThread();	// ������ ��� ����
}
