#pragma once


class BN25_TYPE BNC_StaticObject
{
private :
	static BNC_StaticObject* s_pInstance;
	BNC_StaticObject(void);
	~BNC_StaticObject(void);


public :
	static void					InitInstance(void);
	static BNC_StaticObject*	GetInstance(void);
	static void					ExitInstance(void);


	static void	ShowRichEditMenu(HWND hNotifyWnd, bool bEnableText, bool bEnableImage);
	static void	ShowRichEditMenu(HWND hNotifyWnd, bool bEnableText, bool bEnableImage, CPoint pt);


private:
	void	CreateRichEditMenu(void);


private :
	//FILE*	m_pConsole;
	UINT	m_uiDummyTemplate;


	// GDI+
	ULONG_PTR m_gpToken;


	// RichEdit �˾� (�ؽ�Ʈ �ٿ��ֱ�, �̹��� �ٿ��ֱ� �ɼ�)
	BNC_PopupMenu	*m_pMenuRichEdit;

};
