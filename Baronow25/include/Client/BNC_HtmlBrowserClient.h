#pragma once

#include <afxhtml.h>


//  OnBeforeNavigate2 : nFlags == 0x140�� �� �Ķ���� ����
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
	BNE_WEBEVENT_TITLE,			// ������ Ÿ��Ʋ ���ŵ�
	BNE_WEBEVENT_NAVIGATION,	// OnNavigateComplete2 ����
	BNE_WEBEVENT_LINKMOVE,		// ���̰��̼� �Ϸ� �� ���콺 Ŭ������ ��ũ �̵�, (LPARAM : BNS_HtmlLinkMove*, PostMessage�� ����, ����ó ���� �ʼ�)
	BNE_WEBEVNET_NEWWINDOW,		// OnNewWindow2 ���� �� ȹ���� UURL ����, (LPARAM : CString* URL, PostMessage�� ����, ����ó ���� �ʼ�)


	BNE_WEBEVENT_ERR_PAGE,		// �������� ã�� �� ����
	BNE_WEBEVENT_ERR_FILE,		// ���� ��û�� URL�� ������ (�ϴ� ����)

	
};


// BNC_HtmlBrowserClient HTML ���Դϴ�.
class BN25_TYPE BNC_HtmlBrowserClient : public CHtmlView
{
	DECLARE_DYNCREATE(BNC_HtmlBrowserClient)

protected:
	BNC_HtmlBrowserClient();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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


	DWORD	m_dwLastBeferFlags;	// OnBeforeNavigate2 : nFlags ��
	


	// ���� OnTitleChange, OnNavigateComplete2 �̺�Ʈ �߻��� ���ڿ� �����ų�� ����
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnAmbientProperty(COleControlSite* pSite, DISPID dispid, VARIANT* pvar);
	virtual void PostNcDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


