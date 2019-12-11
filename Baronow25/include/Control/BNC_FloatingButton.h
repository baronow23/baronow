#pragma once


class BN25_TYPE BNC_FloatingButton : public BNC_BaseFloating
{
public:
	BNC_FloatingButton();
	virtual ~BNC_FloatingButton();
	

protected :
	HWND				m_hNotifyEvent;		// 이벤트 알림 핸들 (기본 : m_pInitParent)
	USHORT				m_uiEventID;
	BNC_MouseControl*	m_pMouseControl;
	HCURSOR				m_hCursor;

	// 플로팅 버튼은 BNC_BaseDialog::SetLayerImage() 설정이 우선되어야 하며
	// 다음 각 point는 SetLayerImage()의 ptImage값에서 offset 처리시킬 이미지의 위치임
	CPoint	m_ptImageFocus;
	CPoint	m_ptImagePush;
	CPoint	m_ptImageDisable;

	
	// Normal, Focus, Push, Disable 상태에 대한 투명값
	BYTE	m_pbtAlpha[4];



private :
	// BNC_MouseControl 상태 변경시 업데이트
	void	OnMouseControlUpdate(BNE_MOUSESTATE state, const CPoint &point);


	// 이벤트 전송
	void	SendNotify(void);



public :
	// 이벤트 설정
	void	SetNotify(HWND hNotify, UINT id);


	// 이미지 레이어 설정
	void	SetStateOffset(CPoint ptFocus, CPoint ptPush, CPoint ptDisable, bool bRedraw);
	void	SetStateAlpha(BYTE btNormal, BYTE btFocus, BYTE btPush, BYTE btDisable, bool bRedraw);


	// 커서 설정
	void	SetCursor(HCURSOR hCursor);
	

	// 현재 상태에 따라 설정된 이미지 레이더 갱신
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

