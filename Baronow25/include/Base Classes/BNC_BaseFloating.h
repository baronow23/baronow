#pragma once

class BN25_TYPE BNC_BaseFloating : public BNC_BaseModaless
{
	friend class BNC_BaseDialog;


public:
	BNC_BaseFloating();
	virtual ~BNC_BaseFloating();


public:
	bool	m_bMouseMoveInitParent;		// 생성에 사용했던 팝업 윈도우 마우스로 이동할 수 있게 허용
	bool	m_MouseClockParentActive;	// 마우스 클릭시 창 종속 팝업에 활성화하고 창닫음

private :
	bool OnDraw(CDC* pMemDC, CDC* pResDC);
	


protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();


public:
	afx_msg void OnDestroy();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

};

