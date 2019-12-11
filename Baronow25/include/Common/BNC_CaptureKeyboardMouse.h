#pragma once

class BNC_BaseClient;
class BN25_TYPE BNC_CaptureKeyboardMouse
{
public:
	BNC_CaptureKeyboardMouse();
	~BNC_CaptureKeyboardMouse();

public :
	// list,tree 뷰에서 휠 동작시 zDelta 방향에 따라 적용할 값 (ctrl, shift는 각 키누르고 동작했을 때)
	static int s_iWheelValue;			// default 30
	static int s_iWheelValueCtrl;		// default 5
	static int s_iWheelValueShift;		// default 1


public :
	bool m_bSupportAutoMouseTracking;

private :
	// 컨트롤이 마우스 캡쳐되었을 때 상위 부모 컨트롤 등록
	// 윈도우10 이전 환경에서 마우스 휠 트래킹 받기 위함)
	BNC_BaseClient*	m_pCaptureClient;
	baro::Performance m_chkDelay;

public :
	bool IsAvailable(void);
	void SetCaptureClient(BNC_BaseClient *pClient);
	
	bool SendKeyDown(WPARAM wParam, BNC_BaseClient* pNotify = NULL);
	bool SendMouseWheel(UINT nFlags, short zDelta, CPoint& pt, BNC_BaseClient* pNotify);


public :
	static short GetWheelValue(short zDelta);
	
};

