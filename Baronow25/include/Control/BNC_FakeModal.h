#pragma once


class BN25_TYPE BNC_FakeModal : public BNC_BaseDialog
{
	friend class BNC_BaseDialog;

public :
	BNC_FakeModal(BNC_BaseDialog* pTarget, BNC_FakeModal **ppRefCurrent = nullptr, bool bAlwaysOK = false);
	virtual ~BNC_FakeModal();

private:
	static set<HWND>	s_sAliveModal;
	static				UINT s_uiCreateCount;
	static				UINT s_uiDestroyCount;

public:
	static set<HWND>	GetAliveModal(void);
	static UINT			GetCreateCount(void);
	static UINT			GetAliveCount(void);


public :
	// callback : 현재는 IDOK, IDCANCEL에서만 호출 ( 종료후 추가 작업 필요 없는 단순 처리시에는 사용 않함)
	// callfinal : 동적객체를 람다 캡쳐인자로 사용하고 메모리 해제가 필요한 경우 지정하여 처리할 것
	// iCallbackFilter : 지정할 경우 callback의 INT_PTR 값이 일치할 경우만 callback 호출 
	static bool Run(_In_ shared_ptr<BNC_FakeModal> pModal,
					_In_opt_ std::function<void(INT_PTR, BNC_FakeModal&)> callback = nullptr,
					_In_opt_ std::function<void(void)> callfinal = nullptr,
					_In_opt_ INT_PTR iCallbackFilter = 0,
					_In_opt_ UINT nDialogID = 0);

		

protected :
	BNC_BaseDialog	*m_pInitTarget;

private :
	BNC_BaseDialog	*m_pTarget;
	HWND			m_hTarget;
	BNC_FakeModal	**m_ppRefCurrent;
	std::function<void(INT_PTR, BNC_FakeModal&)> m_callback;
	std::function<void(void)> m_callfinal;
	shared_ptr<BNC_FakeModal> m_instance;
	INT_PTR m_iCallbackFilter;
	INT_PTR m_iBreakResult;


public :
	// m_bIgnoreAltF4는 항상 ture로 설정됨
	// enter, esc, alt+f4 종료 무시 여부 설정
	bool m_bIgnoreExitKey;


	// 사용자 선택에 상관없이 항상 종료시 다음단계로 진행이 필요할 때 true로 설정
	// ex) 확인 버튼만 있는 메시지 박스
	// true : alt+f4, esc누름)시 IDCANCEL -> IDOK로 콜백처리
	bool m_bAlwaysOK;


	// space키 눌렀을 때 엔터와 같은 동작 하도록 처리
	bool m_bSpaceOk;
	

private :
	bool Create(UINT nDialogID);
	BNC_BaseDialog* GetLastActive(void);


public :
	void Break(INT_PTR iResult);
	void EndDialog(int nResult) = delete;
	BNC_BaseDialog* GetInitTarget(void) const;
	bool IsAlawaysOK(void) const;


protected :
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();


private :
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg void OnClose();


	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();
};

