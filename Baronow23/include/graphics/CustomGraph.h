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
		CGL_NOT_USED,		// 표기않함
		CGL_ALIGN_DEFAULT,	// 주눈금선에 표기
		CGL_ALIGN_CENTER,	// 주눈금선 사이에 표기
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

	// 그리기 리소스
	CDC		m_dcBackground;
	CBitmap	m_bmBackground;
	Gdiplus::Bitmap	*m_pbmSource;
	Gdiplus::Bitmap	*m_pbmOverlay;


protected :
	// 출력 정보 (Initialize에서 초기화)
	CSize	m_szBK;
	CRect	m_rcBoundary;
	Gdiplus::RectF	m_rcfBoundary;
	Gdiplus::SizeF	m_szShift;
	Gdiplus::SizeF	m_szMainGridCell;
	CSize			m_szMainGridCount;

	bool	m_bUsingRemark;


public :
	// 기본 색상 (초기화 전에 수정)
	COLORREF	m_clrBackground;
	COLORREF	m_clrBoundary;
	COLORREF	m_pclrGridColor[3];		// [0] 원점축, [1] 메인그리드, [2] 서브그리드
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
	// 사용자 커스텀 처리
	virtual void OnDrawRemark(	Gdiplus::Graphics &g, CDC &dc) = 0;
	virtual void OnDrawReset(	Gdiplus::Graphics &g, CDC &dc, const size_t iUsingCount, DWORD_PTR dwUserFlags) = 0;
	virtual void OnDrawUpdate(	Gdiplus::Graphics &g, CDC &dc, const size_t idx, DWORD_PTR dwUserFlags) = 0;
	virtual void OnDrawOverlay(	Gdiplus::Graphics &g, CDC &dc, const size_t iUsingCount, DWORD_PTR dwUserFlags) = 0;
	virtual void OnDrawSelect(	Gdiplus::Graphics &g, CDC &dc, int x, int y, const size_t idx, DWORD_PTR dwUserFlags) = 0;


protected:
	virtual void OnDrawLabelX(size_t index, CDC &dc, float fx, float fy, float fValue);
	virtual void OnDrawLabelY(size_t index, CDC &dc, float fx, float fy, float fValue);



protected :
	// 사용자 그리기 커스텀 처리시
	// GetPointCoord(i)->GetCoord() 사용
	const std::shared_ptr<PointCoord> GetPointCoord(size_t idxType);


	// 그래프 초기화
	// 배경, 그리드가 포함된 백그라운드 이미지 설정
	// iWidth, iHeight	: 전체 그리기 영역
	// rcBlank			: 전체 그리기 영역에서 그래프 출력 경계로 사용 할 상하좌우 여백
	// szMinValue		: 최소(원점) 값 (left-bottom)
	// szMaxValue		: 최대 값 (right-top)
	// szMainGridCount	: 주 눈금선 갯수 (0,1,2,3,4,5 표기라면 5)
	// szSubGridCount	: 주 눈금선을 나눠줄 구간 갯수 (0~1은 표기 않함)
	// xLabel, yLabel	: xy 라벨 출력 설정
	// bCenterLabel		: 주 눈금선 중심에 라벨 표시
	// bUsingRemark		: 상단에 범례 표기
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
	// 데이터 추가, 초기화
	void Add(size_t idxType, int x, int y);
	void Add(size_t idxType, float fx, float fy);
	void Clear(size_t idxType);
	void Clear(void);
	


	// 캐쉬 이미지를 삭제하고 iUsingCount 만큼 다시 그림 (0 이면 전체)
	void ResetImage(const size_t iUsingCount, bool bUsingOverlay, DWORD_PTR dwUserFlags = 0);


	// 이전 이미지에 마지막에 추가된 데이터만 덮어 그림
	void UpdateImage(bool bUsingOverlay, DWORD_PTR dwUserFlags = 0);


	// cache 이미지 출력
	void DrawCache(CDC *pMemDC, CDC *pResDC, int x, int y, CustomGraphResource type, int idxSelect = -1, DWORD_PTR dwUserFlags = 0);
	void DrawCache(Gdiplus::Graphics &g, int x, int y, CustomGraphResource type, int idxSelect = -1, DWORD_PTR dwUserFlags = 0);

	
	// cache 이미지 저장
	// return : filesize
	double SaveCache(CString strPath, CustomGraphResource type, LPCWSTR lpszFmt = L"image/png");

	
	// m_szBK 범위안의 픽셀 위치를 m_Boundary 내의 픽셀 위치로 보정하거나 위치비 반환
	Gdiplus::Point	PixelToBoundaryPoint(int xPixel, int yPixel) const;
	Gdiplus::PointF	PixelToBoundaryRatio(int xPixel, int yPixel) const;



	// 원점 LeftTop(0,0) 기준으로 xPixel, yPixel의 위치에 해당하는 xy 값 또는 입력된 데이터와 가장 가까운 인덱스 반환
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

