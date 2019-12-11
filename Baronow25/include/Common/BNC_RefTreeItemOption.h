#pragma once


// BNC_ReferenceItem�� m_pOption���� ���
class BN25_TYPE BNC_RefTreeItemOption
{
	friend class BNC_RefTreeControl;


public:
	BNC_RefTreeItemOption(BNC_ReferenceItem* pRefItem);
	virtual ~BNC_RefTreeItemOption();
	

private :
	BNC_ReferenceItem*	m_pRefItem;

	// �ʱ� ���� ��
	bool 	m_bFolder;		// ����, ���ϱ���
	int		m_iDepth;		// Ʈ�� ���� (������ �߰��� 1�� ����)


	// �θ� ������ ���� ����
	int		m_iPIndex;		// �θ� ����Ʈ ������ ���ĵ� ���� (pParent->vpChile�� index) : ���Ĺ����� �������� �׷��� �� ���ŵ�


	bool	m_bExtended;	// �ڽ� ��� ��ħ ����
	int		m_iExHeight;	// ������ �ڽĸ���� ���� (�������� ���� �׸� ����),
	int		m_iOptWidth;	// �׸��� �ִ� ����(option)
	// �� �׸��� �ڽĵ��� ���°� ����Ǿ��� �� �θ� �����͸� �����Ͽ� ������

	
	// �θ�, �ڽ� ���� ������
	BNC_ReferenceItem*						m_pParent;			// ���� �θ�
	std::vector<BNC_ReferenceItem*>			m_vpChild;			// ���� �ڽ� (���� ������ �����ϸ� ���� �Ǵ� ���)
	std::map<CString, BNC_ReferenceItem*>	m_mpChildFolder;	// ��� ���� �ڽ� (������)
	std::map<CString, BNC_ReferenceItem*>	m_mpChildFile;		// ��� ���� �ڽ� (���ϸ�)


public :
	bool	IsFolder(void) const;
	bool	IsExtended(void) const;
	int		GetDepth(void) const;
	int		GetExHeight(void) const;


	const BNC_ReferenceItem*	GetItem(void);
	const BNC_ReferenceItem*	GetParentItem(void);


	UINT	GetChildCount(void) const;
	UINT	GetChildFolderCount(void) const;
	UINT	GetChildFileCount(void) const;


	std::map<CString, BNC_ReferenceItem*>::const_iterator	GetChildFolderBegin(void) const;
	std::map<CString, BNC_ReferenceItem*>::const_iterator	GetChildFolderEnd(void) const;
	std::map<CString, BNC_ReferenceItem*>::const_iterator	GetChildFileBegin(void) const;
	std::map<CString, BNC_ReferenceItem*>::const_iterator	GetChildFileEnd(void) const;

};

