// TabDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "NewCom.h"
#include "TabDlg.h"
#include "afxdialogex.h"


// CTabDlg 대화 상자입니다.

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
	// 리스트 컨트롤에 헤더 컨트롤을 추가
	m_List.AddColumn(0, "파일 이름");
	m_List.AddColumn(1, "크기");
	m_List.AddColumn(2, "변경 날짜");

	CString strFile;
	DWORD dwSize;	// 파일 크기
	CTime upTime;	// 파일 갱신 날짜
	int index = 0;
	BOOL bFind = m_File.FindFile();
	while (bFind)
	{
		bFind = m_File.FindNextFileW();
		strFile = m_File.GetFileName();	// 파일 이름 얻음
		dwSize = m_File.GetLength();	// 파일 크기 얻음
		m_File.GetLastWriteTime(upTime);	// 파일 갱신 날짜
		if (m_File.IsDirectory())
			;	// 디렉토리는 리스트 항목에 추가하지 않는다.
		else
		{	// 파일의 경우 리스트 항목에 추가한다.
			m_List.AddItem(index, 0, (LPCSTR)(LPCWSTR)strFile);	// 메인 아이템 추가
			strFile.Format(_T("%d KB"), dwSize / 1024);			// 파일 크기 형식 설정
			m_List.AddItem(index, 1, (LPCSTR)(LPCWSTR)strFile);	// 첫번째 서브 아이템 추가
			strFile = upTime.Format("%c");						// 갱신된 날짜 형식 설정
			m_List.AddItem(index, 2, (LPCSTR)(LPCWSTR)strFile);	// 두번째 서브 아이템 추가
			index++;
		}
	}
	m_List.AutoSize();	// 헤더 컨트롤의 크기 조절
	m_File.Close();
}


BEGIN_MESSAGE_MAP(CTabDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTabDlg::OnSelchangeTab1)
END_MESSAGE_MAP()


// CTabDlg 메시지 처리기입니다.

BOOL CTabDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 탭 컨트롤에 사용할 이미지 설정
	CImageList imgList;
	imgList.Create(IDB_COMBO, 16, 0, (COLORREF)-1);
	m_Tab.SetImageList(&imgList);
	imgList.Detach();
	// 탭에 타이틀과 이미지 추가
	m_Tab.InsertItem(0, _T("Address"), 0);	// (인덱스, 탭제목, 이미지 인덱스)
	m_Tab.InsertItem(1, _T("Memo"), 1);
	m_Tab.InsertItem(2, _T("News"), 2);
	m_Tab.InsertItem(3, _T("Link"), 3);

	m_List.ShowWindow(SW_SHOW);
	m_Memo.ShowWindow(SW_HIDE);
	m_Memo.SetWindowTextW(_T("메모를 남겨주세요."));

	FillList();	// 리스트 항목 추가
	return TRUE;
}


void CTabDlg::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int count = m_Tab.GetCurSel();
	switch (count)
	{
	case 0:							// Address 탭 선택시
		m_List.ShowWindow(SW_SHOW);
		m_Memo.ShowWindow(SW_HIDE);
		break;
	case 1:							// Memo 탭 선택시
		m_List.ShowWindow(SW_HIDE);
		m_Memo.ShowWindow(SW_SHOW);
		break;
	case 2:							// News 탭 선택시
		m_List.ShowWindow(SW_HIDE);
		m_Memo.ShowWindow(SW_HIDE);
		break;
	case 3:							// Link 탭 선택시
		m_List.ShowWindow(SW_HIDE);
		m_Memo.ShowWindow(SW_HIDE);
		break;
	}
	*pResult = 0;
}
