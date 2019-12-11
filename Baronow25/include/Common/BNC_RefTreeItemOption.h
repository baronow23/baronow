#pragma once


// BNC_ReferenceItem의 m_pOption으로 사용
class BN25_TYPE BNC_RefTreeItemOption
{
	friend class BNC_RefTreeControl;


public:
	BNC_RefTreeItemOption(BNC_ReferenceItem* pRefItem);
	virtual ~BNC_RefTreeItemOption();
	

private :
	BNC_ReferenceItem*	m_pRefItem;

	// 초기 설정 값
	bool 	m_bFolder;		// 폴더, 파일구분
	int		m_iDepth;		// 트리 깊이 (아이템 추가시 1씩 증가)


	// 부모 아이템 기준 정보
	int		m_iPIndex;		// 부모 리스트 내에서 정렬된 순서 (pParent->vpChile의 index) : 정렬문제로 아이템이 그려질 때 갱신됨


	bool	m_bExtended;	// 자식 목록 펼침 여부
	int		m_iExHeight;	// 펼쳐진 자식목록의 높이 (펼쳐지지 않은 항목 제외),
	int		m_iOptWidth;	// 그리기 최대 넓이(option)
	// 이 항목은 자식들이 상태가 변경되었을 때 부모 데이터를 접근하여 수정함

	
	// 부모, 자식 참조 포인터
	BNC_ReferenceItem*						m_pParent;			// 상위 부모
	std::vector<BNC_ReferenceItem*>			m_vpChild;			// 하위 자식 (직속 하위만 포함하며 정렬 되는 대상)
	std::map<CString, BNC_ReferenceItem*>	m_mpChildFolder;	// 모든 하위 자식 (폴더만)
	std::map<CString, BNC_ReferenceItem*>	m_mpChildFile;		// 모든 하위 자식 (파일만)


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

