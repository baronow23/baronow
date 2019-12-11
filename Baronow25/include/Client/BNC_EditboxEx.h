#pragma once



// 부모윈도우는 반드시  BNC_BaseClient 이여야함!!

class BN25_TYPE BNC_EditboxEx : public BNC_BaseClient
{
public:
	BNC_EditboxEx();
	virtual ~BNC_EditboxEx();


private :
	// 입력 에디트 실체
	BNC_Edit	m_Edit;
	USHORT		m_uiEditID;


	// 크기 정보
	CRect		m_rcBlank;		// 입력 에디트의의 상하좌우 여백
	int			m_iTextWidth;	// 출력가능한 텍스트 넓이(픽셀좌표)
	int			m_iFontHeight;	// 폰트크기
	int			m_iEditHeight;


	// 적용 폰트
	CFont		m_fontNormal;
	CFont		m_fontBold;


	// 에디트 포커스 상태에 따라 그려줄 테두리
	COLORREF	m_pColorEdge[2];
	CPen		m_pPenEdge[2];
	
	// 테두리 사용 여부 ; true : 사각 테두리 표현 | false : 밑줄로 표현 (로그인 시)
	bool		m_bUseBorder;


private :
	// 옵션 : delete 버튼 사용시 설정
	//(텍스트 내용 있을 때 보여지고 없을 때 감춰짐)
	BNC_Button	m_btnClear;
	CPoint		m_ptBtnClearPos;	// x = 클라이언트 right위치에서 좌측으로 위치할 값, y = 클라이언트 top 기준 위치
	


	// 에디트 좌측에 보여질 이미지 사용시 설정
	CBitmap*		m_pGuideBmPtr;
	Gdiplus::Image* m_pGuideImgPtr;
	CPoint			m_ptGuideImageDraw;	// 출력 위치 (LeftTop)
	CPoint			m_ptGuideImage;		// 리소스 위치
	CSize			m_szGuideImage;		// 리소스 크기


	// 에디트 좌측에 보여질 이미지 사용시 설정 (Focus 상태)
	CBitmap*		m_pGuideBmPtr2;
	Gdiplus::Image* m_pGuideImgPtr2;
	CPoint			m_ptGuideImageDraw2;	// 출력 위치 (LeftTop)
	CPoint			m_ptGuideImage2;		// 리소스 위치
	CSize			m_szGuideImage2;		// 리소스 크기



public :
	// true : 입력 텍스트가 있을 때 보여지고 없어질 때 감춰짐 (default = false)
	// false : show/hide 사용자 지정 (ShowClearButton사용)
	bool	m_bAutoClearButton;

	
	// SetText, AddEOL, SetState 호출시 bAfterEvent에 false를 지정하거나 
	// 특정 시점의 에디트 박스 업데이트를 일시적으로 받고싶지 않을 때 1회에 한하여 부모에게 이벤트 발생 않함
	bool	m_bPassNextUpdateNoti;



private:
	bool	OnCreate(void);
	void	OnModifyPopupPtr(BNC_BaseDialog* pNewPopup);
	void	OnUpdateSize(int cx, int cy);				
	bool	OnDraw(CDC* pMemDC, CDC* pResDC);			
	LRESULT OnMessageEdit(WPARAM wParam, LPARAM lParam);
	LRESULT OnMessageButton(WPARAM wParam, LPARAM lParam);


public:
	// create 이후 컨트롤 생성
	bool	CreateEdit(USHORT m_uiEventID, CRect rcBlank, CString strFont, int iFontHeight, DWORD dwStyle, bool bUseBorder = true);
	bool	CreateClearButtonBm(USHORT uiEventID, CPoint ptSyncRT, CBitmap *pBitmapPtr, CPoint ptRes, CSize szRes4);
	bool	CreateClearButtonImg(USHORT uiEventID, CPoint ptSyncRT, Gdiplus::Image* pImgPtr, CPoint ptRes, CSize szRes4, COLORREF clrBk);
	void	SetClearBtnTooltip(CString strTip);


	// 가이드 이미지 설정
	void	SetGuideBitmap(CBitmap* pBitmapPtr, CPoint ptDrawPos, CPoint ptRes, CSize szRes);
	void	SetGuideImage(Gdiplus::Image* pImgPtr, CPoint ptDrawPos, CPoint ptRes, CSize szRes);

	void	SetGuideBitmapFocus(CBitmap* pBitmapPtr, CPoint ptDrawPos, CPoint ptRes, CSize szRes);
	void	SetGuideImageFocus(Gdiplus::Image* pImgPtr, CPoint ptDrawPos, CPoint ptRes, CSize szRes);


	// 에디트 박스 입력 문자가 없을 때 지정된 메시지 출력
	// 글자 입력이 시작되면 메시지가 사라지고 입력문자가 지워지면 다시 출력
	// pFont 미지정시 initalize에서 설정한 폰트 사용
	void	SetGuideText(CString strGuide);
	void	SetGuideText(CString strGuide, COLORREF color, CFont* pFontPtr);
	void	SetGuideTextAdd(CString strGuideLast, COLORREF color);



	// 배경, 텍스트 색상 변경 EnableWindow(FALSE)일 때는 텍스트 색 변경 않되고 회색으로 표현됨
	void	SetTextColor(COLORREF clrFocus, COLORREF clrUnFocus, bool bReDraw = true);
	void	SetBkColor(COLORREF clrEnable, COLORREF clrDisable, bool bReDraw = true);


	// 테두리 색상 변경
	void	SetEdgeColor(COLORREF clrUnFocus, COLORREF clrFocus, bool bReDraw = true);


	// 텍스트 설정, 반환
	void	SetText(CString str, bool bReDraw = true, bool bAfterEvent = true);
	CString	GetText(void);
	int		GetNumber(void);
	int		GetTextLength(void);

	void	SetState(BNC_EditState &state, bool bReDraw, bool bFocus, bool bAfterEvent = true);
	void	GetState(BNC_EditState &state);


	// 텍스트 최대 길이 설정
	void	SetLimitText(UINT uiMax);


	// 에디트 박스컨트롤 반환
	CEdit* GetEditCtl(void)
	{
		return &m_Edit;
	};

	// 마지막 입력키 반환
	WPARAM	GetLastPressKey(void);


	// 현재 텍스트 마지막에 문자열 붙임
	void	AddEOL(CString str, bool bSelect, bool bAfterEvent = true);


	// m_bAutoClearButton이 false일 때만 적용
	void	ShowClearButton(bool bShow);



private:

	// 호출전후에 크리티컬 섹션 사용해 줄 것!!!
	void	UpdateTextExtent(const HDC hDC, const CString &srcStr, CString &destStr, int iMaxExtent);


	// 에디트 텍스트 변경시 show/hide 업데이트
	void	UpdateDeleteButton(void);


protected:
	DECLARE_MESSAGE_MAP()
	

public:
	afx_msg void OnDestroy();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

