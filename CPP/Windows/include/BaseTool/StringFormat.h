#pragma once
#include <string>
#include <vector>
#include "StringDef.h"
#include <sstream>

/************************************************************************/
/*  ACCESS相关                                                    */          
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
	static string U2A(const wstring& str);//Unicode字符转Ascii字符
	static wstring A2U(const string& str);//Ascii字符转Unicode字符
	static wstring Utf2U(const string &str);//utf8转Unicode
	static string U2Utf(const wstring& wstrUnicode);//Unicode转utf8 

	//无论是GB2312到UTF-8的转换，还是UTF-8到GB2312的转换，都需要注意的是在使用字符串后，需要删除字符串指针；
	static char* U2G(const char* utf8);//UTF-8到GB2312的转换
	static char* G2U(const char* gb2312);//GB2312到UTF-8的转换

	static BaseString Encode(const BaseString& strPlaintext, const vector<int> vecKey);//异或加密
	static BaseString Decode(const BaseString& strCiphertext, const vector<int> vecKey);//异或解密

#ifdef _AFXDLL 
	static CStringA CStrW2CStrA(const CStringW &cstrSrcW);//MFC-CString Unicode 转 Ascii
	static CStringW CStrA2CStrW(const CStringA &cstrSrcA);//MFC-CString Ascii 转 Unicode												  //MFC dll
#else
														  //static
#endif
};

