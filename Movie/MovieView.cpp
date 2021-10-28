
// MovieView.cpp : CMovieView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Movie.h"
#endif

#include "MovieDoc.h"
#include "MovieView.h"
#include "DataDlg.h"
#include "MySheet.h"

#include "resource.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMovieView

IMPLEMENT_DYNCREATE(CMovieView, CFormView)

BEGIN_MESSAGE_MAP(CMovieView, CFormView)
	ON_BN_CLICKED(IDC_FORM_MODAL, &CMovieView::OnFormModal)
	ON_BN_CLICKED(IDC_FORM_MODALESS2, &CMovieView::OnCFormModaless)
	ON_BN_CLICKED(IDC_FORM_PROPERTY, &CMovieView::OnClickedFormProperty)
	ON_BN_CLICKED(IDC_FORM_WIZARD, &CMovieView::OnClickedFormWizard)
	ON_COMMAND(ID_POPUP_OPEN, &CMovieView::OnPopupOpen)
	ON_COMMAND(ID_POPUP_COLOR, &CMovieView::OnPopupColor)
	ON_COMMAND(ID_POPUP_EXIT, &CMovieView::OnPopupExit)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

// CMovieView ����/�Ҹ�

CMovieView::CMovieView() : CFormView(IDD_MOVIE_FORM)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_pDlg = NULL;	// �ʱ�ȭ
}

CMovieView::~CMovieView()
{
}

void CMovieView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMovieView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CMovieView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	
}


// CMovieView ����

#ifdef _DEBUG
void CMovieView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMovieView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMovieDoc* CMovieView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMovieDoc)));
	return (CMovieDoc*)m_pDocument;
}
#endif //_DEBUG


// CMovieView �޽��� ó����


void CMovieView::OnFormModal()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDataDlg dlg;


	if (dlg.DoModal() == IDOK)	// OK ��ư ������
		SetDlgItemText(IDC_FORM_COUNT, dlg.m_strCount);
}


void CMovieView::OnCFormModaless()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_pDlg->GetSafeHwnd() == NULL)	// ���� ��޸��� ���̾�αװ� �ִ��� �Ǵ�
	{
		m_pDlg = new CPixelDlg;	// �� �޸𸮿� ���̾�α� ��ü�� �����Ѵ�.
		m_pDlg->Create(IDD_MODALESS);
		m_pDlg->ShowWindow(SW_SHOW);

	}
}


void CMovieView::OnProperties()
{
	// ������Ʈ �������� ���� �߰��� �ڵ�κ�����
	// ������Ƽ ���̾�α׸� ȭ�鿡 ����Ѵ�.
	CMySheet propSheet;
	propSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;	// ���� ��ư ����
	propSheet.DoModal();

}


void CMovieView::OnClickedFormProperty()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnProperties();	// ������Ʈ �������� ���� �߰��� �Լ��� ȣ��
}


void CMovieView::OnClickedFormWizard()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMySheet propSheet;
	propSheet.SetWizardMode();	// ������ ���̾�α� ���� ����
	propSheet.DoModal();
}


void CMovieView::OnPopupOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog dlg(TRUE);	// ���� ���̾�α� ��ü ����/ FALSE�� ���� ���̾�α� ����
	if (dlg.DoModal() == IDOK)	// ���� ���̾�α� ���
	{
		ShellExecute(NULL, _T("open"), dlg.GetFileName(), NULL, NULL, SW_SHOW);	// �ý��ۿ� ��ϵ� Ȯ���ڿ� ����� ���α׷��� �����ϰ� ���õ� ������ ����
	}
}


void CMovieView::OnPopupColor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		COLORREF color = dlg.GetColor();	// ���� ���õ� ������ ����
		CString strInfo;
		strInfo.Format(_T("Red: %d, Green: %d, Blue: %d"), GetRValue(color), GetGValue(color), GetBValue(color));
		AfxMessageBox(strInfo);
	}
}


void CMovieView::OnPopupExit()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxGetMainWnd()->PostMessageW(WM_QUIT);	// ���α׷� ����
}


void CMovieView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CRect rc;
	CStatic* pFrame = (CStatic*)GetDlgItem(IDC_FORM_IMAGE);
	pFrame->GetWindowRect(rc);	// ��ũ�� ��ǥ�踦 ���������� �簢�� ����
	if (rc.PtInRect(point))	// ���콺 Ŀ���� ���� ��Ʈ�� ���� �ִ��� �Ǵ�
	{
		CMenu menu;
		menu.LoadMenuW(IDR_POPUP);	// �޴� ���ҽ� �ε�
		CMenu* pPopup = menu.GetSubMenu(0);	// ����� ���� �޴��� ��ü ������
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}
