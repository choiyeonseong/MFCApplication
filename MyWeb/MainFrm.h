
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once
#include "afxcmn.h"
#include "afxext.h"
#include "afxwin.h"

class CMainFrame : public CFrameWnd
{
	
protected: // serialization������ ��������ϴ�.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	// ���α׷��� ��ü ����
	CProgressCtrl m_Progress;
	// ���α׷��� ��Ʈ�� ����
	void InitProgress();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CDialogBar m_wndDlgBar;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// Ȯ��� �޺��ڽ����� ����� �̹��� ����
	CImageList m_imgCombo;
	void AddUrl(LPCSTR strUrl);
	afx_msg void OnCbnSelchangeUrlCombo();
	afx_msg void OnViewUrlbar();
	afx_msg void OnUpdateViewUrlbar(CCmdUI *pCmdUI);
	// �ִϸ��̼� ��ü ����
	//CAnimateCtrl m_Animate;
	// �ִϸ��̼� ��Ʈ�� ����
	//void InitAnimation();
};


