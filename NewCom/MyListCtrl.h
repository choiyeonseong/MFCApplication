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
	void AutoSize();	// ��� ��Ʈ���� ũ�⸦ �ڵ� ����
	BOOL AddItem(int nItem, int nSubItem,LPCSTR strItem, int nImageIndex = -1);	// ����Ʈ ��Ʈ�ѿ� ������ �߰�
	BOOL AddColumn(int nItem, LPCSTR strItem, int nSubItem = -1, int nMask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_SUBITEM, 
				int nFmt = LVCFMT_LEFT);	// ��� ��Ʈ���� �÷� ����
};


