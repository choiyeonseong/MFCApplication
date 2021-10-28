
// SrvrItem.h : CActSrvrItem Ŭ������ �������̽�
//

#pragma once

class CActSrvrItem : public CDocObjectServerItem
{
	DECLARE_DYNAMIC(CActSrvrItem)

// �������Դϴ�.
public:
	CActSrvrItem(CActDoc* pContainerDoc);

// Ư���Դϴ�.
	CActDoc* GetDocument() const
		{ return reinterpret_cast<CActDoc*>(CDocObjectServerItem::GetDocument()); }

// �������Դϴ�.
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);

// �����Դϴ�.
public:
	~CActSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // ���� ��/����� ���� �����ǵǾ����ϴ�.
};

