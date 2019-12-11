#pragma once
class BN25_TYPE BNC_GDI
{
public:
	BNC_GDI(HWND hWnd);
	~BNC_GDI(void);


private :
	HWND	m_hTarget;
	CSize	m_szClient;

	CDC			*m_pDC;
	CClientDC	*m_pClientDC;
	CDC			m_MemDC;
	CDC			m_ResDC;
	CBitmap		m_ResBitmap;
	CBitmap		*m_pOldBitmap;
	RECT		*m_prcClip;


private :
	void Reset(void);

public :
	void Begin(CDC* pDC, RECT *prcClip, COLORREF colorBG);
	void End(void);

	inline CDC* GetMemDC(void);
	inline CDC* GetResDC(void);
	inline int	GetWidth(void);
	inline int	GetHeight(void);
};

