
// HttpDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Http.h"
#include "HttpDlg.h"
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


// CHttpDlg ��ȭ ����



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


// CHttpDlg �޽��� ó����

BOOL CHttpDlg::OnInitDialog()
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CHttpDlg::OnPaint()
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
HCURSOR CHttpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CHttpDlg::PreTranslateMessage(MSG * pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CComboBoxEx* pCombo = (CComboBoxEx*)GetDlgItem(IDC_URL);
	CEdit* pEdit = pCombo->GetEditCtrl();
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CString strUrl;
		pEdit->GetWindowTextW(strUrl);	// Ȯ��� �޺��ڽ��� ���ڿ� ����
										// ���� Ÿ�Կ� ���� URL �м�
		DWORD dwServiceType = AFX_INET_SERVICE_HTTP;
		CString strServer;
		CString strObject;
		INTERNET_PORT nPort;
		if (!AfxParseURL(strUrl, dwServiceType, strServer, strObject, nPort))
		{
			strUrl = _T("http://") + strUrl;
			DisplayData(strUrl);	// HTML ���� ���
			SetUrlCombo(strUrl);	// �޺��ڽ��� URL �߰�
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
	if (pFile)	// ������ ���������� �����ϸ�
	{
		CString strData;		// �� ������ ������
		CString totalData;		// �� ������
		pFile->SetReadBufferSize(4096);	// ���۵� �����͸� �޴� ���� ����
		while (pFile->ReadString(strData))	// �� ���ξ� ���� �д´�.
		{
			totalData = totalData + CA2W((LPCSTR)strData.GetBuffer(), CP_UTF8) + _T("\r\n");
		}
		EndWaitCursor();
		SetDlgItemTextW(IDC_DATA, totalData);	// ����Ʈ ��Ʈ�ѿ� ���� ���
		pFile->Close();
	}
}


void CHttpDlg::SetUrlCombo(CString strUrl)
{
	CComboBoxEx* pCombo = (CComboBoxEx*)GetDlgItem(IDC_URL);
	static UINT idx = 0;
	COMBOBOXEXITEM test;
	test.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_INDENT | CBEIF_SELECTEDIMAGE;
	test.iItem = idx;	// �׸� �ε���
	test.pszText = (LPWSTR)(LPCTSTR)strUrl;	// �׸� ��µ� ���ڿ�
	test.iImage = 1;	// �׸��� �̹��� �ε���
	test.iIndent = 1;	// �鿩���� ��ġ ����
	test.iSelectedImage = 0;	// ���õ� �׸��� �̹��� �ε���
	pCombo->InsertItem(&test);	// Ȯ��� �޺� �ڽ��� �׸� �߰�
	pCombo->SetCurSel(idx++);
}


void CHttpDlg::OnSelchangeUrl()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CComboBoxEx* pCombo = (CComboBoxEx*)GetDlgItem(IDC_URL);
	int nIndex = pCombo->GetCurSel();	// ������ URL �׸��� �ε���
	CString str;
	pCombo->GetLBText(nIndex, str);	// �ε����κ��� ���ڿ��� ����
	DisplayData(str);	// ���õ� URL�� �̵� �� ������ ����Ѵ�.
}


HBRUSH CHttpDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	if (pWnd->GetDlgCtrlID() == IDC_DATA)
	{
		pDC->SetBkColor(RGB(255, 255, 0));	// ���� ����
		pDC->SetTextColor(RGB(0, 0, 255));	// ���ڻ� ����
	}
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}
