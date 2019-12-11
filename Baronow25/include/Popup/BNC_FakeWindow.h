#pragma once


// BNC_FakeWindow

class BN25_TYPE BNC_FakeWindow : public CWnd
{
	DECLARE_DYNAMIC(BNC_FakeWindow)

public:
	BNC_FakeWindow();
	virtual ~BNC_FakeWindow();


private:
	static UINT s_uiCreateCount;
	static UINT s_uiDestroyCount;


public:
	static UINT	GetCreateCount(void);
	static UINT	GetAliveCount(void);



private :
	HWND	m_hTarget;
	bool	m_bIsCreate;


public :
	CRect	m_rcWindow;
	CSize	m_szWindow;


public :
	bool	create(HWND hTarget);


protected:
	DECLARE_MESSAGE_MAP()


public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);


public :
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


