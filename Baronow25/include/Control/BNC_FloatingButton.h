#pragma once


class BN25_TYPE BNC_FloatingButton : public BNC_BaseFloating
{
public:
	BNC_FloatingButton();
	virtual ~BNC_FloatingButton();
	

protected :
	HWND				m_hNotifyEvent;		// �̺�Ʈ �˸� �ڵ� (�⺻ : m_pInitParent)
	USHORT				m_uiEventID;
	BNC_MouseControl*	m_pMouseControl;
	HCURSOR				m_hCursor;

	// �÷��� ��ư�� BNC_BaseDialog::SetLayerImage() ������ �켱�Ǿ�� �ϸ�
	// ���� �� point�� SetLayerImage()�� ptImage������ offset ó����ų �̹����� ��ġ��
	CPoint	m_ptImageFocus;
	CPoint	m_ptImagePush;
	CPoint	m_ptImageDisable;

	
	// Normal, Focus, Push, Disable ���¿� ���� ����
	BYTE	m_pbtAlpha[4];



private :
	// BNC_MouseControl ���� ����� ������Ʈ
	void	OnMouseControlUpdate(BNE_MOUSESTATE state, const CPoint &point);


	// �̺�Ʈ ����
	void	SendNotify(void);



public :
	// �̺�Ʈ ����
	void	SetNotify(HWND hNotify, UINT id);


	// �̹��� ���̾� ����
	void	SetStateOffset(CPoint ptFocus, CPoint ptPush, CPoint ptDisable, bool bRedraw);
	void	SetStateAlpha(BYTE btNormal, BYTE btFocus, BYTE btPush, BYTE btDisable, bool bRedraw);


	// Ŀ�� ����
	void	SetCursor(HCURSOR hCursor);
	

	// ���� ���¿� ���� ������ �̹��� ���̴� ����
	void	UpdateImageLayer(void);


protected :
	DECLARE_MESSAGE_MAP()


public :
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	virtual BOOL OnInitDialog();
	afx_msg void OnEnable(BOOL bEnable);
	
};

