#pragma once
struct BN25_TYPE BNS_ImageInfo
{
public:
	BNS_ImageInfo();
	~BNS_ImageInfo();


public :
	// 리소스
	Gdiplus::Image*	ptr;
	CSize			size;
	CPoint			pPos[4];

	// 출력 위치
	CPoint			draw;
	

public :
	void SetSinglePosition(CPoint pt);
	void Draw(Gdiplus::Graphics *pGraphics, UINT iState, int iOffset);
};

