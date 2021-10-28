// MyListCtrl.cpp : 구현 파일입니다.
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



// CMyListCtrl 메시지 처리기입니다.




void CMyListCtrl::AutoSize()
{
	CHeaderCtrl* pHD = (CHeaderCtrl*)GetDlgItem(0);
	pHD->ModifyStyle(0, HDS_HOTTRACK);		// 헤더 컨트롤에 핫트래킹 설정
	int nCount = pHD->GetItemCount();		// 컬럼 개수 얻음
	for (int i = 0; i < nCount; i++)
		SetColumnWidth(i, LVSCW_AUTOSIZE);	// 컬럼의 폭 설정
}

BOOL CMyListCtrl::AddItem(int nItem, int nSubItem, LPCSTR strItem, int nImageIndex)
{
	LV_ITEM lvit;
	lvit.mask = LVIF_TEXT;	// 아이템에서 텍스트를 사용하기 위한 플래그
	lvit.iItem = nItem;	// 아이템의 인덱스
	lvit.iSubItem = nSubItem;	//서브 아이템의 인덱스
	lvit.pszText = (LPWSTR)(LPSTR)strItem;
	if (nImageIndex != -1)	// 이미지를 사용하는 경우
	{
		lvit.mask != LVIF_IMAGE;	// 이미지를 사용하기 위한 플래그 설정
		lvit.iImage = nImageIndex;	// 리스트 컨트롤에서 사용할 이미지 인덱스
	}
	if (nSubItem == 0)
		return InsertItem(&lvit);	// 아이템 삽입
	return SetItem(&lvit);	// 서브 아이템 설정
	return 0;
}

BOOL CMyListCtrl::AddColumn(int nItem, LPCSTR strItem, int nSubItem, int nMask, int nFmt)
{
	LV_COLUMN lvc;
	lvc.mask = nMask;
	lvc.fmt = nFmt;	// 헤더 컨트롤에 출력될 문자열 포맷 설정
	lvc.pszText = (LPWSTR)(LPSTR)strItem;	// 출력될 문자열
	lvc.cx = GetStringWidth(lvc.pszText) + 15;	// 컬럼 폭 설정
	if (nMask&LVCF_SUBITEM)
	{
		if (nSubItem != -1)
			lvc.iSubItem = nSubItem;	// 서브 아이템 설정
		else
			lvc.iSubItem = nItem;		// 아이템 설정
	}
	return InsertColumn(nItem, &lvc);	// 컬럼 추가
}


