#pragma once

namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
class BN23_CLASS PointCoord final : public CheckPointer
{
public:
	explicit PointCoord();
	~PointCoord();


private :
	// 구간 범위가 그려질 픽셀 크기
	Gdiplus::SizeF		m_szPixel;
	Gdiplus::SizeF		m_szOnePixelRatio;	// 1pixel 거리에 해당하는 xy축 비율


	// 구간 범위
	Gdiplus::PointF		m_ptBegin;
	Gdiplus::PointF		m_ptEnd;
	Gdiplus::SizeF		m_szDistance;	// end - begin


	// 원본 값과 0~1사이로 매핑된 좌표(dest)
	std::vector<Gdiplus::PointF>	m_vptSrc;
	std::vector<Gdiplus::PointF>	m_vptDest;


	// 구간 범위안에 위치시킨 좌표
	std::vector<Gdiplus::PointF>	m_vptCoord;
	std::vector<bool>				m_vbOutRange;	// 구간 범위를 벗어났는지 여부


	// 최대, 최소 좌표 범위
	Gdiplus::RectF	m_rcfCoordBoundary;


public :
	// 초기화
	void	Initialize(int iWidth, int iHeight, float x0, float y0, float x1, float y1);


	// 데이터 설정
	void	Add(Gdiplus::REAL x, Gdiplus::REAL y);
	void	Clear(void);
	


public :
	///////////////////////////////////////////////
	// 됴구
	///////////////////////////////////////////////

	// x,y 값에 해당하는 위치비 반환
	Gdiplus::PointF	MakeRatio(float xValue, float yValue) const;	


	// x,y 위치비에 해당하는 값 반환
	Gdiplus::PointF MakeValue(float xRatio, float yRatio) const;	// ratio = 0~1


	// x,y 값에 해당하는 픽셀 좌표 반환
	Gdiplus::PointF MakeCoordF(Gdiplus::PointF ptRatio) const;
	Gdiplus::PointF MakeCoordF(float xValue, float yValue) const;
	Gdiplus::PointF MakeCoordF(float xValue, float yValue, _Ret_ bool &bOutRange) const;
	Gdiplus::PointF MakeCoordF(float xValue, float yValue, _Ret_ bool &bOutRange, _Ret_ Gdiplus::PointF &ptRatio) const;



public:
	///////////////////////////////////////////////
	// 추가된 데이터에서 탐색
	///////////////////////////////////////////////
	size_t	Size(void)
	{
		return m_vptSrc.size();
	};

	Gdiplus::PointF	GetSrc(size_t index) const;
	Gdiplus::PointF GetDest(size_t index) const;
	Gdiplus::PointF GetCoord(size_t index) const;
	Gdiplus::RectF	GetMinMaxCoordBoundary(Gdiplus::SizeF szShift) const;


	// 지정 인덱스 좌표 반환
	void	GetCoord(size_t index,
					 Gdiplus::SizeF szShift,
					 _Ret_ Gdiplus::Point &ptCoord,
					 _Ret_ bool &bOutRange) const;

	void	GetCoordF(size_t index,
					  Gdiplus::SizeF szShift,
					  _Ret_ Gdiplus::PointF &ptCoord,
					  _Ret_ bool &bOutRange) const;


	// iOutCount 갯수만큼 좌표 반환
	// iOutCount가 0이면 전체 반환
	size_t	GetCoordArray(Gdiplus::SizeF szShift,
						  _Ret_ std::vector<Gdiplus::Point> &vptCoord,
						  _Ret_ std::vector<bool> &vbOutRange,
						  size_t iOutCount = 0) const;


	size_t	GetCoordArrayF(Gdiplus::SizeF szShift,
						   _Ret_ std::vector<Gdiplus::PointF> &vptCoord,
						   _Ret_ std::vector<bool> &vbOutRange,
						   size_t iOutCount = 0) const;
	



	// x,y 비율 값에 가장 가까이 있는 범위안의 값 또는 추가된 데이터 인덱스 반환
	// 이분법으로 탐색하므로 선형 타입에만 사용 할 것
	int		GetNearIndexFromRatio(bool bFindX, float fRatio) const;


	// 전체 순환하면서 가장 가까운 인덱스 반환
	int		GetNearIndexFromRatio(float xRatio, float yRatio) const;
	

	// xy 범위가 같은지 체크
	bool	IsEqualRange(void);
};
//////////////////////////////////////////////////////////////////////////////////////////
};

