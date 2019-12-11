#pragma once


namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////

class BN23_CLASS CryptBuffer final : public CheckPointer
{
public:
	explicit CryptBuffer(size_t length = 0);
	explicit CryptBuffer(CryptBuffer &rhs);
	explicit CryptBuffer(LPCSTR lpszSrc);
	explicit CryptBuffer(LPCWSTR lpszSrc);
	explicit CryptBuffer(const void* pSrc, size_t copyBytes);
	~CryptBuffer();

	CryptBuffer& operator = (const CryptBuffer &rhs);


public :
	const BYTE* GetBuffer(void);
	LPCSTR		GetStrBuffer(void);
	size_t		GetLength(void);
	bool		IsValid(void);


	// 메모리 해제 후 length 만큼 버퍼 할당
	bool	ReAllocate(size_t length);


	// 메모리 해제
	void	Delete(void);


	// iPos위치에 copyBytes만큼 pSrc를 복사
	bool	Update(size_t iPos, const void* pSrc, const size_t copyBytes);


	// iPos위치에 멀티바이트로 변환된 lpszSrc 전체 복사
	bool	UpdateA(size_t iPos, LPCSTR lpszSrc);
	bool	UpdateW(size_t iPos, LPCWSTR lpszSrc);



	/////////////////////////////////////////////////////////////////////
	// m_pBuffer 가공

	bool	ANSItoUTF8(void);
	bool	UTF8toANSI(void);

	bool	EncryptBase64A(void);
	bool	DecryptBase64A(void);


	bool	CryptEncrypt(CryptHandle handle, _Ret_opt_ DWORD *pError = nullptr);
	bool	CryptEncrypt(HCRYPTKEY hKey, HCRYPTHASH hHash, _Ret_opt_ DWORD *pError = nullptr);

	bool	CryptDecrypt(CryptHandle handle, _Ret_opt_ DWORD *pError = nullptr);
	bool	CryptDecrypt(HCRYPTKEY hKey, HCRYPTHASH hHash, _Ret_opt_ DWORD *pError = nullptr);


	// DEBUG : m_pBuffer 16진수 출력
	void	Print(void);


private :
	void	CheckLastError(_Ret_opt_ DWORD *pError = nullptr);

private :
	BYTE	*m_pBuffer;
	size_t	m_iLength;
};
//////////////////////////////////////////////////////////////////////////////////////////
};