
// NewComView.cpp : CNewComView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "NewCom.h"
#endif

#include "NewComDoc.h"
#include "NewComView.h"

#include "TabDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNewComView

IMPLEMENT_DYNCREATE(CNewComView, CFormView)

BEGIN_MESSAGE_MAP(CNewComView, CFormView)
	ON_BN_CLICKED(IDC_RESULT, &CNewComView::OnClickedResult)
	ON_CBN_SELCHANGE(IDC_COMBOBOXEX1, &CNewComView::OnSelchangeComboboxex1)
	ON_BN_CLICKED(IDC_TABDLG_BTN, &CNewComView::OnClickedTabdlgBtn)
END_MESSAGE_MAP()

// CNewComView ����/�Ҹ�

CNewComView::CNewComView()
	: CFormView(IDD_NEWCOM_FORM)
	, m_Month(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CNewComView::~CNewComView()
{
}

void CNewComView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR1, m_Month);
	DDX_Control(pDX, IDC_COMBOBOXEX1, m_Combo);
}

BOOL CNewComView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CNewComView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CString strIP = _T("210.127.234.16");
	SetDlgItemText(IDC_IPADDRESS1, strIP);	// IP �ּ� ��Ʈ���� �ʱⰪ ����
	m_Month = CTime::GetCurrentTime();		// �޷� ��Ʈ���� �ʱⰪ ����
	UpdateData(FALSE);
	// ��Ӵٿ� �޷��� �ؽ�Ʈ�� ��� ������ ����
	GetDlgItem(IDC_DATETIMEPICKER1)->SendMessage(DTM_SETMCCOLOR, MCSC_TITLEBK, (LPARAM)RGB(255, 255, 0));
	GetDlgItem(IDC_DATETIMEPICKER1)->SendMessage(DTM_SETMCCOLOR, MCSC_TITLETEXT, (LPARAM)RGB(255, 0, 0));
	GetDlgItem(IDC_DATETIMEPICKER1)->SendMessage(DTM_SETMCCOLOR, MCSC_MONTHBK, (LPARAM)RGB(0, 0, 255));

	FillComboBox();	// Ȯ��� �޺��ڽ��� �׸��� ä���.

	// ���� ����
	m_Tip.Create(this);	// ���� ������ ����
	m_Tip.SetTipBkColor(RGB(0, 0, 255));	// ���� ���� ����
	m_Tip.SetTipTextColor(RGB(255, 255, 255));	// ���� �ؽ�Ʈ ���� ����
	m_Tip.AddTool(GetDlgItem(IDC_MONTHCALENDAR1), _T("Date Picker ��Ʈ��"));
	m_Tip.AddTool(GetDlgItem(IDC_DATETIMEPICKER1), _T("Date Picker ��Ʈ��"));
	m_Tip.AddTool(GetDlgItem(IDC_DATETIMEPICKER2), _T("Time Picker ��Ʈ��"));
	}


// CNewComView ����

#ifdef _DEBUG
void CNewComView::AssertValid() const
{
	CFormView::AssertValid();
}

void CNewComView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CNewComDoc* CNewComView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNewComDoc)));
	return (CNewComDoc*)m_pDocument;
}
#endif //_DEBUG


// CNewComView �޽��� ó����


void CNewComView::OnClickedResult()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strInfo;
	CString strResult;
	GetDlgItemText(IDC_DATETIMEPICKER1, strInfo);	// Date Picker ���� ����
	strResult = _T("Date Time Picker ��Ʈ��1: ") + strInfo + _T("\r\n");
	GetDlgItemText(IDC_DATETIMEPICKER2, strInfo);	// Time Picker ���� ����
	strResult += _T("Date Time Picker ��Ʈ��2: ") + strInfo + _T("\r\n");
	GetDlgItemText(IDC_IPADDRESS1, strInfo);	// IP �ּ� ��Ʈ���� ���� ����
	strResult += _T("IP �ּ� ��Ʈ��: ") + strInfo + _T("\r\n");
	UpdateData(TRUE);
	strInfo.Format(_T("�޷� ��Ʈ��: %d�� %d�� %d��"), m_Month.GetYear(), m_Month.GetMonth(), m_Month.GetDay());
	strResult += strInfo;
	AfxMessageBox(strResult);
}


HRESULT CNewComView::accDoDefaultAction(VARIANT varChild)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CFormView::accDoDefaultAction(varChild);
}


void CNewComView::FillComboBox()
{
	// Ȯ��� �޺��ڽ��� �׸� ����� �ؽ�Ʈ
	char *stritem[10] =
	{
		"http://www.kitri.re.kr", "a:\\MFC ����",
		"http://www.yahoo.com", "b:\\Image\\icons",
		"mailto:motungi@kitri.re.kr", "c:\\Temp",
		"http://www.visionx.com", "d:\\windows",
		"ftp://www.microsoft.com", "e:\\HNC",
	};
	// Ȯ��� �޺��ڽ����� ����� �̹��� ����
	CImageList imgList;
	imgList.Create(IDB_COMBO, 16, 0, (COLORREF)-1);
	m_Combo.SetImageList(&imgList);
	imgList.Detach();

	//Ȯ��� �޺��ڽ��� �׸� ����
	COMBOBOXEXITEM test;
	test.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_INDENT | CBEIF_SELECTEDIMAGE;
	for (int i = 0; i < 10; i++)
	{
		test.iItem = i;				// �׸� �ε���
		test.pszText =(LPWSTR)(LPCWSTR)stritem[i];	// �׸� ��µ� ���ڿ�(����)
		test.iImage = i;			// �׸��� �̹��� �ε���
		test.iIndent = i;			// �鿩���� ��ġ ����(1�� 10�ȼ�)
		test.iSelectedImage = i;	// ���õ� �׸��� �̹��� �ε���
		m_Combo.InsertItem(&test);	// Ȯ��� �޺� �ڽ��� �׸� �߰�
	}
	m_Combo.SetCurSel(0);
}


void CNewComView::OnSelchangeComboboxex1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nIndex = m_Combo.GetCurSel();	// ���õ� �׸��� �ε���
	CString str;
	m_Combo.GetLBText(nIndex, str);		// �ε����κ��� ���ڿ��� ����
	SetDlgItemText(IDC_SELCOMBO, str);	// ���õ� �׸��� ���ڿ��� ���
}


void CNewComView::OnClickedTabdlgBtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CTabDlg dlg;
	dlg.DoModal();
}

BOOL CNewComView::PreTranslateMessage(MSG* pMsg)
{
	m_Tip.RelayEvent(pMsg);
	return CFormView::PreTranslateMessage(pMsg);
}