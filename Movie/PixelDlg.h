#pragma once


// CPixelDlg 대화 상자입니다.

class CPixelDlg : public CDialog
{
	DECLARE_DYNAMIC(CPixelDlg)

public:
	CPixelDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPixelDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODALESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnOk();
	virtual void PostNcDestroy();
	// 현재 픽셀의 색상을 표시
	void CurrentPixelColor(COLORREF color);
	void SendCurrentColor(COLORREF color);
};
