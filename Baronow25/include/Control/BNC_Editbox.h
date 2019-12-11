#pragma once
#include "BNC_Edit.h"

// Edit Style
#define BND_ES_ALIGNLEFT		0x00000000
#define BND_ES_ALIGNRIGHT		0x00000001
#define BND_ES_ALIGNCENTER		0x00000002
#define BND_ES_NUMBER			0x00000004
#define BND_ES_PASSWORD			0x00000008
#define BND_ES_READONLY			0x00000010
#define BND_ES_MULTILINE		0x00000020

#define BND_ES_TEXTBOLD			0x10000000
#define BND_ES_NOBOLDSWITCH		0x20000000
#define BND_ES_DIALMODE			0x40000000

//#define BND_ES_FIXBLANKSIZE		0x01000000



class BN25_TYPE BNC_Editbox : public BNC_BaseControl
{
public:
	BNC_Editbox();
	virtual ~BNC_Editbox();
	

protected :
	// 텍스트 동기화용
	CRITICAL_SECTION m_cs;

	// 입력 에디트 실체
	BNC_Edit	m_Edit;		

	
	// Initlize Style
	DWORD		m_dwInitStyle;


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
		

	// 멀티라인 사용시 (m_rcBlank무시)
	bool	m_bExtendEdit;
	int		m_iEditWidth;
	int		m_iVerScrollWidth;
	int		m_iScreenLine;
	void	UpdateEditExtend(void);

protected :
	virtual bool	OnCreate(void);
	virtual void	OnUpdateSize(int cx, int cy);
	virtual bool	OnDraw(CDC* pMemDC, CDC* pResDC);
	virtual LRESULT OnMessageEdit(WPARAM wParam, LPARAM lParam);

public :
	// 초기화 (BNC_BaseControl::create 이 후)
	bool	Initialize(CRect rtBlank, CString strFont, int iFontHeight, DWORD dwStyle);

	
	
	// 에디트 박스 입력 문자가 없을 때 지정된 메시지 출력
	// 글자 입력이 시작되면 메시지가 사라지고 입력문자가 지워지면 다시 출력
	// pFont 미지정시 initalize에서 설정한 폰트 사용
	void	SetGuideText(CString strGuide);
	void	SetGuideText(CString strGuide, COLORREF color, CFont* pFontPtr);

	
	// 배경, 텍스트 색상 변경 EnableWindow(FALSE)일 때는 텍스트 색 변경 않되고 회색으로 표현됨
	void	SetTextColor(COLORREF clrFocus, COLORREF clrUnFocus, bool bReDraw = true);
	void	SetBkColor(COLORREF clrEnable, COLORREF clrDisable, bool bReDraw = true);


	// 테두리 색상 변경
	void	SetEdgeColor(COLORREF clrUnFocus, COLORREF clrFocus, bool bReDraw = true);


	// 텍스트 설정, 반환
	void	SetText(CString str, bool bReDraw = true);
	CString	GetText(void);
	int		GetNumber(void);
	int		GetTextLength(void);

	
	// 텍스트 최대 길이 설정
	void	SetLimitText(UINT uiMax);

	
	// 에디트 박스컨트롤 반환
	CEdit*	GetEditCtl(void){	return &m_Edit; };
	

	// 마지막 입력키 반환
	WPARAM	GetLastPressKey(void);


private :

	// 호출전후에 크리티컬 섹션 사용해 줄 것!!!
	void	UpdateTextExtent(const HDC hDC, const CString &srcStr, CString &destStr, int iMaxExtent);
	

protected:
	DECLARE_MESSAGE_MAP()
	

public:
	afx_msg void OnDestroy();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


