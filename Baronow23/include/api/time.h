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

	// 두 시간이 어느 위치까지 같은지 체크 (년월일시분초 순서로 체크)
	BN23_API(baro::SystemtimePos) GetDateEqualPos(const SYSTEMTIME &st1, const SYSTEMTIME &st2);
	BN23_API(baro::SystemtimePos) GetTodayEqualPos(const SYSTEMTIME &st);


	// 두 시간 비교
	// 0 : st1 == st2
	// -1 : st1 < st2
	// 1 : st1 > st2
	BN23_API(int) CompareDate(const SYSTEMTIME &st1, const SYSTEMTIME &st2);
	BN23_API(int) CompareToday(const SYSTEMTIME &st);
//////////////////////////////////////////////////////////////////////////////////////////
};
