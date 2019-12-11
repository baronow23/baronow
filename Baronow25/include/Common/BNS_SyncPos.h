#pragma once


// 윈도우 위치 동기화 

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

