#pragma once

namespace bapi 
{
//////////////////////////////////////////////////////////////////////////////////////////

	// 1000 ������ , ���� ���ڿ� ��ȯ
	template <typename _Type>
	CString MakeNumberString(_Type num)
	{
		bool bNegative = num < 0 ? true : false;
		CString str, strTemp;
		while(1)
		{
			_Type iRemain = abs( num % 1000 );
			num /= 1000;

			if(num)
			{
				strTemp.Format(_T("%03d"), (int)iRemain);
			}
			else
			{
				if(iRemain < 10)
				{
					strTemp.Format(_T("%d"), (int)iRemain);
				}
				else if(iRemain < 100)
				{
					strTemp.Format(_T("%02d"), (int)iRemain);
				}
				else
				{
					strTemp.Format(_T("%03d"), (int)iRemain);
				}
			}


			if(str.GetLength())
			{
				str = strTemp + _T(",") + str;
			}
			else
			{
				str = strTemp;
			}

			if(num == 0)
			{
				break;
			}
		}

		return bNegative ? _T("-") + str : str;
	};


	BN23_API(CString) MakeString(LPCTSTR lpszFormat, ...);
	BN23_API(CString) MakeNumberString(int num);
	BN23_API(CString) MakeNumberString(float num);
	BN23_API(CString) MakeNumberString(double num);


	// ����ð� (�����_�ú���) ���ڿ� ���� �� ��ȯ
	BN23_API(CString) MakeLocalTimeString(SYSTEMTIME &st);
	BN23_API(CString) MakeLocalTimeString(void);
	

	// ���� ũ�⸦ Bytes, KB, MB, GB�� ����� ���ڿ� ��ȯ
	BN23_API(CString) FileSizeToString(double lfSize, bool bInsertSpace = true);

	
	// winapi �����ڵ忡 �����ϴ� ��� ���ڿ� ��ȯ
	BN23_API(CString) MakeErrorString(DWORD dwCode, DWORD dwFlags = FORMAT_MESSAGE_FROM_SYSTEM);


	// gdiplus �����ڵ忡 �����ϴ� ��� ���ڿ� ��ȯ
	BN23_API(CString) MakeGdiErrorString(Gdiplus::Status status);


	// CException ���ڿ� ��ȯ
	BN23_API(CString) MakeExceptionString(CException *e);


	// GUID to string
	BN23_API(CString) MakeGuidString(void);
	BN23_API(CString) MakeGuidString(const GUID &guid);


	// ���� �ð��� �����Ͽ� ���ڿ��� ��ȯ
	BN23_API(CString) SystemTimeToString(const SYSTEMTIME &t);
	BN23_API(CString) SystemTimeToString2(const SYSTEMTIME &t);
	BN23_API(CString) SystemTimeToStringEx(const SYSTEMTIME &t, bool bChkFullDateReturn = false);
	BN23_API(CString) SystemTimeToJustHourString(const SYSTEMTIME &t);

	BN23_API(CString) SystemtimeToFullString(const SYSTEMTIME &t);	// "��-��-�� ��:��:��.�и���"
	BN23_API(CString) SystemtimeToMonthString(const SYSTEMTIME &t);
	BN23_API(CString) SystemtimeToDayString(const SYSTEMTIME &t);


	// SYSTEMTIME <> DATE ��ȯ (VariantTimeToSystemTime �ٷ� ���� millisecond ������ ��������)
	BN23_API(double)		SystemTimeToVariantTimeMS(SYSTEMTIME st);
	BN23_API(SYSTEMTIME)	VariantTimeToSystemTimeMS(double lfDate);


	// ���� ���� �ð� ��ȯ
	BN23_API(SYSTEMTIME)	GetLocalTime(void);
	BN23_API(double)		GetLocalTimeMS(void);


	// str���� cFind ���� ã�Ƽ� strLeft, strRight�� �й�
	BN23_API(bool) FindCharCut(_In_ const CString &strSrc, TCHAR cFind, _Ret_ CString &strLeft, _Ret_ CString &strRight);
	BN23_API(bool) FindCharCut(_In_ const CString &strSrc, CString strFind, _Ret_ CString &strLeft, _Ret_ CString &strRight);
	BN23_API(bool) FindCharCutReverse(_In_ const CString &strSrc, TCHAR cFind, _Ret_ CString &strLeft, _Ret_ CString &strRight);



	// TODO : src���� ã�� find�� ���� �ε�������Ʈ ��ȯ (���̾�� �˰��� ���� ����)
	//BN23_API vector<size_t> FindString(_In_ const CString &strSrc, CString strFind);



	// ���ڼ� ��ȯ
	BN23_API(LPCWSTR)	ConvertA2W(_In_ LPCSTR lpszSourceA, _In_ UINT CodePage, _Ret_ CAutoPtrArray<WCHAR>& cAutoPtrArrayW);
	BN23_API(LPCSTR)	ConvertW2A(_In_ LPCWSTR lpszSourceW, _In_ UINT CodePage, _Ret_ CAutoPtrArray<char>& cAutoPtrArrayA);
	BN23_API(CStringA)	GetConvertStringA(_In_ CStringW strIn);
	BN23_API(CStringW)	GetConvertStringW(_In_ CStringA strIn);

//////////////////////////////////////////////////////////////////////////////////////////
};


#define USES_SMARTCONVERSION CAutoPtrArray<char> _cAutoPtrArrayA; CAutoPtrArray<WCHAR> _cAutoPtrArrayW  
#define SMART_A2W_CP(lpszSourceA, CodePage) (bapi::ConvertA2W(lpszSourceA, CodePage,	_cAutoPtrArrayW))
#define SMART_A2W(lpszSourceA)				(bapi::ConvertA2W(lpszSourceA, CP_ACP,		_cAutoPtrArrayW))
#define SMART_W2A_CP(lpszSourceW, CodePage) (bapi::ConvertW2A(lpszSourceW, CodePage,	_cAutoPtrArrayA))
#define SMART_W2A(lpszSourceW)				(bapi::ConvertW2A(lpszSourceW, CP_ACP,		_cAutoPtrArrayA))