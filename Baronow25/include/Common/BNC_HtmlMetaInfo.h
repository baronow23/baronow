#pragma once


#define HPD_MAX_METALENGTH		10240		// 10k		URL�κ��� �о���� �ִ� ����ũ��, �̹��� �ȿ��� ��Ÿ������ üũ
#define HPD_MAX_CONTENTLENGTH	1024000		// 1mb		�ش� ũ�Ⱑ ��Ÿ�����͸� ���� �ʰ� ����ó����
#define HPD_MAX_FILELENGTH		10240000	// 10mb		�ٿ�ε� �� �̹���, �ĺ����� �ִ� ũ��, �дµ��� �Ѿ�� ����ó����
//#define USING_FAVICON_IMAGE


#include <mutex>
class BN25_TYPE BNC_HtmlMetaInfo
{
private :
	static mutex s_cacheMutex;
	static map<CString, Image*> s_mCacheImage;
	static map<CString, HICON> s_mCacheFavicon;

	static Image*	AddRefCacheImage(CString strPath, CSize szResize);
	static HICON	AddRefCacheFavicon(CString strPath, bool bUseFileIcon);


public :
	static void		ReleaseCache(void);


public:
	BNC_HtmlMetaInfo(CString strURL);
	~BNC_HtmlMetaInfo();

public:
	// ������ ���ڿ��� meta property�� ã�Ƽ� content ���� ��ȯ
	static CString GetProperty(_In_ CString &strSrc, _In_ int iBegin, _In_ CString strProperty);

	// str���� strTokenLeft-strTokenRight ���̰��� ã�Ƽ� ��ȯ
	static CString GetString(_In_ CString &str, _In_ int iBegin, _In_ CString strTokenLeft, _In_ CString strTokenRight);


public :
	CString		m_strURL;		// _T("og:url")
	CString		m_strTitle;		// _T("og:title")
	CString		m_strTitleB64;
	CString		m_strDesc;		// _T("og:description")
	CString		m_strImage;		// _T("og:image")
	CString		m_strFavicon;	// url + favicon.ico
	CString		m_strFavicon2;	// find 'shortcut icon'


public :
	Image*		m_pRefImage;

#ifdef USING_FAVICON_IMAGE
	Image*		m_pRefFavicon;
#else
	HICON		m_pRefFavicon;
#endif
	


private:
	bool Load(_In_ CString &strURL, _Out_ CString &strMeta);
	void Update(_In_ CString &strMeta);
	bool DownLoad(CString strURL, CString strFullPath);


public :
	// strPath�� '\\'�� ���ϸ��� ������ ���� ��ġ
	bool DownloadImage(CString strPath, CSize szResize = CSize(0, 0));	
	bool DownloadFavicon(CString strPath);
	bool DownloadFavicon2(CString strPath);
};

