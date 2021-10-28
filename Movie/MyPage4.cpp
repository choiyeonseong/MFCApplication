// MyPage4.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Movie.h"
#include "MyPage4.h"
#include "afxdialogex.h"
#include "resource.h"

// CMyPage4 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMyPage4, CPropertyPage)

CMyPage4::CMyPage4()
	: CPropertyPage(IDD_PROPPAGE3)
{

}

CMyPage4::~CMyPage4()
{
}

void CMyPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(CMyPage4, CPropertyPage)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMyPage4::OnSelchangedTree1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMyPage4::OnItemchangedList1)
END_MESSAGE_MAP()


// CMyPage4 �޽��� ó�����Դϴ�.


void CMyPage4::FillTree()
{
	// Ʈ�� ��Ʈ�ѿ��� ����� �̹��� ����Ʈ ����
	m_imageTree.Create(IDB_LIST,16,1,(COLORREF)-1);
	m_Tree.SetImageList(&m_imageTree, TVSIL_NORMAL);

	HTREEITEM hSub = m_Tree.InsertItem(_T("�ó׸� õ��"), 0, 1);	// top
	m_Tree.InsertItem(_T("�Ƹ��Ե�"), 2, 1, hSub);					// first
	m_Tree.InsertItem(_T("�𸶷�"), 2, 1, hSub);					// first
	
	hSub = m_Tree.InsertItem(_T("ŰƮ�� ����"), 0, 1);				// top
	hSub = m_Tree.InsertItem(_T("�������"), 2, 1,hSub);			// first
	m_Tree.InsertItem(_T("�������2"), 3, 1, hSub);					// second

}


void CMyPage4::FillList()
{
	m_List.InsertColumn(0, _T("�ֿ� ���"));	// ��� ��Ʈ���� �÷� ����
	// Ʈ����Ʈ�ѿ��� ����� �̹��� ����Ʈ ����
	m_imageList.Create(IDB_LIST, 16, 1, (COLORREF)-1);
	m_List.SetImageList(&m_imageList, LVSIL_SMALL);

	// ����Ʈ ��Ʈ�ѿ� �׸� �߰�
	m_List.InsertItem(0, _T("�Ѽ���"), 2);
	m_List.InsertItem(1, _T("��罺 ������"), 2);
	m_List.InsertItem(2, _T("�Ը� �õ常"), 2);
	m_List.InsertItem(3, _T("������� ��ȣ"), 2);
	m_List.InsertItem(4, _T("�躴��"), 2);

}

BOOL CMyPage4::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	FillTree();
	FillList();
	return TRUE;
}


void CMyPage4::OnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hSel = pNMTreeView->itemNew.hItem;	// ���õ� �׸��� �ڵ�
	if (hSel != NULL)
	{
		CString strText = m_Tree.GetItemText(hSel);
		SetDlgItemText(IDC_SELECT_TREE, strText);
	}
	*pResult = 0;
}


void CMyPage4::OnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nSel = pNMListView->iItem;	// ���õ� �׸��� �ε���
	if (nSel != -1)
	{
		CString strText = m_List.GetItemText(nSel,0);
		SetDlgItemText(IDC_SELECT_LIST, strText);
	}
	*pResult = 0;
}


BOOL CMyPage4::OnSetActive()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);	// �ڷ�, ��ħ ��ư Ȱ��ȭ
	return CPropertyPage::OnSetActive();
}
