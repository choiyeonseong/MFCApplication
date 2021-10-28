
// MainFrm.h : CMainFrame 클래스의 인터페이스
//

#pragma once
#include "afxcmn.h"
#include "afxext.h"
#include "afxwin.h"

class CMainFrame : public CFrameWnd
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	// 프로그레스 객체 생성
	CProgressCtrl m_Progress;
	// 프로그레스 컨트롤 생성
	void InitProgress();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CDialogBar m_wndDlgBar;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// 확장된 콤보박스에서 사용할 이미지 관리
	CImageList m_imgCombo;
	void AddUrl(LPCSTR strUrl);
	afx_msg void OnCbnSelchangeUrlCombo();
	afx_msg void OnViewUrlbar();
	afx_msg void OnUpdateViewUrlbar(CCmdUI *pCmdUI);
	// 애니메이션 객체 생성
	//CAnimateCtrl m_Animate;
	// 애니메이션 컨트롤 생성
	//void InitAnimation();
};


