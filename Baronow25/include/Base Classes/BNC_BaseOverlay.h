#pragma once


class BN25_TYPE BNC_BaseOverlay : public BNC_BaseDialog
{

public:
	BNC_BaseOverlay(UINT nDialogID, CWnd* pTarget, CDialog* pChildModal, BYTE btAlpha = 80, COLORREF clrBk = RGB(0, 0, 0));
	virtual ~BNC_BaseOverlay(void);


private:
	static std::set<HWND>	s_sAliveOverlay;
	static					UINT s_uiCreateCount;
	static					UINT s_uiDestroyCount;


public:
	static std::set<HWND>	GetAliveOverlay(void);
	static UINT				GetCreateCount(void);
	static UINT				GetAliveCount(void);


private :
	HWND		m_hTarget;
	CDialog*	m_pChildModal;


private :
	bool OnCreate(void);
	void OnUpdateSize(int cx, int cy);
	bool OnDraw(CDC* pMemDC, CDC* pResDC);


public :
	// pChildModal이 지정되지 않았을 때
	// bActivateTarget == true -> pTarget 활성화
	// bActivateTarget == false -> IDABORT
	INT_PTR Modal(bool bActivateTarget);
	void	Break(void);
	
protected :
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};