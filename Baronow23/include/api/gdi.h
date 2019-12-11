#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////
#define VSCLR_BK			RGB(30, 30, 30)
#define VSCLR_BK2			RGB(37, 37, 38)
#define VSCLR_CLASS			RGB(135, 206, 250)
#define VSCLR_VARIABLE		RGB(200, 200, 200)
#define VSCLR_DEFINE		RGB(127, 127, 127)
#define VSCLR_TEXT			RGB(230, 230, 230)

#define VSCLR_MACRO			RGB(218, 112, 214)
#define VSCLR_METHOD		RGB(255, 215, 0)
#define VSCLR_STRING		RGB(214, 157, 133)
#define VSCLR_COMMENT		RGB(107, 183, 94)
#define VSCLR_NUMBER		RGB(255, 100, 100)

#define VSCLR_FOCUS_BK		RGB(15, 15, 15)
#define VSCLR_FOCUS_LI		RGB(40, 40, 40)
#define VSCLR_SELECT_BK		RGB(38, 79, 120)

#define VSCLR_MENU_BK		RGB(27, 27, 28)
#define VSCLR_MENU_BK_SEL	RGB(51, 51, 52)
#define VSCLR_MENU_TXT		RGB(241, 241, 241)
#define VSCLR_MENU_TXT_GRAY	RGB(101, 101, 101)


#define VSCLR_LIST_BK		VSCLR_BK2
#define VSCLR_LIST_BK_OVER	RGB(63, 63, 70)
#define VSCLR_LIST_BK_SEL	RGB(53, 153, 255)
#define VSCLR_LIST_WHITE	RGB(241, 241, 241)
#define VSCLR_LIST_BLUE		RGB(55, 173, 231)
#define VSCLR_LIST_BEIGE	RGB(241, 202, 147)


#define VSCLR_SCROLL_BK			RGB(62, 62, 66)
#define VSCLR_SCROLL_BAR_NOR	RGB(104, 104, 104)
#define VSCLR_SCROLL_BAR_OVER	RGB(158, 158, 158)
#define VSCLR_SCROLL_BAR_DOWN	RGB(239, 235, 239)
#define VSCLR_SCROLL_BTN_NOR	RGB(153, 153, 153)
#define VSCLR_SCROLL_BTN_OVER	RGB(28, 151, 234)
#define VSCLR_SCROLL_BTN_DOWN	RGB(0, 122, 204)



#define VSCLR_FILL_CAPTION	RGB(45, 45, 48)
#define VSCLR_FILL_GRAY		RGB(63, 63, 70)
#define VSCLR_FILL_ORANGE	RGB(202, 81, 0)
#define VSCLR_FILL_BLUE		RGB(0, 122, 204)
#define VSCLR_FILL_VIOLET	RGB(104, 33, 122)
#define VSCLR_FILL_YELLOW	RGB(255, 204, 0)
#define VSCLR_FILL_BLUE_D	RGB(14, 99, 156)


#define OFCLR_GRAPH_RED		RGB(189, 64, 51)
#define OFCLR_GRAPH_GREEN	RGB(113, 172, 69)
#define OFCLR_GRAPH_BLUE	RGB(41, 152, 209)
#define OFCLR_GRAPH_YELLOW	RGB(221, 163, 0)
#define OFCLR_GRAPH_CYAN	RGB(22, 158, 140)
#define OFCLR_GRAPH_MAGENTA	RGB(190, 63, 120)
#define OFCLR_GRAPH_VIOLET	RGB(147, 89, 199)
#define OFCLR_GRAPH_ORANGE	RGB(211, 98, 6)

#define OFCLR_GRAPH_L_RED		RGB(224, 145, 140)
#define OFCLR_GRAPH_L_GREEN		RGB(169, 211, 147)
#define OFCLR_GRAPH_L_BLUE		RGB(138, 195, 241)
#define OFCLR_GRAPH_L_YELLOW	RGB(251, 204, 132)
#define OFCLR_GRAPH_L_CYAN		RGB(134, 200, 187)
#define OFCLR_GRAPH_L_MAGENTA	RGB(224, 144, 173)
#define OFCLR_GRAPH_L_VIOLET	RGB(191, 156, 232)
#define OFCLR_GRAPH_L_ORANGE	RGB(242, 161, 132)

#define OFCLR_GRAPH_BK		RGB(50, 50, 50)// RGB(64, 64, 64)
#define OFCLR_GRAPH_GRID	RGB(83, 83, 83)
#define OFCLR_GRAPH_LINE	RGB(127, 127, 127)
#define OFCLR_GRAPH_AXIS	RGB(200, 200, 200)
#define OFCLR_GRAPH_TEXT	RGB(191, 191, 191)

#define MSCLR_RED		RGB(235, 78, 33)
#define MSCLR_GREEN		RGB(124, 181, 0)
#define MSCLR_BLUE		RGB(0, 159, 232)
#define MSCLR_YELLOW	RGB(248, 180, 0)

#define GPCOLOR(rgb)		Gdiplus::Color(GetRValue(rgb), GetGValue(rgb), GetBValue(rgb))
#define GPCOLORA(a, rgb)	Gdiplus::Color(a, GetRValue(rgb), GetGValue(rgb), GetBValue(rgb))


namespace bapi
{
//////////////////////////////////////////////////////////////////////////////////////////
	
	BN23_API(COLORREF)			IncreaseColor(COLORREF color, float fIncRatio);
	BN23_API(Gdiplus::Color)	IncreaseColor(Gdiplus::Color color, float fIncRatio, float fIncAlpha = 0);

	BN23_API(COLORREF)			DirectColor(COLORREF color, float fRatio);
	BN23_API(Gdiplus::Color)	DirectColor(Gdiplus::Color color, float fColor, float fAlpha = 1);

	BN23_API(COLORREF)			MakeRandomRGB(void);
	BN23_API(Gdiplus::Color)	MakeRandomColor(void);


	//////////////////////////////////////////////////////////////////////////
	// 도구
	//////////////////////////////////////////////////////////////////////////
	BN23_API(void) SetGraphics(Gdiplus::Graphics *pGdi, bool bSrcOver = true, bool bHighCompositingQuality = false);

	// pDC에 str 출력한 크기 반환
	BN23_API(CSize) GetDrawTextSize(CDC* pDC, LPCTSTR lpszText);


	// 텍스트 출력이 설정된 pDC에 lpszStr을 출력할 때의 크기 반환
	BN23_API(CSize) GetDisplayStringSize(CDC* pDC, LPCTSTR lpszStr);


	// pDC에 str을 출력할 때 iMaxExtent를 벗어나면 ...으로 조절된 문자열 반환
	BN23_API(CString) GetFitStringAddDot(CDC* pDC, LPCTSTR str, int iMaxExtent, _Ret_ CSize *pszDraw);
	BN23_API(CString) GetFitStringAddDotReverse(CDC* pDC, CString str, int iMaxExtent, _Ret_ CSize *pszDraw);


	BN23_API(void) DrawOutsideTabLine(CDC *pMemDC, CRect &rect, bool bRight);
	BN23_API(void) DrawOutsideTabLineEx(CDC *pMemDC, CRect &rect);
	BN23_API(void) DrawFrameRect(CDC *pMemDC, int iLeft, int iTop, int iWidth, int iHeight, COLORREF color, int iThickness = 1);
	BN23_API(void) DrawFrameRect(CDC *pMemDC, int iLeft, int iTop, int iWidth, int iHeight, COLORREF clr1, COLORREF clr2);
	BN23_API(void) DrawFrameRect(Gdiplus::Graphics &g, Gdiplus::Pen &pen, CRect &rect);
	BN23_API(void) DrawFrameRect(Gdiplus::Graphics &g, Gdiplus::Pen &pen, Gdiplus::RectF &rect);
	BN23_API(void) DrawFrameRect(Gdiplus::Graphics &g, Gdiplus::Pen &pen, Gdiplus::PointF &ptLT, Gdiplus::PointF &ptRB);


	// bitmap/hbm bits 데이터를 alloc에 할당해서 복사
	BN23_API(bool) GetBitmapBits(_In_ CBitmap &bitmap, _Ret_ baro::TBuffer<byte> &bmBits);
	BN23_API(bool) GetBitmapBits(_In_ const HBITMAP hbm, _Ret_ baro::TBuffer<byte> &bmBits);
	

//////////////////////////////////////////////////////////////////////////////////////////
};