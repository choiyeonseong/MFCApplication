
// MovieView.h : CMovieView Ŭ������ �������̽�
//

#pragma once

#include "PixelDlg.h"

class CMovieView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CMovieView();
	DECLARE_DYNCREATE(CMovieView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MOVIE_FORM };
#endif

// Ư���Դϴ�.
public:
	CMovieDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CMovieView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFormModal();
	afx_msg void OnCFormModaless();

protected:
	CPixelDlg* m_pDlg;	// ��� ���� �߰�
public:
	afx_msg void OnClickedFormProperty();
	void OnProperties();
	afx_msg void OnClickedFormWizard();
	afx_msg void OnPopupOpen();
	afx_msg void OnPopupColor();
	afx_msg void OnPopupExit();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};

#ifndef _DEBUG  // MovieView.cpp�� ����� ����
inline CMovieDoc* CMovieView::GetDocument() const
   { return reinterpret_cast<CMovieDoc*>(m_pDocument); }
#endif

