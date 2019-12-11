#pragma once

#include <atlimage.h>
#define BND_FONTCOUNT	60
class BN25_TYPE BNC_DrawObject
{
public:
	BNC_DrawObject(void);
	virtual ~BNC_DrawObject(void);


public :
	//////////////////////////////////////////////////////
	static Gdiplus::ColorMatrix s_colorMatrixAlpha;
	static Gdiplus::ColorMatrix s_colorMatrixGray;
	static Gdiplus::ColorMatrix s_colorMatrixGray2;

	


private :
	//////////////////////////////////////////////////////
	std::vector<Gdiplus::Image*>	m_vGdiImage;
	std::vector<CSize>				m_vGdiSize;

	std::vector<CImage*>			m_vCdcImage;
	std::vector<CBitmap*>			m_vCdcBitmap;
	std::vector<CSize>				m_vCdcSize;

	

public :

	//////////////////////////////////////////////////////
	// �׷��� ��
	CPen	pGrayPen[256];



	//////////////////////////////////////////////////////
	// ��Ʈ
	CFont	pFont[BND_FONTCOUNT];
	CFont	pFontLine[BND_FONTCOUNT];
	CFont	pFontBold[BND_FONTCOUNT];
	CFont	pFontBoldLine[BND_FONTCOUNT];
	CFont	pFontSemiBold[BND_FONTCOUNT];

	CFont	font9;
	CFont	font10;
	CFont	font11;
	CFont	font12;
	CFont	font13;
	CFont	font14;
	CFont	font15;
	CFont	font16;
	CFont	font18;
	CFont	font20;
	CFont	font22;

	CFont	font9b;
	CFont	font10b;
	CFont	font11b;
	CFont	font12b;
	CFont	font13b;
	CFont	font14b;
	CFont	font15b;
	CFont	font16b;
	CFont	font18b;
	CFont	font20b;
	CFont	font22b;


public :
	// ���Ͽ��� �̹��� �о����
	static bool LoadFromFile(Gdiplus::Image **ppImage, LPCTSTR lpszPath);


	// ���ҽ� �̹��� �о �Ķ���Ϳ� ����
	static bool LoadFromResource(_In_	UINT nRes,
								 _Out_	CImage** pImage,
								 _Out_	CBitmap** pBitmap,
								 _Out_  CSize& size,
								 _In_	LPCTSTR pType = _T("PNG"),
								 _In_	HMODULE hInst = AfxGetInstanceHandle());


	// ���ҽ� �̹��� �о����
	static bool LoadFromResource(CImage& img, UINT nRes, LPCTSTR pType = _T("PNG"), HMODULE hInst = AfxGetInstanceHandle());
	static bool LoadFromResource(Gdiplus::Image **ppImage, UINT nRes, LPCTSTR pType = _T("PNG"), HMODULE hInst = AfxGetInstanceHandle());

	static void	GetAlphaMatrix(_In_ BYTE btAlpha, _Ret_ Gdiplus::ColorMatrix &matrix);
	static void CreateFont(CFont &font, LPCTSTR strFaceName, UINT iFontHeight, UINT iWeight, bool bUnderline, int iLetterSpacing = 0);


	// hDC�� str�� ����� �� iMaxExtent�� ����� ...���� ������ ���ڿ� ��ȯ
	static CString GetFitStringAddDot(HDC hDC, LPCTSTR str, int iMaxExtent, _Ret_ CSize &szDraw);


	// str + str2�� ��ģ string�� GetFitStringAddDot�� ����
	static CString GetFitStringAddDotEx(HDC hDC, LPCTSTR str1, LPCTSTR str2, int iMaxExtent, _Ret_ CSize &szDraw);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ������ Gdiplus::Image�� CBitmap���� ��ȯ
	// ���ο��� ppBitmap ���� ����
	static void	CreateBitmapFromImage(CDC* pDC, _In_ COLORREF clrBk, _In_ Gdiplus::Image *pImage, _Ret_ CBitmap ** ppBitmap);
	

	// szStretch�� ����� �� �ִ� ���� ������ �������� ���� �κ��� �ڸ�
	static void	CreateClipBitmapFromImage(CDC* pDC,
										  _In_ COLORREF clrBk,
										  _In_ CSize szStretch,
										  _In_ Gdiplus::Image *pImage,
										  _Ret_ CBitmap **ppBitmap);
	
	// �̹��� ������ szStretch ������ ���� �̹����� �÷��� ����ϰ� ���� �κ��� clrBK�� ä��
	static void	CreateStretchBitmapFromImage(CDC* pDC,
											 _In_ COLORREF clrBk,
											 _In_ CSize szStretch,
											 _In_ bool bAdjust,
											 _In_ Gdiplus::Image *pImage,
											 _Ret_ CBitmap **ppBitmap);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

public :

	void	Create(LPCTSTR strFaceName = BND_DEFAULT_FONT);
	int		AddGdiImage(UINT uiRes);
	int		AddCdcImage(UINT uiRes);

	int		AddGdiImage(Gdiplus::Image *pImage);
	int		AddCdcImage(CImage *pImage);

	void	ReplaceGdiImage(UINT index, Gdiplus::Image *pImage);
	void	ReplaceCdcImage(UINT index, CImage *pImage);

	void	ClearGdiImage(void);
	void	ClearCdcImage(void);


	Gdiplus::Image*	GetGdiImage(UINT index);
	CBitmap*		GetCdcBitmap(UINT index);

	CSize			GetGdiImageSize(UINT index);
	CSize			GetCdcBitmapSize(UINT index);


protected :
	virtual void OnCreate(LPCTSTR lpszFaceName);
};

