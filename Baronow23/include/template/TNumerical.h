#pragma once

#include <iostream>
#include <limits>
#include "../interface/ISerialize.h"

namespace baro 
{
	// excel GROWTH
	template <typename _Type>
	double NumGrowth(_Type newX, const vector<_Type> &vKnownX, const vector<_Type> &vKnownY)
	{
		ASSERT_RETVAL(vKnownX.size() == vKnownY.size(), 0);
		size_t iSize = vKnownX.size();
		if(iSize == 0)
		{
			return 0;
		}
		else if(iSize == 1)
		{
			return ((double)vKnownY[0] / (double)vKnownX[0]) * (double)newX;
		}


		double AvgX = 0;
		double AvgY = 0;
		double AvgXY = 0;
		double AvgXX = 0;


		double X, Y;
		for(size_t i=0; i<iSize; i++)
		{
			X = vKnownX[i];
			Y = log(vKnownY[i]);

			AvgX += X;
			AvgY += Y;
			AvgXY += X * Y;
			AvgXX += X * X;
		}

		AvgX /= iSize;
		AvgY /= iSize;
		AvgXY /= iSize;
		AvgXX /= iSize;


		double lfBeta = (AvgXY - AvgX * AvgY) / (AvgXX - AvgX * AvgX);
		double lfAlpha = AvgY - lfBeta * AvgX;
		return exp(lfAlpha + lfBeta * (double)newX);
	};


	// excel TREND, LeastSquaresFitLinear
	template <typename _Type>
	double NumTrend(_Type newX, const vector<_Type> &vKnownX, const vector<_Type> &vKnownY)
	{
		ASSERT_RETVAL(vKnownX.size() == vKnownY.size(), 0);
		size_t iSize = vKnownX.size();
		if(iSize == 0)
		{
			return 0;
		}

		double m = 0;
		double b = 0;
		double X1 = 0;
		double Y1 = 0;
		double XY = 0;
		double X2 = 0;

		double X, Y;
		for(size_t i=0; i<iSize; i++)
		{
			X = vKnownX[i];
			Y = vKnownY[i];

			X1 += X;
			Y1 += Y;
			XY += X * Y;
			X2 += X * X;
		}


		double J = (double)iSize * X2 - (X1 * X1);
		if(J != 0)
		{
			m = (double)iSize * XY - (X1 * Y1);
			b = (Y1 * X2) - (X1 * XY);

			m /= J;
			b /= J;
		}

		return m * (double)newX + b;
	};

};

namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
template <typename _Type, typename _Calc> class TNumerical : public ISerialize
{
public:
	explicit TNumerical()
	{
		_ntrace_construct;
		//_trace("%s", GetTypeName());
		ASSERT(sizeof(_Calc) >= sizeof(_Type));
		
		m_iDepth = 0;
		Clear();
	};

	TNumerical(const TNumerical &rhs) 
	{
		_ntrace_construct;
		*this = rhs;
	};

	TNumerical& operator = (const TNumerical &rhs)
	{
		m_iDepth	= rhs.m_iDepth;
		m_vTag		= rhs.m_vTag;
		m_vValue	= rhs.m_vValue;

		m_idxMin	= rhs.m_idxMin;
		m_idxMax	= rhs.m_idxMax;
		m_idxMid	= rhs.m_idxMid;
		m_idxAvg	= rhs.m_idxAvg;

		m_Sum		= rhs.m_Sum;
		m_Average	= rhs.m_Average;
		m_AverageEx	= rhs.m_AverageEx;
		m_Median	= rhs.m_Median;
		m_StdDeviation = rhs.m_StdDeviation;

		m_iUpdateCount = 0;
		m_lfUpdateAvailRatio = 0;
		m_pValidNums.reset();
		Update(rhs.m_lfUpdateAvailRatio);
		return *this;
	};


public :
	~TNumerical()
	{
		_ntrace_destruct;
		Clear();
	};
	

	void Clear(void)
	{
		m_vTag.clear();
		m_vValue.clear();

		m_iUpdateCount	= 0;
		m_lfUpdateAvailRatio = 0;
		m_pValidNums.reset();

		m_idxMin = 0;
		m_idxMax = 0;
		m_idxMid = 0;
		m_idxAvg = 0;

		m_Sum		= 0;
		m_Average	= 0;
		m_AverageEx	= 0;
		m_Median	= 0;
		m_StdDeviation = 0;
	};


	void Print(bool bWithList = false) const
	{
		_traceLine;
		_traceC(baro::TextColor::WHITE, "---[ depth %d, refCount %d ]---", m_iDepth, m_vTag.size());


		_Type _mid = Mid();
		_Type _avg = NearAvg();
		_trace("min :	%lf", (double)Min());
		_trace("max :	%lf", (double)Max());
		_trace("mid :	%lf", (double)_mid);
		_trace("navg :	%lf", (double)_avg);

		_trace("sum :	%lf", (double)m_Sum);
		_trace("avg :	%lf", (double)m_Average);
		_trace("avg2 :	%lf", (double)m_AverageEx);
		_trace("med :	%lf", (double)m_Median);
		_trace("dev :	%lf (%lf%%)", (double)m_StdDeviation, (double)StdDevRatio());


		if(bWithList)
		{
			for(size_t i=0; i<m_vValue.size(); i++)
			{
				if(m_vValue[i] == _mid && m_vValue[i] == _avg)
				{
					_traceC(baro::TextColor::LIGHT_GREEN, "[%d]	%.1lf - %.1lf", i, (double)m_vTag[i], (double)m_vValue[i]);
				}
				else if(m_vValue[i] == _mid)
				{
					_traceC(baro::TextColor::CYAN, "[%d]	%.1lf - %.1lf", i, (double)m_vTag[i], (double)m_vValue[i]);
				}
				else if(m_vValue[i] == _avg)
				{
					_traceC(baro::TextColor::YELLOW, "[%d]	%.1lf - %.1lf", i, (double)m_vTag[i], (double)m_vValue[i]);
				}
				else
				{
					_trace("[%d]	%.1lf - %.1lf", i, (double)m_vTag[i], (double)m_vValue[i]);
				}
			}
		}


		if(m_pValidNums)
		{
			m_pValidNums->Print();
		}
	};

	CString GetTypeName(void) const
	{
		CString strName;
		strName = typeid(_Type).name();
		return strName;
	};


	size_t Size(void) const
	{
		return m_vTag.size();
	};


	bool Get(size_t index, _Type &tag, _Type &value) const
	{
		if(index >= Size())
		{
			return false;
		}

		tag = m_vTag[index];
		value = m_vValue[index];
		return true;
	};

	_Type GetValue(size_t index) const
	{
		if(index >= Size())
		{
			return 0;
		}
		return m_vValue[index];
	};

	vector<_Type> GetValue(void) const
	{
		return m_vValue;
	};

	vector<_Type> GetSortValue(bool bAsecnding) const
	{
		if(Size() <= 1)
		{
			return m_vValue;
		}

		vector<_Type> vSort = m_vValue;
		if(bAsecnding)
		{
			std::stable_sort(vSort.begin(), vSort.end(), [](const _Type &left, const _Type &right)
			{
				return left < right;
			});
		}
		else
		{
			std::stable_sort(vSort.begin(), vSort.end(), [](const _Type &left, const _Type &right)
			{
				return right < left;
			});
		}
		return vSort;
	};

	_Type GetTag(size_t index) const
	{
		if(index >= Size())
		{
			return 0;
		}
		return m_vTag[index];
	};

	vector<_Type> GetTag(void) const
	{
		return m_vTag;
	};

	_Type Min(void) const
	{
		return GetValue(m_idxMin);
	};

	_Type Max(void) const
	{
		return GetValue(m_idxMax);
	};

	_Type Mid(void) const
	{
		return GetValue(m_idxMid);
	};

	_Type NearAvg(void) const
	{
		return GetValue(m_idxAvg);
	};

	_Calc Sum(void) const
	{
		return m_Sum;
	};

	_Calc Average(void) const
	{
		return m_Average;
	};

	_Calc AverageEx(void) const
	{
		return m_AverageEx;
	};

	_Calc Median(void) const
	{
		return m_Median;
	};

	_Calc StdDeviation(void) const
	{
		return m_StdDeviation;
	};

	// 표준 편차율 (표준편차 / 평균)
	_Calc StdDevRatio(void) const
	{
		if(m_Average == 0)
		{
			return 0;
		}

		return (m_StdDeviation / m_Average) * 100;
	};


	_Calc StdDevRatioEx(void) const
	{
		if(m_AverageEx == 0)
		{
			return 0;
		}

		return m_StdDeviation / m_AverageEx;
	};
	

	const TNumerical<_Type, _Calc>* GetValidTarget(void) const
	{
		if(m_pValidNums)
		{
			return m_pValidNums.get();
		}
		
		return this;
	};


	////////////////////////////////////////////////////////////////////////////////////////////////

	void Add(_Type value)
	{
		m_vTag.push_back(m_vTag.size() + 1);
		m_vValue.push_back(value);
	};
	
	void Add(_Type tag, _Type value)
	{
		m_vTag.push_back(tag);
		m_vValue.push_back(value);
	};


	////////////////////////////////////////////////////////////////////////////////////////////////
	// 수치 분석
	// lfAvailRatio : 산출된 중간값을 기준으로 최소,최대 유효값 산정 (0~1, ex) 0.01 = 0.99 ~ 1.01로 범위 설정)
	void Update(double lfAvailRatio = 0)
	{
		size_t iSize = m_vTag.size();
		if( iSize <= 0 ) 
		{
			return;
		}
		if( (iSize == m_iUpdateCount) && lfAvailRatio == m_lfUpdateAvailRatio )
		{
			return;
		}
		m_iUpdateCount = iSize;
		m_lfUpdateAvailRatio = lfAvailRatio;


		if(iSize == 1)
		{
			m_idxMin = 0;
			m_idxMax = 0;
			m_idxMid = 0;
			m_idxAvg = 0;

			m_Sum		= (_Calc)m_vValue[0];
			m_Average	= m_Sum;
			m_AverageEx	= m_Sum;
			m_Median	= m_Sum;
			m_StdDeviation = 0;
			return;
		}


		////////////////////////////////////////////
		// 오름차순 정렬
		vector<_Type> vSort = m_vValue;
		stable_sort(vSort.begin(), vSort.end(), [](const _Type &lhs, const _Type &rhs)
		{
			return lhs < rhs;
		});

		_Type _Min = vSort[0];
		_Type _Max = vSort[iSize-1];
		_Type _Mid = vSort[iSize / 2];


		// 평균
		m_Sum = 0;
		for(size_t i=0; i<iSize; i++)
		{
			m_Sum += m_vValue[i];
			m_Average += m_vValue[i];
		}
		m_Average = m_Sum / (_Calc)iSize;

		if(iSize >= 3)
		{
			m_AverageEx = m_Sum;
			m_AverageEx -= vSort[0];
			m_AverageEx -= vSort[iSize-2];
			m_AverageEx /= (_Calc)( iSize-2 );
		}
		else
		{
			m_AverageEx = m_Average;
		}
			


		// 중간값
		if(iSize % 2 == 1)
		{
			m_Median = (_Calc)_Mid;
		}
		else
		{
			// 짝수 갯수면 중앙 2개값 평균 처리
			size_t idxMid = iSize / 2;
			m_Median = (_Calc)(vSort[idxMid-1] + vSort[idxMid]) / 2;


			// 중앙 2개중 편차가 작은것을 mid로 재설정
			if(fabs((_Calc)vSort[idxMid-1]) < fabs((_Calc)vSort[m_idxMid]))
			{
				_Mid = vSort[idxMid-1];
			}
		}




		// 유효범위 설정
		_Calc _Lower, _Upper;
		if(lfAvailRatio == 0 || iSize == 2)
		{
			_Lower = (_Calc)_Min;
			_Upper = (_Calc)_Max;
		}
		else
		{
			m_pValidNums = make_unique<TNumerical<_Type, _Calc>>();
			m_pValidNums->m_iDepth = m_iDepth + 1;

			_Lower = m_Median - (m_Median * lfAvailRatio);
			_Upper = m_Median + (m_Median * lfAvailRatio);
		}

		
		//////////////////////////////////////////////////////////////////////
		// 원본 순환하면서 분산, 표준편차, 유효값 체크
		_Calc _Val, _Dev = 0;
		_Calc _LowerDev = fabs( (_Calc)_Max - m_Average );	// default 최대편차
		_Calc _Var = 0;

		for(size_t i=0; i<iSize; i++)
		{
			_Val = (_Calc)m_vValue[i];


			// 편차, 분산
			_Dev = fabs(_Val - m_Average);
			_Var += _Dev * _Dev;


			// 최소,최대 인덱스
			if(m_vValue[i] == _Min)	m_idxMin = i;
			if(m_vValue[i] == _Max) m_idxMax = i;
			if(m_vValue[i] == _Mid) m_idxMid = i;

			
			// 최소 편차 체크
			if(_Dev < _LowerDev)
			{
				_LowerDev = _Dev;
				m_idxAvg = i;
			}
			


			// 유효범위 분류
			if(lfAvailRatio != 0 && m_pValidNums)
			{
				if(_Val >= _Lower && _Val <= _Upper)
				{
					m_pValidNums->Add( m_vTag[i], m_vValue[i] );
				}
			}
		}

		// 표준편차, 표준편차율
		_Var /= (_Calc)(iSize - 1);
		m_StdDeviation = sqrt(_Var);



		if(m_pValidNums)
		{
			// 현재 depth와 크기가 같으면 GetValidTarget이 this가 되도록 reset
			if(m_pValidNums->Size() == iSize)
			{
				m_pValidNums.reset();
			}
			else
			{
				// 유효범위안의 값이 없을 경우 평균에 가장 가까운 대상만 추가
				if(m_pValidNums->Size() == 0)
				{
					m_pValidNums->Add(m_vTag[m_idxAvg], m_vValue[m_idxAvg]);
				}

				m_pValidNums->Update(0);
			}
		}
	};

	
	// excel GROWTH 함수 
	// known_y = m_vValue
	// known_x = m_vTag
	// new_x = newTag
	double Growth(_Type newTag) const
	{
		return baro::NumGrowth<_Type>(newTag, m_vTag, m_vValue);

		//size_t iLength = Size();
		//if(iLength == 0)
		//{
		//	return 0;
		//}
		//
		//double AvgX = 0;
		//double AvgY = 0;
		//double AvgXY = 0;
		//double AvgXX = 0;
		//

		//double X, Y;
		//for(size_t i=0; i<iLength; i++)
		//{
		//	X = m_vTag[i];
		//	Y = log(m_vValue[i]);

		//	AvgX += X;
		//	AvgY += Y;
		//	AvgXY += X * Y;
		//	AvgXX += X * X;
		//}

		//AvgX /= iLength;
		//AvgY /= iLength;
		//AvgXY /= iLength;
		//AvgXX /= iLength;


		//double lfBeta = (AvgXY - AvgX * AvgY) / (AvgXX - AvgX * AvgX);
		//double lfAlpha = AvgY - lfBeta * AvgX;
		//return exp(lfAlpha + lfBeta * (double)newTag);
	};



	// excel TREND 함수 
	// known_y = m_vValue
	// known_x = m_vTag
	// new_x = newTag
	double Trend(_Type newTag) const
	{
		return baro::NumTrend<_Type>(newTag, m_vTag, m_vValue);
		//double m, b;
		//LeastSquaresFitLinear(m, b);
		//return m * (double)newTag + b;
	}

private:
	void LeastSquaresFitLinear(_Ret_ double &m, _Ret_ double &b) const
	{
		m = 0;
		b = 0;
		
		size_t iLength = Size();
		if(iLength == 0)
		{
			return;
		}

		double X1 = 0;
		double Y1 = 0;
		double XY = 0;
		double X2 = 0;

		double X, Y;
		for(size_t i=0; i<iLength; i++)
		{
			X = m_vTag[i];
			Y = m_vValue[i];

			X1 += X;
			Y1 += Y;
			XY += X * Y;
			X2 += X * X;
		}


		double J = (double)iLength * X2 - (X1 * X1);
		if(J != 0)
		{
			m = (double)iLength * XY - (X1 * Y1);
			b = (Y1 * X2) - (X1 * XY);

			m /= J;
			b /= J;
		}
	};


private :
	baro::StreamResult OnReadStream(_In_ Stream &stream, float /*fReadVersion = 0*/)
	{
		_NextReadStream(stream, m_iDepth);
		_NextReadStream(stream, m_vTag);
		_NextReadStream(stream, m_vValue);
		_NextReadStream(stream, m_iUpdateCount);
		_NextReadStream(stream, m_lfUpdateAvailRatio);

		_NextReadStream(stream, m_idxMin);
		_NextReadStream(stream, m_idxMax);
		_NextReadStream(stream, m_idxMid);
		_NextReadStream(stream, m_idxAvg);

		_NextReadStream(stream, m_Sum);
		_NextReadStream(stream, m_Average);
		_NextReadStream(stream, m_AverageEx);
		_NextReadStream(stream, m_Median);
		_NextReadStream(stream, m_StdDeviation);

		bool bValidNums = false;
		_NextReadStream(stream, bValidNums);
		if(bValidNums)
		{
			m_pValidNums = make_unique<TNumerical<_Type, _Calc>>();
			return m_pValidNums->ReadStream(stream, false);
		}
		return StreamResult::Ok;
	};

	baro::StreamResult OnWriteStream(_Ret_ Stream &stream) const
	{
		_NextWriteStream(stream, m_iDepth);
		_NextWriteStream(stream, m_vTag);
		_NextWriteStream(stream, m_vValue);
		_NextWriteStream(stream, m_iUpdateCount);
		_NextWriteStream(stream, m_lfUpdateAvailRatio);
		
		_NextWriteStream(stream, m_idxMin);
		_NextWriteStream(stream, m_idxMax);
		_NextWriteStream(stream, m_idxMid);
		_NextWriteStream(stream, m_idxAvg);
		
		_NextWriteStream(stream, m_Sum);
		_NextWriteStream(stream, m_Average);
		_NextWriteStream(stream, m_AverageEx);
		_NextWriteStream(stream, m_Median);
		_NextWriteStream(stream, m_StdDeviation);

		bool bValidNums = m_pValidNums ? true : false;
		_NextWriteStream(stream, bValidNums);
		if(bValidNums)
		{
			return m_pValidNums->WriteStream(stream, false);
		}
		return StreamResult::Ok;
	};


private :
	// 최초 데이터로부터 필터링 된 계층 구간, source는 0
	size_t	m_iDepth;


	// source
	vector<_Type> m_vTag;		// 기본값은 인덱스+1
	vector<_Type> m_vValue;


	// Update() 처리된 Size()와 유효범위
	size_t	m_iUpdateCount;
	double	m_lfUpdateAvailRatio;

 
	// Update() 유효범위 지정시 범위에 속한 원본 재분류
	unique_ptr<TNumerical<_Type, _Calc>> m_pValidNums;


	// 참조위치
	size_t	m_idxMin;
	size_t	m_idxMax;
	size_t	m_idxMid;	// 정렬된 값의 중심위치, 데이터 갯수가 짝수면 2개중 편차가 낮은 위치
	size_t	m_idxAvg;	// 평균에 가장 가까운 위치


	// 계산 결과
	_Calc	m_Sum;
	_Calc	m_Average;
	_Calc	m_AverageEx;		// 최소, 최대값을 제외한 평균, 데이터 갯수가 3개보다 작으면 평균으로 처리
	_Calc	m_Median;			// 중간값, 데이터 갯수가 짝수면 중앙 2개의 평균
	_Calc	m_StdDeviation;		// 표준편차
};
//////////////////////////////////////////////////////////////////////////////////////////
};
