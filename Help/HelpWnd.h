#pragma once


// CHelpWnd �������Դϴ�.

class CHelpWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CHelpWnd)
public:	// �����ڿ� �Ҹ����� ���� ����� public���� ����
	CHelpWnd();           
	virtual ~CHelpWnd();

public:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


