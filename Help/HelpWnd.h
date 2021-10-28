#pragma once


// CHelpWnd 프레임입니다.

class CHelpWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CHelpWnd)
public:	// 생성자와 소멸자의 접근 지정어를 public으로 설정
	CHelpWnd();           
	virtual ~CHelpWnd();

public:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


