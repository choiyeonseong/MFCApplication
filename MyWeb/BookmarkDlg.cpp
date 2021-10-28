// BookmarkDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MyWeb.h"
#include "BookmarkDlg.h"
#include "afxdialogex.h"


// CBookmarkDlg 대화 상자입니다.

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


// CBookmarkDlg 메시지 처리기입니다.


// 레지스트리에 등록된 북마크 내용 로드
void CBookmarkDlg::RegBookmarkLoad()
{
	m_Bookmark.InsertColumn(0, _T("타이틀/인터넷 주소"));	// 헤더 컨트롤의 컬럼 생성
	m_Bookmark.SetColumnWidth(0, 200);
	// 리스트 컨트롤에서 사용할 이미지 리스트 추가
	m_ImgList.Create(IDB_BOOKMARK, 16, 1, (COLORREF)-1);
	m_Bookmark.SetImageList(&m_ImgList, LVSIL_SMALL);

	int count = AfxGetApp()->GetProfileInt(_T("북마크"), _T("Count"), 0);	// 북마크 개수 얻기
	if (count == 0)
	{
		AfxMessageBox(_T("레지스트리에 등록된 북마크가 없습니다."));
		return;
	}
	CString strUrl, entry;
	for (int i = 0; i < count; i++)
	{
		entry.Format(_T("URL %d"), i);
		strUrl = AfxGetApp()->GetProfileString(_T("북마크"), entry, _T("error"));
		m_Bookmark.InsertItem(i, strUrl, 0);	// 리스트 컨트롤에 항목 추가
	}
}


BOOL CBookmarkDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	RegBookmarkLoad();	// 레지스트리에 저장된 북마크 내용 로드
	return TRUE;
}


//void CBookmarkDlg::OnDeleteall()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	m_Bookmark.DeleteAllItems();	// 리스트 컨트롤의 아이템을 모두 삭제
//	HKEY hKey;
//	LONG err;
//	//err = RegOpenKey(HKEY_CURRENT_USER, _T("SOFTWARE\\로컬 응용 프로그램 마법사에서 생성된 응용 프로그램\\MyWeb"), &hKey);
//	err = RegOpenKey(HKEY_CURRENT_USER, _T("SOFTWARE\\Local AppWizard-Generated Applications\\MyWeb"), &hKey);
//	if (err != ERROR_SUCCESS)
//	{
//		AfxMessageBox(_T("레지스트리 열기 실패"));
//		return;
//	}
//	RegDeleteKey(hKey, _T("북마크"));	// 레지스트리에 등록된 서브키("북마크") 삭제
//	RegCloseKey(hKey);
//}


void CBookmarkDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnCancel();
	 // TODO: 여기에 명령 처리기 코드를 추가합니다.
		m_Bookmark.DeleteAllItems();	// 리스트 컨트롤의 아이템을 모두 삭제
		HKEY hKey;
		LONG err;
		err = RegOpenKey(HKEY_CURRENT_USER, _T("SOFTWARE\\로컬 응용 프로그램 마법사에서 생성된 응용 프로그램\\MyWeb"), &hKey);
		//err = RegOpenKey(HKEY_CURRENT_USER, _T("SOFTWARE\\Local AppWizard-Generated Applications\\MyWeb"), &hKey);
		if (err != ERROR_SUCCESS)
		{
			AfxMessageBox(_T("레지스트리 열기 실패"));
			return;
		}
		RegDeleteKey(hKey, _T("북마크"));	// 레지스트리에 등록된 서브키("북마크") 삭제
		RegCloseKey(hKey);
}
