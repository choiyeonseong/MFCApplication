
// CountDlg.h : 헤더 파일
//

#pragma once
class CMyThread;	// 후위 참조를 위해

// CCountDlg 대화 상자
class CCountDlg : public CDialogEx
{
// 생성입니다.
public:
	CCountDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COUNT_DIALOG };
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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedStartCount();
	
public:
	static UINT MySumProc(void* lParam);	// 작업 스레드 함수의 원형
											// UI 스레드 객체 포인터
	CMyThread* m_pMyThread;
	afx_msg void OnClickedStartProgress();
	afx_msg void OnClickedCheck1();
};
