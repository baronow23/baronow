#pragma once


namespace bapi 
{
//////////////////////////////////////////////////////////////////////////////////////////

	// Registry Read/Write (�Ǽ����� ���ο��� fDiv��ŭ �����ְų� �������� �����)
	BN23_API(HWND)		RegistryHwnd(bool bWrite, LPCTSTR strSubKey, LPCTSTR strValueName, HWND hWnd);
	BN23_API(CString)	RegistryString(bool bWrite, LPCTSTR strSubKey, LPCTSTR strValueName, LPCTSTR strValue);
	BN23_API(DWORD)		RegistryDword(bool bWrite, LPCTSTR strSubKey, LPCTSTR strValueName, DWORD dwValue);
	BN23_API(bool)		RegistryBool(bool bWrite, LPCTSTR strSubKey, LPCTSTR strValueName, bool bValue);
	BN23_API(float)		RegistryFloat(bool bWrite, LPCTSTR strSubKey, LPCTSTR strValueName, float fValue, float fDiv);


	// HKEY_LOCAL_MACHINE �б�
	//HKEY_LOCAL_MACHINE
	BN23_API(CString)	ReadRegistryString(HKEY hKey, LPCTSTR strSubKey, LPCTSTR strValueName, CString strDefault = _T(""));
	BN23_API(CString)	ReadLocalRegistryString(LPCTSTR strSubKey, LPCTSTR strValueName, CString strDefault = _T(""));
	BN23_API(CString)	ReadUserRegistryString(LPCTSTR strSubKey, LPCTSTR strValueName, CString strDefault = _T(""));

//////////////////////////////////////////////////////////////////////////////////////////
};
