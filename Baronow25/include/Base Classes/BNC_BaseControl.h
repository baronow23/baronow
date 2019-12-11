#pragma once


class BNC_BaseClient;
class BNC_BaseDialog;
class BN25_TYPE BNC_BaseControl : public CWnd
{
	DECLARE_DYNAMIC(BNC_BaseControl)

public:
	BNC_BaseControl(void);
	virtual ~BNC_BaseControl(void);

private:
	static UINT s_uiCreateCount;
	static UINT s_uiDestroyCount;


public:
	static UINT	GetCreateCount(void);
	static UINT	GetAliveCount(void);
	

protected :
	bool				m_bIsCreate;
	DWORD				m_dwWindowStyle;
	BNC_BaseClient*		m_pParentClientPtr;	
	HWND				m_hNotifyEvent;		// 이벤트 알림 핸들 (기본 : m_pParentClientPtr)
	USHORT				m_uiEventID;
	CSize				m_szClient;

	
	// 부모 클라이언트를 배경으로 사용할지 여부
	bool				m_bUseParnetBk;


	// 툴팁
	CToolTipCtrl		*m_pTooltip;

	
	// 기본 마우스(L버튼) 동작 관리
	BNC_MouseControl*	m_pMouseControl;


	// 포커스 상태에서 사용할 커서 (마우스 누름 관련 포함)
	HCURSOR				m_hFocusCursor;


	// 커서 변경 여부 체크 (true == m_bSendMouseEventToPopup 무시됨)
	bool	m_bChangeCursor;


public :
	// 마우스 버튼조작시 팝업 윈도우 포커싱 (기본 true)
	bool	m_bSetPopupFocus;

	bool	m_bSendMouseEventToPopup;


////////////////////////////////////////////////////////////////////////////////////////////////
// Overriding 
////////////////////////////////////////////////////////////////////////////////////////////////
private :
	virtual bool OnCreate(void);
	virtual void OnUpdateSize(int cx, int cy);
	virtual	bool OnDraw(CDC* pMemDC, CDC* pResDC) = 0;

	
	// BNC_MouseControl 상태 변경시 업데이트
	virtual void OnMouseControlUpdate(BNE_MOUSESTATE state, CPoint &point);


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
public :
	bool			create(BNC_BaseClient* pParentClientPtr, USHORT uiEventID, CRect rcWindow = CRect(0, 0, 0, 0));
	bool			createEx(CWnd* pParent,  USHORT uiEventID);
	bool			createTooltip(CString strText);
	CToolTipCtrl*	GetTooltipPtr(void);
	void			SetFocusCursor(HCURSOR hCursor);
	LRESULT			SendMouseEventToPopup(UINT uiMsg, UINT uiFlags, CPoint &point);

	// 이벤트 수신 핸들 변경
	void			MotifyNotiWindow(HWND hWnd);


	// 종속 클라이언트의 팝업 반환
	BNC_BaseDialog*	GetPopupPtr(void);
	HWND			GetPopupHwnd(void);


//protected :
public :
	void	Draw(CDC* pDC = NULL);
	CSize	GetClientSize()
	{
		return m_szClient;
	};


protected :
	void	CopyParentClientMemDC(CDC* pMemDC);


public:
	DWORD GetThreadID(void);
	UINT GetSyncWindowPosFlag(void);
	UINT GetSyncWindowPosFlags(DWORD dwFlags);
	void SetWindowPosEx(const CWnd* pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags);


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
protected :
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()


public :
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	
	
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};
