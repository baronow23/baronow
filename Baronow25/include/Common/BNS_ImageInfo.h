#pragma once
struct BN25_TYPE BNS_ImageInfo
{
public:
	BNS_ImageInfo();
	~BNS_ImageInfo();


public :
	// ���ҽ�
	Gdiplus::Image*	ptr;
	CSize			size;
	CPoint			pPos[4];

	// ��� ��ġ
	CPoint			draw;
	

public :
	void SetSinglePosition(CPoint pt);
	void Draw(Gdiplus::Graphics *pGraphics, UINT iState, int iOffset);
};

