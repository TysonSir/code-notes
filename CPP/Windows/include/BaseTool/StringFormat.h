#pragma once
#include <string>
#include <vector>
#include "StringDef.h"
#include <sstream>

/************************************************************************/
/*  ACCESS���                                                    */          
/* http://www.360doc.com/content/15/0405/20/14832860_460858669.shtml    */
/************************************************************************/

#ifdef UNICODE
#define ACCESS _waccess
#define COUT std::wcout
typedef std::wifstream IFileStream;
typedef std::wofstream OFileStream;
typedef std::wistringstream IStrStream;
typedef std::wostringstream OStrStream;
#else
#define ACCESS _access
#define COUT std::cout
typedef std::ifstream IFileStream;
typedef std::ofstream OFileStream;
typedef std::istringstream IStrStream;
typedef std::ostringstream OStrStream;
#endif

using namespace std;
class CStringFormat
{
public:
	static string U2A(const wstring& str);//Unicode�ַ�תAscii�ַ�
	static wstring A2U(const string& str);//Ascii�ַ�תUnicode�ַ�
	static wstring Utf2U(const string &str);//utf8תUnicode
	static string U2Utf(const wstring& wstrUnicode);//Unicodeתutf8 

	//������GB2312��UTF-8��ת��������UTF-8��GB2312��ת��������Ҫע�������ʹ���ַ�������Ҫɾ���ַ���ָ�룻
	static char* U2G(const char* utf8);//UTF-8��GB2312��ת��
	static char* G2U(const char* gb2312);//GB2312��UTF-8��ת��

	static BaseString Encode(const BaseString& strPlaintext, const vector<int> vecKey);//������
	static BaseString Decode(const BaseString& strCiphertext, const vector<int> vecKey);//������

#ifdef _AFXDLL 
	static CStringA CStrW2CStrA(const CStringW &cstrSrcW);//MFC-CString Unicode ת Ascii
	static CStringW CStrA2CStrW(const CStringA &cstrSrcA);//MFC-CString Ascii ת Unicode												  //MFC dll
#else
														  //static
#endif
};

