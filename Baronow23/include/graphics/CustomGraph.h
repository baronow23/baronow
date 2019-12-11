#pragma once


namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
class BN23_CLASS CustomGraph : public CheckPointer
{
public:
	explicit CustomGraph(size_t iTypeCount);
	virtual ~CustomGraph();


public :
	enum CustomGraphLabel
	{
		CGL_NOT_USED,		// ǥ�����
		CGL_ALIGN_DEFAULT,	// �ִ��ݼ��� ǥ��
		CGL_ALIGN_CENTER,	// �ִ��ݼ� ���̿� ǥ��
	};

	enum CustomGraphResource
	{
		CGR_BACKGROUND,	// m_bmBackground
		CGR_SOURCE,		// m_pbmSource
		CGR_OVERLAY,	// m_pbmOverlay
		CGR_ALL,
	};



protected :
	const size_t m_iTypeCount;

private:
	std::vector< std::shared_ptr<PointCoord> > m_vpPointCoord;

	// �׸��� ���ҽ�
	CDC		m_dcBackground;
	CBitmap	m_bmBackground;
	Gdiplus::Bitmap	*m_pbmSource;
	Gdiplus::Bitmap	*m_pbmOverlay;


protected :
	// ��� ���� (Initialize���� �ʱ�ȭ)
	CSize	m_szBK;
	CRect	m_rcBoundary;
	Gdiplus::RectF	m_rcfBoundary;
	Gdiplus::SizeF	m_szShift;
	Gdiplus::SizeF	m_szMainGridCell;
	CSize			m_szMainGridCount;

	bool	m_bUsingRemark;


public :
	// �⺻ ���� (�ʱ�ȭ ���� ����)
	COLORREF	m_clrBackground;
	COLORREF	m_clrBoundary;
	COLORREF	m_pclrGridColor[3];		// [0] ������, [1] ���α׸���, [2] ����׸���
	COLORREF	m_clrLabelX;
	COLORREF	m_clrLabelY;


private :
	void DrawDefaultGridline(Gdiplus::Graphics &g, Gdiplus::SizeF szDistance, COLORREF color);
	void DrawSquareGridline(Gdiplus::Graphics &g, Gdiplus::SizeF szDistance, COLORREF color);


	//void DrawDefaultGridline(CDC* pMemDC, Gdiplus::SizeF szDistance);
	//void DrawSquareGridline(CDC* pMemDC, Gdiplus::SizeF szDistance);
	void DrawImage(Gdiplus::Bitmap *pbm, size_t iRange, DWORD_PTR dwUserFlags,
				   std::function<void(Gdiplus::Graphics&, CDC&, const size_t, DWORD_PTR)>);


private :
	// ����� Ŀ���� ó��
	virtual void OnDrawRemark(	Gdiplus::Graphics &g, CDC &dc) = 0;
	virtual void OnDrawReset(	Gdiplus::Graphics &g, CDC &dc, const size_t iUsingCount, DWORD_PTR dwUserFlags) = 0;
	virtual void OnDrawUpdate(	Gdiplus::Graphics &g, CDC &dc, const size_t idx, DWORD_PTR dwUserFlags) = 0;
	virtual void OnDrawOverlay(	Gdiplus::Graphics &g, CDC &dc, const size_t iUsingCount, DWORD_PTR dwUserFlags) = 0;
	virtual void OnDrawSelect(	Gdiplus::Graphics &g, CDC &dc, int x, int y, const size_t idx, DWORD_PTR dwUserFlags) = 0;


protected:
	virtual void OnDrawLabelX(size_t index, CDC &dc, float fx, float fy, float fValue);
	virtual void OnDrawLabelY(size_t index, CDC &dc, float fx, float fy, float fValue);



protected :
	// ����� �׸��� Ŀ���� ó����
	// GetPointCoord(i)->GetCoord() ���
	const std::shared_ptr<PointCoord> GetPointCoord(size_t idxType);


	// �׷��� �ʱ�ȭ
	// ���, �׸��尡 ���Ե� ��׶��� �̹��� ����
	// iWidth, iHeight	: ��ü �׸��� ����
	// rcBlank			: ��ü �׸��� �������� �׷��� ��� ���� ��� �� �����¿� ����
	// szMinValue		: �ּ�(����) �� (left-bottom)
	// szMaxValue		: �ִ� �� (right-top)
	// szMainGridCount	: �� ���ݼ� ���� (0,1,2,3,4,5 ǥ���� 5)
	// szSubGridCount	: �� ���ݼ��� ������ ���� ���� (0~1�� ǥ�� ����)
	// xLabel, yLabel	: xy �� ��� ����
	// bCenterLabel		: �� ���ݼ� �߽ɿ� �� ǥ��
	// bUsingRemark		: ��ܿ� ���� ǥ��
	void Initialize(int iWidth, int iHeight,
					CRect rcBlank,			// CRect(60, 20, 30, 40)
					CPoint ptMinValue,
					CPoint ptMaxValue,
					CSize szMainGridCount,
					CSize szSubGridCount,
					CustomGraphLabel xLabel,
					CustomGraphLabel yLabel,
					CFont* pLabelFont,
					CFont* pRemarkFont,
					bool bUsingRemark,
					bool bDataClear = true);

	
public :
	// ������ �߰�, �ʱ�ȭ
	void Add(size_t idxType, int x, int y);
	void Add(size_t idxType, float fx, float fy);
	void Clear(size_t idxType);
	void Clear(void);
	


	// ĳ�� �̹����� �����ϰ� iUsingCount ��ŭ �ٽ� �׸� (0 �̸� ��ü)
	void ResetImage(const size_t iUsingCount, bool bUsingOverlay, DWORD_PTR dwUserFlags = 0);


	// ���� �̹����� �������� �߰��� �����͸� ���� �׸�
	void UpdateImage(bool bUsingOverlay, DWORD_PTR dwUserFlags = 0);


	// cache �̹��� ���
	void DrawCache(CDC *pMemDC, CDC *pResDC, int x, int y, CustomGraphResource type, int idxSelect = -1, DWORD_PTR dwUserFlags = 0);
	void DrawCache(Gdiplus::Graphics &g, int x, int y, CustomGraphResource type, int idxSelect = -1, DWORD_PTR dwUserFlags = 0);

	
	// cache �̹��� ����
	// return : filesize
	double SaveCache(CString strPath, CustomGraphResource type, LPCWSTR lpszFmt = L"image/png");

	
	// m_szBK �������� �ȼ� ��ġ�� m_Boundary ���� �ȼ� ��ġ�� �����ϰų� ��ġ�� ��ȯ
	Gdiplus::Point	PixelToBoundaryPoint(int xPixel, int yPixel) const;
	Gdiplus::PointF	PixelToBoundaryRatio(int xPixel, int yPixel) const;



	// ���� LeftTop(0,0) �������� xPixel, yPixel�� ��ġ�� �ش��ϴ� xy �� �Ǵ� �Էµ� �����Ϳ� ���� ����� �ε��� ��ȯ
	CPoint	PixelToGraphValue(size_t idxType, int xPixel, int yPixel) const;
	int		PixelToGraphIndexX(size_t idxType, int xPixel) const;
	int		PixelToGraphIndexY(size_t idxType, int yPixel) const;
	int		PixelToGraphIndexXY(size_t idxType, int xPixel, int yPixel) const;
	CPoint	PixelToMainGridIndexXY(int xPixel, int yPixel) const;


	CSize	GetSize(void){ return m_szBK; };
	CRect	GetBoundary(void){ return m_rcBoundary; };
};
//////////////////////////////////////////////////////////////////////////////////////////
};

