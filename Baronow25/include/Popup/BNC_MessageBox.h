#pragma once

class BN25_TYPE BNC_MessageBox : public BNC_BaseModal
{
public:
	BNC_MessageBox(UINT nDialogID, CWnd *pTarget, CWnd *pParent);
	virtual ~BNC_MessageBox();


public :
	static CFont*	s_pFontTitle;
	static CFont*	s_pFontSubstance;


private :
	BNC_TempClient	m_RootClient;
	BNC_Button*		m_pBtnOK;
	BNC_Button*		m_pBtnCancel;


protected :
	COLORREF		m_colorTitle;
	COLORREF		m_colorControl;
	// 본문은 배경색 사용


	BNC_DrawString					m_Title;
	std::vector<BNC_DrawString*>	m_vSubstance;
	
	
	UINT		m_uiHeightTitle;	// 타이틀바 영역 
	UINT		m_uiHeightControl;	// 컨트롤 영역
	UINT		m_uiHeightTop;		// 본문 영역 상단 여백
	UINT		m_uiHeightBottom;	// 본문 영역 하단 여백
	UINT		m_uiHeightSpacing;	// 본문 줄간격



	// 고정 가로폭 사용 여부
	bool	m_bUseDefaultWidth;
	UINT	m_uiDefaultWidth;
	

private :
	// 내부처리
	void	Clear(void);
	void	UpdateSize(void);
	LRESULT OnMessageButton(WPARAM wParam, LPARAM lParam);


protected :
	CPoint	GetButtonPos(HWND hButton, int iCenter);



private :
	// 버튼 스타일 정의 (옵션)
	virtual bool OnSetButton(BNC_Button* pBtnOK, BNC_Button* pBtnCancel);	
	

	// 버튼 위치 재정의 (옵션)
	virtual void OnButtonPos(HDWP &hdwp, HWND hBtnOK, HWND hBtnCancel);

	
	// Clinet 그리기 재정의
	virtual bool OnDrawRootClient(CDC* pMemDC, CDC* pResDC);
	


public :
	// 타이틀바 미사용시 _T("") 입력
	// strSubstance 내용 줄바꿈은 '/n' 또는 '/r/n'
	bool	InitMessageBox(CString strTitle, CString strSubstance, bool bUseCancel);


	// iTitle : 타이틀바 높이
	// iControl : 확인/취소 컨트롤 영역 높이
	// iTop : 본문 출력 상단 여백
	// iBottom : 본문 출력 하단 여백
	// iSpacing : 본문 각 중간 여백
	void	SetHeight(UINT uiTitle, UINT uiControl, UINT uiTop, UINT uiBottom, UINT uiSpacing);



	// Title 출력 스타일
	void	SetTitleStyle(CFont* pFontPtr,
						COLORREF color,
						UINT uiAlign = TA_LEFT,
						UINT uiLeftBlank = 5,
						UINT uiRightBlank = 5);



	// 내용 출력 스타일 (일괄 지정)
	void	SetSubstanceStyle(CFont* pFontPtr,
							  COLORREF color,
							  UINT uiAlign = TA_CENTER,
							  UINT uiLeftBlank = 10,
							  UINT uiRightBlank = 10);


	// 내용 출력 스타일 (개별 지정)
	// index는 InitMessageBox() 에서 입력한 strSubstance 줄바꿈 단위
	bool	SetSubstanceStyle(UINT index,
							  CFont* pFontPtr,
							  COLORREF color,
							  UINT uiAlign = TA_CENTER,
							  UINT uiLeftBlank = 10,
							  UINT uiRightBlank = 10);

	

	// 설정 옵션 적용 : ShowMessage() 미사용시 (DoModal(), Modal() 직접 호출시) 
	void	UpdateMessage(void);


	// UpdateMessage() 적용후 Modal() 처리함
	INT_PTR	ModalMessage(bool bUseOverlay = true, BYTE btOverlayAlpha = 25, COLORREF clrOverlayBk = RGB(0, 0, 0));


protected :
	virtual BOOL OnInitDialog();
	
public :
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

