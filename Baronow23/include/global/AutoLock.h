#pragma once

namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
class CriticalSection;
class BN23_CLASS AutoLock final
{
public:
	explicit AutoLock(CriticalSection &cs, CString strName = _T(""));
	explicit AutoLock(CRITICAL_SECTION &cs, CString strName = _T(""));
	~AutoLock();

private:
	void Initialize(CString strName);

private:
	CRITICAL_SECTION	&m_cs;
	TCHAR*				m_pstrName;

};
//////////////////////////////////////////////////////////////////////////////////////////
};

#define _AutoLock(cs)	baro::AutoLock lock(cs);
#define _TraceLock(cs)	baro::AutoLock lock(cs, __FUNCTIONW__);