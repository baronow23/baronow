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
	COLORREF		colorBk;		// �⺻���
	COLORREF		colorEdge;		// �׵θ�
	COLORREF		colorFocus;		// ���콺 ��Ŀ�� ��
	COLORREF		colorSeparator;	// ���м�
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
	// �⺻ �̹��� ���ø�
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
	// ���� �θ� �޴�
	BNC_PopupMenu* m_pParentMenu;


	// Ȱ��ȭ�� ���� �ڽ� �޴�
	BNC_PopupMenu*	m_pActiveChild;


	// ���� ĸ�ļҸ�� hide ����
	bool	m_bIgnoreNextCapture;


	bool	m_bIsCreate;
	HWND	m_hNotifyWindow;
	UINT	m_uiNotifyMenuID;


	// Show() �Ű�����
	HWND				m_hInsertAfter;
	HWND				m_hMouseNotify;		// ���콺 �̺�Ʈ ���� ������
	bool				m_bPosParentRight;	// ���� �θ� ������ ��ġ�ϴ��� ����
	BNE_MONITOR_CHECK	m_MonitorCheck;		// ���� �˾� ������ �� ���� üũ�� �÷���



	// ������
	std::vector<BNC_PopupMenuItem*>	m_vItem;
	int								m_iFocusIndex;
	int								m_iFocusHotKeyIndex;



	// ���� ���� ���
	int		m_iScrollPos;
	UINT	m_uiFixHeight;
	BNC_SimpleVScrollbar	m_vScrollbar;


	// m_pLeftText ��� BNC_PopupMenu::s_DefaultStyle.txtInfo ��뿩��
	bool	m_bUsingDefaultLeftText;


private:
	CRect	m_rcInnerBlank;		//  ���ʿ��� (�׵θ� 1px ����)
	UINT	m_puiSection[4];	// ���� �̹���, ���� �ؽ�Ʈ, ����Ű �ؽ�Ʈ, ���� �̹��� ����
	CRect	m_rcItem;			// ������ ��ü ����
	CSize	m_szClient;



	// ���콺 ĸ�� ������ �ӽ� ���
	int		m_iMouseMoveThrowCount;
	bool	m_bHiding;



public:
	// ���콺 Ŭ������ ĸ�İ� �Ҹ�� �� ������ ������
	CWnd*		m_pIgnoreCaptureWnd;


	// ���� ����
	COLORREF	m_colorBk;			// �⺻���
	COLORREF	m_colorEdge;		// �׵θ�
	COLORREF	m_colorFocus;		// ���콺 ��Ŀ�� ��
	COLORREF	m_colorSeparator;	// ���м�


	// ���м�
	int			m_iPenStyle;
	bool		m_bSeparatorPos0;	// section[0]��ġ���� �������� �ʰ� x=0���� �׸��� ����


	// ��Ŭ���̾�Ʈ Ŭ������ �޴��� ����� ��
	// ���콺 Ŀ�� ��ġ�� �ִ� �����쿡�� �޽��� ������ ���� ����
	DWORD		m_dwNonClientClickNotify;	// WM_LBUTTONDOWN | WM_RBUTTONDOWN | WM_MBUTTONDOWN
	HWND		m_hNotifyIconOverflowWindow;


private:
	bool			SelectItem(int index);
	bool			ShowChildMenu(int iActiveChild);
	void			HideChildMenu(void);
	BNC_PopupMenu*	GetChildMenu(int index);
	void			OnFocusFromChild(void);


private:
	// ���콺�� ��ġ�ϴ� ���� ������� ������ �ε��� ��ȯ (-2:�޴�������, -1:�޴�������, 0~~ : �޴� �ε���)
	CWnd*	MouseToMenuIndex(CPoint &point, _Ret_ int &iFocus);


	// ���� ��Ŀ���� �ε����� �˾� ���������� Ȯ��
	bool	IsFocusPopupItem(void);


	// point�� hWndŬ���̾�Ʈ ��ǥ�� �����ϰ� hWndŬ���̾�Ʈ ������ ���ԵǾ����� Ȯ��
	bool	IsClientPointInMenuWindow(CPoint &point, HWND hWnd);


	// ���콺 �������� �޴��� ����� �� �� ȣ�� (�޴� ���߰� ȣ�� �����쿡�� ���콺 �޽��� ����)
	void	MouseResultHideMenu(UINT uiMessage, UINT nFlags, CPoint point);


	void	DrawItem(CDC* pMemDC, CDC* pResDC);


	// ���콺 �̺�Ʈ ������ ������ �ڵ� ���
	// m_hMouseNotify�� �����Ǿ� ������ �ٷ� �����ϰ�
	// ������ ���� �θ� Ž���Ͽ� m_hMouseNotify�� ã��
	// ��ã���� NULL ��ȯ
	HWND	GetMouseNotifyWindow(void);


	// bShow	: True -> bHideParentMenu ���ʵ�, 
	// mcFlags	: BNE_MC_NONE(ptLeftTop �״�� ���), BNE_MC_WORK(Work Area ������ ����), BNE_MC_MONITOR(Monitor Area ������ ����)
	// hMouseNotify : ���콺 ������� �޴�â�� ������ �� ���콺 �̺�Ʈ�� ���� �ڵ�
	// ptLeftTop : �޴���ġ
	void	Show(bool bShow,
				 bool bHideParentMenu,
				 CPoint				ptLeftTop		= CPoint(0, 0),
				 HWND				hInsertAfter	= NULL,
				 HWND				hMouseNotify	= NULL,
				 bool				bPosParentRight	= true,
				 BNE_MONITOR_CHECK	mcFlags			= BNE_MC_MONITOR,
				 UINT				iParentHeight	= 0);


	// �������� ����
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


	// ������ �߰�
	// iSection1~4�� BNE_PI_POPUP�� �� �ڽ��˾� ���� (������ �θ� ����)
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


	// �޴� ��Ÿ�� ���� (AddItem�� ������ �̹��� or �ؽ�Ʈ�� ���� ����)
	void	ModifyItemStyle(UINT index,
							BNS_ImageInfo*	pLeftImage,
							BNS_ImageInfo*	pLeftTextImage,
							BNS_TextInfo*	pLeftText,
							BNS_TextInfo*	pRightText,
							BNS_ImageInfo*	pRightImage);


	//  ������ ���� ����
	void SetItemEnable(UINT uiIndex, bool bEnable, bool bRedraw);
	void SetItemCheck(UINT uiIndex, bool bEnable, bool bUseChkImage, bool bRedraw);	// bUseChkImage == false�� radio �̹��� ���
	void SetItemText(UINT uiINdex, CString str);	// �������� ����


	// AddItem �Է� index ��ġ�� ������ ���� ���
	BNC_PopupMenuItem* GetMenuItem(UINT index);


	// ���� �޴� ������
	BNC_PopupMenu* GetParentMenu(void);


	// ���� ����ũ��
	CSize	GetClientSize(void);


	// �̺�Ʈ ���� ������
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

