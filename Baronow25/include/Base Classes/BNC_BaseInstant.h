#pragma once



enum BNE_INSTANT_HIDE_REASON
{
	BNE_INSTANT_HIDE_REASON_UNKNOWN,
	BNE_INSTANT_HIDE_REASON_FORCE,
	BNE_INSTANT_HIDE_REASON_OTHER,	// ´Ù¸¥À©µµ¿ì¿¡°Ô Ä¸ÃÄ »©¾Ñ±è
	BNE_INSTANT_HIDE_REASON_CHILD,	// Â÷ÀÏµå À©µµ¿ì¿¡°Ô Ä¸ÃÄ »©¾Ñ±è

	BNE_INSTANT_HIDE_REASON_MOUSE,	// m_bCheckMouseMove ¼³Á¤À¸·Î Å¬¶óÀÌ¾ðÆ® ¿µ¿ª ¹þ¾î³²
	BNE_INSTANT_HIDE_REASON_LDN,
	BNE_INSTANT_HIDE_REASON_RDN,
	BNE_INSTANT_HIDE_REASON_MDN,
	BNE_INSTANT_HIDE_REASON_XDN,
};


class BN25_TYPE BNC_BaseInstant : public BNC_BaseModaless
{
public:
	BNC_BaseInstant();
	virtual ~BNC_BaseInstant();


private :
	CWnd*	m_pCallWindow;
	CWnd*	m_pCallWndParent;
	BNE_INSTANT_HIDE_REASON	m_HideReason;


public :
	bool	m_bCheckMouseMove;



private :
	void	MouseAction(UINT &nFlags, CPoint &point, BNE_INSTANT_HIDE_REASON reason);
	
protected :
	bool	CheckCursorWindow(void);
	bool	IsFamilyWindow(CWnd *pWnd);


public :
	bool	Show(CWnd* pCallWindow, int x, int y);
	bool	Hide(BNE_INSTANT_HIDE_REASON reason);
	BNE_INSTANT_HIDE_REASON GetHideReason(void);


public :
	virtual bool OnHide(BNE_INSTANT_HIDE_REASON reason);
	

private :
	virtual void OnUpdateSize(int cx, int cy);



	
protected :
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();



public :
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnXButtonDown(UINT nFlags, UINT nButton, CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	
	
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseLeave();
};

