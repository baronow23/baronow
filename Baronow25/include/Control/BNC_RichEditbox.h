#pragma once


// BNC_RichEditbox
#define NCT_EDIT_UNDO        _T("���� ���(&U)")
#define NCT_EDIT_CUT         _T("�߶󳻱�(&T)")
#define NCT_EDIT_COPY        _T("����(&C)")
#define NCT_EDIT_PASTE_TEXT  _T("�ؽ�Ʈ�� �ٿ��ֱ�(&P)")
#define NCT_EDIT_PASTE_IMAGE _T("�̹����� �ٿ��ֱ�(&P)")
#define NCT_EDIT_DELETE      _T("����(&D)")
#define NCT_EDIT_SELECTALL   _T("��� ����(&A)")
#define BND_WM_SELECTALL    WM_USER + 0x7000



class BN25_TYPE BNC_RichEditbox : public CRichEditCtrl
{
	DECLARE_DYNAMIC(BNC_RichEditbox)

public:
	BNC_RichEditbox();
	virtual ~BNC_RichEditbox();


public:
	static UINT s_uiCreateCount;
	static UINT s_uiDestroyCount;

protected:
	BNC_BaseClient*		m_pParentClientPtr;
	HWND				m_hNotifyEvent;
	UINT				m_uiEventID;
	CString				m_strEdit;

	COLORREF	m_colorBk;
	COLORREF	m_colorText;
	COLORREF	m_colorBkDim;
	COLORREF	m_colorTextDim;

	BNC_ClipboardImage	m_cbImage;


protected:
	// �˾� �޴� Ȱ��ȭ üũ
	bool	m_bActiveMenu;


public:
	// enter �Է½� �ٰ��� ��� (false�� shift+enter ������ ����)
	bool	m_bEnterToEOL;

public:
	bool	create(BNC_BaseClient* pClientPtr, USHORT uiEventID, CRect rcWindow = CRect(0, 0, 0, 0), UINT uiAddStyle = 0);
	bool	Initialize(CString strFont,
					   int iFontHeight,
					   bool bBold,
					   COLORREF crBk		= RGB(255, 255, 255),
					   COLORREF crText		= RGB(0, 0, 0),
					   COLORREF crBkDim		= RGB(240, 240, 240),
					   COLORREF crTextDim	= RGB(100, 100, 100));

	bool	UpdateColor(void);


private:
	void	AddEOL(void);

protected:
	virtual LRESULT OnMessageContextMenu(WPARAM wParam, LPARAM lParam);


public:
	CString GetText(void);
	void	SetText(CString str, bool bReDraw = true);


protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL	PreTranslateMessage(MSG* pMsg);
	virtual BOOL	Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	virtual BOOL	CreateEx(DWORD dwExStyle, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

public:

	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void	OnDestroy();


	afx_msg HBRUSH	OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH	CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg void	OnEnChange();
	afx_msg void	OnEnUpdate();
	afx_msg void	OnEnSetfocus();
	afx_msg void	OnEnKillfocus();
	afx_msg void	OnEnMsgfilter(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL	OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	afx_msg void OnEnDropfiles(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEnable(BOOL bEnable);
	virtual void PreSubclassWindow();
	afx_msg LRESULT OnPaste(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPasteImage(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


