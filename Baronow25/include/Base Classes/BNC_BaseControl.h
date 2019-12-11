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
	HWND				m_hNotifyEvent;		// �̺�Ʈ �˸� �ڵ� (�⺻ : m_pParentClientPtr)
	USHORT				m_uiEventID;
	CSize				m_szClient;

	
	// �θ� Ŭ���̾�Ʈ�� ������� ������� ����
	bool				m_bUseParnetBk;


	// ����
	CToolTipCtrl		*m_pTooltip;

	
	// �⺻ ���콺(L��ư) ���� ����
	BNC_MouseControl*	m_pMouseControl;


	// ��Ŀ�� ���¿��� ����� Ŀ�� (���콺 ���� ���� ����)
	HCURSOR				m_hFocusCursor;


	// Ŀ�� ���� ���� üũ (true == m_bSendMouseEventToPopup ���õ�)
	bool	m_bChangeCursor;


public :
	// ���콺 ��ư���۽� �˾� ������ ��Ŀ�� (�⺻ true)
	bool	m_bSetPopupFocus;

	bool	m_bSendMouseEventToPopup;


////////////////////////////////////////////////////////////////////////////////////////////////
// Overriding 
////////////////////////////////////////////////////////////////////////////////////////////////
private :
	virtual bool OnCreate(void);
	virtual void OnUpdateSize(int cx, int cy);
	virtual	bool OnDraw(CDC* pMemDC, CDC* pResDC) = 0;

	
	// BNC_MouseControl ���� ����� ������Ʈ
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

	// �̺�Ʈ ���� �ڵ� ����
	void			MotifyNotiWindow(HWND hWnd);


	// ���� Ŭ���̾�Ʈ�� �˾� ��ȯ
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
