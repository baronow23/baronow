#pragma once
class BN25_TYPE BNC_DrawString
{
public:
	BNC_DrawString();
	BNC_DrawString(LPCTSTR str);
	~BNC_DrawString();

public :
	CString		m_str;
	CFont*		m_pFontPtr;
	UINT		m_uiAlign;		// TA_LEFT, TA_CENTER, TA_RIGHT 만 허용하고 항상 TA_TOP 임
	COLORREF	m_color;
	UINT		m_uiLeftBlank;
	UINT		m_uiRightBlank;
	int			m_iDrawPos;



public :
	void	Default(void);
	void	Draw(bool bUseExtent, CDC* pDC, int iWidth);
	CSize	GetDrawArea(CDC* pDC);


};

