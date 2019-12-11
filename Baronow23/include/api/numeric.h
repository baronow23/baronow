#pragma once

#include <random>
namespace bapi
{
//////////////////////////////////////////////////////////////////////////////////////////

	// min, max ������ �ش��ϴ� ���� �� ��ȯ
	template <typename _Num>
	_Num MakeRandom(_Num min, _Num max)
	{
		static random_device seed;		//�õ� ��
		static mt19937_64 rnd(seed());   //random_device�� �õ� ������ �Ͽ� �ʱ�ȭ

		uniform_int_distribution<_Num> iDist(min, max);
		return iDist(rnd);
	};


	// base�� �������� -1~1������ �����ִ� ������ �ش��ϴ� ���� �� ��ȯ
	template <typename _Num>
	_Num MakeRandom(_Num base, double lfMinRatio, double lfMaxRatio)
	{
		_Num min = base + _Num((double)base * lfMinRatio);
		_Num max = base + _Num((double)base * lfMaxRatio);
		return MakeRandom(min, max);
	};


	// szSrc ��Ⱦ�� ���� szTarget�� Ȯ��/����� ũ�� ��ȯ
	BN23_API(CSize) MakeStretchSize(CSize szSrc, CSize szTarget);

//////////////////////////////////////////////////////////////////////////////////////////
};
