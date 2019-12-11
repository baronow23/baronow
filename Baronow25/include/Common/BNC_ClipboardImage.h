#pragma once

#include "BNC_ClipboardImageOLE.h"

// CF_HDROP 처리않함
class BN25_TYPE BNC_ClipboardImage
{
public:
	BNC_ClipboardImage();
	~BNC_ClipboardImage();

public :
	static bool s_bUsingOLE;

//private :
public :
	Gdiplus::Image *m_pImage;
	CBitmap *m_pBitmap;
	

protected :
	void	CreateSubBitmap(HBITMAP hBitmap);
	bool	Update(HBITMAP hBitmap);	// DeleteObject(hBitmap) : O
	bool	Update2(HBITMAP hBitmap);	// DeleteObject(hBitmap) : X
	bool	LoadBitmap(void);
	bool	LoadImage(void);
	Gdiplus::Status HBitmapToBitmap(HBITMAP source, Gdiplus::PixelFormat pixel_format, Gdiplus::Bitmap** result_out);
	int		GetEncoderCLSID(_In_ const LPCWSTR lpszFmt, _Ret_ CLSID &Clsid);

public :
	bool	Load(void);
	bool	Clone(Gdiplus::Image **ppDest, bool bDeleteSrc = true);
	bool	IsAvailable(void);
	bool	IsLoad(void);


	
private :
	// 클립보드 이미지 생성
	__declspec(deprecated) bool CreateBitmapFromClipboard(_Ret_ CBitmap &bmClipboard);
	__declspec(deprecated) bool CreateBitmapFromClipboard(_Ret_ Gdiplus::Bitmap **ppBitmap);
	__declspec(deprecated) bool CreateImageFromClipboard(_Ret_ Gdiplus::Image **ppImage);
};

