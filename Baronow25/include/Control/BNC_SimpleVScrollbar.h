#pragma once


#define BND_SCROLL_DRAW_LEFT	0x00000001
#define BND_SCROLL_DRAW_RIGHT	0x00000002
#define BND_SCROLL_DRAW_TOP		0x00000004
#define BND_SCROLL_DRAW_BOTTOM	0x00000008
#define BND_SCROLL_DRAW_BAREDGE	0x00000010


enum BNE_SCROLL_UPDATE_REASON
{
	BNE_SCROLL_UPDATE_REASON_UNKNOWN,
	BNE_SCROLL_UPDATE_REASON_FORCE,			// 함수 호출
	BNE_SCROLL_UPDATE_REASON_WNDSIZE,		// 윈도우 크기 변경
	BNE_SCROLL_UPDATE_REASON_TIMER,			// non-bar영역 클릭중
	BNE_SCROLL_UPDATE_REASON_LDN,			// lbtn down
	BNE_SCROLL_UPDATE_REASON_LUP,			// lbtn up
	BNE_SCROLL_UPDATE_REASON_MOVE,			// bar move
	BNE_SCROLL_UPDATE_REASON_MOVESTOP,		// move-up
	BNE_SCROLL_UPDATE_REASON_TIMERSTOP,		// killtimer
	BNE_SCROLL_UPDATE_REASON_WHEEL,			// 마우스 휠
	BNE_SCROLL_UPDATE_REASON_KEY,			// 키보드 단축키 
	BNE_SCROLL_UPDATE_REASON_CAPTURE,		// capture release
};


struct BNS_ScrollbarLayout
{
	 BNS_ScrollbarLayout(void)
	 {
		 rcBlank			= CRect(2, 2, 2, 2);
		 uiWidth			= 10;
		 uiMinHeight		= 20;
		 uiBarWidth			= 0;
		 colorActiveBG		= RGB(248, 248, 248);
		 colorInactiveBG	= RGB(220, 230, 248);
		 colorNormal		= RGB(190, 190, 190);
		 colorFocus			= RGB(150, 150, 150);
		 colorPress			= RGB(130, 130, 130);
	 };

	CRect		rcBlank;		// 상하좌우 여백 크기
	UINT		uiWidth;		// Bar영역 폭
	UINT		uiMinHeight;	// 최소 크기 높이
	UINT		uiBarWidth;

	COLORREF	colorActiveBG;
	COLORREF	colorInactiveBG;

	COLORREF	colorNormal;
	COLORREF	colorFocus;
	COLORREF	colorPress;
};


class BN25_TYPE BNC_SimpleVScrollbar : public BNC_BaseControl
{
	DECLARE_DYNAMIC(BNC_SimpleVScrollbar)


public:
	BNC_SimpleVScrollbar(void);
	virtual ~BNC_SimpleVScrollbar(void);


public :
	static BNS_ScrollbarLayout	s_DefaultLayout;
	static void SetDefaultLayout(BNS_ScrollbarLayout &layout);
		

private :
	bool	m_bFirstVisible;

protected :
	BNS_ScrollbarLayout		m_layout;
	CRect	m_rcAbleArea;	// rcMargin를 제외한 실제 영역
	CRect	m_rcBar;		// Bar영역
	bool	m_bMinBar;		// 최소사이즈 bar사용됨

	int		m_iLength;		// 타겟 윈도우 높이
	int		m_iPos;			// 보여지는 상단 위치

	bool	m_bFocus;		// 포커스여부
	bool	m_bEndPos;		// 스크롤 위치 끝으로 이동여부


	// 마우스 누름 체크
	bool	m_bLBtnDn;	
	CPoint	m_ptLBtnMouse;		// 좌측마우스 눌렀을 때 마우스 좌표
	int		m_iFocusDnTop;		// bar영역 큵릭시 m_rcBar.top과의 거리
	int		m_iFocusDnBottom;	// bar영역 클릭시 m_rcBar.bottom과의 거리


	// 스크롤바 잡고 마우스 이동시 체크 (LBtnDown 포함)
	int		m_iOldMovePos;
	CPoint	m_ptLBtnPos0;
	

public :
	bool	m_bAutoHide;
	CWnd*	m_pCaptureAfterRelease;
	USHORT	m_uiEventUpdateID;

private:
	UINT	m_uiTimerUpdateCount;
	BNE_SCROLL_UPDATE_REASON m_UpdateReason;


private:
	// Overriding 
	bool OnCreate(void);
	void OnUpdateSize(int cx, int cy);
	bool OnDraw(CDC* pMemDC, CDC* pResDC);



	// 스크롤크기 및 타겟 윈도우 높이 변경시 호출
	// m_uiPos, m_rcBar 재산정
	void	UpdateScroll(bool bReDraw, BNE_SCROLL_UPDATE_REASON reason);


	
	// 스크롤영역의 위치(y)와 대상 윈도우 위치(y) 상호변환
	int		ClientPosToTargetPos(int iPos);
	int		TargetPosToClientPos(int iPos);


protected :
	// 부모에게 스크롤 위치 메시지 보냄
	void	SendScrollPos(void);	

	// 부모에게 업데이트 메시지 보냄, m_uiEventUpdateID 설정시
	void	SendUpdate(void);
	
	
public :
	void	SetLayout(BNS_ScrollbarLayout *pLayout, bool bRedraw = false);
	void	SetLength(int iLength, bool bUpdateNotify, bool bReDraw);
	void	SetPos(int iPos, bool bUpdateNotify, bool bReDraw, BNE_SCROLL_UPDATE_REASON reason);
	int		GetPos(void) const;
	int		GetLength(void) const;
	int		GetLayoutWidth(void) const;
	float	GetPosRatio(void) const;
	void	SetPosLength(int iPos, int iLength);
	bool	IsLBtnDown(void);
	bool	IsShowScroll(void) const;

	
	
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
};
