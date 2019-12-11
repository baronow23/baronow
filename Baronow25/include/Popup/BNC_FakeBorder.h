#pragma once


// BNC_FakeBorder 대화 상자입니다.

//#define USING_FAKEBORDER_DRAW	// 테스트용
class BN25_TYPE BNC_FakeBorder : public CDialog
{
	DECLARE_DYNAMIC(BNC_FakeBorder)
	
public :
	static int s_iBorder;


public:
	BNC_FakeBorder();   // 표준 생성자입니다.
	virtual ~BNC_FakeBorder();

private :
	bool				m_bSyncTimer;
	CSize				m_szClient;
	CRect				m_rcLastSyncPos;
	BNC_BaseDialog*		m_pActualDialog;
	HWND				m_hActualDialog;


public :
	bool	m_bUsingInitTimerPos;


public :
	bool	create(UINT nIDTemplate, BNC_BaseDialog* pActualDialog, CWnd* pParentWnd = nullptr);
	void	OnActualStatusUpdate(BNE_POPUP_STATUS status);
	void	OnActualPos(int x, int y, int cx, int cy, UINT uiAddFlags, bool bReqUpdateWnd);
	void	ClientPointToActualPoint(_Inout_ CPoint &point);

private :
	void	ShowSync(void);
	void	ShowSyncTimer(void);
	void	SendMouseEvent(UINT message, UINT nFlags, CPoint point);

	// 임시
	void	Draw(void);


private :
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);


protected:
	virtual BOOL OnInitDialog();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);


public :
	virtual BOOL DestroyWindow();


protected :
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();


public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
