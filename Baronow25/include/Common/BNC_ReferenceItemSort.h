#pragma once


struct BNS_ReferenceItemSortOption
{
	BNS_ReferenceItemSortOption(void)
	{
		Clear();
	};

	void Clear(void)
	{
		iType			= -1;
		iOption			= 0;
		iRefStringIndex	= -1;
		bAsecending		= true;
		iEqualRefIndex	= -1;
		bEqualAsecnding	= true;
	};

	int		iType;				// -1(정렬전), 0(sequence), 1(string);
	int		iOption;

	int		iRefStringIndex;
	bool	bAsecending;
	int		iEqualRefIndex;
	bool	bEqualAsecnding;
};


//////////////////////////////////////////////////////////////////////////
// BNS_ReferenceItem 아이템 정렬
//////////////////////////////////////////////////////////////////////////
/*
조건자 함수를 함수 포인터가 아닌 함수 객체를 사용
함수 객체를 사용한 이유는 함수 객체는 inline화 되므로
함수 포인터와 비교하면 함수 포인터 참조와 함수 호출에 따른 작업이 필요 없으며
함수 객체를 사용하면 객체에 특정 데이터를 저장할 수 있어서 조건자가 유연해 짐
*/

class BN25_TYPE BNC_ReferenceItemSort
{
public:
	// Reference String Sort
	BNC_ReferenceItemSort(BNS_ReferenceItemSortOption &option);
	BNC_ReferenceItemSort(UINT uiRefStringIndex, bool bAsecending, int iEqualRefIndex = -1, bool bEqualAsecnding = true);
	~BNC_ReferenceItemSort();


private :
	bool	m_bAscending;
	UINT	m_uiRefStringIndex;

	// uiRefStringIndex 비교 결과가 같을 경우
	// iEqualRefIndex로 추가 비교함 ( -1이면 생략)
	int		m_iEqualRefIndex;	
	bool	m_bEqualAscending;


private :
	bool sort(const BNC_ReferenceItem* pItem1, const BNC_ReferenceItem* pItem2);
	bool sort(const BNC_ReferenceItemEx* pItem1, const BNC_ReferenceItemEx* pItem2);


public :
	bool operator()(const BNC_ReferenceItem* pItem1, const BNC_ReferenceItem* pItem2);
	bool operator()(const BNC_ReferenceItemEx* pItem1, const BNC_ReferenceItemEx* pItem2);
};



class BN25_TYPE BNC_ReferenceItemSeqSort
{
public:
	// Sequence Sort
	BNC_ReferenceItemSeqSort(bool bAsecending);
	~BNC_ReferenceItemSeqSort();
	

private:
	bool	m_bAscending;


public :
	bool operator()(const BNC_ReferenceItem* pItem1, const BNC_ReferenceItem* pItem2);
	bool operator()(const BNC_ReferenceItemEx* pItem1, const BNC_ReferenceItemEx* pItem2);

};



class BN25_TYPE BNC_ReferenceItemTreeSort
{
public :
	// BNC_RefTreeItemOption sort
	BNC_ReferenceItemTreeSort(const BNC_ReferenceItemTreeSort &rhs);
	BNC_ReferenceItemTreeSort(BNS_ReferenceItemSortOption &option);
	BNC_ReferenceItemTreeSort(UINT uiRefStringIndex, bool bAsecending, int iEqualRefIndex = -1, bool bEqualAsecnding = true);
	~BNC_ReferenceItemTreeSort();


private:
	bool	m_bAscending;
	UINT	m_uiRefStringIndex;

	// uiRefStringIndex 비교 결과가 같을 경우
	// iEqualRefIndex로 추가 비교함 ( -1이면 생략)
	int		m_iEqualRefIndex;
	bool	m_bEqualAscending;


private :
	bool sort(const BNC_ReferenceItem* pItem1, const BNC_ReferenceItem* pItem2);


public :
	bool operator()(const BNC_ReferenceItem* pItem1, const BNC_ReferenceItem* pItem2);
};


