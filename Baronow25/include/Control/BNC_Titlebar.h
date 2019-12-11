#pragma once

enum ID_TITLEBAR
{
	ID_TITLEBAR_TOPMOST = 60000,
	ID_TITLEBAR_NOTOPMOST,
	ID_TITLEBAR_MINIMIZE,
	ID_TITLEBAR_MAXIMIZE,
	ID_TITLEBAR_RESTORE,
	ID_TITLEBAR_CLOSE,
};


// BNC_Titlebar::Create의 dwFlags
// 시스템 버튼 사용여부 (닫기 버튼은 기본포함, resotre는 maximize 지정시 포함)
#define BND_TBAR_FLAG_TOPMOST		0x0001
#define BND_TBAR_FLAG_MINIMIZE		0x0002
#define BND_TBAR_FLAG_MAXIMIZE		0x0004	// with restore

#define BND_TBAR_FLAG_MINIMUM		0
#define BND_TBAR_FLAG_NOSIZE		BND_TBAR_FLAG_MINIMIZE
#define BND_TBAR_FLAG_RESIZEALL		BND_TBAR_FLAG_TOPMOST | BND_TBAR_FLAG_MINIMIZE | BND_TBAR_FLAG_MAXIMIZE


class BN25_TYPE BNC_Titlebar
{
	friend class BNC_BaseClient;
public:
	BNC_Titlebar();
	virtual ~BNC_Titlebar();

protected :
	BNC_BaseDialog*	m_pPopup;
	BNC_BaseClient* m_pParent;
	

private :
	BNC_Button	*m_pBtnTopmost;
	BNC_Button	*m_pBtnNoTopmost;
	BNC_Button	*m_pBtnMinimize;
	BNC_Button	*m_pBtnMaximize;
	BNC_Button	*m_pBtnRestore;
	BNC_Button	*m_pBtnClose;


	// 위치 조정용
	std::vector<BNC_Button*>	m_vpSysbtn;
	std::vector<int>			m_viSysbtnPos;


protected :

	int			m_iHeight;
	DWORD		m_dwFlags;
	bool		m_bTransparent;
	

	// 가장 좌측에 위치하는 시스템 버튼 offset
	int		m_iLeftBtnOffset;


	// 활성, 비활성 상태 색상
	COLORREF	m_clrBkActivate;
	COLORREF	m_clrBkInActivate;
	COLORREF	m_clrTxtAvtivate;
	COLORREF	m_clrTxtInactivate;


	// 그리기 정보
	bool	m_bDrawLine;
	bool	m_bDrawText;
	bool	m_bAlignCenter;


	// 상속 클래스 지정
	CPen*	m_pPenPtr;
	CFont*	m_pFontPtr;


private :
	bool	CreateSystemButton(bool bTransparent, DWORD dwFlags);
	bool	CreateSystemButton(BNC_Button **ppBtn,
							   USHORT uiEventID,
							   CString strTooltip,
							   CPoint ptRes,
							   CSize szRes);
	void	Draw(CDC* pMemDC, CDC* pResDC, int iClientWidth);
	bool	SysBtnDown(WPARAM wParam, LPARAM lParam);
	void	UpdatePopupStatus(BNE_POPUP_STATUS status);


public :
	bool	Create(BNC_BaseDialog*	pPopup,
				   BNC_BaseClient*	pParent,
				   int				iHeight,
				   DWORD			dwFlags,
				   bool				bTransparent,
				   int				iClientWidth = 0);
	
	void	SetDrawInfo(bool bDrawLine, bool bDrawText, bool bAlignCenter);
	void	SetColor(COLORREF clrBkActivate, COLORREF clrBkInactivate, COLORREF clrTxtAvtivate, COLORREF clrTxtInactivate);
		


	/*
	시스템 버튼 위치 업데이트
	리사이징 되는 팝업의 크기 변경시 호출
	BNC_BaseClient::OnUpdateClient()
	{
		HDWP hdwp = BeginDeferWindowPos(m_Titlebar.GetSysBtnCount() + X);
		m_Titlebar.DeferSystemBtnPos(hdwp, cx);
	}
	*/
	// 시스템 버튼 위치 설정
	UINT	GetSysBtnCount(void);
	void	DeferSystemBtnPos(HDWP hdwp, int cx);
	

	// 버튼 활성화 변경
	void	EnableButton(ID_TITLEBAR id, BOOL bEnable);


public :
	virtual void	OnEnableTopmost(bool bEnable);
	virtual CString GetToolTipText(ID_TITLEBAR id);



	virtual CBitmap*		GetSysBtnBitmap(void) = 0;
	virtual Gdiplus::Image* GetSysBtnImage(void) = 0;
	virtual void GetSysBtnRes(CSize &szRes,
							  CPoint &ptClose,
							  CPoint &ptMinimize,
							  CPoint &ptMaximize,
							  CPoint &ptRestore,
							  CPoint &ptTopmost,
							  CPoint &ptNotopmost) = 0;
};

