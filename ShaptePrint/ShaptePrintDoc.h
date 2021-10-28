
// ShaptePrintDoc.h : CShaptePrintDoc Ŭ������ �������̽�
//


#pragma once


class CShaptePrintDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CShaptePrintDoc();
	DECLARE_DYNCREATE(CShaptePrintDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CShaptePrintDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	typedef CArray<CRect, CRect&> CRectArray;	// CRectArray �÷��� Ŭ���� ����
	CRectArray m_ellipseArray;	// CRectArray Ÿ���� ����
	enum { nLinesPerPage = 12 };	// define ��� ������ ���� ����. ������ ���� ���
};
