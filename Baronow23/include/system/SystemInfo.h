#pragma once
#include "template/TSingleton.h"

namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
class BN23_CLASS SystemInfo final : public TSingleton<const SystemInfo>
{
public:
	explicit SystemInfo(TSingleton::_token);
	~SystemInfo();


private :
	void InitOsInfo(void);
	

public :
	CString		m_strCpuName;
	CString		m_strMemSize;
	CString		m_strMainboardInfo;
	CString		m_strFirstLanDevice;
	CString		m_strFirstLanIP;
	CString		m_strFirstLanMacAddress;

	OSVERSIONINFOEX	m_osvi;
	DWORD			m_dwOsVerCode;
	UINT			m_iOsVerNumber;
	bool			m_bArchitecture64;

	CString		m_strOsName;
	CString		m_strOsVersion;
	CString		m_strSpVersion;
	
	CString		m_strPcName;
	CString		m_strUserName;
	CString		m_strUserNameBlind;
	CString		m_strApplicationVersion;

};
//////////////////////////////////////////////////////////////////////////////////////////
};

