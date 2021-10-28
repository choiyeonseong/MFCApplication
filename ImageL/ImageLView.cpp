
// ImageLView.cpp : CImageLView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageL.h"
#endif

#include "ImageLDoc.h"
#include "ImageLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageLView

IMPLEMENT_DYNCREATE(CImageLView, CView)

BEGIN_MESSAGE_MAP(CImageLView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CImageLView 생성/소멸

CImageLView::CImageLView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_pImage = NULL;


}

CImageLView::~CImageLView()
{
}

BOOL CImageLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageLView 그리기

void CImageLView::OnDraw(CDC* pDC)
{
	CImageLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	if (m_pImage->GetSafeHandle())		// 선택된 비트맵이 있는지 판단
		CenterImage(pDC);				// 비트맥을 우측 페인 중앙에 출력
}

void CImageLView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageLView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageLView 진단

#ifdef _DEBUG
void CImageLView::AssertValid() const
{
	CView::AssertValid();
}

void CImageLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageLDoc* CImageLView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageLDoc)));
	return (CImageLDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageLView 메시지 처리기

void CImageLView::RefreshImage(CString strPath)	// strPath : 비트맵 파일의 절대 경로
{
	if (m_pImage->GetSafeHandle())	// 기존에 출력된 비트맵이 있는지 판단
	{
		m_pImage->DeleteObject();	// 기존 비트맵을 제거
		delete m_pImage;			// 힙 영역에 할당된 메모리 해제
		m_pImage = NULL;
	}
	// 파일로부터 비트맵 이미지를 읽어들인다.
	m_hBitmap = (HBITMAP)LoadImage(NULL, strPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | DI_DEFAULTSIZE);
	m_pImage = new CBitmap;			// 힙 메모리 할당
	m_pImage->Attach(m_hBitmap);	// 비트맵 핸들을 CBitmap에 연결
	Invalidate();					// 뷰 윈도우를 갱신
}


void CImageLView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pImage->GetSafeHandle())
	{
		m_pImage->DeleteObject();	// 기존 비트맵을 제거
		delete m_pImage;			// 힙 영역에 할당된 메모리 해제
		m_pImage = NULL;
	}
}

void CImageLView::CenterImage(CDC* pDC)
{
	CDC memDC;	// 메모리 DC
	BITMAP bm;	// GDI 비트맵(DDB)의 정보를 저장할 구조체 변수
	m_pImage->GetObject(sizeof(BITMAP), &bm);	// 비트맵에 대한 정보를 얻는다.
	memDC.CreateCompatibleDC(pDC);	// 화면 DC와 호환되는 메모리 DC 생성
	CBitmap* pOldBit = memDC.SelectObject(m_pImage);	// 메모리 DC로 비트맵 선택
	CRect rc;
	GetClientRect(rc);
	int x = (rc.Width() - bm.bmWidth) / 2;
	int y = (rc.Height() - bm.bmHeight) / 2;
	pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBit);	// 반환
}
