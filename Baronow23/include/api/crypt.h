#pragma once


#include "../template/TBuffer.h"
namespace bapi 
{
//////////////////////////////////////////////////////////////////////////////////////////

	__declspec(deprecated) BN23_API(bool) EncodeBase64(_In_ CString strSrc, _Ret_ CString &strEncode);
	__declspec(deprecated) BN23_API(bool) DecodeBase64(_In_ CString strSrc, _Ret_ CString &strDecode);
	__declspec(deprecated) BN23_API(bool) EncodeAES(_In_ LPCTSTR lpszSrc, _In_ LPCTSTR lpszKey, _Ret_ CString &strEncode);
	__declspec(deprecated) BN23_API(bool) DecodeAES(_In_ LPCTSTR lpszSrc, _In_ LPCTSTR lpszKey, _Ret_ CString &strDecode);


	// CryptBinaryToString, CryptStringToBinary,
	// dwCryptType : CRYPT_STRING_
	BN23_API(bool)	EncryptString(CString strPlain, DWORD dwCryptType, _Ret_ CString &strResult);
	BN23_API(bool)	DecryptString(CString strCrypt, DWORD dwCryptType, _Ret_ CString &strResult);
	BN23_API(bool)	EncryptStringA(CStringA strPlain, DWORD dwCryptType, _Ret_ CStringA &strResult);
	BN23_API(bool)	DecryptStringA(CStringA strCrypt, DWORD dwCryptType, _Ret_ CStringA &strResult);
	BN23_API(bool)	EncryptStringW(CStringW strPlain, DWORD dwCryptType, _Ret_ CStringW &strResult);
	BN23_API(bool)	DecryptStringW(CStringW strCrypt, DWORD dwCryptType, _Ret_ CStringW &strResult);

	BN23_API(bool)	BinaryToStringA(_In_ const BYTE *pBinary, _In_ DWORD dwBytes, _Ret_ CStringA &strRet);
	BN23_API(bool)	StringToBinaryA(_In_ LPCSTR lpszSrc, _Ret_ baro::TBuffer<BYTE> &retBuffer);
	BN23_API(bool)	BinaryToStringW(_In_ const BYTE *pBinary, _In_ DWORD dwBytes, _Ret_ CStringW &strRet);
	BN23_API(bool)	StringToBinaryW(_In_ LPCWSTR lpszSrc, _Ret_ baro::TBuffer<BYTE> &retBuffer);

//////////////////////////////////////////////////////////////////////////////////////////
};
