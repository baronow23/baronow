#pragma once

class BN25_TYPE BNC_ButtonEx : public BNC_Button
{
public:
	BNC_ButtonEx();
	virtual ~BNC_ButtonEx();


private :
	bool	m_bDrawEnable;


	// 보드판 (Resource Line 적용 않함)
	Gdiplus::Image* m_pBoradImage;
	bool			m_bUseSingleState;		// Normal 이미지 하나만 사용
	CPoint			m_ptBoard;
	CSize			m_szBoard;
	CPoint			m_ptBoardOffset;		// 부모 버튼기준 그리기 LeftTop 위치
	CPoint			m_ptBoardCenter;		// 보드판 중심
	
	// 출력 텍스트(출력위치는 board 중심)
	CString			m_strBoardText;
	COLORREF		m_pBoardTextColor[4];
	CFont			m_fontBoardText;
	CPoint			m_ptBoardText;
	CSize			m_szBoardText;
	

protected :
	virtual bool OnDrawEx(CDC* pMemDC, Gdiplus::Graphics *pGraphics, UINT iStateIndex);
	void	UpdateBoardTextPos(void);


public :
	void	SetDrawEnable(bool bEnable);
	void	SetBoardImage(Gdiplus::Image* pImagePtr, bool bUseSingleState, CPoint ptLeftTop, CSize szQuarter, CPoint ptParentOffset, bool bRedraw = false);
	void	SetBoardText(CString str, bool bRedraw = false);
	void	SetBoardText(UINT uiCount, bool bRedraw = false);
	void	SetBoardTextFont(LPCTSTR strFont, UINT iHeight, UINT iWeight = FW_NORMAL, bool bRedraw = false);
	void	SetBoardTextColor(COLORREF clrNormal, COLORREF clrFocus, COLORREF clrDown, COLORREF clrDisable, bool bRedraw = false);
	CString GetBoardText(void);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
};

