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
	// callback : ����� IDOK, IDCANCEL������ ȣ�� ( ������ �߰� �۾� �ʿ� ���� �ܼ� ó���ÿ��� ��� ����)
	// callfinal : ������ü�� ���� ĸ�����ڷ� ����ϰ� �޸� ������ �ʿ��� ��� �����Ͽ� ó���� ��
	// iCallbackFilter : ������ ��� callback�� INT_PTR ���� ��ġ�� ��츸 callback ȣ�� 
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
	// m_bIgnoreAltF4�� �׻� ture�� ������
	// enter, esc, alt+f4 ���� ���� ���� ����
	bool m_bIgnoreExitKey;


	// ����� ���ÿ� ������� �׻� ����� �����ܰ�� ������ �ʿ��� �� true�� ����
	// ex) Ȯ�� ��ư�� �ִ� �޽��� �ڽ�
	// true : alt+f4, esc����)�� IDCANCEL -> IDOK�� �ݹ�ó��
	bool m_bAlwaysOK;


	// spaceŰ ������ �� ���Ϳ� ���� ���� �ϵ��� ó��
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

