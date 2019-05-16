#include "StringFormat.h"
#include <windows.h>



string CStringFormat::U2A(const wstring& str)//Unicode字符转Ascii字符
{
	string strDes;
	if (str.empty())
		goto __end;
	int nLen = ::WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.size(), NULL, 0, NULL, NULL);
	if (0 == nLen)
		goto __end;
	char* pBuffer = new char[nLen + 1];
	memset(pBuffer, 0, nLen + 1);
	::WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.size(), pBuffer, nLen, NULL, NULL);
	pBuffer[nLen] = '\0';
	strDes.append(pBuffer);
	delete[] pBuffer;
__end:
	return strDes;
}

wstring CStringFormat::A2U(const string& str)//Ascii字符转
{
	wstring strDes;
	if (str.empty())
		goto __end;
	int nLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	if (0 == nLen)
		goto __end;
	wchar_t* pBuffer = new wchar_t[nLen + 1];
	memset(pBuffer, 0, nLen + 1);
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), pBuffer, nLen);
	pBuffer[nLen] = '\0';
	strDes.append(pBuffer);
	delete[] pBuffer;
__end:
	return strDes;
}


wstring CStringFormat::Utf2U(const string &str)//utf8转Unicode
{
	int u16Len = ::MultiByteToWideChar(CP_UTF8, NULL, str.c_str(), (int)str.size(), NULL, 0);
	wchar_t* wstrBuf = new wchar_t[u16Len + 1];
	::MultiByteToWideChar(CP_UTF8, NULL, str.c_str(), (int)str.size(), wstrBuf, u16Len);
	wstrBuf[u16Len] = L'\0';
	wstring wStr;
	wStr.assign(wstrBuf, u16Len);
	delete[] wstrBuf;
	return wStr;
}

string CStringFormat::U2Utf(const wstring& wstrUnicode)//Unicode转utf8  
{
	string strRet;
	if (wstrUnicode.empty())
		return strRet;
	int nLen = WideCharToMultiByte(CP_UTF8, 0, wstrUnicode.c_str(), -1, NULL, 0, NULL, NULL);
	char* pBuffer = new char[nLen + 1];
	pBuffer[nLen] = '\0';
	nLen = WideCharToMultiByte(CP_UTF8, 0, wstrUnicode.c_str(), -1, pBuffer, nLen, NULL, NULL);
	strRet.append(pBuffer);
	delete[] pBuffer;
	return strRet;
}

char* CStringFormat::U2G(const char* utf8) //UTF-8到GB2312的转换
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
}

char* CStringFormat::G2U(const char* gb2312) //GB2312到UTF-8的转换
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
}

BaseString CStringFormat::Encode(const BaseString& strPlaintext, const vector<int> vecKey)
{
	BaseString strPText = strPlaintext;
	int len = strPText.size();
	int nKeyLen = vecKey.size();
	for (int i = 0; i < len; i++)
	{
		strPText[i] = strPText[i] ^ vecKey[i % nKeyLen];
	}
	return strPText;
}

BaseString CStringFormat::Decode(const BaseString& strCiphertext, const vector<int> vecKey)
{
	BaseString strCText = strCiphertext;
	int len = strCText.size();
	int nKeyLen = vecKey.size();

	for (int i = 0; i < len; i++)
	{
		strCText[i] = strCText[i] ^ vecKey[i % nKeyLen];
	}
	return strCText;
}

#ifdef _AFXDLL 
CStringA CStringFormat::CStrW2CStrA(const CStringW &cstrSrcW)
{
	int len = WideCharToMultiByte(CP_ACP, 0, LPCTSTR(cstrSrcW), -1, NULL, 0, NULL, NULL);
	char *str = new char[len];
	memset(str, 0, len * sizeof(char));
	WideCharToMultiByte(CP_ACP, 0, LPCWSTR(cstrSrcW), -1, str, len, NULL, NULL);
	CStringA cstrDestA = str;
	delete str;
	return cstrDestA;
}

CStringW CStringFormat::CStrA2CStrW(const CStringA &cstrSrcA)
{
	int len = MultiByteToWideChar(CP_ACP, 0, LPCSTR(cstrSrcA), -1, NULL, 0);
	wchar_t *wstr = new wchar_t[len];
	memset(wstr, 0, len * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, LPCSTR(cstrSrcA), -1, wstr, len);
	CStringW cstrDestW = wstr;
	delete wstr;
	return cstrDestW;
}
#else
#endif
