#pragma once


class BN25_TYPE BNC_TabControl : public BNC_BaseClient
{
public:
	BNC_TabControl();
	virtual ~BNC_TabControl();



private :
	HWND		m_hNotifyEvent;
	USHORT		m_uiEventID;

	USHORT		m_uiTabCount;
	USHORT		m_uiSelect;
	BNC_Button *m_pTabButton;
	int			*m_piTabBtnLeft;

	COLORREF	m_clrOutside;
	COLORREF	m_clrSelBottom;



public :
	bool Initialize(HWND hNotifyWnd, USHORT uiEventID, USHORT iTabCount, LPCTSTR strFont, UINT iHeight);
	void SetEdgeColor(COLORREF clrOutside, COLORREF clrSelBottom, bool bRedraw);


	////////////////////////////////////////////////////////////////////////////////////////////////
	// Initialize 이 후 설정
	bool SetTabText(USHORT iIndex, CString str, CRect rcBlank = CRect(2, 2, 2, 2));


	bool SetTextFontStyle(BNE_FONT_STYLE normal = BNE_FS_NORMAL,
						  BNE_FONT_STYLE down	= BNE_FS_NORMAL,
						  BNE_FONT_STYLE focus	= BNE_FS_BOLD,
						  BNE_FONT_STYLE disable= BNE_FS_NORMAL,
						  bool bRedraw = false);


	bool SetBkColor(COLORREF clrNormal	= RGB(255, 255, 255),
					COLORREF clrFocus	= RGB(0, 200, 200),
					COLORREF clrDown	= RGB(0, 255, 255),
					COLORREF clrDisable	= RGB(50, 50, 50),
					bool bRedraw = false);

	
	bool SetTextColor(COLORREF clrNormal = RGB(0, 0, 0),
					  COLORREF clrFocus	 = RGB(0, 0, 0),
					  COLORREF clrDown	 = RGB(0, 0, 0),
					  COLORREF clrDisable= RGB(50, 50, 50),
					  bool bRedraw = false);


	bool	SetSelect(USHORT index, bool bRedrawOld, bool bRedrawNew);
	USHORT	GetSelect(void);
	////////////////////////////////////////////////////////////////////////////////////////////////


	void	SetEnable(USHORT index, bool bEnable);
	bool	GetEnable(USHORT index);


	// 탭컨트롤 모두 다시 그림
	virtual void OnRedraw(bool bTopMsg);


private:
	bool	OnCreate(void);
	void	OnUpdateClient(int cx, int cy);
	bool	OnDraw(CDC* pMemDC, CDC* pResDC);
	void	OnDrawButton(USHORT uiEventID, CDC* pMemDC, CDC* pResDC, Gdiplus::Graphics *pGraphics, int iState, CSize szCtl);
	LRESULT OnMessageButton(WPARAM wParam, LPARAM lParam);


protected :
	/*
	virtual void OnDrawTab(UINT uiTabID, UINT idxTab, CDC* pMemDC, CDC* pResDC, Gdiplus::Graphics *pGraphics,
						   int iState, bool bSelect, CSize szTab);
	*/


protected :
	DECLARE_MESSAGE_MAP()

public :
	afx_msg void OnDestroy();
};

