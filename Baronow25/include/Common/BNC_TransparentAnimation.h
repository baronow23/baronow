#pragma once

class BNC_BaseDialog;
enum class TransparentStep : BYTE
{
	BeginShow,
	ProgressShow,
	EndShow,

	BeginHide,
	ProgressHide,
	EndHide,
};


class BN25_TYPE BNC_TransparentAnimation : public baro::CriticalSection
{
public :
	BNC_TransparentAnimation(BNC_BaseDialog *pTarget);
	~BNC_TransparentAnimation(void);

private :
	CWinThread*	m_pThread;
	BNC_BaseDialog*			m_pTarget;
	HWND					m_hTarget;
	
	const CWnd*				m_pAfterInsert;
	baro::Performance		m_RequestTime;		// 요청 시간 
	double					m_lfDelay;			// 수행 할 시간
	bool					m_bShow;
	bool					m_bShowActivate;	
	//bool					m_bFirstProcess;	// run이후 첫 번째 OnProcess 도달 체크
	bool					m_bAsyncUpdate;

	
	// 레이어드 복구 관련
	LONG		m_oldExStyle;
	COLORREF	m_oldColorKey;
	BYTE		m_oldAlpha;
	DWORD		m_oldFlags;


	// 업데이트 값
	BYTE		m_btBegin;
	BYTE		m_btEnd;
	BYTE		m_btLastUpdate;


	// 최대 최소 투명값 설정 (사용자 지정)
	BYTE		m_btMin;
	BYTE		m_btMax;
	BYTE		m_btLength;

	bool		m_bDestroy;
	
private :
	bool	IsValid(void);
	bool	Run(void);
	bool	Update(void);
	void	End(void);
	bool	UpdateTransparent(TransparentStep step, BYTE btAlpha, float fRatio, _Out_opt_ BYTE *pbtUpdate = nullptr);


public :
	bool				SetRange(BYTE btMin = 0, BYTE btMax = 255);
	pair<BYTE, BYTE>	GetRange(void);
	bool	Show(double lfDelay = 100, const CWnd *pAfterInsert = NULL, bool bShowActivate = true);
	bool	Hide(double lfDelay = 100);
	void	Stop(void);

	
	// -1 : 대기중
	// 0 : hide 애니메이션 진행중
	// 1 : show 애니메이션 진행중
	int		GetState(void);
	void	WaitProcess(DWORD dwMilliseconds = INFINITE);


	void	OnCreate(void);
	void	OnDestroy(void);
	


private :
	static UINT OnProcess(LPVOID pParam);
};
