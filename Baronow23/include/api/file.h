#pragma once


namespace bapi 
{
//////////////////////////////////////////////////////////////////////////////////////////

	// 실행중인 인스턴스 폴더 반환 (마지막 \\ 제외)
	BN23_API(CString) GetInstancePath(bool bExecutePath = true);


	// 폴더 생성용 (없으면 만듬)
	BN23_API(BOOL) CreateFolder(CString strPath);					// 마지막에 "\\" 붙여주지 않으면 파일로 인식하고 상위 depth까지만 생성함
	BN23_API(int) DeleteFolder(CString strPath, int iRecursive);	// 하위폴더 모두 돌면서 삭제


	// 지정경로에 폴더 있으면 넘버링 해서 반환
	BN23_API(void) FolderExistIsAddNumbering(_Inout_ CString &strPath);


	// 지정경로에 파일 있으면 넘버링 해서 반환
	BN23_API(bool) FileExistAddNumbering(_Inout_ CString &strPath);


	// 지정경로에서 파일이름, 폴더 추출
	// bDeleteExt가 ture이면 확장자 지움
	BN23_API(bool) GetPathNameFolder(CString &strPath, bool bDeleteExt, _Ret_ CString &strFolder, _Ret_ CString &strFileName);
	

	// 필터 샘플 ".png;.jpg;.jpeg;.bmp;" 구분자 ; 는 반드시 넣어야 하며 끝에 반드시 포함시켜야 마지막 구분 필터를 수행한다.
	// 확장자명 strChkExt가 strIncludeExt에 포함되었는지 확인
	// strChkExt는 확장자, 파일 이름, pull path 모두 입력 가능
	// strIncludeExt는 파일 다이얼로그 확장자 규칙으로 작성되어야 함 ';'확인!!!!
	// ex) _T(".png;.jpg;.jpeg;.bmp;")
	// return true시 strFindExt에 확장자 입력
	BN23_API(bool) IsIncludeExtension(CString strChkExt, CString strFilterExt, _Ret_ CString& strFindExt);


	// 지정 경로의 파일 크기 반환
	BN23_API(double) GetFileSize(CString strPath);


	// 지정 경로의 파일 정보 반환
	BN23_API(bool) GetFileVersion(LPCTSTR lpszFileName, _Ret_ VS_FIXEDFILEINFO &fi);


	// 호출 인스턴스 버전
	BN23_API(bool)		GetInstanceFileVersion(bool bAppInstance, _Ret_ VS_FIXEDFILEINFO &fi);
	BN23_API(CString)	GetInstanceFileVersion(bool bAppInstance);


	// 파일 읽기
	BN23_API(bool) ReadBinaryFile(CString strPath, std::function<bool(CFile &file)> _callback);
	BN23_API(bool) WriteBinaryFile(CString strPath, bool bOverWrite, std::function<bool(CFile &file)> _callback);
	


	// 지정 경로 안의 파일 리스트 얻기
	// ext는 '.' 제외
	BN23_API(vector<CString>) FindFileList(CString strFolder);
	BN23_API(vector<CString>) FindFileList(CString strFolder, CString strExt);
	BN23_API(vector<CString>) FindFileList(CString strFolder, vector<CString> vStrExt);

//////////////////////////////////////////////////////////////////////////////////////////
};
