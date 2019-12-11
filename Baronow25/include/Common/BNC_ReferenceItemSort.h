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

	int		iType;				// -1(������), 0(sequence), 1(string);
	int		iOption;

	int		iRefStringIndex;
	bool	bAsecending;
	int		iEqualRefIndex;
	bool	bEqualAsecnding;
};


//////////////////////////////////////////////////////////////////////////
// BNS_ReferenceItem ������ ����
//////////////////////////////////////////////////////////////////////////
/*
������ �Լ��� �Լ� �����Ͱ� �ƴ� �Լ� ��ü�� ���
�Լ� ��ü�� ����� ������ �Լ� ��ü�� inlineȭ �ǹǷ�
�Լ� �����Ϳ� ���ϸ� �Լ� ������ ������ �Լ� ȣ�⿡ ���� �۾��� �ʿ� ������
�Լ� ��ü�� ����ϸ� ��ü�� Ư�� �����͸� ������ �� �־ �����ڰ� ������ ��
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

	// uiRefStringIndex �� ����� ���� ���
	// iEqualRefIndex�� �߰� ���� ( -1�̸� ����)
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

	// uiRefStringIndex �� ����� ���� ���
	// iEqualRefIndex�� �߰� ���� ( -1�̸� ����)
	int		m_iEqualRefIndex;
	bool	m_bEqualAscending;


private :
	bool sort(const BNC_ReferenceItem* pItem1, const BNC_ReferenceItem* pItem2);


public :
	bool operator()(const BNC_ReferenceItem* pItem1, const BNC_ReferenceItem* pItem2);
};


