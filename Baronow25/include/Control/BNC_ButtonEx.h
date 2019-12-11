#pragma once

class BN25_TYPE BNC_ButtonEx : public BNC_Button
{
public:
	BNC_ButtonEx();
	virtual ~BNC_ButtonEx();


private :
	bool	m_bDrawEnable;


	// ������ (Resource Line ���� ����)
	Gdiplus::Image* m_pBoradImage;
	bool			m_bUseSingleState;		// Normal �̹��� �ϳ��� ���
	CPoint			m_ptBoard;
	CSize			m_szBoard;
	CPoint			m_ptBoardOffset;		// �θ� ��ư���� �׸��� LeftTop ��ġ
	CPoint			m_ptBoardCenter;		// ������ �߽�
	
	// ��� �ؽ�Ʈ(�����ġ�� board �߽�)
	CString			m_strBoardText;
	COLORREF		m_pBoardTextColor[4];
	CFont			m_fontBoardText;
	CPoint			m_ptBoardText;
	CSize			m_szBoardText;
	

protected :
	virtual bool OnDrawEx(CDC* pMemDC, Gdiplus::Graphics *pGraphics, UINT iStateIndex);
	void	UpdateBoardTextPos(void);


public :
	void	SetDrawEnable(bool bEnable);
	void	SetBoardImage(Gdiplus::Image* pImagePtr, bool bUseSingleState, CPoint ptLeftTop, CSize szQuarter, CPoint ptParentOffset, bool bRedraw = false);
	void	SetBoardText(CString str, bool bRedraw = false);
	void	SetBoardText(UINT uiCount, bool bRedraw = false);
	void	SetBoardTextFont(LPCTSTR strFont, UINT iHeight, UINT iWeight = FW_NORMAL, bool bRedraw = false);
	void	SetBoardTextColor(COLORREF clrNormal, COLORREF clrFocus, COLORREF clrDown, COLORREF clrDisable, bool bRedraw = false);
	CString GetBoardText(void);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
};

