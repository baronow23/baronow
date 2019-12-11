#pragma once

namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////

class BN23_CLASS CryptHandle final
{
public :
	explicit CryptHandle(bool bOrigin = false);
	explicit CryptHandle(const CryptHandle &rhs);
	CryptHandle& operator = (const CryptHandle& rhs);
	~CryptHandle();

public :
	void Release();
	bool IsValid() const;

private :
	bool m_bOrigin;

public :
	HCRYPTPROV	m_hProv;
	HCRYPTHASH	m_hHash;
	HCRYPTKEY	m_hKey;
};


namespace CryptFactory
{
	BN23_API(std::shared_ptr<CryptHandle>) CreateAES256(CStringA strKey32A,
													   bool bUsingIV16 = true,
													   DWORD dwMode = CRYPT_MODE_CBC,
													   DWORD dwPadding = PKCS5_PADDING);


	BN23_API(std::shared_ptr<CryptHandle>) CreateAES256(CStringW strKey32W,
													   bool bUsingIV16 = true,
													   DWORD dwMode = CRYPT_MODE_CBC,
													   DWORD dwPadding = PKCS5_PADDING);


	BN23_API(std::shared_ptr<CryptHandle>) CreateAES256(const BYTE *pKey32,
													   const BYTE *pIV16 = nullptr,
													   DWORD dwMode = CRYPT_MODE_CBC,
													   DWORD dwPadding = PKCS5_PADDING);

	BN23_API(size_t) EncryptWidhBase64A(const CryptHandle *pHandle, _In_ LPCSTR lpszPlain, _Ret_ CStringA &strCipher);
	BN23_API(size_t) DecryptWithBase64A(const CryptHandle *pHandle, _In_ LPCSTR lpszCipher, _Ret_ CStringA &strPlain);


	BN23_API(TBuffer<byte>) CreateHash(ALG_ID Algid, _In_ const byte* pSource, size_t szSource);
	BN23_API(TBuffer<byte>) CreateHash(ALG_ID Algid, _In_ const TBuffer<byte> &source);
};
//////////////////////////////////////////////////////////////////////////////////////////
};