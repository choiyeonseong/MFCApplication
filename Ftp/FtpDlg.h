
// FtpDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include <afxinet.h>

// CFtpDlg 대화 상자
class CFtpDlg : public CDialogEx
{
// 생성입니다.
public:
	CFtpDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FTP_DIALOG };
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
	CListCtrl m_localList;	// 서브 클래싱
	CListCtrl m_remoteList;	// 서브 클래싱

	// 로컬리스트 초기화
	void InitLocalList();
	// 로컬 리스트를 갱신
	BOOL RefreshLocalList();
	// 리모트 리스트를 초기화
	void InitRemoteList();
	// 리모트 리스트를 갱신
	BOOL RefreshRemoteList();
	// 툴바 생성
	void InitToolBar();

protected:
	CString m_curDir;	// 로컬 시스템의 현재 디렉토리
	CString m_curRemoteDir;	// 리모트 시스템의 현재 디렉토리
	CFtpConnection* m_pFtp;	// FTP 연결 포인터(FTP 명령 제어)
	CInternetSession m_session;	// 세션 객체
	CToolBar m_wndToolBar;	// 툴바 객체
	CString m_updownFile;	// 파일 업로드/다운로드시 사용
	int m_updownIndex;	// 파일 업로드/다운로드시 사용
public:
	afx_msg void OnConnect();
	afx_msg void OnDisconnect();
	afx_msg void OnDblclkRemoteList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnItemchangedRemoteList(NMHDR *pNMHDR, LRESULT *pResult);
};
