#pragma once


#define BND_SCROLL_DRAW_LEFT	0x00000001
#define BND_SCROLL_DRAW_RIGHT	0x00000002
#define BND_SCROLL_DRAW_TOP		0x00000004
#define BND_SCROLL_DRAW_BOTTOM	0x00000008
#define BND_SCROLL_DRAW_BAREDGE	0x00000010


enum BNE_SCROLL_UPDATE_REASON
{
	BNE_SCROLL_UPDATE_REASON_UNKNOWN,
	BNE_SCROLL_UPDATE_REASON_FORCE,			// �Լ� ȣ��
	BNE_SCROLL_UPDATE_REASON_WNDSIZE,		// ������ ũ�� ����
	BNE_SCROLL_UPDATE_REASON_TIMER,			// non-bar���� Ŭ����
	BNE_SCROLL_UPDATE_REASON_LDN,			// lbtn down
	BNE_SCROLL_UPDATE_REASON_LUP,			// lbtn up
	BNE_SCROLL_UPDATE_REASON_MOVE,			// bar move
	BNE_SCROLL_UPDATE_REASON_MOVESTOP,		// move-up
	BNE_SCROLL_UPDATE_REASON_TIMERSTOP,		// killtimer
	BNE_SCROLL_UPDATE_REASON_WHEEL,			// ���콺 ��
	BNE_SCROLL_UPDATE_REASON_KEY,			// Ű���� ����Ű 
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

	CRect		rcBlank;		// �����¿� ���� ũ��
	UINT		uiWidth;		// Bar���� ��
	UINT		uiMinHeight;	// �ּ� ũ�� ����
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
	CRect	m_rcAbleArea;	// rcMargin�� ������ ���� ����
	CRect	m_rcBar;		// Bar����
	bool	m_bMinBar;		// �ּһ����� bar����

	int		m_iLength;		// Ÿ�� ������ ����
	int		m_iPos;			// �������� ��� ��ġ

	bool	m_bFocus;		// ��Ŀ������
	bool	m_bEndPos;		// ��ũ�� ��ġ ������ �̵�����


	// ���콺 ���� üũ
	bool	m_bLBtnDn;	
	CPoint	m_ptLBtnMouse;		// �������콺 ������ �� ���콺 ��ǥ
	int		m_iFocusDnTop;		// bar���� ������ m_rcBar.top���� �Ÿ�
	int		m_iFocusDnBottom;	// bar���� Ŭ���� m_rcBar.bottom���� �Ÿ�


	// ��ũ�ѹ� ��� ���콺 �̵��� üũ (LBtnDown ����)
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



	// ��ũ��ũ�� �� Ÿ�� ������ ���� ����� ȣ��
	// m_uiPos, m_rcBar �����
	void	UpdateScroll(bool bReDraw, BNE_SCROLL_UPDATE_REASON reason);


	
	// ��ũ�ѿ����� ��ġ(y)�� ��� ������ ��ġ(y) ��ȣ��ȯ
	int		ClientPosToTargetPos(int iPos);
	int		TargetPosToClientPos(int iPos);


protected :
	// �θ𿡰� ��ũ�� ��ġ �޽��� ����
	void	SendScrollPos(void);	

	// �θ𿡰� ������Ʈ �޽��� ����, m_uiEventUpdateID ������
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
