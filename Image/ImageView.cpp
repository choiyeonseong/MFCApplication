
// ImageView.cpp : CImageView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Image.h"
#endif

#include "ImageDoc.h"
#include "ImageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageView

IMPLEMENT_DYNCREATE(CImageView, CView)

BEGIN_MESSAGE_MAP(CImageView, CView)
	ON_COMMAND(ID_IMAGE_CENTER, &CImageView::OnImageCenter)
	ON_COMMAND(ID_IMAGE_TILE, &CImageView::OnImageTile)
	ON_COMMAND(ID_IMAGE_STRETCH, &CImageView::OnImageStretch)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_CENTER, &CImageView::OnUpdateImageCenter)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_STRETCH, &CImageView::OnUpdateImageStretch)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_TILE, &CImageView::OnUpdateImageTile)
END_MESSAGE_MAP()

// CImageView 생성/소멸

CImageView::CImageView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_Type = CENTER;	// 비트맵을 클라이언트 영역의 중앙에 위치
}

CImageView::~CImageView()
{
}

BOOL CImageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageView 그리기

void CImageView::OnDraw(CDC* pDC)
{
	CImageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	switch (m_Type)
	{
	case CImageView::CENTER:	// 비트맵을 중앙에 출력
		CenterImage(pDC);
		break;
	case CImageView::TILE:		// 비트맵을 바둑판 모양으로 출력
		TileImage(pDC);
		break;
	case CImageView::STRETCH:	// 비트맵을 클라이언트 영역에 맞게 출력
		StretchImage(pDC);
		break;
	}

}


// CImageView 진단

#ifdef _DEBUG
void CImageView::AssertValid() const
{
	CView::AssertValid();
}

void CImageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageDoc* CImageView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageDoc)));
	return (CImageDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageView 메시지 처리기


void CImageView::CenterImage(CDC* pDC)
{
	CBitmap myBit, *pOldBit;
	CDC memDC;	// 메모리 DC
	BITMAP bm;	// GDI 비트맵(DDB)의 정보를 저장할 구조체 변수
	myBit.LoadBitmapW(IDB_IMAGE);	// 비트맵 리소스를 로드한다. -> GDI 비트맵 생성
	myBit.GetObject(sizeof(BITMAP), &bm);	// 비트맵 오브젝트에 대한 정보를 얻는다.
	memDC.CreateCompatibleDC(pDC);	// 화면 DC와 호환되는 DC 생성, 메모리 DC는 화면을 나타내는 메모리 버퍼 역할을 한다.
	pOldBit = memDC.SelectObject(&myBit);	// 메모리 DC로 비트맵 선택
	CRect rc;
	GetClientRect(rc);
	int x = (rc.Width() - bm.bmWidth) / 2;
	int y = (rc.Height() - bm.bmHeight) / 2;

	pDC->BitBlt(x, y,						// 대상 DC 사각형의 좌측 꼭지점 좌표
				bm.bmWidth, bm.bmHeight,	// 전송되는 비트맵의 폭과 높이
				&memDC,						// 원본 DC
				0, 0,						// 원본 비트맵의 좌측 꼭지점 좌표
				SRCCOPY);					// ROP 코드
	memDC.SelectObject(pOldBit);	// 반환
}


// 비트맵을 바둑판 모양으로 출력
void CImageView::TileImage(CDC* pDC)
{
	CBitmap myBit, *pOldBit;
	CDC memDC;
	BITMAP bm;
	myBit.LoadBitmapW(IDB_IMAGE);
	myBit.GetObject(sizeof(BITMAP), &bm);

	memDC.CreateCompatibleDC(pDC);
	pOldBit = memDC.SelectObject(&myBit);
	CRect rc;
	GetClientRect(rc);
	int x, y;
	for (y = 0; y < rc.bottom; y += bm.bmHeight)
		for (x = 0; x < rc.right; x += bm.bmWidth)
			pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBit);
}


// 비트맵을 클라이언트 영역의 크기에 맞게 출력
void CImageView::StretchImage(CDC* pDC)
{
	CBitmap myBit, *pOldBit;
	CDC memDC;
	BITMAP bm;
	myBit.LoadBitmapW(IDB_IMAGE);
	myBit.GetObject(sizeof(BITMAP), &bm);

	memDC.CreateCompatibleDC(pDC);
	pOldBit = memDC.SelectObject(&myBit);
	CRect rc;
	GetClientRect(rc);
	int x = rc.Width();		// 클라이언트 영역의 폭
	int y = rc.Height();	// 클라이언트 영역의 높이
	pDC->StretchBlt(0, 0, 
					x, y, 
					&memDC, 
					0, 0,
					bm.bmWidth, bm.bmHeight, 
					SRCINVERT);
	memDC.SelectObject(pOldBit);
}

// 메뉴항목이나 툴바 버튼을 누를 때 나열형 변수 m_Type의 값이 변경된다.

void CImageView::OnImageCenter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_Type = CENTER;	// 비트맵을 중앙에 배치
	Invalidate();
}


void CImageView::OnImageTile()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_Type = TILE;	// 비트맵을 바둑판 모양으로 배치
	Invalidate();
}


void CImageView::OnImageStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_Type = STRETCH;
	Invalidate();
}


void CImageView::OnUpdateImageCenter(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_Type == CENTER);
}



void CImageView::OnUpdateImageTile(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetRadio(m_Type == TILE);
}


void CImageView::OnUpdateImageStretch(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_Type == STRETCH);
}


