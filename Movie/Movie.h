
// Movie.h : Movie ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif


// CMovieApp:
// �� Ŭ������ ������ ���ؼ��� Movie.cpp�� �����Ͻʽÿ�.
//

class CMovieApp : public CWinApp
{
public:
	CMovieApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMovieApp theApp;
