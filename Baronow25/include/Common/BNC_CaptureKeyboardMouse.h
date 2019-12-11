#pragma once

class BNC_BaseClient;
class BN25_TYPE BNC_CaptureKeyboardMouse
{
public:
	BNC_CaptureKeyboardMouse();
	~BNC_CaptureKeyboardMouse();

public :
	// list,tree �信�� �� ���۽� zDelta ���⿡ ���� ������ �� (ctrl, shift�� �� Ű������ �������� ��)
	static int s_iWheelValue;			// default 30
	static int s_iWheelValueCtrl;		// default 5
	static int s_iWheelValueShift;		// default 1


public :
	bool m_bSupportAutoMouseTracking;

private :
	// ��Ʈ���� ���콺 ĸ�ĵǾ��� �� ���� �θ� ��Ʈ�� ���
	// ������10 ���� ȯ�濡�� ���콺 �� Ʈ��ŷ �ޱ� ����)
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

