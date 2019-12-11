#pragma once


namespace bapi 
{
//////////////////////////////////////////////////////////////////////////////////////////

	// window version
	BN23_API(BOOL)	GetWinVersion(OSVERSIONINFOEX &osvi);
	BN23_API(BOOL)	GetWinVersion(DWORD &dwMajor, DWORD &dwMinor);
	BN23_API(BOOL)	GetBuildVersion(DWORD &dwBuild);
	

	// 사용자,컴퓨터 이름
	BN23_API(CString) GetPcName(void);
	BN23_API(CString) GetUserName(bool bBlind);


	// 확인된 lan 카드 목록 반환
	BN23_API(bool) GetLanAdapterList(_Ret_ std::vector<CString> &vDesc,
									_Ret_ std::vector<CString> &vIP,
									_Ret_ std::vector<CString> &vAddress);


	// 지정 포맷의 clsid 얻기
	BN23_API(int) GetEncoderCLSID(_In_ const LPCWSTR lpszFmt, _Ret_ CLSID &Clsid);


	// 윈도우가 포커싱 되어 있지 않아도 마우스휠 조작등의 트래킹을 지원하는지 여부 반환
	BN23_API(bool) IsSupportAutoMouseTracking(void);

//////////////////////////////////////////////////////////////////////////////////////////
};
