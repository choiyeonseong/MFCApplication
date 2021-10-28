
// ImageView.h : CImageView Ŭ������ �������̽�
//

#pragma once


class CImageView : public CView
{
protected: // serialization������ ��������ϴ�.
	CImageView();
	DECLARE_DYNCREATE(CImageView)

// Ư���Դϴ�.
public:
	CImageDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CImageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	void CenterImage(CDC* pDC);
	// ��Ʈ���� �ٵ��� ������� ���
	void TileImage(CDC* pDC);
	// ��Ʈ���� Ŭ���̾�Ʈ ������ ũ�⿡ �°� ���
	void StretchImage(CDC* pDC);

// ��µ� ������ �ĺ��ϱ� ���� ����
public:
	enum IMAGE_TYPE { CENTER, TILE, STRETCH };	// ������ ����
	IMAGE_TYPE m_Type;	// ������ ���� m_Type ����
	afx_msg void OnImageCenter();
	afx_msg void OnImageTile();
	afx_msg void OnImageStretch();
	afx_msg void OnUpdateImageCenter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImageStretch(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImageTile(CCmdUI *pCmdUI);
//	virtual HRESULT accDoDefaultAction(VARIANT varChild);
};

#ifndef _DEBUG  // ImageView.cpp�� ����� ����
inline CImageDoc* CImageView::GetDocument() const
   { return reinterpret_cast<CImageDoc*>(m_pDocument); }
#endif

