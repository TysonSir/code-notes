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

	//����ֵ��0ʧ�ܣ�1�ɹ�
	int HttpGet(const BaseString& strRequestUrl, const BaseString& strSaveTo);
	//����ֵ��0ʧ�ܣ�1�ɹ�
	int HttpPost(const BaseString& strRequestUrl, const PostData& postData, ResponseData& responseData = ResponseData());
	//����ֵ��0ʧ�ܣ�1�ɹ�
	int HttpDelete(const BaseString& strRequestUrl, const PostData& postData);
	//Post���ݵĲ�������Dome
	virtual PostData MakePostData(const BaseString& strData, const BaseString& strUsername = _T(""), const BaseString& strPassword = _T(""));
	
private:
	CHttpClient();
	bool Init();
	//user_p��һ���ļ�ָ�룬��������д���Ӧ�ļ���
	static size_t process_data_get_file(void *buffer, size_t size, size_t nmemb, void *user_p);
	//user_p��һ���ַ�������������д���ַ�����
	static size_t process_data_get_string(void *buffer, size_t size, size_t nmemb, string &content);
	//post�ύʱ����ȡ�ύ/�ϴ����ȣ����ݱ��浽m_progressInfo�У��԰ٷֱ�(100%)��ʽ
	static int progress_func(void* ptr, double TotalToDownload, double NowDownloaded,
		double TotalToUpload, double NowUploaded);//������	

	//��ַ�д����ģ���ʹ�ñ�����ת������ҳ��
	BOOL UrlEncode(const char* szSrc, char* pBuf, int cbBufLen, BOOL bUpperCase);

	static DWORD WINAPI MessageBoxThread(LPVOID lpParam);
	BaseString SubGuidByPath(BaseString& strLocalProj);
public:
	static ProgressInfo m_progressInfo;//���� 100 %
private:
	static CHttpClient *m_instance;
	static bool m_stopCurl;
};

