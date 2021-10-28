
// CallDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Call.h"
#include "CallDlg.h"
#include "afxdialogex.h"

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


// CCallDlg ��ȭ ����



CCallDlg::CCallDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CALL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hInstDll = NULL;	// �ʱⰪ ������
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


// CCallDlg �޽��� ó����

BOOL CCallDlg::OnInitDialog()
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCallDlg::OnPaint()
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
HCURSOR CCallDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// [����Ʈ ���̺귯���� �̿��� ���� ���] ��ư�� ���� ���
void CCallDlg::OnClickedImportLib()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	char szMail[40];
	TCHAR szPath[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH, szPath);	// ���� �۾� ���丮 ����
	if (ShowSetupDialog(szMail, (LPSTR)(LPWSTR)szPath))	// DLL �Լ��� ȣ��Ǿ� ���̾�α� ���
	{
		CString strInfo;
		strInfo.Format(L"E-mail : %s\n��ġ ��� : %s", szMail, szPath);
		AfxMessageBox(strInfo);	// DLL�� ���̾�α׿��� �Է��� ������ ���
	}
}


void CCallDlg::OnClickedRuntimeLink()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_hInstDll == NULL)	// DLL�� �ε�� �������� �Ǵ�
	{
		m_hInstDll = LoadLibrary(_T("Help.dll"));	// Help.dll �ε�, �ش� DLL����� �ν��Ͻ� �ڵ��� ����
		if (m_hInstDll == NULL)
		{
			AfxMessageBox(_T("Help.dll�ε� ����"));
			return;
		}
	}
}


void CCallDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_hInstDll!=NULL)	// DLL�� �ε�� �������� �Ǵ�
	{
		if (!FreeLibrary(m_hInstDll))	// �ν��Ͻ� �ڵ��� ����� �ε�� DLL����
		{
			AfxMessageBox(_T("Help.dll���� ����"));
		}
	}
	CDialogEx::OnOK();
}


void CCallDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_hInstDll!=NULL)	// DLL�� �ε�� �������� �Ǵ�
	{
		if (!FreeLibrary(m_hInstDll))	// �ν��Ͻ� �ڵ��� ����� �ε�� DLL����
		{
			AfxMessageBox(_T("Help.dll ���� ����"));
		}
	}
	CDialogEx::OnCancel();
}


void CCallDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_hInstDll!=NULL)	// DLL�� �ε�� �������� �Ǵ�
	{
		BOOL(*pFunc)();	// �Լ� ������ ����
		pFunc = (BOOL(*)())GetProcAddress(m_hInstDll, "ShowHelp");
		if (pFunc==NULL)
		{
			AfxMessageBox(_T("ShowHelp() �Լ� ����"));
			return;	// DLL�� �ͽ���Ʈ�ϴ� ShowHelp() ȣ��
		}
		pFunc();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CCallDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_hInstDll != NULL)	// DLL�� �ε�� �������� �Ǵ�
	{
		void(*pFunc)();	// �Լ� ������ ����
		pFunc = (void(*)())GetProcAddress(m_hInstDll, "DestroyHelp");
		if (pFunc == NULL)
		{
			AfxMessageBox(_T("DestroyHelp() �Լ� ����"));
			return;	// DLL�� �ͽ���Ʈ�ϴ� DestroyHelp() ȣ��
		}
		pFunc();
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}
