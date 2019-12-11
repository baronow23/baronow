#pragma once


namespace bapi 
{
	//////////////////////////////////////////////////////////////////////////////////////////
	namespace Icon
	{
		// 파일 확장자, 패스로 아이콘얻기 (strExt는 ".txt" 형태)
		BN23_API(bool) GetFileExtensionToIcon(_In_ CString strExt, _Ret_ HICON &hIconL, _Ret_ HICON &hIconS, _Ret_ bool &bLinkedIcon);
		BN23_API(bool) GetFilePathToIcon(_In_ CString strPath, _Ret_ HICON &hIconL, _Ret_ HICON &hIconS, _Ret_ bool &bLinkedIcon);


		// 기존 아이콘에 바로가기 아이콘 merge
		BN23_API(bool) AddLinkedIconMerge(_Inout_ HICON &hIcon);
	};



	//////////////////////////////////////////////////////////////////////////////////////////
	namespace Image
	{
		// 이미지 포맷 clsid 얻기 
		// lpszFmt : "image/png", "image/jpeg", 등등
		BN23_API(int) GetEncoderCLSID(_In_ const LPCWSTR lpszFmt, _Ret_ CLSID &Clsid);



		// szSrc를 szDest크기로 맞추고 싶을 때 종회비가 적용된 사이즈 반환
		// (옵션) pptDestShift : dest 중간 영역에 반환 크기를 출력 할 때 shift 시켜야 할 left,top 위치
		BN23_API(CSize) GetAspectResize(_In_ CSize szSrc, _In_ CSize szDest, _Out_opt_ CPoint *pptDestShift = nullptr);


		// hBitmap을 파일로 저장
		BN23_API(Gdiplus::Status) SaveImageFile(_In_ HBITMAP hBitmap,
											   _In_ LPCTSTR lpszSavePath,
											   _In_ LPCWSTR lpszImgType = L"image/png");


		// szResize : 사용자 지정 크기 (원본 크기비율에 맞게 생성한 해상도 반환)
		// szSrc : 원본 해상도 반환
		BN23_API(bool) CreateImageThumbnail(_In_ CString strSrcPath,
										   _In_ CString strDestPath,
										   _Inout_ CSize &szResize,
										   _Ret_ CSize &szSrc);
	};
	//////////////////////////////////////////////////////////////////////////////////////////
};
