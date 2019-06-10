#include "HttpTool\CHttpClient.h"
#include "StringFormat.h"
//#include "CWriteLog.h"
#include <sstream>
#include <algorithm>
//#include "CBaseRegEdit.h"
#include <windows.h>
using namespace std;

CHttpClient* CHttpClient::m_instance = NULL;
bool CHttpClient::m_stopCurl = false;
ProgressInfo CHttpClient::m_progressInfo = { -1,-1 };


CHttpClient::CHttpClient()
{
}


CHttpClient::~CHttpClient()
{
}


CHttpClient* CHttpClient::GetInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new CHttpClient();
		m_instance->Init();
	}

	return m_instance;
}

void CHttpClient::DestroyInstance()
{
	if (m_instance != NULL)
	{
		m_stopCurl = true;

		curl_global_cleanup();// will crash on Qt windows

		delete m_instance;
		m_instance = NULL;
	}
}


int CHttpClient::HttpGet(const BaseString& strRequestUrl, const BaseString& strSaveTo)
{
	// ��ȡeasy handle
	CURL *easy_handle = curl_easy_init();
	if (NULL == easy_handle)
	{
		//cerr << "get a easy handle failed." << endl;
		curl_global_cleanup();
		return 0;
	}

	FILE *fp = NULL;
#ifdef UNICODE
	fopen_s(&fp, CStringFormat::U2A(strSaveTo).c_str(), "ab+");
	const char* szSrc = CStringFormat::U2A(strRequestUrl).c_str();	
#else
	fopen_s(&fp, strSaveTo.c_str(), "ab+");
	const char* szSrc = strRequestUrl.c_str();
#endif	
	const int BUF_SIZE = 10240;
	char* pBuf = new char[BUF_SIZE];
	UrlEncode(szSrc, pBuf, BUF_SIZE, true);
	// ����easy handle����
	curl_easy_setopt(easy_handle, CURLOPT_URL, pBuf);//�������ص�ַ

	// ����easy handle����
	curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, &process_data_get);
	curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(easy_handle, CURLOPT_NOPROGRESS, FALSE);
	curl_easy_setopt(easy_handle, CURLOPT_PROGRESSFUNCTION, progress_func);

	// ִ����������
	int ret = 0;
	int i = 1;
	CURLcode res;
	while (i <= 3)
	{	
		if (CURLE_OK != (res = curl_easy_perform(easy_handle)))
		{
			BASELOG_INFO(_T("HttpGet: curl_easy_perform() failed: %s"), curl_easy_strerror(res));
			BASELOG_INFO(_T("�� %d/3 �� �ļ���ʧ�ܣ����ڼ���..."), i);
			i++;
			ret = 0;
		//	DWORD threadID;
		//	HANDLE hThread;
		//	hThread = CreateThread(NULL, 0, MessageBoxThread, &BaseString(_T("�����жϣ��ļ���ʧ�ܣ��������´�...")), 0, &threadID);	// �����߳���ʾ��
		}
		else
		{
			BASELOG_INFO(_T("HttpGet: curl_easy_perform() OK"));
			BASELOG_INFO(_T("�� %d/3 �� �ļ��򿪳ɹ���"), i);
			ret = 1;
			break;//���سɹ��˳�ѭ������������
		}
		Sleep(500);
	}
	// �ͷ���Դ
	fclose(fp);
	curl_easy_cleanup(easy_handle);
	delete[] pBuf;
	return ret;
}

int CHttpClient::HttpPost(const BaseString& strRequestUrl, const PostData& postData)
{
	CURL *curl;
	CURLcode res;
	int ret = 0;

	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	struct curl_slist *headerlist = NULL;
	static const char buf[] = "Referer: ";

	//curl_global_init(CURL_GLOBAL_ALL);

	/* Fill in the file upload field */
	
	///////////////////////��ͨ���� ��ʼ////////////////////////////////////////
	string strName, strContents;
	for (auto it = postData.mapParams.begin();it != postData.mapParams.end();it++)
	{
#ifdef UNICODE
		strName = CStringFormat::U2A(it->first);
		strContents = CStringFormat::U2A(it->second);
#else
		strName = it->first;
		strContents = it->second;
#endif
		/* ���post���� */
		/* Fill in the filename field */
		curl_formadd(&formpost,
			&lastptr,
			CURLFORM_COPYNAME, strName.c_str(),
			CURLFORM_COPYCONTENTS, strContents.c_str(),
			CURLFORM_END);
	}
	///////////////////////��ͨ���� ����////////////////////////////////////////
	///////////////////////�ļ����� ��ʼ////////////////////////////////////////
	string strCopyName, strFile;
	for (auto it = postData.mapFiles.begin();it != postData.mapFiles.end();it++)
	{
#ifdef UNICODE
		strCopyName = CStringFormat::U2A(it->first);
		strFile = CStringFormat::U2A(it->second);
#else
		strCopyName = it->first;
		strFile = it->second;
#endif
		curl_formadd(&formpost,
			&lastptr,
			CURLFORM_COPYNAME, strCopyName.c_str(),
			CURLFORM_FILE, strFile.c_str(),
			CURLFORM_END);
	}
	///////////////////////�ļ����� ����////////////////////////////////////////

	/* Fill in the submit field too, even if this is rarely needed */
	//curl_formadd(&formpost,
	//	&lastptr,
	//	CURLFORM_COPYNAME, "submit",
	//	CURLFORM_COPYCONTENTS, "Submit",
	//	CURLFORM_END);

	curl = curl_easy_init();//��������֤�Ƿ�init�ɹ�

	/* initalize custom header list (stating that Expect: 100-continue is not wanted */
	//////////////////////////��Ϣͷ ��ʼ/////////////////////////////////////////
	string strKey, strValue, strAll;
	for (auto it = postData.mapHeaders.begin();it != postData.mapHeaders.end();it++)
	{
#ifdef UNICODE
		strKey = CStringFormat::U2A(it->first);
		strValue = CStringFormat::U2A(it->second);
#else
		strKey = it->first;
		strValue = it->second;
#endif
		strAll = strKey + ": " + strValue;
		headerlist = curl_slist_append(headerlist, strAll.c_str());
	}
	//headerlist = curl_slist_append(headerlist, buf2);//����Զ���header
	//////////////////////////��Ϣͷ ����/////////////////////////////////////////

	if (curl) {
		/* what URL that receives this POST */
		string ascii_strRequestUrl;
#ifdef UNICODE
		ascii_strRequestUrl = CStringFormat::U2A(strRequestUrl);
#else
		ascii_strRequestUrl = strRequestUrl;
#endif
		curl_easy_setopt(curl, CURLOPT_URL, ascii_strRequestUrl.c_str());
		//if ((argc == 2) && (!strcmp(argv[1], "noexpectheader")))/* only disable 100-continue header if explicitly requested */			
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);//��������ͷ
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);//����post����
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
		curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_func);

		// ����ҪPOST��JSON����
		if(!postData.mapJson.empty())
		{ 
			BaseString jsonData = postData.mapJson.begin()->second;
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, CStringFormat::G2U(CStringFormat::U2A(jsonData).c_str()));
			//curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonData.size());//�����ϴ�json������,������ò���д���������ݳ�����Ӱ�죬���·��Ͱ���ȫ
		}
#ifdef _TEST_
		//�����������������-������
		FILE *fp = NULL;
		BaseString strSaveTo = _T("HttpTool_POST_Response.html");
#ifdef UNICODE
		fopen_s(&fp, CStringFormat::U2A(strSaveTo).c_str(), "ab+");
		const char* szSrc = CStringFormat::U2A(strRequestUrl).c_str();
#else
		fopen_s(&fp, strSaveTo.c_str(), "ab+");
		const char* szSrc = strRequestUrl.c_str();
#endif	
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &process_data_get);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
#endif

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		
		int i = 1;
		while (i <= 3)
		{		
			if (res != CURLE_OK) 
			{
				ret = 0;
				//fprintf(stderr, "curl_easy_perform() failed: %s\n",	curl_easy_strerror(res));
				BASELOG_INFO(_T("HttpPost: curl_easy_perform() failed: %s"), curl_easy_strerror(res));
				BASELOG_INFO(_T("�� %d/3 �� �ļ�����ʧ�ܣ��������±���..."), i);
				i++;
				res = curl_easy_perform(curl);//���´���
				//DWORD threadID;
				//HANDLE hThread;
				//hThread = CreateThread(NULL, 0, MessageBoxThread, &BaseString(_T("�����жϣ��ļ�����ʧ�ܣ��������±���...")), 0, &threadID);	// �����߳���ʾ��
			}
			else
			{
				BASELOG_INFO(_T("HttpPost: curl_easy_perform() OK"));
				BASELOG_INFO(_T("�� %d/3 �� �ļ�����ɹ���"), i);
				ret = 1;
				break;
			}
			Sleep(500);
		}
		/* always cleanup */
		curl_easy_cleanup(curl);

		/* then cleanup the formpost chain */
		curl_formfree(formpost);
		/* free slist */
		curl_slist_free_all(headerlist);
	}
	else
	{
		return 0;
	}
	return ret;
}

PostData CHttpClient::MakePostData(const BaseString& strData, const BaseString& strUsername, const BaseString& strPassword)
{
	PostData postData;
	//������������

	//����ͷ
	postData.mapHeaders[_T("Host")] = _T("im-test-2.lubansoft.net:8899");
	postData.mapHeaders[_T("Connection")] = _T("keep-alive");
	postData.mapHeaders[_T("Content-Length")] = TO_STRING(strData.length());
	postData.mapHeaders[_T("Accept")] = _T("application/json, text/plain, */*");
	postData.mapHeaders[_T("Origin")] = _T("http://im-test-2.lubansoft.net:8899");
	postData.mapHeaders[_T("User-Agnet")] = _T("Mozilla/5.0 (Windows NT 6.2; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.76 Safari/537.36");
	postData.mapHeaders[_T("Content-Type")] = _T("application/json");
	postData.mapHeaders[_T("Referer")] = _T("http://im-test-2.lubansoft.net:8899/LBIM/resource/index.html");
	postData.mapHeaders[_T("Accept-Encoding")] = _T("gzip, deflate");
	postData.mapHeaders[_T("Accept-Language")] = _T("en-US,en;q=0.8");
	postData.mapHeaders[_T("Cookie")] = _T("JSESSIONID=0CB39CE6D265276CB16C8E1AC61A587F");

	//����Json����
	postData.mapJson[_T("jsonData")] = strData;

	//<input type="file" />
	//postData.mapFiles[_T("file")] = strData; //strData Ϊ�ļ�·��

	//<input type="text" />
	//postData.mapParams[_T("password")] = strPassword;

	return postData;
}

bool CHttpClient::Init()
{
	if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK)
	{
		//cerr << "init libcurl failed." << endl;
		return false;
	}	

	return true;
}

size_t CHttpClient::process_data_get(void *buffer, size_t size, size_t nmemb, void *user_p)
{
	FILE *fp = (FILE *)user_p;
	size_t return_size = fwrite(buffer, size, nmemb, fp);
	//cout << (char *)buffer << endl;
	return return_size;
	//return size_t();
}


int CHttpClient::progress_func(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
{
	int totaldotz = 100;
	double fractiondownloaded = NowDownloaded / TotalToDownload;
	double fractionuploaded = NowUploaded / TotalToUpload;

	m_progressInfo.nDownloadRate = round(fractiondownloaded * totaldotz);//round��������,�ٷֱ�
	m_progressInfo.nUploadRate = round(fractionuploaded * totaldotz);//round��������,�ٷֱ�

//#ifdef UNICODE
//	wostringstream os; //����һ������ַ�������������Ϊ�� 
//#else
//	ostringstream os; //����һ������ַ�������������Ϊ�� 
//#endif
//	
	//os << m_progressInfo.nUploadRate; //������ַ����������int����i������ 
	//BaseString strLog = _T("�ϴ����ȣ�") + BaseString(os.str().c_str());
	////MessageBox(NULL, os.str().c_str(), _T("�ϴ�����ChttpClient"), NULL);
	//BASELOG_INFO_S(strLog);
	return 0;
}

DWORD WINAPI CHttpClient::MessageBoxThread(LPVOID lpParam)
{
	BaseString* strMessage = (BaseString*)lpParam;
	MessageBox(NULL, strMessage->c_str(),_T("����"),MB_OK);
	return 0;
}

BOOL CHttpClient::UrlEncode(const char* szSrc, char* pBuf, int cbBufLen, BOOL bUpperCase)
{
	if (szSrc == NULL || pBuf == NULL || cbBufLen <= 0)
		return FALSE;

	size_t len_ascii = strlen(szSrc);
	if (len_ascii == 0)
	{
		pBuf[0] = 0;
		return TRUE;
	}

	//��ת����UTF-8
	char baseChar = bUpperCase ? 'A' : 'a';
	int cchWideChar = MultiByteToWideChar(CP_ACP, 0, szSrc, len_ascii, NULL, 0);
	LPWSTR pUnicode = (LPWSTR)malloc((cchWideChar + 1) * sizeof(WCHAR));
	if (pUnicode == NULL)
		return FALSE;
	MultiByteToWideChar(CP_ACP, 0, szSrc, len_ascii, pUnicode, cchWideChar + 1);

	int cbUTF8 = WideCharToMultiByte(CP_UTF8, 0, pUnicode, cchWideChar, NULL, 0, NULL, NULL);
	LPSTR pUTF8 = (LPSTR)malloc((cbUTF8 + 1) * sizeof(CHAR));
	if (pUTF8 == NULL)
	{
		free(pUnicode);
		return FALSE;
	}
	WideCharToMultiByte(CP_UTF8, 0, pUnicode, cchWideChar, pUTF8, cbUTF8 + 1, NULL, NULL);
	pUTF8[cbUTF8] = '\0';

	unsigned char c;
	int cbDest = 0; //�ۼ�
	unsigned char *pSrc = (unsigned char*)pUTF8;
	unsigned char *pDest = (unsigned char*)pBuf;
	while (*pSrc && cbDest < cbBufLen - 1)
	{
		c = *pSrc;
		if (isalpha(c) || isdigit(c) || c == '-' || c == '.' || c == '~' || c == ':' || c == '/')
		{
			*pDest = c;
			++pDest;
			++cbDest;
		}
		else if (c == ' ')
		{
			*pDest = '+';
			++pDest;
			++cbDest;
		}
		else
		{
			//��黺������С�Ƿ��ã�
			if (cbDest + 3 > cbBufLen - 1)
				break;
			pDest[0] = '%';
			pDest[1] = (c >= 0xA0) ? ((c >> 4) - 10 + baseChar) : ((c >> 4) + '0');
			pDest[2] = ((c & 0xF) >= 0xA) ? ((c & 0xF) - 10 + baseChar) : ((c & 0xF) + '0');
			pDest += 3;
			cbDest += 3;
		}
		++pSrc;
	}
	//null-terminator
	*pDest = '\0';
	free(pUnicode);
	free(pUTF8);
	return TRUE;
}

BaseString CHttpClient::SubGuidByPath(BaseString& strLocalProj)
{
	int nGuidLen = BaseString(_T("8625B768-1D2D-48C0-8087-9B1236EEEACE")).length();
	BaseString strFlag = _T("LFSJ.");
	//BaseString strLocalProjUpper;
	::transform(strLocalProj.begin(), strLocalProj.end(), strLocalProj.begin(), ::toupper);

	int nPos = strLocalProj.rfind(strFlag);

	BaseString strGuid = strLocalProj.substr(nPos + strFlag.length(), nGuidLen);

	return strGuid;
}
