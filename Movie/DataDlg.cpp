// DataDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Movie.h"
#include "DataDlg.h"
#include "afxdialogex.h"
#include "resource.h"


// CDataDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDataDlg, CDialog)

CDataDlg::CDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_strEdit3(_T(""))
	, m_strCount(_T(""))
	, m_strStatic3(_T(""))
{

}

CDataDlg::~CDataDlg()
{
}

void CDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_ctlEdit2);
	DDX_Text(pDX, IDC_EDIT3, m_strEdit3);
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
	DDX_Text(pDX, IDC_STATIC_COUNT, m_strCount);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_ImageCtrl);
	DDX_Control(pDX, IDC_STATIC2, m_ctlStatic2);
	DDX_Text(pDX, IDC_STATIC3, m_strStatic3);
}


BEGIN_MESSAGE_MAP(CDataDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDataDlg::OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDataDlg::OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDataDlg::OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDataDlg::OnButton4)
	ON_BN_CLICKED(IDC_COMBO_ADD, &CDataDlg::OnComboAdd)
	ON_BN_CLICKED(IDC_LIST_ADD, &CDataDlg::OnListAdd)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDataDlg::OnSelchangeCombo1)
	ON_LBN_DBLCLK(IDC_LIST1, &CDataDlg::OnDblclkList1)
	ON_COMMAND(IDC_RADIO1, &CDataDlg::OnRadio1)
	ON_COMMAND(IDC_RADIO2, &CDataDlg::OnRadio2)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CDataDlg �޽��� ó�����Դϴ�.


void CDataDlg::OnButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	GetDlgItemText(IDC_EDIT1, str);		// IDC_EDIT1�� �Է��� ���ڿ��� ����
	SetDlgItemText(IDC_STATIC1, str);	// IDC_STATIC1�� ���ڿ��� ���
}


void CDataDlg::OnButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ��Ʈ���� �̿��ϴ� ���(Category - Control)
	CString str;
	m_ctlEdit2.GetWindowTextW(str);		// CEdit�� �������
	m_ctlStatic2.SetWindowTextW(str);	// CStatic�� �������
}


void CDataDlg::OnButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ������ ���� �̿��ϴ� ���(Category - Value)
	UpdateData(TRUE);
	m_strStatic3 = m_strEdit3;	// CString�� �������
	UpdateData(FALSE);
}


void CDataDlg::OnButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ��ü �����͸� �̿��ϴ� ���
	CString str;
	CEdit* pE4 = (CEdit*)GetDlgItem(IDC_EDIT4);	// ��Ʈ�� ID�� �ش��ϴ� ��ü�� ���� �����͸� ����
	pE4->GetWindowTextW(str);

	CStatic* pS4 = (CStatic*)GetDlgItem(IDC_STATIC4);
	pS4->SetWindowTextW(str);
}


void CDataDlg::OnComboAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	GetDlgItemText(IDC_EDIT1, str);
	m_Combo.AddString(str);

	GetDlgItemText(IDC_EDIT2, str);
	m_Combo.AddString(str);

	GetDlgItemText(IDC_EDIT3, str);
	m_Combo.AddString(str);

	GetDlgItemText(IDC_EDIT4, str);
	m_Combo.AddString(str);
	m_Combo.SetCurSel(0);	// ù��° �׸��� ���� ���õ� �׸����� �����Ѵ�.
}


void CDataDlg::OnListAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST1);
	GetDlgItemText(IDC_EDIT1, str);
	pList->AddString(str);

	GetDlgItemText(IDC_EDIT2, str);
	pList->AddString(str);

	GetDlgItemText(IDC_EDIT3, str);
	pList->AddString(str);

	GetDlgItemText(IDC_EDIT4, str);
	pList->AddString(str);

	pList->SetCurSel(2);	// ����° �׸��� ���� ���õ� �׸����� �����Ѵ�.
}


void CDataDlg::OnSelchangeCombo1()	// �޺� �ڽ��� �׸��� ������ ��
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nIndex;
	nIndex = m_Combo.GetCurSel();	// ���� ���õ� �׸��� �ε����� ����

	CString str;
	m_Combo.GetLBText(nIndex, str);	// �ε����� �ش��ϴ� �׸��� ���ڿ� ����
	SetDlgItemText(IDC_STATIC_COMBO, str);	// ���õ� �׸��� ���ڿ� ���
}


void CDataDlg::OnDblclkList1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nIndex;
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST1);
	nIndex = pList->GetCurSel();	// ���� ���õ� �׸��� �ε����� ����
	
	CString str;
	pList->GetText(nIndex, str);	// �ε����� �ش��ϴ� �׸��� ���ڿ� ����
	SetDlgItemText(IDC_STATIC_LIST, str);	// ���õ� �׸��� ���ڿ� ���
}

BOOL CDataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// ���� ��ư ��Ʈ��
	CButton* pOption = (CButton*)GetDlgItem(IDC_RADIO1);
	pOption->SetCheck(1);	// ���� ��ư [��Ʈ��]�� ����
	m_imgBatman.LoadBitmapW(IDB_CHUN);			// ��Ʈ�� ���ҽ� �ε�
	m_imgBatgirl.LoadBitmapW(IDB_BATGIRL);		// ��Ʈ�� ���ҽ� �ε�
	
	// ��ũ�ѹ� ��Ʈ��
	CScrollBar* pScroll = (CScrollBar*)GetDlgItem(IDC_SCROLLBAR1);
	pScroll->SetScrollRange(0, 100);	// ��ũ�ѹ��� ���� ����
	pScroll->SetScrollPos(0);			// ��ũ�ѹ��� �ʱ� ��ġ ����

	return TRUE;
}


void CDataDlg::OnRadio1()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_ImageCtrl.SetBitmap(m_imgBatman);
}


void CDataDlg::OnRadio2()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_ImageCtrl.SetBitmap(m_imgBatgirl);
}


void CDataDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	UINT nTemp;
	nTemp = pScrollBar->GetScrollPos();	// ���� ��ũ�� �ڽ�(Thumb)�� ��ġ
	switch (nSBCode)	// ��ũ�ѹ��� ��� �κ��� Ŭ���ߴ��� �Ǵ�
	{
	case SB_LINELEFT:	// ���� ȭ��ǥ ��ư Ŭ����
		if (nTemp > 0)
			nTemp -= 5;	// ���� ��ġ���� �·� 5��ŭ �̵�
		else
			nTemp = 0;
		pScrollBar->SetScrollPos(nTemp);
		break;
	case SB_PAGELEFT:	// Thumb�� ���� ȭ��ǥ ��ư ���� Ŭ����
		if (nTemp >= 0)
			nTemp -= 20;	// ���� ��ġ���� �·� 20��ŭ �̵�
		else
			nTemp = 0;
		pScrollBar->SetScrollPos(nTemp);
		break;
	case SB_LINERIGHT:	// ���� ȭ��ǥ ��ư Ŭ����
		if (nTemp <100)
			nTemp += 5;	// ���� ��ġ���� ��� 5��ŭ �̵�
		else
			nTemp = 100;
		pScrollBar->SetScrollPos(nTemp);
		break;
	case SB_PAGERIGHT:	// Thumb�� ���� ȭ��ǥ ��ư���� Ŭ����
		if (nTemp <= 90)
			nTemp += 20;	// ���� ��ġ���� ��� 20��ŭ �̵�
		else
			nTemp = 0;
		pScrollBar->SetScrollPos(nTemp);
		break;
	case SB_THUMBTRACK:	// Thumb�� �巡��&����� ��
		nTemp = nPos;
		pScrollBar->SetScrollPos(nTemp);
		break;
	}
	CString str;
	str.Format(_T("%d%%"), nTemp);
	m_strCount = str;
	UpdateData(FALSE);		// ��������� ������ ���� ����Ѵ�.
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
