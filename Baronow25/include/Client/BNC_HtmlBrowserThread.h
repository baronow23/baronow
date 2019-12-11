#pragma once

#include <mutex>
#include "BNC_HtmlBrowserClient.h"

enum HTML_THREAD_MESSAGE
{
	HTML_THREAD_MESSAGE_INITIALIZE = WM_APP + 1,	// WPARAM : 이벤트 수신 핸들
	HTML_THREAD_MESSAGE_RELEASE,
	HTML_THREAD_MESSAGE_NAVIGATION,					// WPARAM : CString* 수신처 삭제, , LPARAM : navigation id
	HTML_THREAD_MESSAGE_NAVIGATION_END,
	HTML_THREAD_MESSAGE_UPDATEVIEW,					// WPARAM : MAKELONG(cx, cy), LPARAM : SetWindowPos flags
};




// BNC_HtmlBrowserThread

class BN25_TYPE BNC_HtmlBrowserThread : public CWinThread
{
	DECLARE_DYNCREATE(BNC_HtmlBrowserThread)

protected:
	BNC_HtmlBrowserThread();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~BNC_HtmlBrowserThread();


private:
	recursive_mutex m_viewtex;
	BNC_HtmlBrowserClient *m_pHtmlView;


	HWND	m_hCheckView;
	int		m_iCheckCount;


public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();


private :
	void	DestroyView(void);
	void	OnMsgInitialize(WPARAM wParam, LPARAM lParam);
	void	OnMsgRelease(WPARAM wParam, LPARAM lParam);
	void	OnMsgNavigation(WPARAM wParam, LPARAM lParam);
	void	OnMsgNavigationEnd(WPARAM wParam, LPARAM lParam);
	void	OnMsgUpdateView(WPARAM wParam, LPARAM lParam);

public :
	// view OnDestroy() 중복 호출때문에 임시 설정
	// BNC_HtmlBrowser의 OnDestroy가 처리기전에 view를 숨기고 부모를 desktopwindow로 변경함
	void	PreDestroyView(void);


public :
	CString GetTitle(void);
	CString GetURL(void);
	//void	UpdateView(int cx, int cy, UINT uiFlags);


protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnIdle(LONG lCount);
};


