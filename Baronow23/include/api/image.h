#pragma once


namespace bapi 
{
	//////////////////////////////////////////////////////////////////////////////////////////
	namespace Icon
	{
		// ���� Ȯ����, �н��� �����ܾ�� (strExt�� ".txt" ����)
		BN23_API(bool) GetFileExtensionToIcon(_In_ CString strExt, _Ret_ HICON &hIconL, _Ret_ HICON &hIconS, _Ret_ bool &bLinkedIcon);
		BN23_API(bool) GetFilePathToIcon(_In_ CString strPath, _Ret_ HICON &hIconL, _Ret_ HICON &hIconS, _Ret_ bool &bLinkedIcon);


		// ���� �����ܿ� �ٷΰ��� ������ merge
		BN23_API(bool) AddLinkedIconMerge(_Inout_ HICON &hIcon);
	};



	//////////////////////////////////////////////////////////////////////////////////////////
	namespace Image
	{
		// �̹��� ���� clsid ��� 
		// lpszFmt : "image/png", "image/jpeg", ���
		BN23_API(int) GetEncoderCLSID(_In_ const LPCWSTR lpszFmt, _Ret_ CLSID &Clsid);



		// szSrc�� szDestũ��� ���߰� ���� �� ��ȸ�� ����� ������ ��ȯ
		// (�ɼ�) pptDestShift : dest �߰� ������ ��ȯ ũ�⸦ ��� �� �� shift ���Ѿ� �� left,top ��ġ
		BN23_API(CSize) GetAspectResize(_In_ CSize szSrc, _In_ CSize szDest, _Out_opt_ CPoint *pptDestShift = nullptr);


		// hBitmap�� ���Ϸ� ����
		BN23_API(Gdiplus::Status) SaveImageFile(_In_ HBITMAP hBitmap,
											   _In_ LPCTSTR lpszSavePath,
											   _In_ LPCWSTR lpszImgType = L"image/png");


		// szResize : ����� ���� ũ�� (���� ũ������� �°� ������ �ػ� ��ȯ)
		// szSrc : ���� �ػ� ��ȯ
		BN23_API(bool) CreateImageThumbnail(_In_ CString strSrcPath,
										   _In_ CString strDestPath,
										   _Inout_ CSize &szResize,
										   _Ret_ CSize &szSrc);
	};
	//////////////////////////////////////////////////////////////////////////////////////////
};
