#pragma once


#define HPD_MAX_METALENGTH		10240		// 10k		URL로부터 읽어들이 최대 버퍼크기, 이범위 안에서 메타데이터 체크
#define HPD_MAX_CONTENTLENGTH	1024000		// 1mb		해당 크기가 메타데이터를 읽지 않고 실패처리함
#define HPD_MAX_FILELENGTH		10240000	// 10mb		다운로드 할 이미지, 파비콘의 최대 크기, 읽는도중 넘어서면 실패처리함
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
	// 지정된 문자열의 meta property를 찾아서 content 값을 반환
	static CString GetProperty(_In_ CString &strSrc, _In_ int iBegin, _In_ CString strProperty);

	// str에서 strTokenLeft-strTokenRight 사이값을 찾아서 반환
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
	// strPath는 '\\'와 파일명을 제외한 폴더 위치
	bool DownloadImage(CString strPath, CSize szResize = CSize(0, 0));	
	bool DownloadFavicon(CString strPath);
	bool DownloadFavicon2(CString strPath);
};

