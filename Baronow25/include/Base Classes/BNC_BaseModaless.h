#pragma once

class BN25_TYPE BNC_BaseModaless : public BNC_BaseDialog
{
public:
	BNC_BaseModaless();
	virtual ~BNC_BaseModaless();


private:
	static UINT s_uiCreateCount;
	static UINT s_uiDestroyCount;


public:
	static UINT	GetCreateCount(void);
	static UINT	GetAliveCount(void);

	
private :
	virtual void OnUpdateSize(int cx, int cy);


protected :
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);


protected :
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
public:
	afx_msg void OnClose();
};

