#pragma once

namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////

// Windows XP 사용불가
class BN23_CLASS A256B64 final
{
public:
	explicit A256B64(CStringA strKey32A, DWORD dwMode = CRYPT_MODE_CBC, DWORD dwPadding = PKCS5_PADDING);
	explicit A256B64(CStringW strKey32W, DWORD dwMode = CRYPT_MODE_CBC, DWORD dwPadding = PKCS5_PADDING);
	explicit A256B64(const BYTE *pKey32 = nullptr, const BYTE *pIV16 = nullptr, DWORD dwMode = CRYPT_MODE_CBC, DWORD dwPadding = PKCS5_PADDING);
	~A256B64();


private :
	HCRYPTPROV	m_hProv;
	HCRYPTKEY	m_hKey;
	void Release(void);


public :
	HCRYPTKEY GetKey(void) const
	{
		return m_hKey;
	};

public:
	bool	Initialize(CStringA strKey32, DWORD dwMode = CRYPT_MODE_CBC, DWORD dwPadding = PKCS5_PADDING);
	bool	Initialize(const BYTE *pKey32, const BYTE *pIV16 = nullptr, DWORD dwMode = CRYPT_MODE_CBC, DWORD dwPadding = PKCS5_PADDING);


public :
	size_t	EncryptA(_In_ LPCSTR lpszPlain, _Ret_ CStringA &strCipher) const;
	size_t	DecryptA(_In_ LPCSTR lpszCipher, _Ret_ CStringA &strPlain) const;
};

//////////////////////////////////////////////////////////////////////////////////////////
};
