
// ActDoc.h : CActDoc Ŭ������ �������̽�
//


#pragma once


class CActSrvrItem;

class CActDoc : public CRichEditDoc
{
protected: // serialization������ ��������ϴ�.
	CActDoc();
	DECLARE_DYNCREATE(CActDoc)

// Ư���Դϴ�.
public:
	CActSrvrItem* GetEmbeddedItem()
		{ return reinterpret_cast<CActSrvrItem*>(CRichEditDoc::GetEmbeddedItem()); }

// �۾��Դϴ�.
public:

// �������Դϴ�.
protected:
	virtual COleServerItem* OnGetEmbeddedItem();
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CActDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual CDocObjectServer* GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite);

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
