// MyPage4.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Movie.h"
#include "MyPage4.h"
#include "afxdialogex.h"
#include "resource.h"

// CMyPage4 대화 상자입니다.

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


// CMyPage4 메시지 처리기입니다.


void CMyPage4::FillTree()
{
	// 트리 컨트롤에서 사용할 이미지 리스트 생성
	m_imageTree.Create(IDB_LIST,16,1,(COLORREF)-1);
	m_Tree.SetImageList(&m_imageTree, TVSIL_NORMAL);

	HTREEITEM hSub = m_Tree.InsertItem(_T("시네마 천국"), 0, 1);	// top
	m_Tree.InsertItem(_T("아마게돈"), 2, 1, hSub);					// first
	m_Tree.InsertItem(_T("퇴마록"), 2, 1, hSub);					// first
	
	hSub = m_Tree.InsertItem(_T("키트리 극장"), 0, 1);				// top
	hSub = m_Tree.InsertItem(_T("동방불패"), 2, 1,hSub);			// first
	m_Tree.InsertItem(_T("동방불패2"), 3, 1, hSub);					// second

}


void CMyPage4::FillList()
{
	m_List.InsertColumn(0, _T("주연 배우"));	// 헤더 컨트롤의 컬럼 생성
	// 트리컨트롤에서 사용할 이미지 리스트 생성
	m_imageList.Create(IDB_LIST, 16, 1, (COLORREF)-1);
	m_List.SetImageList(&m_imageList, LVSIL_SMALL);

	// 리스트 컨트롤에 항목 추가
	m_List.InsertItem(0, _T("한석규"), 2);
	m_List.InsertItem(1, _T("브루스 윌리스"), 2);
	m_List.InsertItem(2, _T("게리 올드만"), 2);
	m_List.InsertItem(3, _T("드까프리 성호"), 2);
	m_List.InsertItem(4, _T("김병세"), 2);

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hSel = pNMTreeView->itemNew.hItem;	// 선택된 항목의 핸들
	if (hSel != NULL)
	{
		CString strText = m_Tree.GetItemText(hSel);
		SetDlgItemText(IDC_SELECT_TREE, strText);
	}
	*pResult = 0;
}


void CMyPage4::OnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nSel = pNMListView->iItem;	// 선택된 항목의 인덱스
	if (nSel != -1)
	{
		CString strText = m_List.GetItemText(nSel,0);
		SetDlgItemText(IDC_SELECT_LIST, strText);
	}
	*pResult = 0;
}


BOOL CMyPage4::OnSetActive()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);	// 뒤로, 마침 버튼 활성화
	return CPropertyPage::OnSetActive();
}
