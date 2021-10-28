
// ShaptePrintDoc.cpp : CShaptePrintDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ShaptePrint.h"
#endif

#include "ShaptePrintDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CShaptePrintDoc

IMPLEMENT_DYNCREATE(CShaptePrintDoc, CDocument)

BEGIN_MESSAGE_MAP(CShaptePrintDoc, CDocument)
END_MESSAGE_MAP()


// CShaptePrintDoc ����/�Ҹ�

CShaptePrintDoc::CShaptePrintDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CShaptePrintDoc::~CShaptePrintDoc()
{
}

BOOL CShaptePrintDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.
	
	// ���������� 50���� ���� �����.
	srand((unsigned)time(NULL));
	int n1, n2, n3;
	m_ellipseArray.SetSize(50);	// �迭 ũ�� ����
	for (int i = 0; i < 50; i++)
	{
		n1 = rand() * 600 / RAND_MAX;
		n2 = rand() * 1000 / RAND_MAX;
		n3 = rand() * 50 / RAND_MAX;
		// ���� ��� MM_LOENGLISH�� ����ϱ� ���� y���� ������ ����
		m_ellipseArray[i] = CRect(n1, -n2, n1 + n3, -(n2 + n3));
	}
	return TRUE;
}




// CShaptePrintDoc serialization

void CShaptePrintDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
		m_ellipseArray.Serialize(ar);	// �迭 ��Ҹ� �ε��ϰ� �����Ѵ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CShaptePrintDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CShaptePrintDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CShaptePrintDoc::SetSearchContent(const CString& value)
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

// CShaptePrintDoc ����

#ifdef _DEBUG
void CShaptePrintDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CShaptePrintDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CShaptePrintDoc ���
