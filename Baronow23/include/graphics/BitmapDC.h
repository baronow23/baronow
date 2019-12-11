#pragma once

namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
class BN23_CLASS BitmapDC : public CheckPointer
{
public:
	explicit BitmapDC(CDC* pCompatibleDC, HBITMAP src);
	explicit BitmapDC(CWnd* pCompatibleWnd, HBITMAP src);
	explicit BitmapDC(CDC* pCompatibleDC, uint32_t width, uint32_t height);
	explicit BitmapDC(CWnd* pCompatibleWnd, uint32_t width, uint32_t height);
	~BitmapDC();


private :
	void Initialize(CDC* pDC);
	void Initialize(CDC* pDC, HBITMAP src);
	void Release(void);

private :
	CDC			m_ResDC;
	CDC			m_MemDC;
	CBitmap		m_bitmap;
	uint32_t	m_width;
	uint32_t	m_height;

public :
	uint32_t Width() const
	{
		return m_width;
	};

	uint32_t Height()
	{
		return m_height;
	};


public :
	// pDC에 m_MemDC 내보내기
	BOOL BitBlt(CDC* pDC, DWORD dwRop = SRCCOPY);
	BOOL BitBlt(CDC* pDC, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, DWORD dwRop = SRCCOPY);
	BOOL StretchBlt(CDC* pDC, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop = SRCCOPY, int nStretchMode = HALFTONE);


	// m_MemDC에 첫 번째 인수 그리기
	BOOL Draw(BitmapDC bdc, DWORD dwRop = SRCCOPY);
	BOOL DrawObject(HGDIOBJ res, DWORD dwRop = SRCCOPY);
	BOOL DrawObject(HGDIOBJ res, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, DWORD dwRop = SRCCOPY);
	BOOL DrawObject(HGDIOBJ res, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop = SRCCOPY, int nStretchMode = HALFTONE);
	BOOL DrawBitmap(CBitmap* pbm, DWORD dwRop = SRCCOPY);
	BOOL DrawBitmap(CBitmap* pbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, DWORD dwRop = SRCCOPY);
	BOOL DrawBitmap(CBitmap* pbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop = SRCCOPY, int nStretchMode = HALFTONE);


public :
	bool GetBitmapBits(TBuffer<byte> &bmBits);


public :
	// Attach(HGDIOBJ); TODO
	HGDIOBJ Detach();

};
//////////////////////////////////////////////////////////////////////////////////////////
};



