#pragma once
#include "BNC_Edit.h"

// Edit Style
#define BND_ES_ALIGNLEFT		0x00000000
#define BND_ES_ALIGNRIGHT		0x00000001
#define BND_ES_ALIGNCENTER		0x00000002
#define BND_ES_NUMBER			0x00000004
#define BND_ES_PASSWORD			0x00000008
#define BND_ES_READONLY			0x00000010
#define BND_ES_MULTILINE		0x00000020

#define BND_ES_TEXTBOLD			0x10000000
#define BND_ES_NOBOLDSWITCH		0x20000000
#define BND_ES_DIALMODE			0x40000000

//#define BND_ES_FIXBLANKSIZE		0x01000000



class BN25_TYPE BNC_Editbox : public BNC_BaseControl
{
public:
	BNC_Editbox();
	virtual ~BNC_Editbox();
	

protected :
	// �ؽ�Ʈ ����ȭ��
	CRITICAL_SECTION m_cs;

	// �Է� ����Ʈ ��ü
	BNC_Edit	m_Edit;		

	
	// Initlize Style
	DWORD		m_dwInitStyle;


	// ũ�� ����
	CRect		m_rcBlank;		// �Է� ����Ʈ���� �����¿� ����
	int			m_iTextWidth;	// ��°����� �ؽ�Ʈ ����(�ȼ���ǥ)
	int			m_iFontHeight;	// ��Ʈũ��
	int			m_iEditHeight;	


	// ���� ��Ʈ
	CFont		m_fontNormal;
	CFont		m_fontBold;

	
	// ����Ʈ ��Ŀ�� ���¿� ���� �׷��� �׵θ�
	COLORREF	m_pColorEdge[2];
	CPen		m_pPenEdge[2];
		

	// ��Ƽ���� ���� (m_rcBlank����)
	bool	m_bExtendEdit;
	int		m_iEditWidth;
	int		m_iVerScrollWidth;
	int		m_iScreenLine;
	void	UpdateEditExtend(void);

protected :
	virtual bool	OnCreate(void);
	virtual void	OnUpdateSize(int cx, int cy);
	virtual bool	OnDraw(CDC* pMemDC, CDC* pResDC);
	virtual LRESULT OnMessageEdit(WPARAM wParam, LPARAM lParam);

public :
	// �ʱ�ȭ (BNC_BaseControl::create �� ��)
	bool	Initialize(CRect rtBlank, CString strFont, int iFontHeight, DWORD dwStyle);

	
	
	// ����Ʈ �ڽ� �Է� ���ڰ� ���� �� ������ �޽��� ���
	// ���� �Է��� ���۵Ǹ� �޽����� ������� �Է¹��ڰ� �������� �ٽ� ���
	// pFont �������� initalize���� ������ ��Ʈ ���
	void	SetGuideText(CString strGuide);
	void	SetGuideText(CString strGuide, COLORREF color, CFont* pFontPtr);

	
	// ���, �ؽ�Ʈ ���� ���� EnableWindow(FALSE)�� ���� �ؽ�Ʈ �� ���� �ʵǰ� ȸ������ ǥ����
	void	SetTextColor(COLORREF clrFocus, COLORREF clrUnFocus, bool bReDraw = true);
	void	SetBkColor(COLORREF clrEnable, COLORREF clrDisable, bool bReDraw = true);


	// �׵θ� ���� ����
	void	SetEdgeColor(COLORREF clrUnFocus, COLORREF clrFocus, bool bReDraw = true);


	// �ؽ�Ʈ ����, ��ȯ
	void	SetText(CString str, bool bReDraw = true);
	CString	GetText(void);
	int		GetNumber(void);
	int		GetTextLength(void);

	
	// �ؽ�Ʈ �ִ� ���� ����
	void	SetLimitText(UINT uiMax);

	
	// ����Ʈ �ڽ���Ʈ�� ��ȯ
	CEdit*	GetEditCtl(void){	return &m_Edit; };
	

	// ������ �Է�Ű ��ȯ
	WPARAM	GetLastPressKey(void);


private :

	// ȣ�����Ŀ� ũ��Ƽ�� ���� ����� �� ��!!!
	void	UpdateTextExtent(const HDC hDC, const CString &srcStr, CString &destStr, int iMaxExtent);
	

protected:
	DECLARE_MESSAGE_MAP()
	

public:
	afx_msg void OnDestroy();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


