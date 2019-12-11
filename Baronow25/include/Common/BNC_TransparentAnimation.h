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
	baro::Performance		m_RequestTime;		// ��û �ð� 
	double					m_lfDelay;			// ���� �� �ð�
	bool					m_bShow;
	bool					m_bShowActivate;	
	//bool					m_bFirstProcess;	// run���� ù ��° OnProcess ���� üũ
	bool					m_bAsyncUpdate;

	
	// ���̾�� ���� ����
	LONG		m_oldExStyle;
	COLORREF	m_oldColorKey;
	BYTE		m_oldAlpha;
	DWORD		m_oldFlags;


	// ������Ʈ ��
	BYTE		m_btBegin;
	BYTE		m_btEnd;
	BYTE		m_btLastUpdate;


	// �ִ� �ּ� ���� ���� (����� ����)
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

	
	// -1 : �����
	// 0 : hide �ִϸ��̼� ������
	// 1 : show �ִϸ��̼� ������
	int		GetState(void);
	void	WaitProcess(DWORD dwMilliseconds = INFINITE);


	void	OnCreate(void);
	void	OnDestroy(void);
	


private :
	static UINT OnProcess(LPVOID pParam);
};
