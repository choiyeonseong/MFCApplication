
// LeftView.cpp : CLeftView 클래스의 구현
//

#include "stdafx.h"
#include "ImageL.h"

#include "ImageLDoc.h"
#include "LeftView.h"
#include "ImageLView.h"

#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	ON_COMMAND(ID_DIR_CHANGE, &CLeftView::OnDirChange)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CLeftView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CLeftView 생성/소멸

CLeftView::CLeftView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서 Window 클래스 또는 스타일을 수정합니다.

	return CTreeView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: TreeView를 항목으로 채우려면
	//  GetTreeCtrl()을 호출하여 해당 tree 컨트롤을 직접 액세스하십시오.
	CTreeCtrl& refTree = GetTreeCtrl();		// 트리뷰와 연결된 트리 컨트롤의 참조형을 얻음
	m_imageList.Create(IDB_TREE, 16, 1, (COLORREF)-1);	// 이미지 리스트 생성
	refTree.SetImageList(&m_imageList, TVSIL_NORMAL);	// 트리 컨트롤에 이미지 설정
	RefreshTree(_T("c:\\windows"));			// windows 디렉토리에 있는 비트맵 파일을 출력한다.
}


// CLeftView 진단

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CImageLDoc* CLeftView::GetDocument() // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageLDoc)));
	return (CImageLDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView 메시지 처리기


void CLeftView::RefreshTree(const CString& strPath)
{
	::SetCurrentDirectory(strPath);	// 현재 작업 디렉토리 설정
	CTreeCtrl& refTree = GetTreeCtrl();	// 트리뷰와 연결된 트리 컨트롤의 참조형을 얻음
	refTree.DeleteAllItems();		// 트리 컨트롤의 기존 항목을 모두 제거
	CString data;
	BOOL bFind = m_File.FindFile(_T("*.bmp"));	// 확장자 .bmp만 찾음
	while (bFind)
	{
		bFind = m_File.FindNextFile();
		data = m_File.GetFileName();		// 파일명 얻음
		refTree.InsertItem(data, 0, 1);		// 비트맵 파일만 항목에 추가한다.
	}
	m_File.Close();
}


void CLeftView::OnDirChange()	// 툴바의 디렉토리 변경 버튼을 누른 경우 디렉토리를 설정할수 있는 다이얼로그가 출력된다.
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	char buffer[MAX_PATH];
	LPITEMIDLIST pDirList;
	BROWSEINFO browseInfo;
	browseInfo.hwndOwner = m_hWnd;
	browseInfo.pidlRoot = NULL;
	browseInfo.lpszTitle = _T("디렉토리를 선택하십시오.");
	browseInfo.pszDisplayName = (LPWSTR)buffer;
	browseInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	browseInfo.lpfn = NULL;
	browseInfo.lParam = 0;
	pDirList = SHBrowseForFolder(&browseInfo);
	if (pDirList != NULL)
	{
		SHGetPathFromIDList(pDirList, (LPWSTR)buffer);
		// 사용자가 선택한 경로를 buffer에 저장
		RefreshTree((LPWSTR)buffer);
		// 좌측 페인의 비트맵 파일 목록을 업데이트 한다.
	}
}


void CLeftView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	CTreeCtrl& refTree = GetTreeCtrl();		// 트리뷰와 연결된 트리 컨트롤의 참조형을 얻음
	HTREEITEM hSel = pNMTreeView->itemNew.hItem;	// 선택된 항목이 핸들
	if(hSel!=NULL)		// 항목을 제대로 선택했는지 판단
	{
		CImageLView* pView =
			(CImageLView*)((CSplitterWnd*)GetParent())->GetPane(0, 1);
		char buffer[MAX_PATH];
		::GetCurrentDirectory(sizeof(buffer), (LPWSTR)buffer);	// 현재 디렉토리 얻음
		CString str = (LPWSTR)buffer;
		str = str + "\\" + refTree.GetItemText(hSel);	// 파일의 절대 경로 설정
		pView->RefreshImage(str);						// 우측 페인에 출력될 이미지 갱신
		GetParentFrame()->SetWindowText(str);			// 캡션바에 파일의 절대 경로 출력
	}
	*pResult = 0;
}
