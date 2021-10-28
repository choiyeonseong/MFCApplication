
// ImageView.h : CImageView 클래스의 인터페이스
//

#pragma once


class CImageView : public CView
{
protected: // serialization에서만 만들어집니다.
	CImageView();
	DECLARE_DYNCREATE(CImageView)

// 특성입니다.
public:
	CImageDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CImageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	void CenterImage(CDC* pDC);
	// 비트맵을 바둑판 모양으로 출력
	void TileImage(CDC* pDC);
	// 비트맵을 클라이언트 영역의 크기에 맞게 출력
	void StretchImage(CDC* pDC);

// 출력된 내용을 식별하기 위한 변수
public:
	enum IMAGE_TYPE { CENTER, TILE, STRETCH };	// 나열형 정의
	IMAGE_TYPE m_Type;	// 나열형 변수 m_Type 선언
	afx_msg void OnImageCenter();
	afx_msg void OnImageTile();
	afx_msg void OnImageStretch();
	afx_msg void OnUpdateImageCenter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImageStretch(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImageTile(CCmdUI *pCmdUI);
//	virtual HRESULT accDoDefaultAction(VARIANT varChild);
};

#ifndef _DEBUG  // ImageView.cpp의 디버그 버전
inline CImageDoc* CImageView::GetDocument() const
   { return reinterpret_cast<CImageDoc*>(m_pDocument); }
#endif

