#pragma once

namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
	
	template <typename _Type> class TSingleton : public baro::CriticalSection
	{
	protected :
		explicit TSingleton()
		{
			_trace_construct;
		};
		virtual ~TSingleton()
		{
			_trace_destruct;
		};
	

	protected :
		struct _token {};

	public :
		using _Instance = TSingleton<_Type>();


	public :
		static _Type& GetInstance(void)
		{
			static _Type instance(_token{});
			return instance;
		};


		TSingleton(const TSingleton&) = delete;
		TSingleton& operator = (const TSingleton&) = delete;

		TSingleton(const TSingleton&&) = delete;
		TSingleton&& operator = (const TSingleton&&) = delete;

		TSingleton(TSingleton&&) = delete;
		TSingleton&& operator = (TSingleton&&) = delete;
	};


	// #define Inst TSingleton<_Type>::GetInstance() 사용시 인텔리전스 문제
	// #define Inst SingletoneInstance<STC_QcData>() 로 대체처리용
	template <typename _Type> _Type& SingletoneInstance(void)
	{
		return TSingleton<_Type>::GetInstance();
	};

//////////////////////////////////////////////////////////////////////////////////////////
};



//template <typename _Type> class TSingletonX
//{
//protected:
//	TSingletonX() {};
//	struct _token {};
//
//public:
//	static _Type& GetInstance(void)
//	{
//		static _Type instance(_token{});
//		return instance;
//	};
//
//
//	TSingletonX(const TSingletonX&) = delete;
//	TSingletonX& operator = (const TSingletonX&) = delete;
//
//	TSingletonX(const TSingletonX&&) = delete;
//	TSingletonX&& operator = (const TSingletonX&&) = delete;
//};