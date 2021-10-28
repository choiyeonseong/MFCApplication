
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "MyWeb.h"

#include "MainFrm.h"
#include "MyWebDoc.h"
#include "MyWebView.h"	// �� Ŭ������ ��������� �����Ұ��, ��ť��Ʈ Ŭ������ ��������� ���� �����ؾ��Ѵ�.

#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_URL_COMBO, &CMainFrame::OnCbnSelchangeUrlCombo)
	ON_COMMAND(ID_VIEW_URLBAR, &CMainFrame::OnViewUrlbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_URLBAR, &CMainFrame::OnUpdateViewUrlbar)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_SEPARATOR,           // ���α׷��� ��Ʈ���� ��ġ�� ����
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("���� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("���� ǥ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	// TODO: ���� ������ ��ŷ�� �� ���� �Ϸ��� �� �� ���� �����Ͻʽÿ�.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	InitProgress();	// ���¹ٿ� ���α׷��� ��Ʈ�� ����

	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, CBRS_ALIGN_TOP, IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;
	}

	CComboBoxEx* pCombo = (CComboBoxEx*)(m_wndDlgBar.GetDlgItem(IDC_URL_COMBO));
	m_imgCombo.Create(IDB_BOOKMARK, 17, 0, (COLORREF)-1);
	pCombo->SetImageList(&m_imgCombo);	// �޺��ڽ��� �̹��� ����Ʈ �߰�

	//InitAnimation();	// ���ٿ� �ִϸ��̼� ��Ʈ�� ����

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	cs.style &= ~FWS_ADDTOTITLE;
	return TRUE;
}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame �޽��� ó����



// ���α׷��� ��Ʈ�� ����
void CMainFrame::InitProgress()
{
	m_wndStatusBar.SetPaneInfo(1, ID_SEPARATOR, ID_SEPARATOR, 100);
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | PBS_SMOOTH;
	m_Progress.Create(dwStyle, CRect(0, 0, 0, 0), &m_wndStatusBar, IDW_PROGRESS);
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	//// �ִϸ��̼� ��Ʈ���� ��ġ�� ���� ������ ���� ��ġ�ϵ��� �Ѵ�.
	//if (m_wndToolBar.GetSafeHwnd())	// ���ٰ� �����Ǿ����� �Ǵ�
	//{
	//	// �ִϸ��̼� ��Ʈ���� ��ġ�� ������ �����Ѵ�.
	//	CRect rect;
	//	m_wndToolBar.GetClientRect(rect);
	//	rect.left = cx - 70;
	//	rect.right = cx;
	//	m_Animate.MoveWindow(rect);	// �ִϸ��̼� ��Ʈ���� ��ġ �̵�
	//}

	// ���¹��� �ι�° ���� ũ�⿡ �°� ���α׷��� ��Ʈ���� �����Ѵ�.
	if (m_wndStatusBar.GetSafeHwnd())
	{
		CRect rect;
		m_wndStatusBar.GetItemRect(1, &rect);	// ���¹��� �ι�° ���� ũ�� ����
		m_Progress.MoveWindow(rect);
	}

	// ���� ������ ũ�� ����� �޺� �ڽ� ��ġ�� �����Ѵ�.
	if (m_wndDlgBar.GetSafeHwnd())	// ���̾�α� �ٰ� �����Ǿ����� �Ǵ�
	{
		CRect rect;
		m_wndDlgBar.GetClientRect(rect);
		rect.left += 100;
		rect.right = cx - 10;
		m_wndDlgBar.GetDlgItem(IDC_URL_COMBO)->MoveWindow(rect);
	}

}


BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CComboBoxEx* pCombo =(CComboBoxEx*)(m_wndDlgBar.GetDlgItem(IDC_URL_COMBO));
	CEdit* pEdit = pCombo->GetEditCtrl();	// �޺��ڽ��� ����Ʈ ��Ʈ��
	// URL ���� �޺��ڽ����� Enter Ű�� ���ȴ��� Ȯ��
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
	{
		if (GetFocus() == pEdit)	// �޺��ڽ��� ����Ʈ ��Ʈ���� ��Ŀ���� ������ �Ǵ�
		{
			CString strUrl;
			// �޺� �ڽ��� ����Ʈ ��Ʈ�� ������ ���ڿ� ����
			pCombo->GetEditCtrl()->GetWindowText(strUrl);
			// ���� Ȱ��ȭ�� �� ��ü�� �����͸� ��´�.
			CMyWebView* pView = (CMyWebView*)GetActiveView();
			pView->m_Web.Navigate(strUrl, NULL, NULL, NULL, NULL);
			AddUrl((LPCSTR)(LPCWSTR)strUrl);	// �޺� �ڽ��� ���ͳ� �ּ� �߰�
		}
	}
	return CFrameWnd::PreTranslateMessage(pMsg);
}

void CMainFrame::AddUrl(LPCSTR strUrl)	// �޺��ڽ��� Url�߰��ϴ� �Լ�
{
	CComboBoxEx* pCombo = (CComboBoxEx*)(m_wndDlgBar.GetDlgItem(IDC_URL_COMBO));
	COMBOBOXEXITEM test;
	test.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_SELECTEDIMAGE;
	test.iItem = 0;					// ������ �ε���
	test.pszText = (LPWSTR)strUrl;	// �������� �ؽ�Ʈ
	test.iImage = 0;				// �������� �̹��� �ε���
	test.iSelectedImage = 0;		// ���õǾ����� �������� �̹��� �ε���
	pCombo->InsertItem(&test);		// Ȯ��� �޺��ڽ��� ������ �߰�
	pCombo->SetCurSel(0);
}


void CMainFrame::OnCbnSelchangeUrlCombo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// Url ���� �޺� �ڽ����� ���ͳ� �ּҸ� �����Ҷ�
	CComboBoxEx* pCombo = (CComboBoxEx*)(m_wndDlgBar.GetDlgItem(IDC_URL_COMBO));
	int nIndex = pCombo->GetCurSel();	// ���õ� �׸��� �ε���
	CString str;
	pCombo->GetLBText(nIndex, str);	// �ε����� �ش��ϴ� ���ڿ� ����
	pCombo->SetCurSel(nIndex);
	CMyWebView* pView = (CMyWebView*)GetActiveView();
	pView->m_Web.Navigate(str, NULL, NULL, NULL, NULL);	// �� ����Ʈ �̵�
}


void CMainFrame::OnViewUrlbar()	// URL�ٸ� ǥ���ϰų� �����
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	BOOL bShow = (m_wndDlgBar.IsWindowVisible() != 0);	// URL�ٰ� ���̴��� �Ǵ�
	ShowControlBar(&m_wndDlgBar, !bShow, FALSE);	// ��� �������� URL�� ǥ��/����
	RecalcLayout();	// ���� �����츦 ������
}


void CMainFrame::OnUpdateViewUrlbar(CCmdUI *pCmdUI)	// URL�ٰ� ��µ� �����̸� �޴��� �ɼ� ��ũ�� ǥ��
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetRadio(m_wndDlgBar.IsWindowVisible());
}


//// �ִϸ��̼� ��Ʈ�� ����
//void CMainFrame::InitAnimation()
//{
//	m_wndToolBar.SetButtonInfo(10, ID_SEPARATOR, TBBS_SEPARATOR, 70);
//	DWORD dwStyle = WS_CHILD | WS_VISIBLE | ACS_CENTER;	// ������ ��Ÿ��
//	m_Animate.Create(dwStyle, CRect(0, 0, 0, 0), &m_wndToolBar, IDW_ANIMATE);
//	m_Animate.Open(IDR_ANIMATION1);
//}
