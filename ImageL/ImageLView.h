
// ImageLView.h : CImageLView Ŭ������ �������̽�
//

#pragma once


class CImageLView : public CView
{
protected: // serialization������ ��������ϴ�.
	CImageLView();
	DECLARE_DYNCREATE(CImageLView)

// Ư���Դϴ�.
public:
	CImageLDoc* GetDocument() const;

	void RefreshImage(CString strPath);

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CImageLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
protected:
	HBITMAP m_hBitmap;
	CBitmap* m_pImage;
	DWORD	m_fileSize;
public:
	afx_msg void OnDestroy();
	void CenterImage(CDC * pDC);
};

#ifndef _DEBUG  // ImageLView.cpp�� ����� ����
inline CImageLDoc* CImageLView::GetDocument() const
   { return reinterpret_cast<CImageLDoc*>(m_pDocument); }
#endif

