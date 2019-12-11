#pragma once

#include <afxhtml.h>


//  OnBeforeNavigate2 : nFlags == 0x140일 때 파라미터 정보
struct BNS_HtmlLinkMove
{
	CString strURL;
	CString strTargetFrameName;
	CString strHeader;
	CString strReferer;
};

// MESSSAGE : BND_WM_HTML_WEBEVENT
// LOWROD(WPARAM) : BNE_WEBEVENT
// HIWROD(WPARAM) : navigation id
enum BNE_WEBEVENT
{
	BNE_WEBEVENT_NONE,
	BNE_WEBEVENT_TITLE,			// 페이지 타이틀 수신됨
	BNE_WEBEVENT_NAVIGATION,	// OnNavigateComplete2 수신
	BNE_WEBEVENT_LINKMOVE,		// 네이게이션 완료 후 마우스 클릭으로 링크 이동, (LPARAM : BNS_HtmlLinkMove*, PostMessage로 전송, 수신처 삭제 필수)
	BNE_WEBEVNET_NEWWINDOW,		// OnNewWindow2 수신 후 획득한 UURL 전송, (LPARAM : CString* URL, PostMessage로 전송, 수신처 삭제 필수)


	BNE_WEBEVENT_ERR_PAGE,		// 페이지를 찾을 수 없음
	BNE_WEBEVENT_ERR_FILE,		// 연결 요청한 URL이 파일임 (일단 막음)

	
};


// BNC_HtmlBrowserClient HTML 뷰입니다.
class BN25_TYPE BNC_HtmlBrowserClient : public CHtmlView
{
	DECLARE_DYNCREATE(BNC_HtmlBrowserClient)

protected:
	BNC_HtmlBrowserClient();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~BNC_HtmlBrowserClient();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


public :
	static CString GetRefererURL(CString strURL);


private :
	HWND	m_hNotify;
	UINT	m_uID;
	
	CString m_strTitle;
	CString m_strURL;
	bool	m_bNavigateError;


	DWORD	m_dwLastBeferFlags;	// OnBeforeNavigate2 : nFlags 값
	


	// 다음 OnTitleChange, OnNavigateComplete2 이벤트 발생시 문자열 적용시킬지 여부
	bool	m_bNextUpdateTitle;
	bool	m_bNextUpdateUrl;


private :
	LRESULT OnNewWindow3(WPARAM wParam, LPARAM lParam);


public :
	virtual void OnNavigateComplete2(LPCTSTR strURL);
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags,
								   LPCTSTR lpszTargetFrameName, CByteArray& baPostedData,
								   LPCTSTR lpszHeaders, BOOL* pbCancel);
	virtual void OnStatusTextChange(LPCTSTR lpszText);
	virtual void OnProgressChange(long nProgress, long nProgressMax);
	virtual void OnCommandStateChange(long nCommand, BOOL bEnable);
	virtual void OnDownloadBegin();
	virtual void OnDownloadComplete();
	virtual void OnTitleChange(LPCTSTR lpszText);
	virtual void OnPropertyChange(LPCTSTR lpszProperty);
	virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	virtual void OnQuit();
	virtual void OnVisible(BOOL bVisible);
	virtual void OnToolBar(BOOL bToolBar);
	virtual void OnMenuBar(BOOL bMenuBar);
	virtual void OnStatusBar(BOOL bStatusBar);
	virtual void OnFullScreen(BOOL bFullScreen);
	virtual void OnTheaterMode(BOOL bTheaterMode);
	virtual void OnNavigateError(LPCTSTR lpszURL, LPCTSTR lpszFrame, DWORD dwError, BOOL *pbCancel);


public:
	void	SetNotify(HWND hNotify);
	void	Navigation(UINT uiNewID, CString strURL);
	CString	GetTitle(void);
	CString GetURL(void);



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnAmbientProperty(COleControlSite* pSite, DISPID dispid, VARIANT* pvar);
	virtual void PostNcDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


