// BookmarkDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MyWeb.h"
#include "BookmarkDlg.h"
#include "afxdialogex.h"


// CBookmarkDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CBookmarkDlg, CDialog)

CBookmarkDlg::CBookmarkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_BOOKMARK, pParent)
{

}

CBookmarkDlg::~CBookmarkDlg()
{
}

void CBookmarkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOOKMARK_LIST, m_Bookmark);
}


BEGIN_MESSAGE_MAP(CBookmarkDlg, CDialog)
//	ON_COMMAND(ID_DELETEALL, &CBookmarkDlg::OnDeleteall)
	ON_BN_CLICKED(IDCANCEL, &CBookmarkDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CBookmarkDlg �޽��� ó�����Դϴ�.


// ������Ʈ���� ��ϵ� �ϸ�ũ ���� �ε�
void CBookmarkDlg::RegBookmarkLoad()
{
	m_Bookmark.InsertColumn(0, _T("Ÿ��Ʋ/���ͳ� �ּ�"));	// ��� ��Ʈ���� �÷� ����
	m_Bookmark.SetColumnWidth(0, 200);
	// ����Ʈ ��Ʈ�ѿ��� ����� �̹��� ����Ʈ �߰�
	m_ImgList.Create(IDB_BOOKMARK, 16, 1, (COLORREF)-1);
	m_Bookmark.SetImageList(&m_ImgList, LVSIL_SMALL);

	int count = AfxGetApp()->GetProfileInt(_T("�ϸ�ũ"), _T("Count"), 0);	// �ϸ�ũ ���� ���
	if (count == 0)
	{
		AfxMessageBox(_T("������Ʈ���� ��ϵ� �ϸ�ũ�� �����ϴ�."));
		return;
	}
	CString strUrl, entry;
	for (int i = 0; i < count; i++)
	{
		entry.Format(_T("URL %d"), i);
		strUrl = AfxGetApp()->GetProfileString(_T("�ϸ�ũ"), entry, _T("error"));
		m_Bookmark.InsertItem(i, strUrl, 0);	// ����Ʈ ��Ʈ�ѿ� �׸� �߰�
	}
}


BOOL CBookmarkDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	RegBookmarkLoad();	// ������Ʈ���� ����� �ϸ�ũ ���� �ε�
	return TRUE;
}


//void CBookmarkDlg::OnDeleteall()
//{
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//	m_Bookmark.DeleteAllItems();	// ����Ʈ ��Ʈ���� �������� ��� ����
//	HKEY hKey;
//	LONG err;
//	//err = RegOpenKey(HKEY_CURRENT_USER, _T("SOFTWARE\\���� ���� ���α׷� �����翡�� ������ ���� ���α׷�\\MyWeb"), &hKey);
//	err = RegOpenKey(HKEY_CURRENT_USER, _T("SOFTWARE\\Local AppWizard-Generated Applications\\MyWeb"), &hKey);
//	if (err != ERROR_SUCCESS)
//	{
//		AfxMessageBox(_T("������Ʈ�� ���� ����"));
//		return;
//	}
//	RegDeleteKey(hKey, _T("�ϸ�ũ"));	// ������Ʈ���� ��ϵ� ����Ű("�ϸ�ũ") ����
//	RegCloseKey(hKey);
//}


void CBookmarkDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialog::OnCancel();
	 // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
		m_Bookmark.DeleteAllItems();	// ����Ʈ ��Ʈ���� �������� ��� ����
		HKEY hKey;
		LONG err;
		err = RegOpenKey(HKEY_CURRENT_USER, _T("SOFTWARE\\���� ���� ���α׷� �����翡�� ������ ���� ���α׷�\\MyWeb"), &hKey);
		//err = RegOpenKey(HKEY_CURRENT_USER, _T("SOFTWARE\\Local AppWizard-Generated Applications\\MyWeb"), &hKey);
		if (err != ERROR_SUCCESS)
		{
			AfxMessageBox(_T("������Ʈ�� ���� ����"));
			return;
		}
		RegDeleteKey(hKey, _T("�ϸ�ũ"));	// ������Ʈ���� ��ϵ� ����Ű("�ϸ�ũ") ����
		RegCloseKey(hKey);
}
