#pragma once


// CPixelDlg ��ȭ �����Դϴ�.

class CPixelDlg : public CDialog
{
	DECLARE_DYNAMIC(CPixelDlg)

public:
	CPixelDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPixelDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODALESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnOk();
	virtual void PostNcDestroy();
	// ���� �ȼ��� ������ ǥ��
	void CurrentPixelColor(COLORREF color);
	void SendCurrentColor(COLORREF color);
};
