#pragma once


// ������ ��ġ ����ȭ 

struct BNS_SyncPos
{
public:
	BNS_SyncPos();
	~BNS_SyncPos();
	

public :
	DWORD		dwFixPoint;
	CPoint		ptOffset;
	DWORD		dwVarSize;
	CSize		szOffset;
	const CWnd*	pAfterInsert;
};

