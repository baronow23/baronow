#pragma once


// BNC_BaseClient

enum BNE_POPUP_STATUS
{
	BNE_POPUP_STATUS_INACTIVE,		// HideWindow ����
	BNE_POPUP_STATUS_ACTIVE,		// ShowWindow ����
	BNE_POPUP_STATUS_MINIMIZE,		
	BNE_POPUP_STATUS_MAXIMIZE,
	BNE_POPUP_STATUS_MAXIMIZE_EX,
	BNE_POPUP_STATUS_RESTORE,		// �ִ�ȭ���� ������ ���
	
	BNE_POPUP_STATUS_TOPMOST,	
	BNE_POPUP_STATUS_NOTOPMOST,

	BNE_POPUP_STATUS_SHOW,
	BNE_POPUP_STATUS_HIDE,

	BNE_POPUP_STATUS_CLOSE,			// OnClose�߻�
	BNE_POPUP_STATUS_DESTROY,		// OnDestroy�߻�
};


class BNC_BaseDialog;
class BNC_Titlebar;
class BN25_TYPE BNC_BaseClient : public CWnd
{
	DECLARE_DYNAMIC(BNC_BaseClient)


public:
	BNC_BaseClient();
	virtual ~BNC_BaseClient();
	

private:
	static UINT s_uiCreateCount;
	static UINT s_uiDestroyCount;


public:
	static UINT	GetCreateCount(void);
	static UINT	GetAliveCount(void);


	int		m_iDrawCount;


protected :
	CRITICAL_SECTION	m_cs;	// ����ȭ ó���� �ʿ��� �� ���


	// �ֻ��� �˾� ������
	// ���� ������ ����
	// UpdatePopupPtr() ȣ��� ����ǹǷ� �ڵ� ó���� �� �ֵ��� ���� Ŭ���̾�Ʈ���� ������ m_vpChildClient�� ����� ��!!!
	BNC_BaseDialog*		m_pPopupPtr;
	BNC_BaseDialog*		m_pOldPopupPtr;


	BNC_BaseClient*		m_pParentClient;
	CWnd*				m_pParentPtr;
	bool				m_bIsCreate;
	DWORD				m_dwWindowStyle;
	BNC_Titlebar*		m_pTitlebar;
	CSize				m_szClient;
		

	bool	m_bLBtnDown;
	bool	m_bRBtnDown;
	bool	m_bNcLBtnDown;
	bool	m_bNcRBtnDown;


	/////////////////////////////////////////////////////////
	// Animation(false~) ȣ�� �����ġ�� DC
	CRect	m_rcAnimation;	
	CDC		m_DcAnimation;

	/////////////////////////////////////////////////////////
	CDC		m_MemDC;


	//////////////////////////////////////////////////////////////
	// OPTION

	// ���õ� Ŭ���̾�Ʈ
	BNC_BaseClient*		m_pSelectClient;			// ���� �������� ����ġ ��Ű�� ���� Client ��� (SetSelectClient)
													// �θ��� SetFocus �̵���
		
	// �ڽ� Ŭ���̾�Ʈ
	vector<BNC_BaseClient*> m_vpChildClient;	// �θ� �˾� ���� ���޹��� Client ��� (UpdatePopupStatus)


	// Tabstop���� ����� �ڽ� ��Ʈ��
	vector<CWnd*>	m_vpTabstop;				// TabŰ�� ���� ������ Focus������ ��Ʈ�� ���
	UINT				m_uiPosTabstop;


protected :
	// �ֻ��� �˾� ����� ������ ���� �ڽ��� ������ �ִ� m_pPopupPtr ������ ���� 
	// ���� ��Ʈ�� create���� �߰���
	vector<BNC_BaseClient*>		m_vpUpdatePopupNoti;


public :
	COLORREF	m_colorBG;
	bool		m_bDrawPassPopup;				// �׸��� �۾��� �˾����� �ѱ��� ����
	bool		m_bSendMouseEventToPopup;		// ���콺 �̺�Ʈ(L��ư, Move)�� �˾��� �ѱ�
	bool		m_bLBtnDblDownSend;				// m_bSendMouseEventToPopup�� true�� �� ����
	bool		m_bNcMouseMove;					// m_bSendMouseEventToPopup�� true�� �� ����
	bool		m_bRejectRedrawTopMsg;			// BND_WM_REDRAW �߻����� redraw�� pass (defautl : false)
	bool		m_bEraseTransparentBkgnd;

	

////////////////////////////////////////////////////////////////////////////////////////////////
// Overriding 
////////////////////////////////////////////////////////////////////////////////////////////////


private :
	virtual bool OnCreate(void);
	virtual void OnUpdateClient(int cx, int cy);
	virtual	bool OnDraw(CDC* pMemDC, CDC* pResDC);	// (�ٸ� CDC�������� ���� pMemDC, pResDC �״�� ���), false��ȯ�� ����blt ����


	// SetSelectClient ���ο��� Show/Hide���� ������ ��ġ ������ ���� ���� ȣ����
	virtual void OnSelectClient(BNC_BaseClient *pSelectClient);

	/*
	// �����θ� ���� �ڽ��� ���õǾ����� ����
	virtual void OnSelect(bool bSelect);
	*/

	
protected :
	// m_vpChildClient, m_vpUpdatePopupNoti, m_vpTabstop ��Ͽ��� ��� Ŭ���̾�Ʈ �ܼ� ����
	void EraseChildClient(BNC_BaseClient* pChild);


public :
	// �޺��ڽ� ���� ȭ�鿡 �������� ���� ����Ʈ�޴� ������û
	// return ture : �θ𿡼� ó������
	// return false : ��Ʈ�ѿ��� ó�� �ʿ�
	virtual bool OnPreVisibleComboList(UINT uiEventID, BNC_PopupMenu &menu, int iSize);

	
public :
	// ��Ŀ�� ���ִ� ��Ʈ��(����Ʈ��)���� ���콺 ��, Ű���� �̺�Ʈ ����
	virtual void OnNotifyMouseWheel(UINT nFlags, short zDelta);
	virtual bool OnNotifyKeyDown(WPARAM wKey);


	virtual UINT GetDeferChildCount(void);
	virtual void OnDeferWindowPos(HDWP hWinPosInfo, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags);


	// �˾� �ּ�,�ִ� ũ�� ����� ó�� (root client�� �ش�)
	// return true�� popup���� ó�� ����
	virtual bool OnPopupMinMaxInfo(MINMAXINFO* lpMMI);


	
protected :
	// ���Ŭ�������� �̱����� �θ� �����쿡�� �޽��� ����
	virtual LRESULT OnMessageSystray(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageContextMenu(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageClient(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageNotify(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDestroyBlock(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageButton(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageCombo(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageEdit(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageList(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageProgress(WPARAM wParam, LPARAM lParam);
	virtual LRESULT	OnMessageScroll(WPARAM wParam, LPARAM lParam);
	virtual LRESULT	OnMessageSlider(WPARAM wParam, LPARAM lParam);
	virtual LRESULT	OnMessageTab(WPARAM wParam, LPARAM lParam);
	virtual LRESULT	OnMessageTree(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageFButton(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageResizeClient(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageHtmlWebEvent(WPARAM wParam, LPARAM lParam);


	// non-overried (2016-09-19 ����)
	virtual LRESULT	OnMessageTabstop(WPARAM wParam, LPARAM lParam);


public :
	// �ڽ� Ŭ���̾�Ʈ���� �׸��� ȣ�� (�ɼ�)
	virtual void	OnDrawChildClient(const BNC_BaseClient *pChild, CDC* pMemDC, CDC* pResDC, CSize szClient);


	// ��ư ��Ʈ�ѿ��� �׸��� �������� ȣ��
	virtual void	OnDrawButton(USHORT uiEventID, CDC* pMemDC, CDC* pResDC, Gdiplus::Graphics *pGraphics, int iState, CSize szCtl);
	

	// ����Ʈ�� �׸��� (���� �Ǵ� �߰��׸� ���� ��)
	virtual void	OnDrawTab(UINT uiTabID, UINT idxTab, CDC* pMemDC, CDC* pResDC, Gdiplus::Graphics *pGraphics,
						   int iState, bool bSelect, CSize szTab);


	// �����̴� �׸��� 
	virtual bool	OnDrawSlider(UINT id, CDC* pMemDC, CDC* pResDC, BNC_MouseControl* pMouseCtl,
								 CRect &rcSlider, CRect &rcDrawPos, bool bDrawBar, CRect &rcDrawBar);


	
	// ����Ʈ��(BNC_RefListView)���� ������ ���� �׸� �ٽ� �׸��� ȣ��
	virtual bool	OnDrawListNoData(UINT id, CDC* pMemDC, CDC* pResDC, CSize szClient);


	// �ٽ� �׸��� ��û (�ڽ��̳� ���� ��Ʈ�ѵ�)
	// OnDrawȣ���� m_vpChildClient ��� Ŭ���̾�Ʈ ȣ��
	// �������̵��� BNC_BaseClient::OnRedraw() ȣ���� �߰� �۾� ����
	// bTopMsg : BND_WM_REDRAW �߻����� �������� ȣ��Ǿ����� ����
	virtual void	OnRedraw(bool bTopMsg);


	// Top Dialog Enable ȣ��� (�ٸ� child��� modal ȣ��õ�)
	// ���� clinet ���� �ʿ�� BNC_BaseClient::OnTopWndEnable(); ȣ�� �� ��
	virtual void	OnTopWndEnable(BOOL bEnable);



	// �ڽ� ��ư���� ���� �ִϸ��̼� ������ ���෮ �˸�, false ��ȯ�� ��ưŸ�̸� �ߴ�
	virtual bool	OnButtonStateAnimation(USHORT uiEventID, float fRatio);



protected :
	// UpdatePopupStatus()���� ȣ��
	virtual void OnUpdatePopupStatus(BNE_POPUP_STATUS status);


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

private :
	// ���콺 �̺�Ʈ �˾��� �ѱ�
	LRESULT SendMouseEventToPopup(UINT uiMsg, UINT uiFlags, CPoint &point);


	void	UpdateClient(int cx, int cy);



////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
protected :
	CWnd*	GetCurrentTabstop(void);
	bool	SetSelectClient(BNC_BaseClient *pSelectClient);
	void	SetNextTabstopFocus(void);
	LRESULT	SendPopupSyscommand(WPARAM wParam);

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
private :
	bool	create(CWnd* pParent);

public :
	bool	CreateRoot(BNC_BaseDialog* pPopupPtr);
	bool	CreateChild(BNC_BaseClient *pParent);
	void	Draw(CDC* pDC = NULL, RECT *prcClip = NULL);
	void	UpdatePopupStatus(BNE_POPUP_STATUS status);
	
	
	__declspec(deprecated) void	Animation(bool bShow, double lfMilliSec);
	__declspec(deprecated) void	CopyDC(OUT CDC *pCopyDC);
	__declspec(deprecated) CDC*	GetMemDC(void);
	



	// m_MemDC�� pDestMemDC�� ���� (hDestWnd�� ������ ����)
	// false ��ȯ�� �������� ����
	bool	CopyIntersectMemDC(IN HWND hDestWnd, OUT CDC *pDestMemDC);
	

	// m_uiPosTabstop��ġ�� ������ m_vpTabstop���� ��Ŀ�� ����
	CWnd*	SetChildTabFocus(void);

	
	// Ŭ���̾�Ʈ ũ�� ��ȯ
	CSize	GetClientSize(void);

	
	// Ÿ��Ʋ�� ���� ���� üũ , OnMessageButton ���ο��� ó��
	bool	CheckTitlebarEvent(WPARAM wParam, LPARAM lParam);


	// �ֻ��� �˾� ������ ��ȯ
	BNC_BaseDialog* GetPopupPtr(void);
	BNC_BaseDialog* GetOldPopupPtr(void);
	HWND			GetPopupHwnd(void);
	HWND			GetOldPopupHwnd(void);

	// ���� Ŭ���̾�Ʈ ����Ʈ ��ȯ
	BNC_BaseClient* GetParentClientPtr(void);


public :
	// CreateRoot()�� ������ �ֻ��� client������ ���, �θ� ����
	bool	SetPopupParentPtr(BNC_BaseDialog* pNewPopup);


private :
	// root�� SetPopupParentPtr�� ȣ��Ǹ� ���� ���ϵ忡 �˾� ���� �˸�
	void	UpdatePopupPtr(BNC_BaseDialog* pNewPopup);


private :
	// sync ���̾�α� ���� ���߸� �� ������ ������ �����
	// TODO
	virtual void OnModifyPopupPtr(BNC_BaseDialog* pNewPopup);// = 0;
	

public:
	DWORD GetThreadID(void);
	UINT GetSyncWindowPosFlag(void);
	UINT GetSyncWindowPosFlags(DWORD dwFlags);
	void SetWindowPosEx(const CWnd* pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags);


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
protected:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

public :
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnNcPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonUp(UINT nHitTest, CPoint point);
	
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};




class BN25_TYPE BNC_TempClient : public BNC_BaseClient
{
public:
	BNC_TempClient()
	{
		//_trace_construct;
	};

	virtual ~BNC_TempClient()
	{
		//_trace_destruct;
	};

	void OnModifyPopupPtr(BNC_BaseDialog* pNewPopup){};
};