#pragma once


// BNC_BaseClient

enum BNE_POPUP_STATUS
{
	BNE_POPUP_STATUS_INACTIVE,		// HideWindow 포함
	BNE_POPUP_STATUS_ACTIVE,		// ShowWindow 포함
	BNE_POPUP_STATUS_MINIMIZE,		
	BNE_POPUP_STATUS_MAXIMIZE,
	BNE_POPUP_STATUS_MAXIMIZE_EX,
	BNE_POPUP_STATUS_RESTORE,		// 최대화에서 복구된 경우
	
	BNE_POPUP_STATUS_TOPMOST,	
	BNE_POPUP_STATUS_NOTOPMOST,

	BNE_POPUP_STATUS_SHOW,
	BNE_POPUP_STATUS_HIDE,

	BNE_POPUP_STATUS_CLOSE,			// OnClose발생
	BNE_POPUP_STATUS_DESTROY,		// OnDestroy발생
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
	CRITICAL_SECTION	m_cs;	// 동기화 처리가 필요할 때 사용


	// 최상위 팝업 포인터
	// 최초 윈도우 생성
	// UpdatePopupPtr() 호출시 변경되므로 자동 처리될 수 있도록 상위 클라이언트에서 생성시 m_vpChildClient에 등록할 것!!!
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
	// Animation(false~) 호출 당시위치와 DC
	CRect	m_rcAnimation;	
	CDC		m_DcAnimation;

	/////////////////////////////////////////////////////////
	CDC		m_MemDC;


	//////////////////////////////////////////////////////////////
	// OPTION

	// 선택된 클라이언트
	BNC_BaseClient*		m_pSelectClient;			// 같은 영역에서 스위치 시키기 위한 Client 등록 (SetSelectClient)
													// 부모의 SetFocus 이동됨
		
	// 자식 클라이언트
	vector<BNC_BaseClient*> m_vpChildClient;	// 부모 팝업 상태 전달받을 Client 등록 (UpdatePopupStatus)


	// Tabstop으로 사용할 자식 컨트롤
	vector<CWnd*>	m_vpTabstop;				// Tab키를 누를 때마다 Focus시켜줄 컨트롤 등록
	UINT				m_uiPosTabstop;


protected :
	// 최상위 팝업 변경시 소유한 하위 자식이 가지고 있는 m_pPopupPtr 변경을 위해 
	// 하위 컨트롤 create에서 추가함
	vector<BNC_BaseClient*>		m_vpUpdatePopupNoti;


public :
	COLORREF	m_colorBG;
	bool		m_bDrawPassPopup;				// 그리기 작업을 팝업에게 넘길지 여부
	bool		m_bSendMouseEventToPopup;		// 마우스 이벤트(L버튼, Move)를 팝업에 넘김
	bool		m_bLBtnDblDownSend;				// m_bSendMouseEventToPopup가 true일 때 전용
	bool		m_bNcMouseMove;					// m_bSendMouseEventToPopup가 true일 때 전용
	bool		m_bRejectRedrawTopMsg;			// BND_WM_REDRAW 발생으로 redraw시 pass (defautl : false)
	bool		m_bEraseTransparentBkgnd;

	

////////////////////////////////////////////////////////////////////////////////////////////////
// Overriding 
////////////////////////////////////////////////////////////////////////////////////////////////


private :
	virtual bool OnCreate(void);
	virtual void OnUpdateClient(int cx, int cy);
	virtual	bool OnDraw(CDC* pMemDC, CDC* pResDC);	// (다른 CDC생성하지 말고 pMemDC, pResDC 그대로 사용), false반환시 최종blt 않함


	// SetSelectClient 내부에서 Show/Hide전에 윈도우 위치 설정을 위해 먼저 호출함
	virtual void OnSelectClient(BNC_BaseClient *pSelectClient);

	/*
	// 상위부모에 의해 자신이 선택되었는지 여부
	virtual void OnSelect(bool bSelect);
	*/

	
protected :
	// m_vpChildClient, m_vpUpdatePopupNoti, m_vpTabstop 목록에서 대상 클라이언트 단순 제거
	void EraseChildClient(BNC_BaseClient* pChild);


public :
	// 콤보박스 사용시 화면에 보여지기 전에 리스트메뉴 설정요청
	// return ture : 부모에서 처리했음
	// return false : 컨트롤에서 처리 필요
	virtual bool OnPreVisibleComboList(UINT uiEventID, BNC_PopupMenu &menu, int iSize);

	
public :
	// 포커스 되있는 컨트롤(에디트등)에서 마우스 휠, 키보드 이벤트 전달
	virtual void OnNotifyMouseWheel(UINT nFlags, short zDelta);
	virtual bool OnNotifyKeyDown(WPARAM wKey);


	virtual UINT GetDeferChildCount(void);
	virtual void OnDeferWindowPos(HDWP hWinPosInfo, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags);


	// 팝업 최소,최대 크기 변경시 처리 (root client만 해당)
	// return true시 popup에서 처리 않함
	virtual bool OnPopupMinMaxInfo(MINMAXINFO* lpMMI);


	
protected :
	// 상속클래스에서 미구현시 부모 윈도우에게 메시지 전달
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


	// non-overried (2016-09-19 삭제)
	virtual LRESULT	OnMessageTabstop(WPARAM wParam, LPARAM lParam);


public :
	// 자식 클라이언트에서 그리기 호출 (옵션)
	virtual void	OnDrawChildClient(const BNC_BaseClient *pChild, CDC* pMemDC, CDC* pResDC, CSize szClient);


	// 버튼 컨트롤에서 그리기 마지막에 호출
	virtual void	OnDrawButton(USHORT uiEventID, CDC* pMemDC, CDC* pResDC, Gdiplus::Graphics *pGraphics, int iState, CSize szCtl);
	

	// 탭컨트롤 그리기 (새로 또는 추가항목 있을 때)
	virtual void	OnDrawTab(UINT uiTabID, UINT idxTab, CDC* pMemDC, CDC* pResDC, Gdiplus::Graphics *pGraphics,
						   int iState, bool bSelect, CSize szTab);


	// 슬라이더 그리기 
	virtual bool	OnDrawSlider(UINT id, CDC* pMemDC, CDC* pResDC, BNC_MouseControl* pMouseCtl,
								 CRect &rcSlider, CRect &rcDrawPos, bool bDrawBar, CRect &rcDrawBar);


	
	// 리스트뷰(BNC_RefListView)에서 아이템 없는 항목 다시 그리기 호출
	virtual bool	OnDrawListNoData(UINT id, CDC* pMemDC, CDC* pResDC, CSize szClient);


	// 다시 그리기 요청 (자신이나 하위 컨트롤등)
	// OnDraw호출후 m_vpChildClient 등록 클라이언트 호출
	// 오버라이딩시 BNC_BaseClient::OnRedraw() 호출후 추가 작업 수행
	// bTopMsg : BND_WM_REDRAW 발생으로 상위에서 호출되었는지 여부
	virtual void	OnRedraw(bool bTopMsg);


	// Top Dialog Enable 호출시 (다른 child등에서 modal 호출시등)
	// 하위 clinet 전달 필요시 BNC_BaseClient::OnTopWndEnable(); 호출 할 것
	virtual void	OnTopWndEnable(BOOL bEnable);



	// 자식 버튼상태 변경 애니메이션 설정시 진행량 알림, false 반환시 버튼타이머 중단
	virtual bool	OnButtonStateAnimation(USHORT uiEventID, float fRatio);



protected :
	// UpdatePopupStatus()에서 호출
	virtual void OnUpdatePopupStatus(BNE_POPUP_STATUS status);


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

private :
	// 마우스 이벤트 팝업에 넘김
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
	



	// m_MemDC를 pDestMemDC에 복사 (hDestWnd와 교차된 영역)
	// false 반환시 교차영역 없음
	bool	CopyIntersectMemDC(IN HWND hDestWnd, OUT CDC *pDestMemDC);
	

	// m_uiPosTabstop위치의 설정된 m_vpTabstop으로 포커스 전달
	CWnd*	SetChildTabFocus(void);

	
	// 클라이언트 크기 반환
	CSize	GetClientSize(void);

	
	// 타이틀바 사용시 동작 체크 , OnMessageButton 내부에서 처리
	bool	CheckTitlebarEvent(WPARAM wParam, LPARAM lParam);


	// 최상위 팝업 포인터 반환
	BNC_BaseDialog* GetPopupPtr(void);
	BNC_BaseDialog* GetOldPopupPtr(void);
	HWND			GetPopupHwnd(void);
	HWND			GetOldPopupHwnd(void);

	// 상위 클라이언트 포인트 반환
	BNC_BaseClient* GetParentClientPtr(void);


public :
	// CreateRoot()로 생성한 최상위 client에서만 사용, 부모 변경
	bool	SetPopupParentPtr(BNC_BaseDialog* pNewPopup);


private :
	// root에 SetPopupParentPtr가 호출되면 하위 차일드에 팝업 변경 알림
	void	UpdatePopupPtr(BNC_BaseDialog* pNewPopup);


private :
	// sync 다이얼로그 사용시 빠뜨릴 수 있으니 순수로 만드셈
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