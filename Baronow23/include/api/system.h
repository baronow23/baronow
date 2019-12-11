#pragma once


namespace bapi 
{
//////////////////////////////////////////////////////////////////////////////////////////

	// window version
	BN23_API(BOOL)	GetWinVersion(OSVERSIONINFOEX &osvi);
	BN23_API(BOOL)	GetWinVersion(DWORD &dwMajor, DWORD &dwMinor);
	BN23_API(BOOL)	GetBuildVersion(DWORD &dwBuild);
	

	// �����,��ǻ�� �̸�
	BN23_API(CString) GetPcName(void);
	BN23_API(CString) GetUserName(bool bBlind);


	// Ȯ�ε� lan ī�� ��� ��ȯ
	BN23_API(bool) GetLanAdapterList(_Ret_ std::vector<CString> &vDesc,
									_Ret_ std::vector<CString> &vIP,
									_Ret_ std::vector<CString> &vAddress);


	// ���� ������ clsid ���
	BN23_API(int) GetEncoderCLSID(_In_ const LPCWSTR lpszFmt, _Ret_ CLSID &Clsid);


	// �����찡 ��Ŀ�� �Ǿ� ���� �ʾƵ� ���콺�� ���۵��� Ʈ��ŷ�� �����ϴ��� ���� ��ȯ
	BN23_API(bool) IsSupportAutoMouseTracking(void);

//////////////////////////////////////////////////////////////////////////////////////////
};
