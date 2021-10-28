#pragma once


// CMyListCtrl

class CMyListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)

public:
	CMyListCtrl();
	virtual ~CMyListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void AutoSize();	// 헤더 컨트롤의 크기를 자동 조절
	BOOL AddItem(int nItem, int nSubItem,LPCSTR strItem, int nImageIndex = -1);	// 리스트 컨트롤에 아이템 추가
	BOOL AddColumn(int nItem, LPCSTR strItem, int nSubItem = -1, int nMask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_SUBITEM, 
				int nFmt = LVCFMT_LEFT);	// 헤더 컨트롤의 컬럼 설정
};


