// MyListCtrl.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "NewCom.h"
#include "MyListCtrl.h"


// CMyListCtrl

IMPLEMENT_DYNAMIC(CMyListCtrl, CListCtrl)

CMyListCtrl::CMyListCtrl()
{

}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
END_MESSAGE_MAP()



// CMyListCtrl �޽��� ó�����Դϴ�.




void CMyListCtrl::AutoSize()
{
	CHeaderCtrl* pHD = (CHeaderCtrl*)GetDlgItem(0);
	pHD->ModifyStyle(0, HDS_HOTTRACK);		// ��� ��Ʈ�ѿ� ��Ʈ��ŷ ����
	int nCount = pHD->GetItemCount();		// �÷� ���� ����
	for (int i = 0; i < nCount; i++)
		SetColumnWidth(i, LVSCW_AUTOSIZE);	// �÷��� �� ����
}

BOOL CMyListCtrl::AddItem(int nItem, int nSubItem, LPCSTR strItem, int nImageIndex)
{
	LV_ITEM lvit;
	lvit.mask = LVIF_TEXT;	// �����ۿ��� �ؽ�Ʈ�� ����ϱ� ���� �÷���
	lvit.iItem = nItem;	// �������� �ε���
	lvit.iSubItem = nSubItem;	//���� �������� �ε���
	lvit.pszText = (LPWSTR)(LPSTR)strItem;
	if (nImageIndex != -1)	// �̹����� ����ϴ� ���
	{
		lvit.mask != LVIF_IMAGE;	// �̹����� ����ϱ� ���� �÷��� ����
		lvit.iImage = nImageIndex;	// ����Ʈ ��Ʈ�ѿ��� ����� �̹��� �ε���
	}
	if (nSubItem == 0)
		return InsertItem(&lvit);	// ������ ����
	return SetItem(&lvit);	// ���� ������ ����
	return 0;
}

BOOL CMyListCtrl::AddColumn(int nItem, LPCSTR strItem, int nSubItem, int nMask, int nFmt)
{
	LV_COLUMN lvc;
	lvc.mask = nMask;
	lvc.fmt = nFmt;	// ��� ��Ʈ�ѿ� ��µ� ���ڿ� ���� ����
	lvc.pszText = (LPWSTR)(LPSTR)strItem;	// ��µ� ���ڿ�
	lvc.cx = GetStringWidth(lvc.pszText) + 15;	// �÷� �� ����
	if (nMask&LVCF_SUBITEM)
	{
		if (nSubItem != -1)
			lvc.iSubItem = nSubItem;	// ���� ������ ����
		else
			lvc.iSubItem = nItem;		// ������ ����
	}
	return InsertColumn(nItem, &lvc);	// �÷� �߰�
}


