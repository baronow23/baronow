#pragma once

#include <random>
namespace bapi
{
//////////////////////////////////////////////////////////////////////////////////////////

	// min, max 범위에 해당하는 랜덤 값 반환
	template <typename _Num>
	_Num MakeRandom(_Num min, _Num max)
	{
		static random_device seed;		//시드 값
		static mt19937_64 rnd(seed());   //random_device를 시드 값으로 하여 초기화

		uniform_int_distribution<_Num> iDist(min, max);
		return iDist(rnd);
	};


	// base를 기준으로 -1~1사이의 최초최대 비율에 해당하는 랜덤 값 반환
	template <typename _Num>
	_Num MakeRandom(_Num base, double lfMinRatio, double lfMaxRatio)
	{
		_Num min = base + _Num((double)base * lfMinRatio);
		_Num max = base + _Num((double)base * lfMaxRatio);
		return MakeRandom(min, max);
	};


	// szSrc 종횡비 따라 szTarget에 확대/축소한 크기 반환
	BN23_API(CSize) MakeStretchSize(CSize szSrc, CSize szTarget);

//////////////////////////////////////////////////////////////////////////////////////////
};
