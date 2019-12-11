#pragma once

//
//class BNC_RichEditboxEx : public CRichEditCtrl
//{
//	DECLARE_DYNAMIC(BNC_RichEditboxEx)
//
//public:
//	BNC_RichEditboxEx();
//	virtual ~BNC_RichEditboxEx();
//
//
//public:
//	static UINT s_uiCreateCount;
//	static UINT s_uiDestroyCount;
//
//protected:
//	BNC_BaseClient*		m_pParentClientPtr;
//	HWND				m_hNotifyEvent;
//	UINT				m_uiEventID;
//	CString				m_strEdit;
//
//	COLORREF	m_colorBk;
//	COLORREF	m_colorText;
//	COLORREF	m_colorBkDim;
//	COLORREF	m_colorTextDim;
//
//
//
//	// 텍스트 미입력시 보여질 가이드
//	bool		m_bDrawGuide;
//	bool		m_bUsingGuide;
//	CString		m_strGuide;
//	CFont		*m_pGuideFontPtr;
//	COLORREF	m_colorGuide;
//
//
//public :
//	// enter 입력시 줄개행 사용 (false시 shift+enter 누르면 개행)
//	bool	m_bEnterToEOL;	
//
//
//public :
//	bool	create(BNC_BaseClient* pClientPtr, USHORT uiEventID, CRect rcWindow = CRect(0, 0, 0, 0), UINT uiAddStyle = 0);
//	bool	Initialize(CString strFont,
//					   int iFontHeight,
//					   bool bBold,
//					   COLORREF crBk		= RGB(255, 255, 255),
//					   COLORREF crText		= RGB(0, 0, 0),
//					   COLORREF crBkDim		= RGB(240, 240, 240),
//					   COLORREF crTextDim	= RGB(100, 100, 100));
//
//	bool	UpdateColor(void);
//
//
//private :
//	void	AddEOL(void);
//
//
//public :
//	CString GetText(void);
//	void	SetText(CString str, bool bReDraw = true);
//
//
//	void DrawGuideText(CDC* pDC = NULL);
//	void SetGuideText(CString strGuide, COLORREF color, CFont* pFontPtr, bool bReDraw);
//	void SetGuideText(CString strGuide);
//	void InsertBitmap(CRichEditCtrl *edit, HBITMAP hBitmap, int position);
//	
//protected:
//	DECLARE_MESSAGE_MAP()
//	virtual BOOL	PreTranslateMessage(MSG* pMsg);
//	virtual BOOL	Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
//	virtual BOOL	CreateEx(DWORD dwExStyle, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
//
//public:
//	
//	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void	OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
//	afx_msg void	OnDestroy();
//
//
//	afx_msg HBRUSH	OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg HBRUSH	CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
//	afx_msg void	OnEnChange();
//	afx_msg void	OnEnUpdate();
//	afx_msg void	OnEnSetfocus();
//	afx_msg void	OnEnKillfocus();
//	afx_msg void	OnEnMsgfilter(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg BOOL	OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
//	
//	afx_msg void OnEnDropfiles(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
//	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
//	afx_msg void OnEnable(BOOL bEnable);
//	
//	//afx_msg void OnPaint();
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//};
//
//
