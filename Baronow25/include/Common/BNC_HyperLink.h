#pragma once
class BN25_TYPE BNC_HyperLink
{
public:
	BNC_HyperLink();
	~BNC_HyperLink();

private :
	std::vector<CString> m_vDomain;

public :
	bool	GetHyperLink(_In_ CString strSrc, _Ret_ CString &strDest);
	bool	GetHyperLinkTrim(_Inout_ CString &strSrc, _Ret_ int &iFirst, _Ret_ int &iLength);
	bool	GetHyperLinkTrimEx(_Inout_ CString &strSrc, _Ret_ int &iFirst, _Ret_ int &iLength);
};


