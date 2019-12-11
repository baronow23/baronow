#pragma once

#include "BNC_HtmlBrowserThread.h"
class BN25_TYPE BNC_HtmlBrowser : public BNC_BaseClient
{
public:
	BNC_HtmlBrowser();
	~BNC_HtmlBrowser();


private :
	UINT m_uiNavigationID;
	BNC_HtmlBrowserThread *m_pThread;
	HANDLE m_hChkThread;


public :
	BNE_WEBEVENT m_NavigationResult;


private:
	bool OnCreate(void);
	void OnModifyPopupPtr(BNC_BaseDialog* pNewPopup);
	void OnUpdateClient(int cx, int cy);
	bool OnDraw(CDC* pMemDC, CDC* pResDC);
	void OnUpdatePopupStatus(BNE_POPUP_STATUS status);


private :
	virtual LRESULT OnMessageHtmlWebEvent(WPARAM wParam, LPARAM lParam);
	

private :
	bool ReleaseThread(void);


public :
	bool		Navigation(CString strURL);
	CString		GetTitle(void);
	CString		GetURL(void);

public :
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();

};

