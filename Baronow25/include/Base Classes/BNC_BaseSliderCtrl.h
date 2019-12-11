#pragma once


// BNC_BaseSliderCtrl
class BN25_TYPE BNC_BaseSliderCtrl : public BNC_BaseControl
{
	DECLARE_DYNAMIC(BNC_BaseSliderCtrl)

public:
	BNC_BaseSliderCtrl();
	virtual ~BNC_BaseSliderCtrl();

	
public :
	bool	m_bVertical;	// �������
	bool	m_bReadOnly;	// �б� ����
	bool	m_bUseBar;		// Bar ��뿩��
	CSize	m_szBarSize;	// Bar�� ����� ũ�� (����, ���� ����)
	float	m_fAddPos;

	COLORREF	m_colorBk;
	COLORREF	m_colorPos;
	COLORREF	m_colorBar;

protected :
	int		m_iBegin;		// ���� ��ġ
	int		m_iEnd;			// ���� ��ġ
	int		m_iPos;			// ���� ��ġ
	float	m_fRatio;		// ���� ��ġ ����
	CRect	m_rcBlank;		// ����(����� ���)
	CRect	m_rcSlider;		// Ŭ���̾�Ʈ �������� ���� ����
	CRect	m_rcSliderEx;	// m_rcSlier�� bar ���
	CRect	m_rcDrawPos;
	CRect	m_rcDrawBar;

	



private :
	// �̰͸� �������̵� �Ͻÿ�
	virtual bool	OnDraw(CDC* pMemDC, CDC* pResDC);


private:
	bool	OnCreate(void);
	void	OnUpdateSize(int cx, int cy);
	void	OnMouseControlUpdate(BNE_MOUSESTATE state, CPoint &point);

private :
	void	SendNotify(void);
	void	UpdatePosRatio(CPoint &ptMouse, bool bNotify, bool bRedraw = false);	// ���� ������Ʈ (Capture, Mouse Event)
	void	UpdatePosRatio(bool bRedraw = false);									// �ܺ� ȣ�� (SetRange, SetPos)
	void	UpdateDrawArea(void);													// Ŭ���̾�Ʈ ũ�� ���� �Ǵ� ��ġ�� ����� ȣ�� 

public :
	void	Initialize(bool bVertical, bool bReadOnly, bool bUseBar, CRect rcBlank = CRect(0, 0, 0, 0));
	void	SetRange(int iBegin, int iEnd, bool bRedraw = false);
	void	SetPos(int iPos, bool bRedraw = false);
	bool	SetPosRatio(float fRatio, bool bRedraw = false);
	
	int		GetPos(void);
	int		GetLength(void);
	float	GetPosRatio(void);

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEnable(BOOL bEnable);
};

