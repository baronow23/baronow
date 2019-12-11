#pragma once


enum BNE_MOUSESTATE
{
	BNE_MS_ENTER,
	BNE_MS_DOWN,
	BNE_MS_UP,
	BNE_MS_LEAVE,
};

class BN25_TYPE BNC_MouseControl
{
public:
	BNC_MouseControl(HWND hTarget);
	~BNC_MouseControl();


private :
	HWND			m_hTarget;
	CWnd*			m_pTarget;

public :
	bool			m_bEntry;
	bool			m_bLBtnDown;
	CPoint			m_ptMouse;
	BNE_MOUSESTATE	m_state;
	BNE_MOUSESTATE	m_stateOld;


public :
	bool IsPointIn(CPoint &point);
	bool Update(BNE_MOUSESTATE update);


public :
	// return : 마우스 조작 상태 변경 여부
	bool OnLButtonDown(UINT nFlags, CPoint &point);
	bool OnLButtonUp(UINT nFlags, CPoint &point);
	bool OnMouseMove(UINT nFlags, CPoint &point);
	bool OnCaptureChanged(CWnd *pWnd);
	
};

