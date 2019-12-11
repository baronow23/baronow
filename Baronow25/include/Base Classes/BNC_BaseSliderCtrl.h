#pragma once


// BNC_BaseSliderCtrl
class BN25_TYPE BNC_BaseSliderCtrl : public BNC_BaseControl
{
	DECLARE_DYNAMIC(BNC_BaseSliderCtrl)

public:
	BNC_BaseSliderCtrl();
	virtual ~BNC_BaseSliderCtrl();

	
public :
	bool	m_bVertical;	// 수직모드
	bool	m_bReadOnly;	// 읽기 전용
	bool	m_bUseBar;		// Bar 사용여부
	CSize	m_szBarSize;	// Bar로 사용할 크기 (수직, 수평 공통)
	float	m_fAddPos;

	COLORREF	m_colorBk;
	COLORREF	m_colorPos;
	COLORREF	m_colorBar;

protected :
	int		m_iBegin;		// 시작 위치
	int		m_iEnd;			// 종료 위치
	int		m_iPos;			// 현재 위치
	float	m_fRatio;		// 현재 위치 비율
	CRect	m_rcBlank;		// 여백(양수만 사용)
	CRect	m_rcSlider;		// 클라이언트 영역에서 여백 제외
	CRect	m_rcSliderEx;	// m_rcSlier에 bar 사용
	CRect	m_rcDrawPos;
	CRect	m_rcDrawBar;

	



private :
	// 이것만 오버라이딩 하시오
	virtual bool	OnDraw(CDC* pMemDC, CDC* pResDC);


private:
	bool	OnCreate(void);
	void	OnUpdateSize(int cx, int cy);
	void	OnMouseControlUpdate(BNE_MOUSESTATE state, CPoint &point);

private :
	void	SendNotify(void);
	void	UpdatePosRatio(CPoint &ptMouse, bool bNotify, bool bRedraw = false);	// 내부 업데이트 (Capture, Mouse Event)
	void	UpdatePosRatio(bool bRedraw = false);									// 외부 호출 (SetRange, SetPos)
	void	UpdateDrawArea(void);													// 클라이언트 크기 변경 또는 위치비 변경시 호출 

public :
	void	Initialize(bool bVertical, bool bReadOnly, bool bUseBar, CRect rcBlank = CRect(0, 0, 0, 0));
	void	SetRange(int iBegin, int iEnd, bool bRedraw = false);
	void	SetPos(int iPos, bool bRedraw = false);
	bool	SetPosRatio(float fRatio, bool bRedraw = false);
	
	int		GetPos(void);
	int		GetLength(void);
	float	GetPosRatio(void);

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEnable(BOOL bEnable);
};

