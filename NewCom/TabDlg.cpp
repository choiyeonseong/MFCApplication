// TabDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "NewCom.h"
#include "TabDlg.h"
#include "afxdialogex.h"


// CTabDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTabDlg, CDialog)

CTabDlg::CTabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TABDIALOG, pParent)
{

}

CTabDlg::~CTabDlg()
{
}

void CTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_LIST2, m_List);
	DDX_Control(pDX, IDC_EDIT1, m_Memo);
}

void CTabDlg::FillList()
{
	// ����Ʈ ��Ʈ�ѿ� ��� ��Ʈ���� �߰�
	m_List.AddColumn(0, "���� �̸�");
	m_List.AddColumn(1, "ũ��");
	m_List.AddColumn(2, "���� ��¥");

	CString strFile;
	DWORD dwSize;	// ���� ũ��
	CTime upTime;	// ���� ���� ��¥
	int index = 0;
	BOOL bFind = m_File.FindFile();
	while (bFind)
	{
		bFind = m_File.FindNextFileW();
		strFile = m_File.GetFileName();	// ���� �̸� ����
		dwSize = m_File.GetLength();	// ���� ũ�� ����
		m_File.GetLastWriteTime(upTime);	// ���� ���� ��¥
		if (m_File.IsDirectory())
			;	// ���丮�� ����Ʈ �׸� �߰����� �ʴ´�.
		else
		{	// ������ ��� ����Ʈ �׸� �߰��Ѵ�.
			m_List.AddItem(index, 0, (LPCSTR)(LPCWSTR)strFile);	// ���� ������ �߰�
			strFile.Format(_T("%d KB"), dwSize / 1024);			// ���� ũ�� ���� ����
			m_List.AddItem(index, 1, (LPCSTR)(LPCWSTR)strFile);	// ù��° ���� ������ �߰�
			strFile = upTime.Format("%c");						// ���ŵ� ��¥ ���� ����
			m_List.AddItem(index, 2, (LPCSTR)(LPCWSTR)strFile);	// �ι�° ���� ������ �߰�
			index++;
		}
	}
	m_List.AutoSize();	// ��� ��Ʈ���� ũ�� ����
	m_File.Close();
}


BEGIN_MESSAGE_MAP(CTabDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTabDlg::OnSelchangeTab1)
END_MESSAGE_MAP()


// CTabDlg �޽��� ó�����Դϴ�.

BOOL CTabDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// �� ��Ʈ�ѿ� ����� �̹��� ����
	CImageList imgList;
	imgList.Create(IDB_COMBO, 16, 0, (COLORREF)-1);
	m_Tab.SetImageList(&imgList);
	imgList.Detach();
	// �ǿ� Ÿ��Ʋ�� �̹��� �߰�
	m_Tab.InsertItem(0, _T("Address"), 0);	// (�ε���, ������, �̹��� �ε���)
	m_Tab.InsertItem(1, _T("Memo"), 1);
	m_Tab.InsertItem(2, _T("News"), 2);
	m_Tab.InsertItem(3, _T("Link"), 3);

	m_List.ShowWindow(SW_SHOW);
	m_Memo.ShowWindow(SW_HIDE);
	m_Memo.SetWindowTextW(_T("�޸� �����ּ���."));

	FillList();	// ����Ʈ �׸� �߰�
	return TRUE;
}


void CTabDlg::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int count = m_Tab.GetCurSel();
	switch (count)
	{
	case 0:							// Address �� ���ý�
		m_List.ShowWindow(SW_SHOW);
		m_Memo.ShowWindow(SW_HIDE);
		break;
	case 1:							// Memo �� ���ý�
		m_List.ShowWindow(SW_HIDE);
		m_Memo.ShowWindow(SW_SHOW);
		break;
	case 2:							// News �� ���ý�
		m_List.ShowWindow(SW_HIDE);
		m_Memo.ShowWindow(SW_HIDE);
		break;
	case 3:							// Link �� ���ý�
		m_List.ShowWindow(SW_HIDE);
		m_Memo.ShowWindow(SW_HIDE);
		break;
	}
	*pResult = 0;
}
