#pragma once

class BN25_TYPE BNC_Base64Low
{
private:
	static int GetBase64Key(char* strKey, char ch);
	static int base64_encode(char *text, int numBytes, char **encodedText);
	static int base64_decode(char *text, unsigned char *dst, int numBytes);


public:
	static bool	Encode(_In_ CString &strSrc, _Ret_ CString &strEncode);
	static bool	Decode(_In_ CString &strSrc, _Ret_ CString &strDecode);
};

