#pragma once
#include "StringDef.h"
#include "HttpTool\curl\curl.h"
#include <map>
#define  BASELOG_INFO(strFormat, ...)   (_T(__FILE__),__LINE__, _T(__FUNCTION__), strFormat,## __VA_ARGS__)
using namespace std;

typedef struct PostData
{
	map<BaseString, BaseString> mapHeaders;
	map<BaseString, BaseString> mapParams;
	map<BaseString, BaseString> mapFiles;
	map<BaseString, BaseString> mapJson;
} PostData;

typedef struct ProgressInfo
{
	int nDownloadRate;
	int nUploadRate;
} ProgressInfo;

class __declspec(dllexport) CHttpClient
{
public:
	~CHttpClient();

	static CHttpClient *GetInstance();
	static void DestroyInstance();

	int HttpGet(const BaseString& strRequestUrl, const BaseString& strSaveTo);
	int HttpPost(const BaseString& strRequestUrl, const PostData& postData);
	virtual PostData MakePostData(const BaseString& strData, const BaseString& strUsername = _T(""), const BaseString& strPassword = _T(""));
	
private:
	CHttpClient();
	bool Init();
	static size_t process_data_get(void *buffer, size_t size, size_t nmemb, void *user_p);
	static int progress_func(void* ptr, double TotalToDownload, double NowDownloaded,
		double TotalToUpload, double NowUploaded);//进度条

	static DWORD WINAPI MessageBoxThread(LPVOID lpParam);
	BOOL UrlEncode(const char* szSrc, char* pBuf, int cbBufLen, BOOL bUpperCase);
	BaseString SubGuidByPath(BaseString& strLocalProj);
public:
	static ProgressInfo m_progressInfo;//进度 100 %
private:
	static CHttpClient *m_instance;
	static bool m_stopCurl;
};

