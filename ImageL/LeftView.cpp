
// LeftView.cpp : CLeftView Ŭ������ ����
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


// CLeftView ����/�Ҹ�

CLeftView::CLeftView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡�� Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CTreeView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: TreeView�� �׸����� ä�����
	//  GetTreeCtrl()�� ȣ���Ͽ� �ش� tree ��Ʈ���� ���� �׼����Ͻʽÿ�.
	CTreeCtrl& refTree = GetTreeCtrl();		// Ʈ����� ����� Ʈ�� ��Ʈ���� �������� ����
	m_imageList.Create(IDB_TREE, 16, 1, (COLORREF)-1);	// �̹��� ����Ʈ ����
	refTree.SetImageList(&m_imageList, TVSIL_NORMAL);	// Ʈ�� ��Ʈ�ѿ� �̹��� ����
	RefreshTree(_T("c:\\windows"));			// windows ���丮�� �ִ� ��Ʈ�� ������ ����Ѵ�.
}


// CLeftView ����

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CImageLDoc* CLeftView::GetDocument() // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageLDoc)));
	return (CImageLDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView �޽��� ó����


void CLeftView::RefreshTree(const CString& strPath)
{
	::SetCurrentDirectory(strPath);	// ���� �۾� ���丮 ����
	CTreeCtrl& refTree = GetTreeCtrl();	// Ʈ����� ����� Ʈ�� ��Ʈ���� �������� ����
	refTree.DeleteAllItems();		// Ʈ�� ��Ʈ���� ���� �׸��� ��� ����
	CString data;
	BOOL bFind = m_File.FindFile(_T("*.bmp"));	// Ȯ���� .bmp�� ã��
	while (bFind)
	{
		bFind = m_File.FindNextFile();
		data = m_File.GetFileName();		// ���ϸ� ����
		refTree.InsertItem(data, 0, 1);		// ��Ʈ�� ���ϸ� �׸� �߰��Ѵ�.
	}
	m_File.Close();
}


void CLeftView::OnDirChange()	// ������ ���丮 ���� ��ư�� ���� ��� ���丮�� �����Ҽ� �ִ� ���̾�αװ� ��µȴ�.
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	char buffer[MAX_PATH];
	LPITEMIDLIST pDirList;
	BROWSEINFO browseInfo;
	browseInfo.hwndOwner = m_hWnd;
	browseInfo.pidlRoot = NULL;
	browseInfo.lpszTitle = _T("���丮�� �����Ͻʽÿ�.");
	browseInfo.pszDisplayName = (LPWSTR)buffer;
	browseInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	browseInfo.lpfn = NULL;
	browseInfo.lParam = 0;
	pDirList = SHBrowseForFolder(&browseInfo);
	if (pDirList != NULL)
	{
		SHGetPathFromIDList(pDirList, (LPWSTR)buffer);
		// ����ڰ� ������ ��θ� buffer�� ����
		RefreshTree((LPWSTR)buffer);
		// ���� ������ ��Ʈ�� ���� ����� ������Ʈ �Ѵ�.
	}
}


void CLeftView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	CTreeCtrl& refTree = GetTreeCtrl();		// Ʈ����� ����� Ʈ�� ��Ʈ���� �������� ����
	HTREEITEM hSel = pNMTreeView->itemNew.hItem;	// ���õ� �׸��� �ڵ�
	if(hSel!=NULL)		// �׸��� ����� �����ߴ��� �Ǵ�
	{
		CImageLView* pView =
			(CImageLView*)((CSplitterWnd*)GetParent())->GetPane(0, 1);
		char buffer[MAX_PATH];
		::GetCurrentDirectory(sizeof(buffer), (LPWSTR)buffer);	// ���� ���丮 ����
		CString str = (LPWSTR)buffer;
		str = str + "\\" + refTree.GetItemText(hSel);	// ������ ���� ��� ����
		pView->RefreshImage(str);						// ���� ���ο� ��µ� �̹��� ����
		GetParentFrame()->SetWindowText(str);			// ĸ�ǹٿ� ������ ���� ��� ���
	}
	*pResult = 0;
}
