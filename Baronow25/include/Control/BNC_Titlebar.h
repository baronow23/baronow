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


// BNC_Titlebar::Create�� dwFlags
// �ý��� ��ư ��뿩�� (�ݱ� ��ư�� �⺻����, resotre�� maximize ������ ����)
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


	// ��ġ ������
	std::vector<BNC_Button*>	m_vpSysbtn;
	std::vector<int>			m_viSysbtnPos;


protected :

	int			m_iHeight;
	DWORD		m_dwFlags;
	bool		m_bTransparent;
	

	// ���� ������ ��ġ�ϴ� �ý��� ��ư offset
	int		m_iLeftBtnOffset;


	// Ȱ��, ��Ȱ�� ���� ����
	COLORREF	m_clrBkActivate;
	COLORREF	m_clrBkInActivate;
	COLORREF	m_clrTxtAvtivate;
	COLORREF	m_clrTxtInactivate;


	// �׸��� ����
	bool	m_bDrawLine;
	bool	m_bDrawText;
	bool	m_bAlignCenter;


	// ��� Ŭ���� ����
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
	�ý��� ��ư ��ġ ������Ʈ
	������¡ �Ǵ� �˾��� ũ�� ����� ȣ��
	BNC_BaseClient::OnUpdateClient()
	{
		HDWP hdwp = BeginDeferWindowPos(m_Titlebar.GetSysBtnCount() + X);
		m_Titlebar.DeferSystemBtnPos(hdwp, cx);
	}
	*/
	// �ý��� ��ư ��ġ ����
	UINT	GetSysBtnCount(void);
	void	DeferSystemBtnPos(HDWP hdwp, int cx);
	

	// ��ư Ȱ��ȭ ����
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

