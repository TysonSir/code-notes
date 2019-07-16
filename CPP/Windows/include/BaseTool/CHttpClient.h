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

typedef struct ResponseData
{
	long nRetCode;
	map<BaseString, BaseString> mapHeaders;
	map<BaseString, BaseString> mapContent;
} ResponseData;

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

	//返回值：0失败，1成功
	int HttpGet(const BaseString& strRequestUrl, const BaseString& strSaveTo);
	//返回值：0失败，1成功
	int HttpPost(const BaseString& strRequestUrl, const PostData& postData, ResponseData& responseData = ResponseData());
	//返回值：0失败，1成功
	int HttpDelete(const BaseString& strRequestUrl, const PostData& postData);
	//Post数据的参数制作Dome
	virtual PostData MakePostData(const BaseString& strData, const BaseString& strUsername = _T(""), const BaseString& strPassword = _T(""));
	
private:
	CHttpClient();
	bool Init();
	//user_p是一个文件指针，所有数据写入对应文件中
	static size_t process_data_get_file(void *buffer, size_t size, size_t nmemb, void *user_p);
	//user_p是一个字符串，所有数据写入字符串中
	static size_t process_data_get_string(void *buffer, size_t size, size_t nmemb, string &content);
	//post提交时，获取提交/上传进度，数据保存到m_progressInfo中，以百分比(100%)形式
	static int progress_func(void* ptr, double TotalToDownload, double NowDownloaded,
		double TotalToUpload, double NowUploaded);//进度条	

	//网址中带中文，可使用本函数转换成网页码
	BOOL UrlEncode(const char* szSrc, char* pBuf, int cbBufLen, BOOL bUpperCase);

	static DWORD WINAPI MessageBoxThread(LPVOID lpParam);
	BaseString SubGuidByPath(BaseString& strLocalProj);
public:
	static ProgressInfo m_progressInfo;//进度 100 %
private:
	static CHttpClient *m_instance;
	static bool m_stopCurl;
};

