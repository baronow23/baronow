#pragma once


// BNC_HtmlBrowserFrame 프레임입니다.

class BN25_TYPE BNC_HtmlBrowserFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(BNC_HtmlBrowserFrame)
protected:
	BNC_HtmlBrowserFrame();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~BNC_HtmlBrowserFrame();

protected:
	DECLARE_MESSAGE_MAP()
};


