#pragma once


class BN25_TYPE BNC_SimpleHScrollbar : public BNC_BaseControl
{
	DECLARE_DYNAMIC(BNC_SimpleHScrollbar)


public:
	BNC_SimpleHScrollbar(void);
	virtual ~BNC_SimpleHScrollbar(void);



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
	int		m_iFocusDnLeft;		// bar영역 큵릭시 m_rcBar.left과의 거리
	int		m_iFocusDnRight;	// bar영역 클릭시 m_rcBar.right과의 거리


	// 스크롤바 잡고 마우스 이동시 체크 (LBtnDown 포함)
	int		m_iOldMovePos;
	CPoint	m_ptLBtnPos0;
	

public :
	bool	m_bAutoHide;
	CWnd*	m_pCaptureAfterRelease;


private:
	// Overriding 
	bool OnCreate(void);
	void OnUpdateSize(int cx, int cy);
	bool OnDraw(CDC* pMemDC, CDC* pResDC);



	// 스크롤크기 및 타겟 윈도우 높이 변경시 호출
	// m_uiPos, m_rcBar 재산정
	void	UpdateScroll(bool bReDraw);


	
	// 스크롤영역의 위치(y)와 대상 윈도우 위치(y) 상호변환
	int		ClientPosToTargetPos(int iPos);
	int		TargetPosToClientPos(int iPos);


protected :
	// 부모에게 스크롤 위치 메시지 보냄
	void	SendScrollPos(void);	
	
	
public :
	void	SetLayout(BNS_ScrollbarLayout *pLayout, bool bRedraw = false);
	void	SetLength(int iLength, bool bUpdateNotify, bool bReDraw);
	void	SetPos(int iPos, bool bUpdateNotify, bool bReDraw);
	int		GetPos(void) const;
	int		GetLength(void) const;
	int		GetLayoutWidth(void) const;
	void	SetPosLength(int iPos, int iLength);
	bool	IsLBtnDown(void);



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
