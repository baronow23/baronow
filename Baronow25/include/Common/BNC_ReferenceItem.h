#pragma once


class BN25_TYPE BNC_ReferenceItem : public baro::CheckPointer
{
	friend class BNC_BaseRefItemControl;
	friend class BNC_RefListControl;
	friend class BNC_RefTreeControl;
	friend class BNC_DummyListControl;
	

public:
	BNC_ReferenceItem(void);
	BNC_ReferenceItem(UINT uiItemHeight, UINT iSortCount, UINT iRectCount);
	BNC_ReferenceItem(const BNC_ReferenceItem &rhs);
	BNC_ReferenceItem& operator = (const BNC_ReferenceItem &rhs);
	virtual  ~BNC_ReferenceItem();


private:
	static UINT s_uiCreateCount;
	static UINT s_uiDestroyCount;
	

public:
	static UINT	GetCreateCount(void);
	static UINT	GetAliveCount(void);


private :
	// List, Tree ��Ʈ�ѿ��� ������ �� ������
	CString		m_strKey;	
	CString		m_strPKey;
	const void*	m_pRefData;			// ���� ������(����� ����)


private :
	UINT		m_uiSequence;
	int			m_iVisibleIndex;	// ȭ�鿡 �������� index (���� �θ𿡼� ����)
	bool		m_bEnable;


	UINT		m_uiSortCount;
	UINT		m_uiRectCount;
	std::vector<CString*>		m_vpStrSort;
	std::vector<BNC_SyncRect*>	m_vpSyncRect;
	

	// Top, Bottom�� ��Ʈ�ѿ��� ������Ʈ�ϸ� ��ũ�Ѹ��� ��Ʈ�� ��ǥ��
	UINT		m_uiItemHeight;		// ������ ����
	UINT		m_uiItemTop;		// top (��Ʈ�� ��ǥ)
	UINT		m_uiItemBottom;		// bottom (��Ʈ�� ��ǥ)



public :
	//////////////////////////////////////////////////////
	// ���� �ؽ�Ʈ ����
	//////////////////////////////////////////////////////
	bool		m_bUseVarText;		// ��뿩��
	int			m_iVarOffset;		// ���� �ؽ�Ʈ�� ��µ� �� �ִ� ���� ���� ( Ŭ���̾�Ʈ ����ũ�� - m_iVarOffset)
	CString		m_strVarText;		// ���� ���̿� ����� �ؽ�Ʈ 
	int			m_iVarTextSpacing;	// �ٹٲ� �ؽ�Ʈ ���� ����
	std::vector<CString*>	m_vpVarTextLine;	// �ٹٲ� ����� �ؽ�Ʈ(m_strVarText �и�)
	


public :
	BNE_MOUSEACTION		m_MouseAction;
	CPoint				m_ptMouse;				// ������ ���� ��ǥ
	int					m_iMouseRectIdx;		// ptMouse�� �ش��ϴ� Rect �ε��� (-1�̸� �ش����)

	BNE_MOUSEACTION		m_MouseActionOld;
	CPoint				m_ptMouseOld;		
	int					m_iMouseRectIdxOld;


	// BNC_ReferenceItem�� ����� ���� Ȯ�� ������
	void*				m_pOption;
	void*				m_pTemplate;


	// ����� ������
	DWORD				m_dwFlags;


private :
	// �Ҹ��ڿ� operator(=)�ܿ��� ȣ�� ����
	void	Clear(void);
	

//����..
public :
	bool	SetEnable(bool bEnable);
	bool	SetSyncRectEnable(UINT index, bool bEnable);


public :
	bool			IsEnable(void) const;
	const void*		GetReferenceData(void) const;
	void*			GetOption(void) const;
	void*			GetTemplate(void) const;

	UINT			GetSequenceNumber(void) const;
	int				GetVisibleIndex(void) const;
	UINT			GetSortStringCount(void) const;
	UINT			GetSyncRectCount(void) const;
	const CString*	GetItemKey(void) const;
	const CString*	GetItemPKey(void) const;


	// �����ڿ��� ������ ���ڱ����� ���� ����
	bool					SetSortString(UINT index, CString str);
	bool					SetSyncRect(UINT index, BNC_SyncRect& rect);
	bool					ModifySyncRect(UINT index, CRect &rect);
	bool					ModifySyncRect(UINT index, CRect &rect, CPoint &ptOffset);

	const CString*			GetSortString(UINT index) const;
	const CRect*			GetSyncRect(UINT index) const;
	const BNC_SyncRect*		GetSyncRectPtr(UINT index) const;
	bool					SetSyncRectCursor(UINT index) const;

	void	SetItemPos(UINT uiTop);
	UINT	GetItemHeight(void) const;
	UINT	GetItemTop(void) const;
	UINT	GetItemBottom(void) const;

	
	// ptItem	: ������ ���� ��ǥ
	// return	: ���� action�� RectIdx�� �ٸ��� true
	bool	UpdateMouseAction(BNE_MOUSEACTION action, const CPoint &ptItem);
	


	// Sync Rect ������Ʈ
	void	UpdateSyncRect(int iItemWidth) const;


	// Var Text ������Ʈ
	void	ClearVarTextLine(void);
	void	PushVarText(LPCTSTR lpszNextLine);


	BNE_MOUSEACTION	GetMouseAction(void) const;
	BNE_MOUSEACTION	GetMouseActionOld(void) const;
	int				GetMouseRectIndex(void) const;
	int				GetMouseRectIndexOld(void) const;
};
