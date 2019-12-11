#pragma once

template <typename _Type> class BN25_TYPE BNC_Instance
{
protected:
	BNC_Instance()
	{
		_ntrace_construct;
		m_iInstance = 0;
	};

	~BNC_Instance()
	{
		_ntrace_destruct;
	};

private:
	static atomic<UINT>	s_iConstruct;
	static atomic<UINT>	s_iDestruct;

protected:
	UINT	m_iInstance;

protected:
	UINT AddInstnace(void)
	{
		if(m_iInstance == 0)
		{
			m_iInstance = ++s_iConstruct;
		}
		return s_iConstruct;
	};

	UINT ReleaseInstance(void)
	{
		if(m_iInstance)
		{
			++s_iDestruct;
			m_iInstance = 0;
		}
		return s_iConstruct - s_iDestruct;
	};

public:
	static UINT GetConstructCount(void)
	{ 
		return s_iConstruct; 
	};

	static UINT GetDestrcutCount(void)
	{
		return s_iDestruct;
	};

	static UINT GetAliveInstanceCount(void)
	{
		return s_iConstruct - s_iDestruct;
	};
};

template <typename _Type> atomic<UINT> BNC_Instance<_Type>::s_iConstruct = 0;
template <typename _Type> atomic<UINT> BNC_Instance<_Type>::s_iDestruct	= 0;