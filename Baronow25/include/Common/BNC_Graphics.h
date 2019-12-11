#pragma once


enum BNE_GRAPHICS_DIRECTION
{
	BNE_GRAPHICS_DIR_LEFT,
	BNE_GRAPHICS_DIR_TOP,
	BNE_GRAPHICS_DIR_RIGHT,
	BNE_GRAPHICS_DIR_BOTTOM,
};


class BN25_TYPE BNC_Graphics
{
public:
	BNC_Graphics(CDC *pMemDC);
	BNC_Graphics(Gdiplus::Graphics *pGraphics);
	~BNC_Graphics();

private:
	CDC* m_pMemDC;
	Gdiplus::Graphics *m_pGraphics;


public:
	void	GradationRoundRect(const Gdiplus::Rect &rect, UINT iRadius, Gdiplus::Color clrCenter, Gdiplus::Color clrBegin, Gdiplus::Color clrEnd);
	void	GradationRect(const Gdiplus::Rect &rect, UINT iRadius, Gdiplus::Color clrCenter, Gdiplus::Color clrBegin, Gdiplus::Color clrEnd);
	void	GradationRect(const Gdiplus::Rect &rect, float fAngle, Gdiplus::Color clrCenter, Gdiplus::Color clrSurround);
	void	GradationEllipse(const Gdiplus::Rect &rect, Gdiplus::Color clrCenter, Gdiplus::Color clrSurround);
	void	FillRect(const Gdiplus::Rect &rect, Gdiplus::Color clr);
	void	FillRoundRect(const Gdiplus::Rect &rect, UINT iRadius, Gdiplus::Color clr);


public:
	static void TransparentBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth,
							   int nHeight, HBITMAP hBitmap, int nXSrc, int nYSrc,
							   COLORREF colorTransparent, HPALETTE hPal);
};

