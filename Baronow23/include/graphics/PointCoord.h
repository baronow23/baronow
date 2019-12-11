#pragma once

namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
class BN23_CLASS PointCoord final : public CheckPointer
{
public:
	explicit PointCoord();
	~PointCoord();


private :
	// ���� ������ �׷��� �ȼ� ũ��
	Gdiplus::SizeF		m_szPixel;
	Gdiplus::SizeF		m_szOnePixelRatio;	// 1pixel �Ÿ��� �ش��ϴ� xy�� ����


	// ���� ����
	Gdiplus::PointF		m_ptBegin;
	Gdiplus::PointF		m_ptEnd;
	Gdiplus::SizeF		m_szDistance;	// end - begin


	// ���� ���� 0~1���̷� ���ε� ��ǥ(dest)
	std::vector<Gdiplus::PointF>	m_vptSrc;
	std::vector<Gdiplus::PointF>	m_vptDest;


	// ���� �����ȿ� ��ġ��Ų ��ǥ
	std::vector<Gdiplus::PointF>	m_vptCoord;
	std::vector<bool>				m_vbOutRange;	// ���� ������ ������� ����


	// �ִ�, �ּ� ��ǥ ����
	Gdiplus::RectF	m_rcfCoordBoundary;


public :
	// �ʱ�ȭ
	void	Initialize(int iWidth, int iHeight, float x0, float y0, float x1, float y1);


	// ������ ����
	void	Add(Gdiplus::REAL x, Gdiplus::REAL y);
	void	Clear(void);
	


public :
	///////////////////////////////////////////////
	// �ͱ�
	///////////////////////////////////////////////

	// x,y ���� �ش��ϴ� ��ġ�� ��ȯ
	Gdiplus::PointF	MakeRatio(float xValue, float yValue) const;	


	// x,y ��ġ�� �ش��ϴ� �� ��ȯ
	Gdiplus::PointF MakeValue(float xRatio, float yRatio) const;	// ratio = 0~1


	// x,y ���� �ش��ϴ� �ȼ� ��ǥ ��ȯ
	Gdiplus::PointF MakeCoordF(Gdiplus::PointF ptRatio) const;
	Gdiplus::PointF MakeCoordF(float xValue, float yValue) const;
	Gdiplus::PointF MakeCoordF(float xValue, float yValue, _Ret_ bool &bOutRange) const;
	Gdiplus::PointF MakeCoordF(float xValue, float yValue, _Ret_ bool &bOutRange, _Ret_ Gdiplus::PointF &ptRatio) const;



public:
	///////////////////////////////////////////////
	// �߰��� �����Ϳ��� Ž��
	///////////////////////////////////////////////
	size_t	Size(void)
	{
		return m_vptSrc.size();
	};

	Gdiplus::PointF	GetSrc(size_t index) const;
	Gdiplus::PointF GetDest(size_t index) const;
	Gdiplus::PointF GetCoord(size_t index) const;
	Gdiplus::RectF	GetMinMaxCoordBoundary(Gdiplus::SizeF szShift) const;


	// ���� �ε��� ��ǥ ��ȯ
	void	GetCoord(size_t index,
					 Gdiplus::SizeF szShift,
					 _Ret_ Gdiplus::Point &ptCoord,
					 _Ret_ bool &bOutRange) const;

	void	GetCoordF(size_t index,
					  Gdiplus::SizeF szShift,
					  _Ret_ Gdiplus::PointF &ptCoord,
					  _Ret_ bool &bOutRange) const;


	// iOutCount ������ŭ ��ǥ ��ȯ
	// iOutCount�� 0�̸� ��ü ��ȯ
	size_t	GetCoordArray(Gdiplus::SizeF szShift,
						  _Ret_ std::vector<Gdiplus::Point> &vptCoord,
						  _Ret_ std::vector<bool> &vbOutRange,
						  size_t iOutCount = 0) const;


	size_t	GetCoordArrayF(Gdiplus::SizeF szShift,
						   _Ret_ std::vector<Gdiplus::PointF> &vptCoord,
						   _Ret_ std::vector<bool> &vbOutRange,
						   size_t iOutCount = 0) const;
	



	// x,y ���� ���� ���� ������ �ִ� �������� �� �Ǵ� �߰��� ������ �ε��� ��ȯ
	// �̺й����� Ž���ϹǷ� ���� Ÿ�Կ��� ��� �� ��
	int		GetNearIndexFromRatio(bool bFindX, float fRatio) const;


	// ��ü ��ȯ�ϸ鼭 ���� ����� �ε��� ��ȯ
	int		GetNearIndexFromRatio(float xRatio, float yRatio) const;
	

	// xy ������ ������ üũ
	bool	IsEqualRange(void);
};
//////////////////////////////////////////////////////////////////////////////////////////
};

