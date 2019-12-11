#pragma once


namespace bapi 
{
//////////////////////////////////////////////////////////////////////////////////////////

	// �������� �ν��Ͻ� ���� ��ȯ (������ \\ ����)
	BN23_API(CString) GetInstancePath(bool bExecutePath = true);


	// ���� ������ (������ ����)
	BN23_API(BOOL) CreateFolder(CString strPath);					// �������� "\\" �ٿ����� ������ ���Ϸ� �ν��ϰ� ���� depth������ ������
	BN23_API(int) DeleteFolder(CString strPath, int iRecursive);	// �������� ��� ���鼭 ����


	// ������ο� ���� ������ �ѹ��� �ؼ� ��ȯ
	BN23_API(void) FolderExistIsAddNumbering(_Inout_ CString &strPath);


	// ������ο� ���� ������ �ѹ��� �ؼ� ��ȯ
	BN23_API(bool) FileExistAddNumbering(_Inout_ CString &strPath);


	// ������ο��� �����̸�, ���� ����
	// bDeleteExt�� ture�̸� Ȯ���� ����
	BN23_API(bool) GetPathNameFolder(CString &strPath, bool bDeleteExt, _Ret_ CString &strFolder, _Ret_ CString &strFileName);
	

	// ���� ���� ".png;.jpg;.jpeg;.bmp;" ������ ; �� �ݵ�� �־�� �ϸ� ���� �ݵ�� ���Խ��Ѿ� ������ ���� ���͸� �����Ѵ�.
	// Ȯ���ڸ� strChkExt�� strIncludeExt�� ���ԵǾ����� Ȯ��
	// strChkExt�� Ȯ����, ���� �̸�, pull path ��� �Է� ����
	// strIncludeExt�� ���� ���̾�α� Ȯ���� ��Ģ���� �ۼ��Ǿ�� �� ';'Ȯ��!!!!
	// ex) _T(".png;.jpg;.jpeg;.bmp;")
	// return true�� strFindExt�� Ȯ���� �Է�
	BN23_API(bool) IsIncludeExtension(CString strChkExt, CString strFilterExt, _Ret_ CString& strFindExt);


	// ���� ����� ���� ũ�� ��ȯ
	BN23_API(double) GetFileSize(CString strPath);


	// ���� ����� ���� ���� ��ȯ
	BN23_API(bool) GetFileVersion(LPCTSTR lpszFileName, _Ret_ VS_FIXEDFILEINFO &fi);


	// ȣ�� �ν��Ͻ� ����
	BN23_API(bool)		GetInstanceFileVersion(bool bAppInstance, _Ret_ VS_FIXEDFILEINFO &fi);
	BN23_API(CString)	GetInstanceFileVersion(bool bAppInstance);


	// ���� �б�
	BN23_API(bool) ReadBinaryFile(CString strPath, std::function<bool(CFile &file)> _callback);
	BN23_API(bool) WriteBinaryFile(CString strPath, bool bOverWrite, std::function<bool(CFile &file)> _callback);
	


	// ���� ��� ���� ���� ����Ʈ ���
	// ext�� '.' ����
	BN23_API(vector<CString>) FindFileList(CString strFolder);
	BN23_API(vector<CString>) FindFileList(CString strFolder, CString strExt);
	BN23_API(vector<CString>) FindFileList(CString strFolder, vector<CString> vStrExt);

//////////////////////////////////////////////////////////////////////////////////////////
};
