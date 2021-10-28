
// NewComView.h : CNewComView 클래스의 인터페이스
//

#pragma once
#include "atltime.h"
#include "afxcmn.h"


class CNewComView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CNewComView();
	DECLARE_DYNCREATE(CNewComView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_NEWCOM_FORM };
#endif

// 특성입니다.
public:
	CNewComDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CNewComView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	// 데이터값 이용
	CTime m_Month;
	//  컨트롤 이용
	CComboBoxEx m_Combo;
	afx_msg void OnClickedResult();
	virtual HRESULT accDoDefaultAction(VARIANT varChild);
	void FillComboBox();
	afx_msg void OnSelchangeComboboxex1();
	afx_msg void OnClickedTabdlgBtn();

	BOOL PreTranslateMessage(MSG * pMsg);

protected:
	CToolTipCtrl m_Tip;	// 툴팁 객체 생성
};

#ifndef _DEBUG  // NewComView.cpp의 디버그 버전
inline CNewComDoc* CNewComView::GetDocument() const
   { return reinterpret_cast<CNewComDoc*>(m_pDocument); }
#endif

