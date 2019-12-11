#pragma once



struct BNS_PopupMenuStyle
{
public:
	BNS_PopupMenuStyle()
	{
		colorBk			= RGB(27, 27, 28);
		colorEdge		= RGB(51, 51, 55);
		colorFocus		= RGB(51, 51, 52);
		colorSeparator	= RGB(51, 55, 55);
		bSeparatorPos0	= false;
	};

	BNS_TextInfo	txtInfo;
	COLORREF		colorBk;		// 기본배경
	COLORREF		colorEdge;		// 테두리
	COLORREF		colorFocus;		// 마우스 포커스 색
	COLORREF		colorSeparator;	// 구분선
	bool			bSeparatorPos0;
};


// BNC_PopupMenu
class BN25_TYPE BNC_PopupMenu : public CWnd
{
	DECLARE_DYNAMIC(BNC_PopupMenu)


public:
	BNC_PopupMenu(void);
	virtual ~BNC_PopupMenu(void);


private:
	static UINT	s_uiCreateCount;
	static UINT	s_uiDestroyCount;


public:
	static UINT	GetCreateCount(void);
	static UINT	GetAliveCount(void);


public:
	static BNS_PopupMenuStyle s_DefaultStyle;


public:
	// 기본 이미지 템플릿
	static BNS_ImageInfo	s_ImageArrow;
	static BNS_ImageInfo	s_ImageCheckOn;
	static BNS_ImageInfo	s_ImageCheckOff;
	static BNS_ImageInfo	s_ImageRadioOn;
	static BNS_ImageInfo	s_ImageRadioOff;



private:
	static BNC_PopupMenu* s_pLastVisibleMenu;
	static void		SetLastVisibleMenu(BNC_PopupMenu* pMenu);


	static HHOOK	s_KeyHook;
	static HHOOK	s_MouseHook;
	static LRESULT	CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	static LRESULT	CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);


public:
	// Event : SendMessage(BND_WM_CONTEXTMENU, WPARAM(uiNotifyMenuID), LPARAM(BNC_PopupMenuItem*) 
	static	void ShowMenu(BNC_PopupMenu &menu, HWND hNotify, BNE_MONITOR_CHECK mc = BNE_MC_MONITOR);
	static	void ShowMenuPoint(BNC_PopupMenu &menu, HWND hNotify, CPoint &pt, BNE_MONITOR_CHECK mc = BNE_MC_MONITOR);
	static  void HideVisibleMenu(void);
	static	BNC_PopupMenu* GetVisibleMenu(void);



private:
	// 상위 부모 메뉴
	BNC_PopupMenu* m_pParentMenu;


	// 활성화된 하위 자식 메뉴
	BNC_PopupMenu*	m_pActiveChild;


	// 다음 캡쳐소멸시 hide 무시
	bool	m_bIgnoreNextCapture;


	bool	m_bIsCreate;
	HWND	m_hNotifyWindow;
	UINT	m_uiNotifyMenuID;


	// Show() 매개변수
	HWND				m_hInsertAfter;
	HWND				m_hMouseNotify;		// 마우스 이벤트 받을 윈도우
	bool				m_bPosParentRight;	// 상위 부모 우측에 위치하는지 여부
	BNE_MONITOR_CHECK	m_MonitorCheck;		// 하위 팝업 등장할 때 영역 체크할 플래그



	// 아이템
	std::vector<BNC_PopupMenuItem*>	m_vItem;
	int								m_iFocusIndex;
	int								m_iFocusHotKeyIndex;



	// 고정 높이 사용
	int		m_iScrollPos;
	UINT	m_uiFixHeight;
	BNC_SimpleVScrollbar	m_vScrollbar;


	// m_pLeftText 대신 BNC_PopupMenu::s_DefaultStyle.txtInfo 사용여부
	bool	m_bUsingDefaultLeftText;


private:
	CRect	m_rcInnerBlank;		//  안쪽여백 (테두리 1px 포함)
	UINT	m_puiSection[4];	// 좌측 이미지, 내용 텍스트, 단축키 텍스트, 우측 이미지 영역
	CRect	m_rcItem;			// 아이템 전체 영역
	CSize	m_szClient;



	// 마우스 캡쳐 문제로 임시 사용
	int		m_iMouseMoveThrowCount;
	bool	m_bHiding;



public:
	// 마우스 클릭으로 캡쳐가 소멸될 때 무시할 윈도우
	CWnd*		m_pIgnoreCaptureWnd;


	// 색상 설정
	COLORREF	m_colorBk;			// 기본배경
	COLORREF	m_colorEdge;		// 테두리
	COLORREF	m_colorFocus;		// 마우스 포커스 색
	COLORREF	m_colorSeparator;	// 구분선


	// 구분선
	int			m_iPenStyle;
	bool		m_bSeparatorPos0;	// section[0]위치에서 시작하지 않고 x=0에서 그리기 시작


	// 비클라이언트 클릭으로 메뉴가 사라질 때
	// 마우스 커서 위치에 있는 윈도우에게 메시지 보낼지 여부 결정
	DWORD		m_dwNonClientClickNotify;	// WM_LBUTTONDOWN | WM_RBUTTONDOWN | WM_MBUTTONDOWN
	HWND		m_hNotifyIconOverflowWindow;


private:
	bool			SelectItem(int index);
	bool			ShowChildMenu(int iActiveChild);
	void			HideChildMenu(void);
	BNC_PopupMenu*	GetChildMenu(int index);
	void			OnFocusFromChild(void);


private:
	// 마우스가 위치하는 곳의 윈도우와 아이템 인덱스 반환 (-2:메뉴영역밖, -1:메뉴영역안, 0~~ : 메뉴 인덱스)
	CWnd*	MouseToMenuIndex(CPoint &point, _Ret_ int &iFocus);


	// 현재 포커스된 인덱스가 팝업 아이템인지 확인
	bool	IsFocusPopupItem(void);


	// point를 hWnd클라이언트 좌표로 변경하고 hWnd클라이언트 영역에 포함되었는지 확인
	bool	IsClientPointInMenuWindow(CPoint &point, HWND hWnd);


	// 마우스 조작으로 메뉴를 감춰야 할 때 호출 (메뉴 감추고 호출 윈도우에게 마우스 메시지 보냄)
	void	MouseResultHideMenu(UINT uiMessage, UINT nFlags, CPoint point);


	void	DrawItem(CDC* pMemDC, CDC* pResDC);


	// 마우스 이벤트 전달할 윈도우 핸들 얻기
	// m_hMouseNotify가 설정되어 있으면 바로 리턴하고
	// 없으면 상위 부모를 탐색하여 m_hMouseNotify를 찾음
	// 못찾으면 NULL 반환
	HWND	GetMouseNotifyWindow(void);


	// bShow	: True -> bHideParentMenu 사용않됨, 
	// mcFlags	: BNE_MC_NONE(ptLeftTop 그대로 사용), BNE_MC_WORK(Work Area 범위로 조정), BNE_MC_MONITOR(Monitor Area 범위로 조정)
	// hMouseNotify : 마우스 명령으로 메뉴창이 감춰질 때 마우스 이벤트를 받을 핸들
	// ptLeftTop : 메뉴위치
	void	Show(bool bShow,
				 bool bHideParentMenu,
				 CPoint				ptLeftTop		= CPoint(0, 0),
				 HWND				hInsertAfter	= NULL,
				 HWND				hMouseNotify	= NULL,
				 bool				bPosParentRight	= true,
				 BNE_MONITOR_CHECK	mcFlags			= BNE_MC_MONITOR,
				 UINT				iParentHeight	= 0);


	// 고정높이 사용시
	LRESULT		OnMessageScroll(WPARAM wParam, LPARAM lParam);

public:
	bool	create(UINT uiNotifyMenuID,
				   CRect rcInnerBlank = CRect(2, 2, 2, 2),
				   UINT iSection1 = 30,
				   UINT iSection2 = 150,
				   UINT iSection3 = 50,
				   UINT iSection4 = 20,
				   BNC_PopupMenu* pParentMenu = NULL,
				   UINT uiFixHeight = 0,
				   bool bSystrayMenu = false,
				   bool bUsingDefaultLeftText = false);


	void	Draw(CDC* pDC);


	// 아이템 추가
	// iSection1~4는 BNE_PI_POPUP일 때 자식팝업 지정 (음수면 부모값 따름)
	void	AddItem(BNC_PopupMenu* pParentMenu,
					BNE_POPUPITEM_TYPE type,
					UINT			uiItemID		= 0,
					UINT			uiItemHeight	= 25,
					BNS_ImageInfo*	pLeftImage		= NULL,
					BNS_ImageInfo*	pLeftTextImage	= NULL,
					BNS_TextInfo*	pLeftText		= NULL,
					BNS_TextInfo*	pRightText		= NULL,
					BNS_ImageInfo*	pRightImage		= NULL,
					bool			bEnable			= true,
					bool			bCheck			= true,
					int				iSection1		= -1,
					int				iSection2		= -1,
					int				iSection3		= -1,
					int				iSection4		= -1);


	// 메뉴 스타일 변경 (AddItem에 설정한 이미지 or 텍스트만 변경 가능)
	void	ModifyItemStyle(UINT index,
							BNS_ImageInfo*	pLeftImage,
							BNS_ImageInfo*	pLeftTextImage,
							BNS_TextInfo*	pLeftText,
							BNS_TextInfo*	pRightText,
							BNS_ImageInfo*	pRightImage);


	//  아이템 상태 변경
	void SetItemEnable(UINT uiIndex, bool bEnable, bool bRedraw);
	void SetItemCheck(UINT uiIndex, bool bEnable, bool bUseChkImage, bool bRedraw);	// bUseChkImage == false면 radio 이미지 사용
	void SetItemText(UINT uiINdex, CString str);	// 넓이조정 않함


	// AddItem 입력 index 위치의 아이템 정보 얻기
	BNC_PopupMenuItem* GetMenuItem(UINT index);


	// 상위 메뉴 포인터
	BNC_PopupMenu* GetParentMenu(void);


	// 최종 갱신크기
	CSize	GetClientSize(void);


	// 이벤트 수신 윈도우
	HWND	GetNotifyWindow(void);


protected:
	DECLARE_MESSAGE_MAP()


private:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);


private:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	LRESULT	OnKeyboradProc(int nCode, WPARAM wParam, PKBDLLHOOKSTRUCT pKey);
	LRESULT OnMouseProc(int nCode, WPARAM wParam, PMSLLHOOKSTRUCT pMouse);
	void	OnNotifyMouseWheel(UINT nFlags, short zDelta);


public:
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

