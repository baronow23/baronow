#pragma once


namespace baro
{
	enum class SystemtimePos
	{
		None,
		Year,			
		Month,			
		Day,			
		Hour,			
		Minute,			
		Second,			
	};
};

namespace bapi 
{
//////////////////////////////////////////////////////////////////////////////////////////

	// �� �ð��� ��� ��ġ���� ������ üũ (����Ͻú��� ������ üũ)
	BN23_API(baro::SystemtimePos) GetDateEqualPos(const SYSTEMTIME &st1, const SYSTEMTIME &st2);
	BN23_API(baro::SystemtimePos) GetTodayEqualPos(const SYSTEMTIME &st);


	// �� �ð� ��
	// 0 : st1 == st2
	// -1 : st1 < st2
	// 1 : st1 > st2
	BN23_API(int) CompareDate(const SYSTEMTIME &st1, const SYSTEMTIME &st2);
	BN23_API(int) CompareToday(const SYSTEMTIME &st);
//////////////////////////////////////////////////////////////////////////////////////////
};
