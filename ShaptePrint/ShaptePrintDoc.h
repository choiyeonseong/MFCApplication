
// ShaptePrintDoc.h : CShaptePrintDoc 클래스의 인터페이스
//


#pragma once


class CShaptePrintDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CShaptePrintDoc();
	DECLARE_DYNCREATE(CShaptePrintDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CShaptePrintDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	typedef CArray<CRect, CRect&> CRectArray;	// CRectArray 컬렉션 클래스 선언
	CRectArray m_ellipseArray;	// CRectArray 타입의 변수
	enum { nLinesPerPage = 12 };	// define 대신 나열형 변수 선언. 페이지 계산시 사용
};
