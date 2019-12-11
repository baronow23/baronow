#pragma once

struct BNS_AsyncMessageBoxLayout
{
	 BNS_AsyncMessageBoxLayout(void)
	 {
		 pFontCaptionPtr	= nullptr;
		 pFontMessagePtr	= nullptr;
		 pbmCloseBtn		= nullptr;
		 ptCloseBtn			= CPoint(0, 0);
		 szCloseBtn			= CSize(0, 0);
	 };

	 // 제목, 내용 폰트
	 CFont* pFontCaptionPtr;
	 CFont* pFontMessagePtr;


	 // 닫기 버튼 이미지
	 CBitmap*	pbmCloseBtn;
	 CPoint		ptCloseBtn;	
	 CSize		szCloseBtn;
};

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

class BN25_TYPE BNC_AsyncMessageBoxRoot : public BNC_BaseClient
{
public:
	BNC_AsyncMessageBoxRoot();
	~BNC_AsyncMessageBoxRoot();

	enum class BtnID
	{
		Close,
		Cancel,
		Ok,
	};


private :
	BNC_Button m_btnClose;
	BNC_Button m_btnOK;
	std::unique_ptr<BNC_Button> m_pBtnCancel;
	
	CString m_strCaption;
	vector<CString> m_vStrMessage;

	size_t	m_iMsgHeight;
	size_t	m_iMsgBlank;


	CFont* m_pFontCaptionPtr;
	CFont* m_pFontMessagePtr;

	COLORREF m_clrCaption;
	COLORREF m_clrMessage;


private:
	bool	OnCreate(void);
	void	OnUpdateClient(int cx, int cy);
	bool	OnDraw(CDC* pMemDC, CDC* pResDC);
	void	OnDrawButton(USHORT uiEventID, CDC* pMemDC, CDC* pResDC, Gdiplus::Graphics *pGraphics, int iState, CSize szCtl);
	void	OnModifyPopupPtr(BNC_BaseDialog* pNewPopup);
	LRESULT OnMessageButton(WPARAM wParam, LPARAM lParam);


private :
	bool	InitButton(BNC_Button &btn, USHORT id, CString strName, COLORREF clrDown);


public :
	CSize	Initialize(LPCTSTR lpszCaption, LPCTSTR lpszMessage, bool bUseCancel, COLORREF clrCaption, COLORREF clrMessage);

public :
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
};


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


class BN25_TYPE BNC_AsyncMessageBox final : public BNC_FakeModal
{
public:
	BNC_AsyncMessageBox(BNC_BaseDialog* pParent, LPCTSTR lpszCaption, LPCTSTR lpszMessage, bool bUseCancel,
					COLORREF clrCaption = VSCLR_TEXT, COLORREF clrMessage = VSCLR_VARIABLE, CSize szMin = CSize(250, 100));
	~BNC_AsyncMessageBox();


public :
	static BNS_AsyncMessageBoxLayout s_DefaultLayout;
	static void SetDefaultLayout(BNS_AsyncMessageBoxLayout &layout);


private :
	BNC_AsyncMessageBoxRoot	m_RootClient;

private:
	bool	OnCreate(void);
	void	OnUpdateSize(int cx, int cy);

	
public :
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
};


