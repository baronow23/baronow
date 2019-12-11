#pragma once


namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////

// ���� ������, operator �̱��� ��ü ���Թ���
// ��ɱ����� ��� ���� �� ��
class BN23_CLASS CheckPointer
{
protected:
	explicit CheckPointer(void) : m_pThisPtr(this) 
	{
		_ntrace_construct;
	};
	
	virtual ~CheckPointer(void)
	{
		_ntrace_destruct;
		ASSERT(m_pThisPtr == this);
	};

private:
	const CheckPointer* m_pThisPtr;
};


class BN23_TYPE CriticalSection : public CheckPointer // ��� Ŭ���� ��������� �ʿ� ��Ȳ���� �ʿ�� ����
{
	friend class AutoLock;

public:
	explicit CriticalSection(void)
	{
		_ntrace_construct;
		m_iRefCount = 0;
		InitializeCriticalSection(&m_cs);
	};

	virtual ~CriticalSection(void)
	{
		_ntrace_destruct;
		Unlock();
		DeleteCriticalSection(&m_cs);
	};

	CriticalSection(const CriticalSection&) = delete;
	CriticalSection& operator = (const CriticalSection&) = delete;


protected:
	CRITICAL_SECTION	m_cs;
	int					m_iRefCount;


public:
	int Lock(void)
	{
		//_trace("----------------------------");
		//_trace("Enter	(L)%d, (R)%d", m_cs.LockCount, m_cs.RecursionCount);
		EnterCriticalSection(&m_cs);
		//_trace("Lock		(L)%d, (R)%d", m_cs.LockCount, m_cs.RecursionCount);
		m_iRefCount++;
		return m_iRefCount;
	};

	int Unlock(void)
	{
		if(m_iRefCount > 0)
		{
			LeaveCriticalSection(&m_cs);
			//_trace("Leave	(L)%d, (R)%d", m_cs.LockCount, m_cs.RecursionCount);
			m_iRefCount--;
		}
		return m_iRefCount;
	};
};
//////////////////////////////////////////////////////////////////////////////////////////
};