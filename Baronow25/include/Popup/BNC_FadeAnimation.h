#pragma once


// BNC_FadeAnimation

class BN25_TYPE BNC_FadeAnimation : public CWnd
{
	DECLARE_DYNAMIC(BNC_FadeAnimation)

private :
	BNC_FadeAnimation();
	virtual ~BNC_FadeAnimation();

private :
	BYTE	m_btAlpha;
	bool	create(CRect rect, CDC* pDC);

public :
	static	bool Run(CRect rect, CDC* pDC);

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


