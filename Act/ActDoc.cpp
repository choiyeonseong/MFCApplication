
// ActDoc.cpp : CActDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Act.h"
#endif

#include "ActDoc.h"
#include "CntrItem.h"
#include "SrvrItem.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CActDoc

IMPLEMENT_DYNCREATE(CActDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CActDoc, CRichEditDoc)
	// �⺻ OLE �����̳� ������ Ȱ��ȭ�մϴ�.
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnUpdateEditLinksMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_POPUP, &CActDoc::OnUpdateObjectVerbPopup)
	ON_COMMAND(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, &CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()


// CActDoc ����/�Ҹ�

CActDoc::CActDoc()
{
	// OLE ���� ������ ����մϴ�.
	EnableCompoundFile();

	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CActDoc::~CActDoc()
{
}

BOOL CActDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}

CRichEditCntrItem* CActDoc::CreateClientItem(REOBJECT* preo) const
{
	return new CActCntrItem(preo, const_cast<CActDoc*>(this));
}


// CActDoc ���� ����

COleServerItem* CActDoc::OnGetEmbeddedItem()
{
	// ������ ���õ� COleServerItem�� �������� ���� �����ӿ�ũ���� OnGetEmbeddedItem��
	//  ȣ���մϴ�.  �̰��� �ʿ��� ���� ȣ��˴ϴ�.

	CActSrvrItem* pItem = new CActSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}


// CActDoc ��Ƽ�� ���� ���� ����

CDocObjectServer *CActDoc::GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite)
{
	return new CDocObjectServer(this, pDocSite);
}




// CActDoc serialization

void CActDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}

	// �⺻ Ŭ������ CRichEditDoc�� ȣ���ϸ� �����̳� ������ COleClientItem ��ü�� ���� serialization��
	//  Ȱ��ȭ�˴ϴ�.
	// TODO: �ؽ�Ʈ�� serialize�� ��� CRichEditDoc::m_bRTF = FALSE�� �����մϴ�.
	CRichEditDoc::Serialize(ar);
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CActDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CActDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CActDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CActDoc ����

#ifdef _DEBUG
void CActDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CActDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG


// CActDoc ���
