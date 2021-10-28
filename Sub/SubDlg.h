
// SubDlg.h : 헤더 파일
//

#pragma once
#define WM_MY_MSG	WM_USER+7	// 사용자 정의 메시지 WM_MY_MSG를 정의


// CSubDlg 대화 상자
class CSubDlg : public CDialogEx
{
// 생성입니다.
public:
	CSubDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUB_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	LONG OnMyUserProc(WPARAM wParam, LPARAM lParam);	// 메시지 핸들러
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
};
